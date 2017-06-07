//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is based on Komei Fukuda's ccd implementation and as such supplied under the GPL license agreement (see license.txt)

/* dplex.c:  dual simplex method c-code
   written by Komei Fukuda, fukuda@ifor.math.ethz.ch
   Version 0.61, December 1, 1997
*/

/* dplex.c : C-Implementation of the dual simplex method for
   solving an LP: max/min  c^T x subject to  x in P, where
   P= {x :  b - A x >= 0}.  
   Please read COPYING (GNU General Public Licence) and
   the manual cddman.tex for detail.
*/

#include "DualSimplex.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <boost/timer.hpp>

namespace abstract {

template <class scalar>
bool DualSimplex<scalar>::ms_incremental=false;

template <class scalar>  DualSimplex<scalar>::DualSimplex(const int size,const int dimension)  :
    Tableau<scalar>(size,dimension),
    m_auxiliaryRow(1,m_dimension),
    m_costs(1,m_dimension),
    m_orBlockSize(1)
{}

template <class scalar>
bool DualSimplex<scalar>::load(const MatrixS &faces,const MatrixS &supports,const bool transpose)
{
  this->Conversion=LPMax;
  if (!Tableau<scalar>::load (faces,supports,transpose)) return false;
  m_auxiliaryRow.resize(1,m_dimension);
  m_costs.resize(1,m_dimension);
  m_pSortedTableau->setCoeff(m_objectiveRow,0,func::ms_hardZero);
  return true;
}

template <class scalar>
inline scalar DualSimplex<scalar>::auxEntry(const int col)
/* Computes m_auxiliaryRow*B^-1(col) */
{
  scalar temp(m_auxiliaryRow.coeff(0,0) * m_basisInverse.coeff(0,col));
  for (int j=1; j< m_dimension; j++) {
    func::madd(temp,m_auxiliaryRow.coeff(0,j),m_basisInverse.coeff(j,col));
  }
  return temp;
}

template <class scalar>
bool DualSimplex<scalar>::SelectPrimalSimplexPivot(pivot_t &pivot)
{ /* selects a primal simplex pivot (*r, *s) if the current
     basis is feasible and not optimal. */


/*    refScalar maxrat=0,rat=0;
    scalar val=0;
    pivot.col=0;
    m_status=eUndecided;
    if (Phase1 && !FindCosts()) return false;

    //Dual Feasible.
    pivot.row=findMinRow(RHSCol);
    if (pivot.row<0) {
      m_status=eOptimal;
    }
    else {
      for (int j=1; j<m_dimension; j++){// ignore RHSCol
        val=m_pSortedTableau->entry(m_basisInverse,pivot.row,j);
        if (func::isNegative(val)) {
          //The zero case would result in a pivot move by a value inside the interval of the hyperplane
          rat=func::toUpper(m_costs.coeff(0,j)/val);
          if ((pivot.col==0) || (rat > maxrat)){
            maxrat=rat;
            pivot.col=j;
          }
        }
      }
      if (pivot.col>0) return true;
      m_status=eInconsistent;
    }
    return false;*/


  scalar val;
  pivot.col=-1;
  pivot.row=-1;
  m_status=eUndecided;
  MatrixS cost(1,m_dimension);
  for (int i=0;i<m_dimension;i++) {
    cost.coeffRef(0,i)=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,i);
  }
  if (ms_trace_pivots>=eTraceCosts) {
    this->ms_logger.logData(cost,"costs:");
  }
  bool optimal=true;
  int selCol=-1;
  refScalar maxCoeff=-func::ms_infinity;
  for (int col=1; col<m_dimension; col++) {// ignore RHSCol
    refScalar coeff=func::toUpper(cost.coeff(0,col));
    if ((coeff<0) && (coeff>maxCoeff)) {
      maxCoeff=func::toUpper(cost.coeff(0,col));
      selCol=col;
    }
  }

  if (selCol>=0) {
    optimal=false;
    refScalar minrat=func::ms_infinity,rat;
    for (int row=0;row<m_objectiveRow;row++) {
      if (m_basicVars[row]<0) {
        val=m_pSortedTableau->entry(m_basisInverse,row,selCol);
        if (func::isPositive(val)) {
          //The zero case would result in a pivot move by a value inside the interval of the hyperplane
          rat=func::toUpper(m_pSortedTableau->entry(m_basisInverse,row,RHSCol)/val);
          if (func::isPositive(rat) && (rat<minrat)) {
            minrat=rat;
            pivot.row=row;
          }
        }
      }
    }
    if (pivot.row>=0) {
      pivot.col=selCol;
      return true;
    }
  }
  m_status=optimal ? eOptimal : eInconsistent;
  return false;
}

