//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is based on Komei Fukuda's ccd implementation and as such supplied under the GPL license agreement (see license.txt)

#include "Tableau.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

namespace abstract{

template <class scalar>  MatToStr<scalar> Tableau<scalar>::ms_logger(true);
template <class scalar>  MatToStr<scalar> Tableau<scalar>::ms_decoder(false);
template <class scalar>  traceTableau_t Tableau<scalar>::ms_trace_tableau=eTraceNoTableau;
template <class scalar>  tracePivots_t Tableau<scalar>::ms_trace_pivots=eTraceNoPivots;
template <class scalar>  bool Tableau<scalar>::ms_trace_errors=false;
template <class scalar>  bool Tableau<scalar>::ms_trace_time=false;
template <class scalar>  bool Tableau<scalar>::ms_useBasis=false;

template <class scalar>
Tableau<scalar>::Tableau(const int size,const int dimension):
  m_dimension(dimension+1),
  m_size(size),
  m_zero(func::ms_weakZero),
  m_objectiveRow(0),
  m_evidenceRow(-1),
  m_evidenceCol(-1),
  Conversion(IneToExt),
  m_faces(0,dimension),
  m_supports(0,1),
  m_tableau(m_size,m_dimension),
  m_sparseTableau(0,m_dimension),
  m_pSortedTableau(&m_tableau),
  m_auxiliaryRow(1,m_dimension),
  m_basisInverse(m_dimension,m_dimension)
{
  m_basicVars.reserve(size+1);
  m_nonBasicRow.reserve(m_dimension);
}
	
template <class scalar>
Tableau<scalar>::~Tableau()
{
}

template <class scalar>
void Tableau<scalar>::Normalize(MatrixS &vector)
{
  refScalar temp;
  refScalar max = 0;
  for (int j = 0; j < m_dimension; j++) {
    temp = func::toUpper(abs(vector.coeff(0,j)));
    if (temp > max) max = temp;
  }
  vector /= max;
}


template <class scalar>
void Tableau<scalar>::ZeroIndexSet(const MatrixS &vector, Set &ZeroSet)
{
  scalar temp;
  ZeroSet.clear();
  for (int i = 0; i < m_size; i++) {
    temp = m_pSortedTableau->entry(vector, i);
    if (func::isNearZero(temp,m_zero)) ZeroSet.add(i);
  }
}

template <class scalar>
bool Tableau<scalar>::SelectPivot(const long rowmax, const Set &noPivotRow, const Set &noPivotCol, pivot_t &pivot)
/* Select a position (pivot) in the matrix X.T such that (X.T)[pivot.row][pivot.col] is nonzero
   The choice is feasible, i.e., not on NopivotRow and NopivotCol, and
   best with respect to the specified roworder 
 */
{
  long rtemp;
  Set rowexcluded(noPivotRow);
  scalar Xtemp;

  for (rtemp=rowmax;rtemp<m_size;rtemp++) {
    rowexcluded.add(rtemp);   /* cannot pivot on any row > rmax */
  }
  while(true) {
    pivot_t bk_pivot;
    bk_pivot.row=-1;
    bk_pivot.col=-1;
    rtemp=-1;
    for (int i=1;i<=m_size;i++) {
      if (!rowexcluded.member(m_pSortedTableau->zeroOrder(i))){
        rtemp=m_pSortedTableau->zeroOrder(i);
        break;
      }
    }
    if (rtemp>=0) {
      pivot.row=rtemp;
      for (pivot.col=0;pivot.col < m_dimension;pivot.col++) {
        if (!noPivotCol.member(pivot.col)) {
          Xtemp=m_pSortedTableau->entry(m_basisInverse,pivot.row,pivot.col);
          char sign=func::softSign(Xtemp);//hardSign(Xtemp);//Zero is ensured by check in entry
          if (sign!=0) return true;
          if (bk_pivot.row<0) {
            sign=func::hardSign(Xtemp);
            if (sign!=0) bk_pivot=pivot;
          }
        }
      }
      rowexcluded.add(rtemp);
    }
    else if (bk_pivot.row>=0) {
      ms_logger.logData("bk_pivot");
      pivot=bk_pivot;
      return true;
    }
    else {
      pivot.row = -1;
      pivot.col = -1;
      return false;
    }
  }
  return true;
}

template <class scalar>
void Tableau<scalar>::ColumnPivot(const pivot_t &pivot)
/* Update the Transformation matrix T with the pivot operation on (row,col)
   This procedure performs a implicit pivot operation on the tableau by
   updating the dual basis inverse.
 */
{
  scalar Xtemp;
  if (m_pSortedTableau->m_dirty) {
    m_pSortedTableau->pivot(m_auxiliaryRow,pivot);
    if (ms_trace_pivots>=eTracePivots) logBasis(pivot.row,pivot.col);
    return;
  }
  refScalar invXtemp0 = func::toCentre(func::ms_1/m_pSortedTableau->entry(m_basisInverse,pivot.row,pivot.col));
  for (int j = 0; j < m_dimension; j++) {
    if (j != pivot.col) {
      Xtemp = m_pSortedTableau->entry(m_basisInverse,pivot.row,j)*invXtemp0;
      for (int j1 = 0; j1 < m_dimension; j1++) {
        func::msub(m_basisInverse.coeffRef(j1,j),m_basisInverse.coeff(j1,pivot.col),Xtemp);
      }
    }
  }
  m_basisInverse.col(pivot.col)*=invXtemp0;
  if (ms_trace_pivots>=eTracePivots) logBasis(pivot.row,pivot.col);
}

template <class scalar>
void Tableau<scalar>::logBasis(int row,int col)
{
  if (ms_trace_pivots>=eTracePivots) {
    std::stringstream buffer;
    buffer << "[" << row << "," << col;
    if (m_nonBasicRow[col]>=0) buffer << "(" << m_nonBasicRow[col] << ")";
    buffer << "]";
    if (ms_trace_pivots>=eTraceBasis) {
      ms_logger.logData(m_basisInverse,buffer.str());
    }
    else if (ms_trace_pivots>=eTraceSimplex){
      MatrixS matrix=m_basisInverse.col(0).transpose();
      ms_logger.logData(matrix,buffer.str());
    }
    else {
      ms_logger.logData(buffer.str(),false);
    }
    if (ms_trace_pivots>=eTraceEntries) {
      int rows=m_pSortedTableau->numRows();
      MatrixS matrix(rows,m_dimension);
      for (int row=0;row<rows;row++) {
        for (int col=0;col<m_dimension;col++) {
          matrix.coeffRef(row,col)=m_pSortedTableau->entry(m_basisInverse,row,col);
        }
      }
      ms_logger.logData(matrix,"Entries");
    }
  }
}

/// Indicates if the tableau is empty
template <class scalar>
bool Tableau<scalar>::isEmpty() const
{
  if (m_faces.rows()<=0) return true;
  if (m_faces.cols()<=0) return true;
  return (m_size == ((Conversion!=ExtToIne) ? 1 : 0));
}

template <class scalar>
void Tableau<scalar>::logTableau(const std::string parameters,bool force)
{
  if ((ms_trace_tableau>=eTraceTableau) || force) {
    if (parameters.length()>0) {
      std::stringstream stream;
      stream << getName();
      stream << ": " << parameters;
      ms_logger.logData(m_faces,m_supports,stream.str());
    }
    else ms_logger.logData(m_faces,m_supports,getName());
  }
}

template <class scalar>
void Tableau<scalar>::logBasic()
{
  ms_logger.logData(m_basicVars,"Basic: ");
}

template <class scalar>
void Tableau<scalar>::logNonBasic()
{
    ms_logger.logData(m_nonBasicRow,"NonBasic: ");
}

template <class scalar>
bool Tableau<scalar>::ColumnPivotAndUpdate(const pivot_t &pivot)
{
  ColumnPivot(pivot);
  m_lastPivot.row=m_nonBasicRow[pivot.col]; // entering variable
  m_lastPivot.col=pivot.col;                // entering column
  m_basicVars[pivot.row]=pivot.col;         // the nonbasic variable r corresponds to column s
  m_nonBasicRow[pivot.col]=pivot.row;       // the nonbasic variable on s column is r
  if (m_lastPivot.row>=0) {
    m_basicVars[m_lastPivot.row]=-1;        // original variables have negative index and should not affect the row index
  }
  return true;
}

template <class scalar>
int Tableau<scalar>::FindEnumerationBasis(Set& rowSelected,std::vector<int> &pivotRows)
{
  Set colSelected(m_dimension);
  pivot_t pivot;

  pivotRows.assign(m_dimension+1,0);
  rowSelected.clear();
  m_basisInverse=MatrixS::Identity(m_dimension,m_dimension);
  for (int i=0;i<m_dimension;i++) {   // Find a set of rows for a basis
    if (!SelectPivot(m_size, rowSelected, colSelected, pivot)) {
      return i;
    }
    rowSelected.add(pivot.row);
    colSelected.add(pivot.col);
    pivotRows[pivot.col+1]=pivot.row+1;    // pivotRows[s] stores the corr. row index //TODO: zero index
    ColumnPivot(pivot);
  }
  return m_dimension;
}

template <class scalar>
int Tableau<scalar>::FindLPBasis()
{ /* Find a LP basis using Gaussian pivots.
     If the problem has an LP basis,
     the procedure returns m_evidenceCol=-1 if LPSundecided and an LP basis.
     If the constraint matrix A (excluding the rhs and objective) is not
     column indepent, there are two cases.  If the dependency gives a dual
     inconsistency, this returns the evidence column m_evidenceCol.  Otherwise, this returns an LP basis of size less than n_size.  Columns j
     that do not belong to the basis (i.e. cannot be chosen as pivot because
     they are all zero) will be indicated in nbindex vector: nbindex[j] will
     be negative and set to -j.
  */
  if (ms_trace_pivots>=eTracePivots) ms_logger.logData("Feasibility Basis");
  ResetTableau();
  Set RowSelected(m_size);
  Set ColSelected(m_dimension);
  RowSelected.add(m_objectiveRow);
  ColSelected.add(RHSCol);
  pivot_t pivot;
  int rank=m_dimension;
  m_evidenceCol=-1;
  for (int i=0;i<m_dimension;i++) {   /* Find a set of rows for a basis */
    if (!SelectPivot(m_size, RowSelected, ColSelected, pivot))
    {
      rank=i;
      for (int j=1;j<m_dimension; j++) {//Skip RHSCol
        if (m_nonBasicRow[j]<0){
          if (!func::isZero(m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,j),m_zero)) {  /* dual inconsistent */
            m_evidenceCol=j;
            break;
          }
        }
      }
      /* dependent columns but not dual inconsistent. */
      break;
    }
    if (ms_trace_pivots>=eTraceEntries) {
      RowSelected.logSet("Available Rows:",true);
      ColSelected.logSet("Available Cols:",true);
    }
    RowSelected.add(pivot.row);
    ColSelected.add(pivot.col);
    if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
      ms_logger.logData("LP Basis cycling error");
    }
  }
  return rank;
}

