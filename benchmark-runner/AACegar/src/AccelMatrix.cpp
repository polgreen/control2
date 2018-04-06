//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#include "AccelMatrix.h"

namespace abstract{

template <class scalar>
bool AccelMatrix<scalar>::ms_roundJordanBlocks=false;

/// Constructs an empty buffer
template <class scalar>
AccelMatrix<scalar>::AccelMatrix(int dimension) : JordanMatrix<scalar>(dimension)
{
}

template <class scalar>
scalar AccelMatrix<scalar>::binomial(powerS n,int k)
{
  scalar num=n;
  for (powerS i=n-k+1;i<n;i++) num*=scalar(i);//TODO: should be direct to reduce cost
  scalar den=k;
  for (int i=2;i<k;i++) den*=scalar(i);
  return num/den;
}

/// indicates if the eigenvalue at index should be overapproximated with a spherical abstraction.
template <class scalar>
int AccelMatrix<scalar>::roundIndex(int index)
{
  int offset=ms_roundJordanBlocks ? m_jordanIndex[index] : 0;
  if (m_conjugatePair[index]>index) return index-2*offset;
  if (m_conjugatePair[index]>=0)    return m_conjugatePair[index]-2*offset;
  if (m_isNegative[index])          return index;
  if (!ms_roundJordanBlocks)        return -1;
  if (offset>0)                     return index-offset;
  if (m_jordanIndex[index+1]>0)     return index;
  return -1;
}

/// Marks the round indices in a rounded vector array
template <class scalar>
void AccelMatrix<scalar>::findRoundIndices(std::vector<int> &isRoundIndex,bool compressed)
{
  int pos=0;
  isRoundIndex.resize(2*m_dimension,-1);
  for (int row=0;row< 2*m_dimension;row++) isRoundIndex[row]=-1;
  for (int row=0;row<m_dimension;row++,pos++) {
    isRoundIndex[pos]=roundIndex(row);
    if (compressed) {
      int row2;
      for (row2=row+1;row2<m_dimension;row2++) {
        if (roundIndex(row2)!=row) break;
      }
      row=row2-1;
    }
  }
  if (compressed) isRoundIndex.resize(pos);
}

/// retrieves J^n
template <class scalar>
typename AccelMatrix<scalar>::MatrixC AccelMatrix<scalar>::getPoweredEigenValues(const powerS iteration)
{
  typename JordanMatrix<scalar>::MatrixC result=m_eigenValues;
  if (iteration==1) return result;
  for (int row=0;row<m_eigenValues.rows();row++)
  {
    result.coeffRef(row,row)=func::c_pow(m_eigenValues.coeff(row,row),iteration);
    int mult=(m_conjugatePair[row]<0) ? 1 : 2;
    for (int offset=1;offset<=m_jordanIndex[row];offset++) {
      result.coeffRef(row-mult*offset,row)=binomial(iteration,offset)*func::c_pow(m_eigenValues.coeff(row,row),iteration-offset);
    }
  }
  return result;
}

/// retrieves F^n
template <class scalar>
typename AccelMatrix<scalar>::MatrixS AccelMatrix<scalar>::getPoweredSingularValues(const powerS iteration)
{
  MatrixS result=m_foldedEigenValues;
  if (iteration==1) return result;
  for (int row=0;row<m_foldedEigenValues.rows();row++)
  {
    result.coeffRef(row,row)=func::pow(m_foldedEigenValues.coeff(row,row),iteration);
    int jordanIndex=0;
    for (int offset=0;offset<row;offset++) {
      if (func::isZero(result.coeffRef(row-offset-1,row-offset))) break;
      jordanIndex++;
    }
    for (int offset=1;offset<=jordanIndex;offset++) {
      result.coeffRef(row-offset,row)=binomial(iteration,offset)*func::pow(m_foldedEigenValues.coeff(row,row),iteration-offset);
    }
  }
  return result;
}

/// retrieves a real pseudoDiagonal of J^n
template <class scalar> typename AccelMatrix<scalar>::MatrixS AccelMatrix<scalar>::getPoweredPseudoEigenValues(powerS iteration)
{
  MatrixC matrix=getPoweredEigenValues(iteration);
  return jordanToPseudoJordan(matrix,eToEigenValues);
}

/// retrieves the dynamics matrix for a given iteration (n)
template <class scalar>
typename JordanMatrix<scalar>::MatrixC AccelMatrix<scalar>::getDynamics(const powerS iteration,const bool input,const space_t space)
{
  if (iteration>func::ms_infPower) return getDynamics(func::ms_infPower,input,space);
  MatrixC nthEigenValues=input ? (calculateIminJn(iteration)*m_invIminJ) : getPoweredEigenValues(iteration);
  MatrixC eigenCalculated=nthEigenValues*m_invEigenVectors;
  if (space>=eEigenSpace) return eigenCalculated;
  MatrixC calculated=m_eigenVectors*eigenCalculated;
  if (iteration<0) calculated=m_invEigenVectors*nthEigenValues*m_eigenVectors;
  return calculated;
}

/// retrieves the dynamics matrix for a given iteration (n) using pseudo eigenvalues
template <class scalar> typename JordanMatrix<scalar>::MatrixS AccelMatrix<scalar>::getPseudoDynamics(powerS iteration,bool input,space_t space)
{
  if (iteration>func::ms_infPower) iteration=func::ms_infPower;
  if (space==eSingularSpace) {
    typename JordanMatrix<scalar>::MatrixS nthEigenValues=getPoweredSingularValues(iteration)*m_invIminF;
    return nthEigenValues;
  }
  MatrixC cEigenValues=input ? (calculateIminJn(iteration)*m_invIminJ) : getPoweredEigenValues(iteration);
  MatrixS nthEigenValues=jordanToPseudoJordan(cEigenValues,eToEigenValues);
  if (space==eEigenSpace) return nthEigenValues;
  if (iteration<0) return m_invPseudoEigenVectors*nthEigenValues*m_invPseudoEigenVectors;
  return m_pseudoEigenVectors*nthEigenValues*m_invPseudoEigenVectors;
}

/// Calculates (I-J^n)
template <class scalar>
typename JordanMatrix<scalar>::MatrixC AccelMatrix<scalar>::calculateIminJn(const powerS iteration)
{
  MatrixC result=MatrixC::Identity(m_dimension,m_dimension)-getPoweredEigenValues(iteration);
  for (int row=0;row<m_dimension;row++) {
    if (m_isOne[row]) {
      result.coeffRef(row,row)=iteration;
      for (int offset=1;offset<=m_jordanIndex[row];offset++) {
        result.coeffRef(row-offset,row)=binomial(iteration,offset+1);
      }
    }
  }
  return result;
}

/// Calculates (I-F^n)
template <class scalar>
typename JordanMatrix<scalar>::MatrixS AccelMatrix<scalar>::calculateIminFn(const powerS iteration)
{
  MatrixS result=MatrixS::Identity(m_dimension,m_dimension)-getPoweredSingularValues(iteration);
  scalar sIteration=iteration;
  for (int row=0;row<m_dimension;row++) {
    if (abs(m_invIminF.coeff(row,row))<this->m_zero) result.coeffRef(row,row)=sIteration;
  }
  return result;
}

/// Calculates (I-J)^-1
template <class scalar> void AccelMatrix<scalar>::calculateInvIminJ()
{
  m_pseudoIminJ=MatrixS::Identity(m_dimension,m_dimension)- m_pseudoEigenValues;
  m_invIminJ=MatrixC::Identity(m_dimension,m_dimension)-m_eigenValues;
  for (int row=0;row<m_dimension;row++) {
    scalar mag=func::ms_1-func::norm2(m_eigenValues.coeff(row,row));
    if (func::isZero(mag)) {
      m_invIminJ.coeffRef(row,row)=func::ms_c_1;
      int mult=(m_conjugatePair[row]<0) ? 1 : 2;
      for (int offset=1;offset<=m_jordanIndex[row];offset++) {
        m_invIminJ.coeffRef(row-mult*offset,row)=0;
      }
    }
    else if (m_isNegative[row]) {
      int jordanSize=1;
      while ((jordanSize<m_dimension-row) && (m_jordanIndex[row+jordanSize]==0)) {
        jordanSize++;
      }
      MatrixC jordanBlock=m_eigenValues.block(row,row,jordanSize,jordanSize);
      MatrixC iMinJ=jordanBlock*(MatrixC::Identity(jordanSize,jordanSize)-jordanBlock*jordanBlock);
      m_invIminJ.block(row,row,jordanSize,jordanSize)=makeInverse(iMinJ);
      m_invIminJ.block(row,row,jordanSize,jordanSize)*=(MatrixC::Identity(jordanSize,jordanSize)+jordanBlock);
    }
    else {
      m_invIminJ.coeffRef(row,row)=func::ms_c_1;
      m_invIminJ.coeffRef(row,row)/=m_invIminJ.coeff(row,row);
      if (m_conjugatePair[row]>=0) {
        if (m_jordanIndex[row+2]>0) {
          for (int col=row+2;col<m_dimension;col+=2){
            int power=(col-row)>>1;
            m_invIminJ.coeffRef(row,col)=func::c_pow(m_invIminJ.coeffRef(row,row),power+1);
            if ((power+1)&1) m_invIminJ.coeffRef(row,col)=-m_invIminJ.coeffRef(row,col);
          }
        }
      }
      else if (m_jordanIndex[row+1]>0) {
        for (int col=row+1;col<m_dimension;col++){
          m_invIminJ.coeffRef(row,col)=func::c_pow(m_invIminJ.coeffRef(row,row),col+1-row);
          if ((col+1-row)&1) m_invIminJ.coeffRef(row,col)=-m_invIminJ.coeffRef(row,col);
        }
      }
    }
  }
  if (m_hasOnes || m_hasNegatives) m_pseudoInvIminJ=this->jordanToPseudoJordan(m_invIminJ,eToEigenValues);
  else m_pseudoInvIminJ=makeInverse(m_pseudoIminJ);
  m_IminA=m_pseudoEigenVectors*m_pseudoIminJ*m_invPseudoEigenVectors;
  m_invIminA=m_pseudoEigenVectors*m_pseudoInvIminJ*m_invPseudoEigenVectors;
}

/// Retrieves a matrix that is Identity for positive blocks and J_s for negative ones
template <class scalar>
typename JordanMatrix<scalar>::MatrixS& AccelMatrix<scalar>::getJnegJ()
{
  MatrixS result=MatrixS::Identity(m_dimension,m_dimension);
  for (int row=0;row<m_dimension;row++) {
    if (m_isNegative[row]) {
      int jordanSize=1;
      while ((jordanSize<m_dimension-row) && (m_jordanIndex[row+jordanSize]==0)) {
        jordanSize++;
      }
      result.block(row,row,jordanSize,jordanSize)=m_pseudoEigenValues.block(row,row,jordanSize,jordanSize);
    }
  }
  return result;
}

/// Calculates the folded matrix over-approximation on the rotation and dilation axes
template <class scalar> void AccelMatrix<scalar>::calculateF()
{
  m_foldedEigenValues=MatrixS::Identity(m_dimension,m_dimension);
  m_svnIndex.resize(m_dimension);
  int transRow=0;
  for (int row=0;row<m_dimension;row++) {
    if ((m_roundings[row]<0) || (m_roundings[row]==row)) {
      if (ms_roundJordanBlocks) {
        m_foldedEigenValues.coeffRef(transRow,transRow)=m_blockSingularValues.coeff(row,0);
      }
      else {
        m_foldedEigenValues.coeffRef(transRow,transRow)=func::norm2(m_eigenValues.coeff(row,row));
        m_jordanIndex[m_dimension+transRow]=m_jordanIndex[row];
        if (m_jordanIndex[row]>0) m_foldedEigenValues.coeffRef(transRow-1,transRow)=func::ms_1;
      }
      m_isOne[m_dimension+transRow]=func::isZero(m_foldedEigenValues.coeffRef(transRow,transRow)-func::ms_1);
      transRow++;
    }
    m_svnIndex[row]=transRow-1;
  }
  m_foldedEigenValues.conservativeResize(transRow,transRow);
}

/// Calculates (I-F)^-1
template <class scalar> void AccelMatrix<scalar>::calculateInvIminF()
{
  int dimension=m_foldedEigenValues.rows();
  m_IminF=MatrixS::Identity(dimension,dimension)-m_foldedEigenValues;
  m_invIminF=m_IminF;
  for (int row=0;row<dimension;row++) {
    if (func::isZero(m_IminF.coeff(row,row))) {
      m_invIminF.coeffRef(row,row)=func::ms_1;
      for (int offset=1;offset<=m_jordanIndex[m_dimension+row];offset++) {
        m_invIminF.coeffRef(row-offset,row)=0;
      }
    }
    else m_invIminF.coeffRef(row,row)=func::ms_1/m_IminF.coeff(row,row);
  }
}

template <class scalar> bool AccelMatrix<scalar>::calculateJordanForm(bool includeSvd)
{
  if (!JordanMatrix<scalar>::calculateJordanForm(includeSvd)) return false;
  findRoundIndices(m_roundings,false);
  calculateInvIminJ();
  calculateF();
  calculateInvIminF();
  if (ms_trace_dynamics[eTraceDynamics]) {
    ms_logger.logData(m_pseudoInvIminJ,"InvIminJ:");
    ms_logger.logData(m_invIminF,"InvIminF:");
  }
  return true;
}

/// Loads a matrix and finds its decomposition
template <class scalar> bool AccelMatrix<scalar>::load(const MatrixS &matrix)
{
  if (!JordanMatrix<scalar>::load(matrix)) return false;
  calculateBlockSVD();
  findRoundIndices(m_roundings,false);
  return true;
}

// Loads a matrix assumed to be a canonical Jordan form
template <class scalar> bool AccelMatrix<scalar>::loadJordan(const MatrixS &matrix)
{
  if (!JordanMatrix<scalar>::loadJordan(matrix)) return false;
  findRoundIndices(m_roundings,false);
  calculateBlockSVD();
  calculateInvIminJ();
  calculateF();
  calculateInvIminF();
  if (ms_trace_dynamics[eTraceDynamics]) {
    ms_logger.logData(m_pseudoInvIminJ,"InvIminJ:");
    ms_logger.logData(m_invIminF,"InvIminF:");
  }
  return true;
}

/// Copies an existing object
template <class scalar>
void AccelMatrix<scalar>::copy(const AccelMatrix &source)
{
  JordanMatrix<scalar>::copy(source);
  m_foldedEigenValues=source.m_foldedEigenValues;
  m_invIminJ=source.m_invIminJ;
  m_pseudoIminJ=source.m_pseudoIminJ;
  m_pseudoInvIminJ=source.m_pseudoInvIminJ;
  m_IminA=source.m_IminA;
  m_invIminA=source.m_invIminA;
  m_IminF=source.m_IminF;
  m_invIminF=source.m_invIminF;
  m_svnIndex=source.m_svnIndex;
}


#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class AccelMatrix<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class AccelMatrix<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
#ifdef USE_SINGLES
    template class AccelMatrix<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class AccelMatrix<mpinterval>;
  #endif
#endif

}