template <class scalar>
bool DualSimplex<scalar>::SelectDualSimplexPivot(const bool Phase1,pivot_t &pivot)
{ /* selects a dual simplex pivot (pivot.row, pivot.col) if the current
     basis is dual feasible and not optimal. If not dual feasible,
     the procedure returns false and m_status=LPSundecided.
     If Phase1=true, the RHS column will be considered as the negative
     of the column of the largest variable (==m_size).  For this case, it is assumed
     that the caller used the auxiliary row (with variable m_size) to make the current
     dictionary dual feasible before calling this routine so that the nonbasic
     column for m_size corresponds to the auxiliary variable.
  */
  refScalar maxrat=0,rat=0;
  scalar val=0;
  pivot.col=0;
  m_status=eUndecided;
  if (Phase1 && !FindCosts()) return false;

  //Dual Feasible.
  pivot.row=Phase1 ? findMaxRow(m_basicVars[m_size]) : findMinRow(RHSCol);
  if (pivot.row<0) {
    m_status=eOptimal;
  }
  else {
    for (int j=1; j<m_dimension; j++){// ignore RHSCol
      val=m_pSortedTableau->entry(m_basisInverse,pivot.row,j);
      if (func::isPositive(val)) {
        //The zero case would result in a pivot move by a value inside the interval of the hyperplane
        if (!Phase1) m_costs.coeffRef(0,j)=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,j);
        rat=func::toUpper(m_costs.coeff(0,j)/val);
        if ((pivot.col==0) || (rat > maxrat)){
          if ((pivot.row==m_lastPivot.row) && (j==m_lastPivot.col)) continue;
          maxrat=rat;
          pivot.col=j;
        }
      }
    }
    if (pivot.col>0) return true;
    m_status=eInconsistent;
  }
  return false;
}

template <class scalar>
bool DualSimplex<scalar>::SelectIncrementalSimplexPivot(pivot_t &pivot)
{ /* selects a pivot on the last added row. This presumes the simplex is
     at a dual feasible location which is made primal infesible by the
     added row (set in pivot.row).
  */
  refScalar maxrat=0,rat=0;
  scalar val=0;
  scalar rcost[m_dimension];

  pivot.col=0;
  m_status=eUndecided;
  for (int j=1; j<m_dimension; j++){//ignore RHSCol
    rcost[j]=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,j);
  }
  //Dual Feasible.
  if (pivot.row<0) m_status=eOptimal;
  else {
    for (int j=1; j<m_dimension; j++){// ignore RHSCol
      val=m_pSortedTableau->entry(m_basisInverse,pivot.row,j);
      if (func::isPositive(val)) {
        //The zero case would result in a pivot move by a value inside the interval of the hyperplane
        rat=func::toUpper(rcost[j]/val);
        if ((pivot.col==0) || (rat > maxrat)){
          maxrat=rat;
          pivot.col=j;
        }
      }
    }
    if (pivot.col>0) return true;
    m_status=eInconsistent;
  }
  return false;
}