template <class scalar>
int Tableau<scalar>::FindFeasBasis(const ResetType_t resetType)
{
  m_rank=0;
  m_pSortedTableau->setCoeff(m_objectiveRow,RHSCol,0);
  if (resetType==eRebaseBasis) {
    int knownPivots=0;
    for (int i=0;i<m_nonBasicRow.size();i++) {
      if (m_nonBasicRow[i]<0) ms_logger.logData(i,"false Rebase",true);//TODO: remove
      else if (m_nonBasicRow[i]>=m_objectiveRow) ms_logger.logData("skewed Rebase");//TODO: remove
      else knownPivots++;
    }
    if (knownPivots==m_nonBasicRow.size()) return Rebase();
  }
  if ((resetType==eUseDefaultBasis) && ms_useBasis) {
    m_basisInverse=m_feasBasisInverse;
    m_basicVars=m_feasBasicVars;
    m_nonBasicRow=m_feasNonBasicRow;
    if (ms_trace_pivots>=eTracePivots) this->logBasis(-1,-1);
    return 0;
  }
  ComputeRowOrderVector(MinIndex);
  int result=FindLPBasis();//TODO: go to feasLP?
  m_feasBasisInverse=m_basisInverse;
  m_feasBasicVars=m_basicVars;
  m_feasNonBasicRow=m_nonBasicRow;
  return result;
}