template <class scalar>
bool DualSimplex<scalar>::SelectOredPivot(const long rowmax, const Set &noPivotRow, const Set &noPivotCol, pivot_t &pivot)
/* Select a position (pivot) in the matrix X.T such that (X.T)[pivot.row][pivot.col] is nonzero
   The choice is feasible, i.e., not on NopivotRow and NopivotCol, and
   best with respect to the specified roworder
 */
{
  long rtemp;
  Set rowexcluded(noPivotRow);
  scalar Xtemp,Xtemp2;
  scalar Ftemp,Ftemp2;
  for (rtemp=rowmax;rtemp<m_size;rtemp++) {
    rowexcluded.add(rtemp);   /* cannot pivot on any row > rmax */
  }
  while(true) {
    rtemp=-1;
    for (int i=1;i<=m_size;i++) {
      if (!rowexcluded.member(m_pSortedTableau->zeroOrder(i))){
        rtemp=m_pSortedTableau->zeroOrder(i);
        break;
      }
    }
    if (rtemp>=0) {
      rtemp-=(rtemp%m_orBlockSize);
      pivot.row=rtemp;
      for (pivot.col=0;pivot.col < m_dimension;pivot.col++) {
        if (!noPivotCol.member(pivot.col)) {
          Xtemp=m_pSortedTableau->entry(m_basisInverse,pivot.row,pivot.col);
          Ftemp=Xtemp/m_pSortedTableau->entry(m_basisInverse,pivot.row,0);
          int offset=0;
          for (int j=1;j<m_orBlockSize;j++) {
            Xtemp2=m_pSortedTableau->entry(m_basisInverse,pivot.row+j,pivot.col);
            Ftemp2=Xtemp2/m_pSortedTableau->entry(m_basisInverse,pivot.row+j,0);
            if (func::isPositive(Ftemp2-Ftemp)) {
              offset=j;
              Xtemp=Xtemp2;
              Ftemp=Ftemp2;
            }
          }
          pivot.row+=offset;
          char sign=func::softSign(Xtemp);//hardSign(Xtemp);//Zero is ensured by check in entry
          if (sign<0) return true;
        }
      }
      for (int i=0;i<m_orBlockSize;i++) rowexcluded.add(rtemp+i);
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
bool DualSimplex<scalar>::AuxiliaryPivotAndUpdate(long col)
{
  MatrixS Rtemp=m_auxiliaryRow*m_basisInverse;
  //MatrixS Rtemp(1,m_dimension);
  //for (int i=0;i<m_dimension;i++) Rtemp.coeffRef(0,i)=auxEntry(i);
  char sign=func::hardSign(Rtemp.coeff(0,col));
  if (sign==0) return false;
  scalar Xtemp;
  refScalar invXtemp0 = func::toCentre(func::ms_1/Rtemp.coeff(0,col));
  for (int j = 0; j < m_dimension; j++) {
    if (j != col) {
      Xtemp = Rtemp.coeff(0,j)*invXtemp0;
      for (int j1 = 0; j1 < m_dimension; j1++)
        func::msub(m_basisInverse.coeffRef(j1,j),m_basisInverse.coeff(j1,col),Xtemp); //m_basisInverse.coeffRef(j1,j) -= m_basisInverse.coeff(j1,col) * Xtemp;
    }
  }
  m_basisInverse.col(col)*=invXtemp0;
  if (ms_trace_pivots>=eTracePivots) logBasis(m_size,col);
  long entering=m_nonBasicRow[col];
  m_basicVars[m_size]=col;              // the nonbasic variable r corresponds to column s
  m_nonBasicRow[col]=m_size;            // the nonbasic variable on s column is r
  if (entering>=0) m_basicVars[entering]=-1; // original variables have negative index and should not affect the row index
  return true;
}

// Find the corresponding row with the minimum entry value for a given column
template <class scalar>
int DualSimplex<scalar>::findMinRow(int col)
{
  int row=-1;
  refScalar minval=0;
  refScalar val;
  if (col<0) col=0;
  for (int i=0; i<m_objectiveRow; i++) {
    if (m_basicVars[i]<0) {  /* i is a basic variable */
      val=func::toUpper(m_pSortedTableau->entry(m_basisInverse,i,col)); // for dual Phase I (auxiliary row is non-basic)
      if (val < minval) {
        row=i;
        minval=val;
      }
    }
  }
  return row;
}

// Find the corresponding row with the minimum entry value for a given column
template <class scalar>
int DualSimplex<scalar>::findMaxRow(int col)
{
  int row=-1;
  refScalar maxval=0;
  refScalar val;
  if (col<0) col=0;
  for (int i=0; i<m_objectiveRow; i++) {
    if (m_basicVars[i]<0) {  /* i is a basic variable */
      // for dual Phase I (auxiliary row is non-basic)
      val=func::toLower(m_pSortedTableau->entry(m_basisInverse,i,col));
      if (val > maxval) {
        row=i;
        maxval=val;
      }
    }
  }
  return row;
}

template <class scalar>
int DualSimplex<scalar>::FindDualFeasibleBasis()
{ /* Find a dual feasible basis using Phase I of Dual Simplex method.
     If the problem is dual feasible,
     the procedure returns m_status=LPSundecided and a dual feasible
     basis.   If the problem is dual infeasible, this returns
     m_status=DualInconsistent and the evidence column.
  */

  long rank=0;
  pivot_t pivot;

  m_status=eUndecided; this->m_evidenceCol=-1;
  if (ms_trace_tableau>eTraceTableau) this->logBasis(m_objectiveRow,-1);
  scalar maxcost=-func::ms_infinity;
  int maxReducedCostCol=0;  /* ms will be the index of column which has the largest reduced cost */
  for (int col=1; col<m_dimension; col++){//ignore RHSCol
    scalar cost=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,col);
    if (func::toLower(cost) > func::toUpper(maxcost)) {maxcost=cost; maxReducedCostCol = col;}//TODO:might want to check for imprecision
  }
  if (ms_trace_pivots>=eTraceCosts) {
    std::stringstream buffer;
    buffer << "Dual feasible Basis. cost=" << ms_logger.MakeNumber(maxcost) << ",c=" << maxReducedCostCol;
    ms_logger.logData(buffer.str());
  }
  if (!func::isPositive(maxcost)) return rank;//Dual feasible

  //The zero case above indicates we are somewhere on the hyperplane which is feasible (or an m_zero overapprox)
  m_auxiliaryRow=MatrixS::Zero(1,m_dimension);
  for (int k=1; k<m_dimension; k++) {
    if (m_nonBasicRow[k]>=0) {
      // To make the auxiliary row (0,-1,-1,...,-1).
      m_pSortedTableau->subRow(m_auxiliaryRow,m_nonBasicRow[k]);
    }
  }
  if (ms_trace_pivots>=eTraceSimplex) {
    ms_logger.logData(m_auxiliaryRow,"Auxiliary Row:");
    if (ms_trace_pivots>=eTraceEntries) {
      this->logNonBasic();
      this->logBasic();
      MatrixS matrix=m_auxiliaryRow*m_basisInverse;
      ms_logger.logData(matrix,"Entries");
    }
  }

  /* Pivot on (m_auxiliaryRow, maxReducedCostCol) so that the dual basic solution becomes feasible */
  AuxiliaryPivotAndUpdate(maxReducedCostCol);
  rank++;

  m_status=eUndecided;/* Dual Simplex Phase I */
  if (m_costs.cols()<m_dimension) m_costs.resize(1,m_dimension);

  while (SelectDualSimplexPivot(true, pivot))  {
    if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
      ms_logger.logData("Dual Feas Cycling");//TODO: remove (change for appropriate action)
    }
    rank++;
    if (m_basicVars[m_size]<0) return rank;
  }

  /* The current dictionary is terminal.  There are two cases:
     TableauEntry(m_objectiveRow,maxReducedCostCol) is negative or zero.
     The first case implies dual infeasible,
     and the latter implies dual feasible but m_size is still in nonbasis.
     We must pivot in the auxiliary variable m_size. */

  pivot.row=findMinRow(maxReducedCostCol);
  pivot.col=maxReducedCostCol;
  if (pivot.row>=0) {
    if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
      ms_logger.logData("Dual Feas Cycling 2");//TODO: remove (change for appropriate action)
    }
    rank++;
  }
  if (func::isNegative(m_pSortedTableau->entry(m_basisInverse,m_objectiveRow, pivot.col))) {
    m_status=eDualInconsistent;
    this->m_evidenceCol=maxReducedCostCol;
  }
  return rank;
}

template <class scalar>
scalar DualSimplex<scalar>::maximise(const std::vector<scalar> &vector,const ResetType_t resetType)
{
  if (vector.size()<this->getDimension()) return func::ms_nan;
  for (int col=1;col<m_dimension;col++) {
    m_pSortedTableau->setCoeff(m_objectiveRow,col,vector.at(col-1));
  }
  return processMaximize(resetType);
}

template <class scalar>
scalar DualSimplex<scalar>::maximise(const MatrixS &vector,const ResetType_t resetType,bool transpose)
{
  if (transpose) m_pSortedTableau->setRow(m_objectiveRow,1,vector.transpose().row(0));
  else m_pSortedTableau->setRow(m_objectiveRow,1,vector.row(0));
  return processMaximize(resetType);
}

template <class scalar>
bool DualSimplex<scalar>::maximiseAll(const MatrixS &vectors, MatrixS &supports,AproxType_t aprox,OrderType order)
{
  boost::timer timer;
  try {
    if (aprox==eOverAprox)       this->toOuter();
    else if (aprox==eUnderAprox) this->toInner();
    if ((supports.rows()!=vectors.cols()) || (supports.cols()!=1)) supports.resize(vectors.cols(),1);
    FindFeasBasis(eResetBasis);
    if (order!=LexNone) {
      SortedMatrix<scalar> sortedVectors(vectors,order,true);
      if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Sort Time",true);
      sortedVectors.block(0,0,sortedVectors.rows(),sortedVectors.cols())=vectors.transpose();
      int index=sortedVectors.zeroOrder(1);
      m_pSortedTableau->setRow(m_objectiveRow,1,vectors.col(index).transpose());
      scalar result=processMaximize(eUseDefaultBasis);
      supports.coeffRef(index,0)=result;
      refScalar max=func::toUpper(supports.coeffRef(index,0));
      for (int i=2;i<=sortedVectors.rows();i++) {
        index=sortedVectors.zeroOrder(i);
        if (index<0) continue;
        m_pSortedTableau->setRow(m_objectiveRow,1,sortedVectors.row(index));
        try {
          result=processMaximize(eKeepBasis);
        }
        catch(std::string error) {
          if (ms_trace_errors) {
            ms_logger.logData("retrying ",false);
            ms_logger.logData(error);
          }
          result=processMaximize(eRebaseBasis);
        }
        supports.coeffRef(index,0)=result;
        if (max<func::toUpper(result)) {
          max=func::toUpper(result);
        }
      }
    }
    else {
      for (int i=0;i<vectors.cols();i++) {
        m_pSortedTableau->setRow(m_objectiveRow,1,vectors.block(0,i,vectors.rows(),1).transpose());
        supports.coeffRef(i,0)=processMaximize(eUseDefaultBasis);
      }
    }
  }
  catch(std::string error) {
    ms_logger.logData(error);
    return false;
  }
  if (this->ms_trace_time) {
    int elapsed=timer.elapsed()*1000;
    if (elapsed>0) {
      ms_logger.logData(this->getName(),false);
      ms_logger.logData(m_iterations,", iters ");
      ms_logger.logData(elapsed," Maximise time",true);
    }
  }
  return true;
}