/// Restarts the Simplex process at the current vertex
template <class scalar>
int Tableau<scalar>::Rebase()
{
  std::vector<int> pivots=m_nonBasicRow;
  //std::set<int> pending;
  if (pivots.size()<getDimension()) return 0;
  if (ms_trace_pivots>=eTracePivots) {
    if (ms_trace_pivots>=eTraceSimplex) {
      MatrixS point=m_basisInverse.col(0).transpose();
      ms_logger.logData(point,"Vertex");
    }
    ms_logger.logData(pivots,"Rebase ");
  }
  ResetTableau();
  Set noPivotCol(m_dimension);
  int rank=0;
  pivot_t pivot;
  scalar Xtemp;
  for (int i=0;i<pivots.size();i++) {
    pivot.row=pivots[i];
    if (pivot.row>0) {
      for (pivot.col=1;pivot.col < m_dimension;pivot.col++) {
        if (!noPivotCol.member(pivot.col)) {
          Xtemp=m_pSortedTableau->entry(m_basisInverse,pivot.row,pivot.col);
          char sign=func::softSign(Xtemp);
          if (sign!=0) break;
        }
      }
      if (pivot.col==m_dimension) {
        for (pivot.col=1;pivot.col < m_dimension;pivot.col++) {
          if (!noPivotCol.member(pivot.col)) continue;
          Xtemp=m_pSortedTableau->entry(m_basisInverse,pivot.row,pivot.col);
          char sign=func::softSign(Xtemp);
          if (sign!=0) {
            int row=m_nonBasicRow[pivot.col];
            for (int col=1;col < m_dimension;col++) {
              if (!noPivotCol.member(col)) {
                Xtemp=m_pSortedTableau->entry(m_basisInverse,pivot.row,col);
                if (func::softSign(Xtemp)!=0) {
                  if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
                    ms_logger.logData("Rebase cycling");//TODO: remove (change for approprite action)
                  }
                  rank++;
                  pivot.row=row;
                  pivot.col=col;
                  break;
                }
              }
            }
            if (pivot.row==row) break;
          }
        }
      }
      if (pivot.col==m_dimension) {//should never happen
        //pending.insert(pivot.row);
        continue;
      }
      noPivotCol.add(pivot.col);
      ColumnPivotAndUpdate(pivot);
      rank++;
    }
  }
  int dimension=getDimension();
  if (rank<dimension) {
    if (ms_trace_pivots>=eTracePivots) ms_logger.logData(rank,"rebase incomplete",true);
    Set RowSelected(m_size);
    RowSelected.add(m_objectiveRow);
    for (int i=0;i<pivots.size();i++) RowSelected.add(pivots[i]);
    noPivotCol.add(RHSCol);
    for (;rank<dimension;rank++) {   // Find a set of rows for a basis
      if (!SelectPivot(m_size, RowSelected, noPivotCol, pivot)) {
        func::imprecise(m_zero,m_zero,"Rebase error");
        break;
      }
      RowSelected.add(pivot.row);
      noPivotCol.add(pivot.col);
      ColumnPivotAndUpdate(pivot);
    }
  }
  if (ms_trace_pivots>=eTraceBasis) {
    MatrixS point=m_basisInverse.col(0).transpose();
    ms_logger.logData(point,"Vertex");
  }
  return rank;
}