template <class scalar>
int DualSimplex<scalar>::ceMaximise(SortedMatrix<scalar> &sortedVectors, MatrixS &supports, MatrixS &inSupports,refScalar &max,MatrixS &ce,scalar &result,int start)
{
  boost::timer timer;
  int index;
  try {
    this->toOuter();
    m_max=max;
    if ((supports.rows()!=sortedVectors.rows()) || (supports.cols()!=1)) supports.resize(sortedVectors.rows(),1);
    index=sortedVectors.zeroOrder((start>0) ? start : 1);
    m_pSortedTableau->setRow(m_objectiveRow,1,sortedVectors.row(index));
    try {
      result=processMaximize((start>0) ? eKeepBasis : eResetBasis);
    }
    catch(std::string error) {
      if (ms_trace_errors) {
        ms_logger.logData("retrying ",false);
        ms_logger.logData(error);
      }
      result=processMaximize(eRebaseBasis);
    }
    if (start==0) start++;
    supports.coeffRef(index,0)=result;
    if (func::toUpper(inSupports.coeffRef(index,0)+result)>max) {
      ce=m_basisInverse.col(RHSCol).transpose();
      return start;
    }
    refScalar maxResult=func::toUpper(result);
    start++;
    for (int i=start;i<=sortedVectors.rows();i++) {
      index=sortedVectors.zeroOrder(i);
      if (index<0) continue;
      m_pSortedTableau->setRow(m_objectiveRow,1,sortedVectors.row(index));
      if (ms_trace_tableau>=eTraceObjectives) {
        std::stringstream buffer;
        buffer << "index[" << i << "]";
        if (ms_trace_pivots>=eTracePivots) {
          buffer << ", cos=" << ms_logger.MakeNumber(sortedVectors.m_cosines[i]);
        }
        if (ms_trace_tableau>=eTraceTableau) {
          MatrixS objective=sortedVectors.row(index);
          ms_logger.logData(objective,buffer.str());
        }
        else ms_logger.logData(buffer.str());
      }
      try {
        result=processMaximize(eCheckBasis);
      }
      catch(std::string error) {
        if (ms_trace_errors) {
          ms_logger.logData("retrying ",false);
          ms_logger.logData(error);
        }
        result=processMaximize(eRebaseBasis);
      }
      if (ms_trace_tableau>=eTraceObjectives) {
        ms_logger.logData(result,"max",true);
      }
      if (func::toUpper(result)>maxResult) {
        maxResult=func::toUpper(result);
      }
      supports.coeffRef(index,0)=result;
      if (func::toUpper(inSupports.coeffRef(index,0)+result)>max) {
        ce=m_basisInverse.col(RHSCol).transpose();
        if (ms_trace_time) {
          int elapsed=timer.elapsed()*1000;
          if (elapsed>0) {
            ms_logger.logData(this->getName(),false);
            ms_logger.logData(i," ");
            ms_logger.logData(m_iterations,", iters ");
            ms_logger.logData(inSupports.coeffRef(index,0)+result,", max ");
            ms_logger.logData(elapsed," Maximise time",true);
          }
        }
        return i;
      }
    }
  }
  catch(std::string error) {
    ms_logger.logData(error);
    return -1;
  }
  if (this->ms_trace_time) {
    int elapsed=timer.elapsed()*1000;
    if (elapsed>0) {
      ms_logger.logData(this->getName(),false);
      ms_logger.logData(m_iterations,", iters ");
      ms_logger.logData(elapsed," Maximise time",true);
    }
  }
  return 0;
}

template <class scalar>
scalar DualSimplex<scalar>::processMaximize(ResetType_t resetType)
/* 
When LP is inconsistent then *re returns the evidence row.
When LP is dual-inconsistent then *se returns the evidence column.
*/
{
  boost::timer timer;
  long rank=0;
  long maxpivfactor=70;
  pivot_t pivot;
  func::setZero(this->m_zero);
  long maxpivots=maxpivfactor*m_dimension;  // maximum pivots to be performed before cc pivot is applied.
  long rebasepivots=(func::getDefaultPrec()>>3)+2*m_dimension;
  /* Initializing control variables. */

  this->m_evidenceRow=-1;
  this->m_evidenceCol=-1;

  if (resetType<eKeepBasis) {
    if (resetType!=eRebaseBasis) m_iterations=0;
    if (ms_trace_pivots>=eTracePivots) logTableau("Maximise");
    m_iterations+=FindFeasBasis(resetType);
    if (this->ms_trace_time && (ms_trace_pivots>=eTracePivots) && (resetType!=eUseDefaultBasis)) {
      logPivotCount(timer.elapsed()*1000,"Find Feasible:");
    }
  }
/*  else {
    while(true) {
      m_status=eUndecided;
      if (m_rank+rank>rebasepivots) {
        m_iterations+=Rebase()+rank;
        m_rank=0;
        rank=FindDualFeasibleBasis();
      }
      if (SelectCrissCrossPivot(pivot)) {
        if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
          ms_logger.logData("Cycling");//TODO: remove (change for appropriate action)
        }
        maxpivots+=maxpivfactor*m_dimension;
        rank++;
      }
      else {
        switch (m_status) {
          case eInconsistent: this->m_evidenceRow=pivot.row;
          case eDualInconsistent:
             this->m_evidenceCol=pivot.col;
             //ms_logger.logData(pivot.row,"Inconsistent",true);
          default:
            break;
        }
        break;
      }
    }
    if ((this->ms_trace_time) && (ms_trace_pivots>=eTracePivots)) {
      logPivotCount(timer.elapsed()*1000,"Find Feasible:");
    }
  }*/
  m_status=eUndecided;
  if (this->m_evidenceCol<0) rank+=FindDualFeasibleBasis();
  if ((this->ms_trace_time) && (ms_trace_pivots>=eTracePivots)) {
    logPivotCount(timer.elapsed()*1000,"Find DualFeasible:");
  }

  if (this->m_evidenceCol>=0){
    if (m_status==eUndecided) m_status=eStrucDualInconsistent;// No LP basis is found, and thus Inconsistent.
    // else No dual feasible basis is found, and thus DualInconsistent.
    return m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,RHSCol);
  }

  /*if ((rank==0) && (resetType==eCheckBasis)) {
    scalar result=entry(m_objectiveRow,RHSCol);
    if (func::toUpper(result)<m_max) {
      m_iterations+=rank;
      m_rank+=rank;
      return result;
    }
  }*/

  /* Dual Simplex Method */
  if (m_costs.cols()<m_dimension) m_costs.resize(1,m_dimension);
  while(true) {
    m_status=eUndecided;
    if (m_rank+rank>rebasepivots) {
      m_iterations+=Rebase()+rank;
      m_rank=0;
      rank=FindDualFeasibleBasis();
    }
    if ((rank<maxpivots) && SelectDualSimplexPivot(false, pivot)) {
      if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
        ms_logger.logData("Process Cycling");//TODO: remove (change for appropriate action)
      }
      rank++;
    }
    else if ((m_status==eUndecided) && SelectCrissCrossPivot(pivot)) {
      /* In principle this should not be executed because we already have dual feasibility
         attained and dual simplex pivot should have been chosen.  This might occur
         under floating point computation, or the case of cycling.
      */
      if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
        ms_logger.logData("Cycling");//TODO: remove (change for appropriate action)
      }
      maxpivots+=maxpivfactor*m_dimension;
      rank++;
    }
    else {
      switch (m_status) {
        case eInconsistent: this->m_evidenceRow=pivot.row;
        case eDualInconsistent:
           this->m_evidenceCol=pivot.col;
           //ms_logger.logData(pivot.row,"Inconsistent",true);
        default:
          if (FindCosts()) rank+=FindDualFeasibleBasis();
          break;
      }
      break;
    }
  }
  m_iterations+=rank;
  if (resetType>=eKeepBasis) m_rank+=rank;
  if ((this->ms_trace_time) && (ms_trace_pivots>=eTracePivots)) logPivotCount(timer.elapsed()*1000,"Find Support");
  scalar result=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,RHSCol);
  if (func::isNan(result)) {
    func::imprecise(result,func::ms_hardZero);
    return result;
  }
  return result;
}

template <class scalar>
scalar DualSimplex<scalar>::processIncremental()
{
  boost::timer timer;
  int rank=0;
  pivot_t pivot;
  long rebasepivots=(func::getDefaultPrec()>>3)+2*m_dimension;
  pivot.row=m_objectiveRow-1;
  if (m_costs.cols()<m_dimension) m_costs.resize(1,m_dimension);
  if (SelectIncrementalSimplexPivot(pivot)) {
    if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
      ms_logger.logData("Cycling Incremental");//TODO: remove (change for appropriate action)
    }
    rank++;
    while(true) {
      m_status=eUndecided;
      if (m_rank+rank>rebasepivots) {
        m_iterations+=Rebase()+rank;
        m_rank=0;
        rank=FindDualFeasibleBasis();
      }
      if (SelectDualSimplexPivot(false, pivot)) {
        if (!ColumnPivotAndUpdate(pivot) && ms_trace_errors) {
          ms_logger.logData("Cycling post-incremental");//TODO: remove (change for appropriate action)
        }
        rank++;
      }
      else {
        switch (m_status) {
          case eInconsistent: this->m_evidenceRow=pivot.row;
          case eDualInconsistent:
             this->m_evidenceCol=pivot.col;
          default: break;
        }
        break;
      }
    }
    m_iterations+=rank;
    m_rank+=rank;
  }
  if ((this->ms_trace_time) && (ms_trace_pivots>=eTracePivots)) logPivotCount(timer.elapsed()*1000,"Find Support:");
  scalar result=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,RHSCol);
  return result;
}