template <class scalar>
void Tableau<scalar>::ResetTableau()
{
  m_nonBasicRow[0]=-1;
  for (int col=1; col<m_dimension; col++) m_nonBasicRow[col]=-col;
  m_lastPivot.row=-1;
  m_nonBasicRow[RHSCol]=0;/* RHS is already in nonbasis and is considered to be associated with the zero-th row of input. */
  m_basisInverse=MatrixS::Identity(m_dimension,m_dimension);
  if (ms_trace_pivots>=eTracePivots) ms_logger.logData("Reset Tableau");
  if (!ms_useBasis) m_pSortedTableau->m_dirty=!loadTableau(false)|| !ms_useBasis;

  /* Set the bflag according to nbindex */
  for (int row=0; row<=m_size; row++) m_basicVars[row]=-1; /* all basic variables have index -1 */
  m_basicVars[ m_objectiveRow]=0;                          /* bflag of the objective variable is 0, different from other basic variables which have -1 */
  for (int col=0; col<m_dimension; col++) {
    if (m_nonBasicRow[col]>0) m_basicVars[m_nonBasicRow[col]]=col; /* bflag of a nonbasic variable is its column number */
  }
}

template <class scalar>
void Tableau<scalar>::ComputeRowOrderVector(const OrderType &type)
{
  m_pSortedTableau->ComputeRowOrderVector(type);
}

template <class scalar>
bool Tableau<scalar>::load(const MatrixS &faces,const MatrixS &supports,const bool transpose)
{
  int numFaces=transpose ? faces.cols() : faces.rows();
  if (supports.rows()!=numFaces) return false;
  int objectiveVar=-1;
  if (m_size<m_basicVars.size()) {
    objectiveVar=m_basicVars[m_size];
    m_basicVars[m_size]=-1;
    m_basicVars[m_objectiveRow]=-1;
  }
  m_isNormalised=false;
  m_pSortedTableau->m_dirty=false;
  m_size =numFaces+ ((Conversion!=ExtToIne) ? 1 : 0);
  m_basicVars.resize(m_size+1,-1);
  m_basicVars[m_size]=objectiveVar;
  m_nonBasicRow.resize(m_dimension);
  if (m_basicVars[m_size]>=0) m_nonBasicRow[m_basicVars[m_size]]=m_size;
  m_objectiveRow=m_size-1;
  m_evidenceRow=-1;
  m_evidenceCol=-1;
  if (&faces!=&m_faces) {
    if (transpose) m_faces=faces.transpose();
    else           m_faces=faces;
  }
  if (&supports!=&m_supports) m_supports=supports;
  m_dimension=m_faces.cols()+1;
  if (m_faces.rows()>0) {
    refScalar max=func::toUpper(m_faces.coeff(0,0));
    refScalar min=func::toLower(m_faces.coeff(0,0));
    for (int row=0;row<m_faces.rows();row++) {
      for (int col=0;col<m_faces.cols();col++) {
        if (func::toUpper(m_faces.coeff(row,col))>max) max=func::toUpper(m_faces.coeff(row,col));
        if (func::toLower(m_faces.coeff(row,col))<min) min=func::toLower(m_faces.coeff(row,col));
      }
    }
    if (-min>max) max=-min;
    m_zero=max*func::ms_weakEpsilon;
  }
  else m_zero=0;
  m_pSortedTableau->setSize(m_size,m_dimension);
  return loadTableau(true);
}

/// Loads the tableau from the face and supprot description
template <class scalar>
bool Tableau<scalar>::loadTableau(bool clearObjective)
{
  if (m_pSortedTableau->numRows()!=m_size) return false;
  for (int row=0;row<m_faces.rows();row++) {
    m_pSortedTableau->setCoeff(row,0,m_supports.coeff(row,0));
    m_pSortedTableau->negRow(row,1,m_faces.row(row));
  }
  if (m_faces.rows()<m_size) {
    m_pSortedTableau->setCoeff(m_faces.rows(),0,func::ms_hardZero);
    if (clearObjective) m_pSortedTableau->setRow(m_faces.rows(),1,MatrixS::Zero(1,m_faces.cols())); //artificial row for x_1 >= 0
  }
  return true;
}

/// Relaxes the polyhedra to its outer boundaries (when using interval representations)
template <class scalar>
void Tableau<scalar>::toOuter(bool force)
{
  for (int i=0;i<m_supports.rows();i++) {
    m_pSortedTableau->setCoeff(i,RHSCol,func::toUpper(m_supports.coeff(i,0)));
    if (force) {
      for (int j=0;j<m_supports.cols();j++) {
        m_supports.coeffRef(i,j)=func::toUpper(m_supports.coeff(i,j));
      }
    }
  }
}

/// Constrains the polyhedra to its inner boundaries (when using interval representations)
template <class scalar>
void Tableau<scalar>::toInner(bool force)
{
  for (int i=0;i<m_supports.rows();i++) {
    m_pSortedTableau->setCoeff(i,RHSCol,func::toLower(m_supports.coeff(i,0)));
    if (force) m_supports.coeffRef(i,0)=func::toLower(m_supports.coeff(i,0));
  }
}


#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class Tableau<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class Tableau<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class Tableau<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class Tableau<mpinterval>;
  #endif
#endif

}