template <class scalar>
int DualSimplex<scalar>::FindFeasOrBasis(int orBlockSize,const ResetType_t resetType)
{
  normalise(true);
  m_orBlockSize=orBlockSize;
  m_pSortedTableau->setCoeff(m_objectiveRow,RHSCol,0);
  if (resetType==eUseDefaultBasis) {
    m_basisInverse=m_feasBasisInverse;
    m_basicVars=m_feasBasicVars;
    m_nonBasicRow=m_feasNonBasicRow;
    if (ms_trace_pivots>=eTracePivots) this->logBasis(-1,-1);
    return 0;
  }
  else if (resetType==eRebaseBasis) return Rebase();
  this->ComputeRowOrderVector(MinIndex);
  int result=this->FindOrLPBasis();
  m_feasBasisInverse=m_basisInverse;
  m_feasBasicVars=m_basicVars;
  m_feasNonBasicRow=m_nonBasicRow;
  return result;
}

template <class scalar>
int DualSimplex<scalar>::FindOrLPBasis()
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
  if (ms_trace_pivots>=eTracePivots) ms_logger.logData("Ored Feasibility Basis");
  ResetTableau();
  Set RowSelected(m_size);
  Set ColSelected(m_dimension);
  RowSelected.add(m_objectiveRow);
  ColSelected.add(RHSCol);
  pivot_t pivot;
  int rank=m_dimension;
  m_evidenceCol=-1;
  for (int i=0;i<m_dimension;i++) {   /* Find a set of rows for a basis */
    if (!SelectOredPivot(m_size, RowSelected, ColSelected, pivot))
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
      ms_logger.logData("Cycling LPOR");//TODO: remove (change for appropriate action)
    }
  }
  return rank;
}

/// Finds the objective row costs
template <class scalar>
bool DualSimplex<scalar>::FindCosts()
{
  for (int j=1; j<m_dimension; j++){//ignore RHSCol
    m_costs.coeffRef(0,j)=m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,j);
    if (func::isPositive(m_costs.coeff(0,j))) {
      //The zero case may cause an overapproximation of an empty set to an m_zero^n size hypercube.
      return false;
    }
  }
  return true;
}

template <class scalar>
bool DualSimplex<scalar>::SelectCrissCrossPivot(pivot_t &pivot)
{
  m_status=eUndecided;
  for (int i=0; i<m_objectiveRow; i++) {
    if (m_basicVars[i]==-1) {  /* i is a basic variable */
      if (func::isNegative(m_pSortedTableau->entry(m_basisInverse,i,RHSCol))) {
        //The zero case above indicates we are somewhere on the hyperplane which is feasible (or an m_zero overapprox)
        pivot.row=i;
        for (int j=0; j<m_size; j++) {
          if (m_basicVars[j] >0) { /* i is nonbasic variable */
             if (func::isPositive(m_pSortedTableau->entry(m_basisInverse,pivot.row,m_basicVars[j]))) {
               pivot.col=m_basicVars[j];
               return true;
             }
          }
        }
        m_status=eInconsistent;
        return false;
      }

    }
    else if (m_basicVars[i] >0) { /* i is nonbasic variable */
      if (func::isPositive(m_pSortedTableau->entry(m_basisInverse,m_objectiveRow,m_basicVars[i]))) {
        //The zero case above indicates we are somewhere on the hyperplane which is feasible (or an m_zero overapprox)
        pivot.col=m_basicVars[i];
        for (int j=0; j<m_size; j++) {
          if (j!=m_objectiveRow && m_basicVars[j]==-1) {  /* i is a basic variable */
            if (func::isNegative(m_pSortedTableau->entry(m_basisInverse,j,pivot.col))) {
              pivot.row=j;
              return true;
            }
          }
        }
        m_status=eDualInconsistent;
        return false;
      }
    }
  }
  m_status=eOptimal;
  return false;
}

/// Normalises the directions of the faces
template <class scalar>
void DualSimplex<scalar>::normalise(bool reload)
{
  if (this->m_isNormalised || m_faces.rows()<=0) return;
  MatrixS norms=m_faces.rowwise().norm();
  for (int i=0;i<m_faces.rows();i++) {
    char sign=func::hardSign(norms.coeff(i));
    if (sign!=0) {
      for (int j=0;j<m_faces.cols();j++) m_faces.coeffRef(i,j)/=norms.coeff(i);
      m_supports.coeffRef(i,0)=m_supports.coeff(i,0)/norms.coeff(i);
    }
  }
  this->m_isNormalised=true;
  if (reload) load(m_faces,m_supports);
}

/// Retrieves an overapproximation support function related to the last solution
template <class scalar>
scalar DualSimplex<scalar>::getOverSupport(MatrixS &vector)
{
  int minRow=m_nonBasicRow[0];
  scalar result=m_supports.coeff(m_nonBasicRow[0],0);
  for (int i=1;i<getDimension();i++) {
    int row=m_nonBasicRow[i];
    if (func::isNegative(m_supports.coeff(row,0)-result)) {
      result=m_supports.coeff(row,0);
      minRow=row;
    }
  }
  scalar cosine=vector.coeff(0,0)*m_faces.coeff(minRow,0);
  for (int i=1;i<getDimension();i++) {
    cosine+=vector.coeff(0,i)*m_faces.coeff(minRow,i);
  }
  result=vector.norm()*m_supports.coeff(minRow,0);
  ms_logger.logData(m_supports.coeff(minRow,0),"overSup");
  result/=cosine;
  cosine/=vector.norm()*m_faces.row(minRow).norm();
  ms_logger.logData(cosine,",cosine",true);
  if (!func::isPositive(cosine)) return func::ms_infinity;
  return result;
}

/// Retrieves the largest support related to the last solution
template <class scalar>
scalar DualSimplex<scalar>::getMaxSupport(scalar &ceiling)
{
  scalar result=-func::ms_infinity;
  for (int i=0;i<getDimension();i++) {
    int row=m_nonBasicRow[i];
    if ((func::isPositive(m_supports.coeff(row,0)-result))
    && (!func::isPositive(m_supports.coeff(row,0)-ceiling))) {
      result=m_supports.coeff(row,0);
    }
  }
  return result;
}

/// Retrieves the smallest support related to the last solution
template <class scalar>
scalar DualSimplex<scalar>::getMinSupport()
{
  scalar result=m_supports.coeff(m_nonBasicRow[0],0);
  for (int i=1;i<getDimension();i++) {
    int row=m_nonBasicRow[i];
    if (func::isNegative(m_supports.coeff(row,0)-result)) {
      result=m_supports.coeff(row,0);
    }
  }
  return result;
}

/// Creates a list of redundant/non-redundant rows of the tableau
template <class scalar>
int DualSimplex<scalar>::findRedundancies(std::vector<bool> &isRedundant)
{
  for (int i=0;i<m_faces.rows();i++) isRedundant[i] =true;
  int redundant=m_faces.rows();
  this->m_isNormalised=false;
  for (int row=0;row<m_faces.rows();row++) {
    for (int col=0;col<m_faces.cols();col++) {
      char sign=func::hardSign(m_faces.coeff(row,col));
      if (sign!=0) {
        isRedundant[row]=false;
        redundant--;
        break;
      }
    }
  }
  normalise(false);
  SortedMatrix<scalar> faces(m_faces,LexMin);
  for (int i=1;i<=m_faces.rows();i++)
  {
    int row=faces.zeroOrder(i);
    if (isRedundant[row]) continue;
    int count=m_faces.rows();
    for (int j=i+1;j<=count;j++) {
      int row2=faces.zeroOrder(j);
      if (isRedundant[row2]) continue;
      char sign=faces.compareZeroOrderRows(i,j);
      if (sign==0) {
        isRedundant[row2]=true;//TODO: should aggregate width(error) on non-redundant vector
        if (func::isNegative(m_supports.coeff(row2,0)-m_supports.coeff(row,0))) {
          isRedundant[row2]=false;
          isRedundant[row]=true;
          i=j;
          row=row2;
        }
        redundant++;
      }
      else break;
    }
  }
}

/// Clears redundant faces in the polyhedra (caused by intersections and reductions)
template <class scalar>
bool DualSimplex<scalar>::removeRedundancies()
{
  if (m_faces.rows()<=0) return false;
  std::vector<bool> isRedundant;
  isRedundant.resize(m_faces.rows());
  int redundant=findRedundancies(isRedundant);
  if (redundant>0) {
    int pos=0;
    m_basicVars.resize(m_faces.rows()-redundant);
    for (int i=0;i<m_faces.rows();i++) {
      if (isRedundant[i]) continue;
      m_faces.row(pos)=m_faces.row(i);
      m_supports.coeffRef(pos,0)=m_supports.coeff(i,0);
      m_basicVars[pos]=m_basicVars[i];
      if (m_basicVars[pos]>=0) m_nonBasicRow[m_basicVars[pos]]=pos;
      pos++;
    }
    m_faces.conservativeResize(pos,m_faces.cols());
    m_supports.conservativeResize(pos,1);
    Tableau<scalar>::load(m_faces,m_supports);
    return true;
  }
  Tableau<scalar>::load(m_faces,m_supports);
  return false;
}

/// Saves the time and iteration count data for the given process
template <class scalar>
void DualSimplex<scalar>::logPivotCount(int time,std::string process)
{
  std::stringstream buffer;
  buffer << process << " " << m_iterations;
  ms_logger.logData(time,buffer.str(),true);
}

#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class DualSimplex<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class DualSimplex<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class DualSimplex<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class DualSimplex<mpinterval>;
  #endif
#endif

}
