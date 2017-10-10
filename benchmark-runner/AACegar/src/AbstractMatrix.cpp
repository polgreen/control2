//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#include <math.h>

#include <Eigen/Eigenvalues>

#include <boost/timer.hpp>

#include "AbstractMatrix.h"

namespace abstract{

template <class scalar>
bool AbstractMatrix<scalar>::ms_continuous=false;

template <class scalar>
bool AbstractMatrix<scalar>::ms_sparse=false;

/// Constructs an empty buffer
template <class scalar>
AbstractMatrix<scalar>::AbstractMatrix(int dimension) : AccelMatrix<scalar>(dimension),
  //m_roundDimension(dimension),
  m_sampleTime(1),
  m_delayTime(0),
  m_abstractDynamics(dimension,ms_sparse),
  m_abstractInputDynamics(dimension,ms_sparse),
  m_abstractRoundDynamics(dimension,ms_sparse)
  {
    m_abstractDynamics.setName("Abstract Dynamics");
    m_abstractRoundDynamics.setName("Round Dynamics");
  }

/// Changes the default dimension of the system
template <class scalar>
void AbstractMatrix<scalar>::changeDimensions(const int dimension)
{
  AccelMatrix<scalar>::changeDimensions(dimension);
  m_abstractDynamics.changeDimension(dimension);
  m_abstractInputDynamics.changeDimension(dimension);
  m_abstractRoundDynamics.changeDimension(dimension);
}

template <class scalar>
void AbstractMatrix<scalar>::swapValues(scalar &low,scalar &high)
{
  scalar temp=low;
  low=high;
  high=temp;
}

template <class scalar>
inline void AbstractMatrix<scalar>::checkRange(const int row,const powerS iteration,const scalar mag,scalar &min,scalar &max)
{
  if (func::isPositive(min-max)) {
    scalar temp=min;
    min=max;
    max=temp;
  }
  if ((m_zeniths[row]>0) && (m_zeniths[row]<=iteration)) {
    scalar mid=condPow(mag,m_zeniths[row],row);
    if (func::isPositive(mid-max)) max=mid;
    if (m_zeniths[row]<iteration) {
      mid=condPow(mag,m_zeniths[row]+1,row);
      if (func::toLower(mid)>func::toUpper(max)) max=mid;
    }
  }
  if (m_freq[row]>0) {
    if (m_freq[row]<=iteration) {
    }
    else if (row>m_dimension) {
      if (func::toUpper(min)<-func::toLower(max)) min=-max;
      else max=-min;
    }
  }
}

template <class scalar>
typename JordanMatrix<scalar>::complexS AbstractMatrix<scalar>::condPow(complexS coef,const powerS n,int row)
{
  if (row>=m_dimension) {
    if (m_inputType==eParametricInputs) row-=m_dimension;
    else {
      coef=complexS(m_foldedEigenValues.coeff(row-m_dimension,row-m_dimension),0);
    }
    if (m_jordanIndex[row]==0) {
      if (func::isZero(func::norm2(coef-ms_complexOne))) return complexS(n,0);
      return this->ms_complexOne-func::c_pow(coef,n);
    }
    if (ms_continuous) {
      int den=m_jordanIndex[row];
      for (int i=2;i<m_jordanIndex[row];i++) den*=i;
      scalar time=func::pow(scalar(n)*m_sampleTime,m_jordanIndex[row])*scalar(den);
      return -time*func::c_pow(coef,n);
    }
    if (n<m_jordanIndex[row]) return complexS(0,0);
    if (func::isZero(func::norm2(coef-ms_complexOne))) {
      complexS mult(binomial(n+1,m_jordanIndex[row]+1),0);
      return mult;
    }
    complexS mult(binomial(n,m_jordanIndex[row]),0);
    return -mult*func::c_pow(coef,n-m_jordanIndex[row]);
  }
  if (m_jordanIndex[row]==0) {
    if (n==1) return coef;
    return func::c_pow(coef,n);
  }
  if (ms_continuous) {
    int den=m_jordanIndex[row];
    for (int i=2;i<m_jordanIndex[row];i++) den*=i;
    scalar time=func::pow(scalar(n)*m_sampleTime,m_jordanIndex[row])*scalar(den);
    return time*func::c_pow(coef,n);
  }
  if (n<m_jordanIndex[row]) return complexS(0,0);
  complexS mult(binomial(n,m_jordanIndex[row]),0);
  return mult*func::c_pow(coef,n-m_jordanIndex[row]);
}

template <class scalar>
scalar AbstractMatrix<scalar>::condPow(scalar coef,const powerS n,int row)
{
  if (row>=m_dimension) {
    if (m_inputType==eParametricInputs) row-=m_dimension;
    else {
      coef=m_foldedEigenValues.coeff(row-m_dimension,row-m_dimension);
    }
    if (m_jordanIndex[row]==0) {
      if (func::isZero(coef-ms_one)) return scalar(n);
      return ms_one-func::pow(coef,n);
    }
    if (ms_continuous) {
      int den=m_jordanIndex[row];
      for (int i=2;i<m_jordanIndex[row];i++) den*=i;
      scalar time=func::pow(scalar(n)*m_sampleTime,m_jordanIndex[row])/scalar(den);
      return -time*func::pow(coef,n);
    }
    if (n<m_jordanIndex[row])  return 0;
    if (func::isZero(coef-ms_one)) return binomial(n+1,m_jordanIndex[row]+1);
    return -binomial(n,m_jordanIndex[row])*func::pow(coef,n-m_jordanIndex[row]);
  }
  if (m_jordanIndex[row]==0) return func::pow(coef,n);
  if (ms_continuous) {
    int den=m_jordanIndex[row];
    for (int i=2;i<m_jordanIndex[row];i++) den*=i;
    scalar result=func::pow(scalar(n)*m_sampleTime,m_jordanIndex[row])/scalar(den);
    return result*func::pow(coef,n);
  }
  if (n<m_jordanIndex[row])  return 0;
  return binomial(n,m_jordanIndex[row])*func::pow(coef,n-m_jordanIndex[row]);
}

template <class scalar>
scalar AbstractMatrix<scalar>::diffPow(scalar coef,const powerS n,int row)
{
  if (row>=m_dimension) {
    if (m_inputType==eParametricInputs) row-=m_dimension;
    else {
      coef=m_foldedEigenValues.coeff(row-m_dimension,row-m_dimension);
    }
    if (m_jordanIndex[row]==0) {
      if (func::isZero(coef-ms_one)) return ms_one;
      return (ms_continuous?-log(coef):(ms_one-coef))*func::pow(coef,n);
    }
    if (ms_continuous) {
      int den=m_jordanIndex[row];
      for (int i=2;i<m_jordanIndex[row];i++) den*=i;
      scalar time=func::pow(scalar(n)*m_sampleTime,m_jordanIndex[row]-1)*scalar(m_jordanIndex[row])/scalar(den);
      return -time*log(coef)*func::pow(coef,n);
    }
    if (n<m_jordanIndex[row])  return 0;
    if (func::isZero(coef-ms_one)) {
      return binomial(n+1,m_jordanIndex[row]+1)-binomial(n,m_jordanIndex[row]+1);
    }
    return (binomial(n,m_jordanIndex[row])-binomial(n+1,m_jordanIndex[row])*coef)*func::pow(coef,n-m_jordanIndex[row]);
  }
  if (m_jordanIndex[row]==0) return (ms_continuous?log(coef):(coef-ms_one))*func::pow(coef,n);
  if (ms_continuous) {
    int den=m_jordanIndex[row];
    for (int i=2;i<m_jordanIndex[row];i++) den*=i;
    scalar result=scalar(n)*m_sampleTime*log(coef)+scalar(m_jordanIndex[row]);
    return result*func::pow(scalar(n)*m_sampleTime,m_jordanIndex[row]-1)*func::pow(coef,n)/scalar(den);
  }
  if (n<m_jordanIndex[row]) return 0;
  return (binomial(n+1,m_jordanIndex[row])*coef-binomial(n,m_jordanIndex[row]))*func::pow(coef,n-m_jordanIndex[row]);
}

/// Calculates the expected iteration of coefficient to obtain value
template <class scalar>
typename AbstractMatrix<scalar>::powerS AbstractMatrix<scalar>::condLog(const refScalar &coef,refScalar value,int row,powerS &range)
{
  range=0;
  if (row>=m_dimension) {
    if (m_inputType==eParametricInputs) row-=m_dimension;
    else {
      if (func::isPositive(value)) value/=func::toCentre(this->m_foldedBinomialMultipliers.coeff(row-m_dimension));
      value=func::ms_1-value;
      if (func::isNegative(value)) return 0;
      return func::toInt(func::log(coef,value));
    }
    if (m_jordanIndex[row]==0) {
      if (abs(coef-ms_one)<m_zero) return func::toInt(value);
      value=func::ms_1-value;
      if (func::isNegative(value)) return 0;
      return func::toInt(func::log(coef,value));
    }
    range=m_jordanIndex[row]-1;
    if (func::isZero(value)) return 1;
    if (abs(coef-ms_one)<m_zero) {
      for (int i=2;i<=m_jordanIndex[row]+1;i++) value*=i;
      refScalar expected=pow(value,1/m_jordanIndex[row]+1);
      return func::toInt(expected);
    }
    value=-value;
    return binomialCondLog(coef,value,row,range);
  }
  if (m_jordanIndex[row]==0) return func::toInt(func::log(coef,value));
  range=m_jordanIndex[row]-1;
  if (func::isZero(value)) return 1;
  return binomialCondLog(coef,value,row,range);
}

/// Calculates the expected iteration of coefficient to obtain value for a jordan diagonal
template <class scalar>
typename AbstractMatrix<scalar>::powerS AbstractMatrix<scalar>::binomialCondLog(const refScalar &coef,refScalar value,int row,powerS &range)
{
  for (int i=2;i<=m_jordanIndex[row];i++) value*=i;
  value/=func::pow(coef,m_jordanIndex[row]);
  powerS low,high;
  if (coef>func::ms_1) {
    high=func::toInt(func::log(coef,value));
    refScalar bin=func::toCentre(binomial(high,m_jordanIndex[row]));
    low=func::toInt(func::log(coef,value/bin));
  }
  else {
    low=func::toInt(pow(value,1/m_jordanIndex[row]));
    refScalar bin=func::toCentre(binomial(low,m_jordanIndex[row]));
    high=func::toInt(func::log(coef,value/bin));
  }
  range=high-low;
  return low;
}


template <class scalar>
void AbstractMatrix<scalar>::fillDirection(const int row,const scalar &min,const scalar &max)
{
  if (m_pos<m_iterations.size()) m_iterations[m_pos]=iteration_pair(row,-1,0);
  m_directions.coeffRef(m_pos,row)=1;
  m_supports.coeffRef(m_pos++,0)=max;
  if (m_pos<m_iterations.size()) m_iterations[m_pos]=iteration_pair(row,-1,0);
  m_directions.coeffRef(m_pos,row)=-1;
  m_supports.coeffRef(m_pos++,0)=-min;
}

template <class scalar>
void AbstractMatrix<scalar>::fillDirections(const int row1,const int row2,const scalar &dir1,const scalar &dir2,const scalar &min,const scalar &max,const powerS iter)
{
  if (m_pos<m_iterations.size()) m_iterations[m_pos]=iteration_pair(row1,row2,iter);
  m_supports.coeffRef(m_pos,0)=-min;
  m_directions.coeffRef(m_pos,row1)=-dir1;
  m_directions.coeffRef(m_pos++,row2)=-dir2;
  if (m_pos<m_iterations.size()) m_iterations[m_pos]=iteration_pair(row1,row2,iter);
  m_supports.coeffRef(m_pos,0)=max;
  m_directions.coeffRef(m_pos,row1)=dir1;
  m_directions.coeffRef(m_pos++,row2)=dir2;
}

template <class scalar>
void AbstractMatrix<scalar>::fillConjugateSupport(const int row1,const int row2,const scalar &angle,const scalar &max,const powerS iter)
{
  m_directions.coeffRef(m_pos,row1)=func::cosine(angle);
  m_directions.coeffRef(m_pos,row2)=func::sine(angle);
  if (m_pos<m_iterations.size()) m_iterations[m_pos]=iteration_pair(row1,row2,iter);
  m_supports.coeffRef(m_pos++)=max;
}

template <class scalar>
void AbstractMatrix<scalar>::fillSupportFromPoints(const int row1,const int row2,const scalar &x1,const scalar &y1,const scalar &x2,const scalar &y2,const scalar &xRef,const scalar &yRef,const powerS iter)
{
  scalar angle=func::invtan(y2-y1,x2-x1)+func::const_pi(this->ms_half);
  scalar max=y1*func::sine(angle)+x1*func::cosine(angle);
  scalar out=yRef*func::sine(angle)+xRef*func::cosine(angle);
  out-=max;
  if (func::isPositive(out)) {
    angle+=func::const_pi(ms_one);
    max=-max;
  }
  fillConjugateSupport(row1,row2,angle,max,iter);
}

// Finds the set of iterations that define the envelope of the conjugate pair
template <class scalar>
bool AbstractMatrix<scalar>::findConjugateBounds(const int row,powerS iter,powerS &start,powerS &end)
{
  complexS coef=m_eigenValues.coeff(row,row);
  scalar angle=func::invtan(coef.imag(),coef.real());
  scalar rad=func::norm2(coef);
  scalar mag=-log(rad);
  scalar diffAngle=func::invtan(angle,mag);
  scalar cos=func::cosine(diffAngle);
  scalar quartFreq=abs(func::const_pi(this->ms_half)/angle);
  powerS offset=func::toInt(trunc(4*func::toLower(quartFreq)));
  offset+=m_jordanIndex[row]+1;
  start=(func::isPositive(rad-ms_one)) ? iter : 1;
  end=func::isPositive(rad-ms_one) ? ((iter>offset) ? iter-offset : 0) : ((iter>offset) ? offset : iter);
  int dir=((end-start)>0) ? 1 : -1;
  powerS bot=end-dir*func::toInt(func::toUpper(quartFreq));
  if ((bot-start)*dir<0) return true;
  complexS coef2=(start==1) ? coef : condPow(coef,start,row);

  //iteratively find (r^{n-1} = cos(n angle)) -> sup_{\lambda}(\lambda^n)=0
  powerS top=end;
  powerS last=(bot+top)/2;
  while((last!=bot) && (last!=top)) {
    complexS powCoef=condPow(coef,last,row);//func::c_pow(coef,last);?
    scalar powAngle=func::invtan(powCoef.imag(),powCoef.real())+diffAngle;
    scalar powMag=func::norm2(powCoef);
    scalar max=powMag*cos;
    scalar out=coef2.imag()*func::sine(powAngle)+coef2.real()*func::cosine(powAngle);
    out-=max;
    char sign=func::hardSign(out);
    if (sign<0) bot=last;
    if (sign>=0) top=last;
    last=(bot+top)/2;
  }
  if (top==end) return true;
  end=last;
  return false;
}

template <class scalar>
void AbstractMatrix<scalar>::fillConjugateSupportFromIter(const int row1,const int row2,powerS iter)
{
  complexS coef=m_eigenValues.coeff(row1,row1);
  complexS powCoef=condPow(coef,iter,row1);
  scalar angle=func::invtan(coef.imag(),coef.real());
  scalar powAngle=func::invtan(powCoef.imag(),powCoef.real());
  scalar mag=-log(func::norm2(coef));
  scalar powMag=func::norm2(powCoef);
  scalar diffAngle=func::invtan(angle,mag);
  if (func::isPositive(diffAngle-func::ms_pi)) diffAngle-=func::ms_pi;
  diffAngle=func::ms_pi_2-diffAngle;
  scalar cos=func::cosine(diffAngle);
  scalar max=powMag*cos;
  fillConjugateSupport(row1,row2,powAngle+diffAngle,max,iter);
}

template <class scalar>
void AbstractMatrix<scalar>::fillConjugateSupportsFromIter(const int row1,const int row2,powerS iter,int precision)
{
  powerS start,end;
  complexS coef=m_eigenValues.coeff(row1,row1);
  scalar angle=func::invtan(coef.imag(),coef.real());
  if (!findConjugateBounds((row1>row2) ? row2 : row1,iter,start,end))
  {
    //We could refine the abstraction here
  }
  if (abs(angle)>func::ms_pi_2) {
    coef=condPow(coef,start,row1);
    scalar max=func::norm2(coef);
    fillDirection(row1,-max,max);
    fillDirection(row2,-max,max);
  }
  int dir=((end-start)>0) ? 1 : -1;
  refScalar iterationStep=(end-start)/precision;
  if (iterationStep<1) {
    iterationStep=1;
    precision=abs(end-start);
  }
  for (refScalar i=0;i<=precision;i++) {
    powerS iter1=start+dir*func::toInt(floor(i*iterationStep));
    fillConjugateSupportFromIter(row1,row2,iter1);
  }
}

template <class scalar>
void AbstractMatrix<scalar>::fillChordSupportFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter)
{
  scalar start1=condPow(mag1,1,row1);
  scalar start2=condPow(mag2,1,row2);
  scalar end1=condPow(mag1,iter,row1);
  scalar end2=condPow(mag2,iter,row2);
  powerS iter2=(iter>4) ? iter>>1 : iter-1;
  scalar mid1=condPow(mag1,iter2,row1);
  scalar mid2=condPow(mag2,iter2,row2);
  scalar angle=func::invtan(end2-start2,end1-start1)+func::const_pi(this->ms_half);
  scalar max=start2*func::sine(angle)+start1*func::cosine(angle);
  scalar out=mid2*func::sine(angle)+mid1*func::cosine(angle);
  out-=max;
  if (func::isPositive(out)) {
    angle+=func::const_pi(ms_one);
    max=-max;
  }
  fillConjugateSupport(row1,row2,angle,max,iter);
  char sign=func::hardSign(mag1-mag2);
  if (sign==0) {
    angle+=func::const_pi(ms_one);
    max=-max;
  }
  else if (rotates(row1)) angle=func::ms_pi-angle;
  else if (rotates(row2)) angle=func::ms_2_pi-angle;
  else return;
  fillConjugateSupport(row1,row2,angle,max,iter);
}

template <class scalar>
void AbstractMatrix<scalar>::fillSupportFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter)
{
#if 0
  {
    powerS iter2=iter+1;
    scalar x1=condPow(mag1,iter1,row1);
    scalar y1=condPow(mag2,iter1,row2);
    scalar x2=condPow(mag1,iter2,row1);
    scalar y2=condPow(mag2,iter2,row2);
    if (iter1==1) {
      scalar x3=condPow(mag1,3,row1);
      scalar y3=condPow(mag2,3,row2);
      fillSupportFromPoints(row1,row2,x1,y1,x2,y2,x3,y3,iter1);
    }
    else fillSupportFromPoints(row1,row2,x1,y1,x2,y2,mag1,mag2,iter1);
    return;
  }
#endif
  scalar xdif=diffPow(mag1,iter,row1);
  scalar ydif=diffPow(mag2,iter,row2);
  scalar angle=func::invtan(ydif,xdif)+func::const_pi(this->ms_half);
  scalar x1=condPow(mag1,iter,row1);
  scalar y1=condPow(mag2,iter,row2);
  scalar max=y1*func::sine(angle)+x1*func::cosine(angle);
  scalar out;
  if (iter<=2) out=condPow(mag2,3,row2)*func::sine(angle)+condPow(mag1,3,row1)*func::cosine(angle);
  else out=mag2*func::sine(angle)+mag1*func::cosine(angle);
  out-=max;
  if (func::isPositive(out)) {
    angle+=func::const_pi(ms_one);
    max=-max;
  }
  fillConjugateSupport(row1,row2,angle,max,iter);
  if ((m_conjugatePair[row1]>=0) || (func::isNegative(mag1))) angle=func::const_pi(ms_one)-angle;
  else if ((m_conjugatePair[row2]>=0) || (func::isNegative(mag2))) angle=-angle;
  else return;
  fillConjugateSupport(row1,row2,angle,max,iter);
}

template <class scalar>
void AbstractMatrix<scalar>::fillSupportsFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter,int precision)
{
  precision=(1<<precision)-2;//Number of faces grows geometrically
  if (precision<1) return;
  if ((m_conjugatePair[row1]>=0) && (m_conjugatePair[row2]>=0) && (m_conjugatePair[row1]!=row2)) return;
  char sign=func::hardSign(mag1-mag2);
  if (rotates(row1) && rotates(row2) && (m_conjugatePair[row1]!=row2))
    return; //cross conjugate
  if (m_conjugatePair[row1]==row2) {
    fillConjugateSupportsFromIter(row1,row2,iter,precision);
    return;
  }
  if ((!rotates(row1) || (sign<=0)) && (!rotates(row2) || (sign>=0)))
    fillChordSupportFromIter(row1,row2,mag1,mag2,iter);
  if ((rotates(row1) && (sign<0)) || (rotates(row2) && (sign>0)) || (sign==0))
    return;

  scalar maga=condPow(mag1,iter,row1);
  scalar magb=condPow(mag2,iter,row2);
  while(func::isZero(maga) && func::isZero(magb) && (iter>0)) {
    iter>>=1;
    maga=condPow(mag1,iter,row1);
    magb=condPow(mag2,iter,row2);
  }

  refScalar iterationStep=iter/precision;
  if (iterationStep<1) {
    iterationStep=1;
    precision=iter;
  }
  int firstIter=1;
  if (m_jordanIndex[row1%m_dimension]>0) firstIter=m_jordanIndex[row1%m_dimension];
  if (m_jordanIndex[row2%m_dimension]>0) firstIter=m_jordanIndex[row2%m_dimension];
  for (int i=firstIter;i<=precision;i++) {
    powerS iter1=func::toInt(floor(i*iterationStep));
    fillSupportFromIter(row1,row2,mag1,mag2,iter1);
  }

}

template <class scalar>
void AbstractMatrix<scalar>::fillSemiConjugateSupportFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter)
{
  fillSupportFromIter(row1,row2,mag1,mag2,iter);
}

template <class scalar>
bool AbstractMatrix<scalar>::fillLastConjugateSupportFromPoints(int row1,int row2,scalar x1,scalar y1,scalar x2,scalar y2,scalar xRef,scalar yRef,bool hasLastQuarter,const powerS iter)
{
  scalar angle=func::invtan(y2-y1,x2-x1)+func::const_pi(this->ms_half);
  scalar max=y1*func::sine(angle)+x1*func::cosine(angle);
  scalar out=yRef*func::sine(angle)+xRef*func::cosine(angle);
  char sign=func::hardSign(max);
  if (sign<0) {//the vector is in the wrong direction rotate 180deg
    angle+=func::const_pi(ms_one);
    max=-max;
    out=-out;
  }
  else if (sign==0) {// Undecided, overapproximate by error.
    max+=m_zero;
    out+=m_zero;
  }
  out-=max;
  sign=func::hardSign(out);
  if (hasLastQuarter) {
    //If the next to last point would be excluded by the restriction, ignore
    if (sign>0) return false;
    //If the next to last point is undecided around the restriction, make sure it remains inside
    if (sign==0) max+=m_zero;
  }
  else if (sign>0) {
    //Revert the bound to close the half-circle
    angle+=func::const_pi(ms_one);
    max=y1*func::sine(angle)+x1*func::cosine(angle);
  }
  else if (sign==0) {
    //should never happen
    func::imprecise(out,func::ms_0,"Conjugate Zeros");
    return false;
  }
  else {
    //should never happen but no error
    return false;
  }
  fillConjugateSupport(row1,row2,angle,max,iter);
  return true;
}

template <class scalar>
bool AbstractMatrix<scalar>::testConjugateSupportFromPoints(const scalar &x1,const scalar &y1,const scalar &x2,const scalar &y2,const scalar &xExt,const scalar &yExt)
{
  scalar angle=func::invtan(y2-y1,x2-x1)+func::const_pi(this->ms_half);
  scalar max=y1*func::sine(angle)+x1*func::cosine(angle);
  scalar ext=yExt*func::sine(angle)+xExt*func::cosine(angle);
  char sign=func::hardSign(max);
  if (sign<0) {
    angle+=func::const_pi(ms_one);
    max=-max;
    ext=-ext;
  }
  else if (sign==0) {
    //should never happen
    func::imprecise(max,func::ms_0,"Conjugate Zeros");
  }
  ext-=max;
  sign=func::hardSign(ext);
  if (sign>0) return false;
  //if ext is zero, the case is dealt when calculating the support function
  return true;
}

template <class scalar>
bool AbstractMatrix<scalar>::fillConjugateSupportFromPoints(const int row1,const int row2,const scalar &x1,const scalar &y1,const scalar &x2,const scalar &y2,const scalar &xExt,const scalar &yExt,const powerS iter)
{
  scalar angle=func::invtan(y2-y1,x2-x1)+func::const_pi(this->ms_half);
  scalar max=y1*func::sine(angle)+x1*func::cosine(angle);
  scalar ext=yExt*func::sine(angle)+xExt*func::cosine(angle);
  char sign=func::hardSign(max);
  if (sign<0) {
    angle+=func::const_pi(ms_one);
    max=-max;
    ext=-ext;
  }
  else if (sign==0) {
    //should never happen
    func::imprecise(max,func::ms_0,"Conjugate Zeros");
  }
  ext-=max;
  sign=func::hardSign(ext);
  if (sign>0) return false;
  if (sign==0) max+=m_zero;
  fillConjugateSupport(row1,row2,angle,max,iter);
  return true;
}

template <class scalar>
void AbstractMatrix<scalar>::fillLinearSupportFromPoints(const int row1,const int row2,const scalar &min1,const scalar &max1,const scalar &min2,const scalar &max2,const powerS iter)
{
  scalar angle=func::invtan(max2-min2,max1-min1)+func::const_pi(this->ms_half);
  scalar min=min2*func::sine(angle)+min1*func::cosine(angle);
  scalar max=max2*func::sine(angle)+max1*func::cosine(angle);
  max=func::getHull(min,max);
  min=-func::toLower(max)+this->m_largeZero;
  max=func::toUpper(max)+this->m_largeZero;
  fillConjugateSupport(row1,row2,angle,max,iter);
  angle+=func::const_pi(ms_one);
  fillConjugateSupport(row1,row2,angle,min,iter);
}

template <class scalar>
void AbstractMatrix<scalar>::fillQuadraticSupport(int row1,int row2,scalar mag1,scalar mag2,powerS iteration,int precision)
{
  precision=(1<<precision)-2;//Number of faces grows geometrically
  if (precision<1) return;

  scalar maga=condPow(mag1,iteration,row1);
  scalar magb=condPow(mag2,iteration,row2);
  while(func::isZero(maga) && func::isZero(magb)) {
    iteration>>=1;
    maga=condPow(mag1,iteration,row1);
    magb=condPow(mag2,iteration,row2);
  }

  refScalar iterationStep=iteration/precision;
  if (iterationStep<1) {
    iterationStep=1;
    precision=iteration;
  }
  int firstIter=1;
  if (m_jordanIndex[row1]>0) firstIter=m_jordanIndex[row1];
  if (m_jordanIndex[row2]>0) firstIter=m_jordanIndex[row2];
  for (int i=firstIter;i<precision;i++) {
    powerS iter1=func::toInt(floor(i*iterationStep));
    fillSupportFromIter(row1,row2,mag1,mag2,iter1);
  }
}

template <class scalar>
void AbstractMatrix<scalar>::fillQuadraticConjugateSupport(int row1,int row2,scalar mag1,scalar mag2,powerS iteration,int precision)
{
  scalar x1=condPow(mag1,1,row1);
  scalar y1=condPow(mag2,1,row2);
  scalar x2=condPow(mag1,iteration,row1);
  scalar y2=condPow(mag2,iteration,row2);
  scalar x3=condPow(mag1,2,row1);
  scalar y3=condPow(mag2,2,row2);  
/*  if (((row2<m_dimension) || (m_inputType<eVariableInputs)) && func::isZero(mag1-mag2)) {
    fillSupportFromIter(row1,row2,mag1,mag2,iteration);
/*    scalar angle=-func::ms_pi_2/2;
    scalar max=abs(func::getHull(x1-y1,x2-y2));
    fillConjugateSupport(row1,row2,angle,max,iteration);
    angle-=func::ms_pi_2;
    fillConjugateSupport(row1,row2,angle,max,iteration);*
    return;
  }*/

  scalar angle=func::invtan(y2-y1,x2-x1)-func::const_pi(this->ms_half);//invtan returns positive values (0-pi)
  scalar max=y1*func::sine(angle)+x1*func::cosine(angle);
  scalar max2=y2*func::sine(angle)+x2*func::cosine(angle);
  max=func::getHull(max,max2);
  scalar out=y3*func::sine(angle)+x3*func::cosine(angle);
  max-=out;
  if (func::isNegative(max)) {//TODO: need to split for jordan blocks
    precision=(1<<precision)-2;//Number of faces grows geometrically
    if (precision<1) return;
    scalar mag=condPow(mag1,iteration,row1);
    while(func::isZero(mag)) {
      iteration>>=2;
      mag=condPow(mag1,iteration,row1);
    }
    refScalar iterationStep=iteration/precision;
    if (iterationStep<1) {
      iterationStep=1;
      precision=iteration;
    }
    for (int i=1;i<precision;i++) {
      powerS iter1=func::toInt(floor(i*iterationStep));
      fillSupportFromIter(row1,row2,mag1,mag2,iter1);
    }
    return;
  }
//  fillSupportFromIter(row1,row2,mag1,mag2,iteration);
  fillSupportFromPoints(row1,row2,x1,y1,x2,y2,0,y1,1);
  fillSupportFromPoints(row1,row2,-x1,y1,-x2,y2,0,y1,1);
}

template <class scalar>
void AbstractMatrix<scalar>::findConjugateSupports(const int row,const complexS &coef,const powerS iteration,int precision)
{
  if (m_conjugatePair[row]<row) return;  
  int row2=row+1;
  if (iteration<=2) {
    complexS p1=condPow(coef,1,row);
    scalar minR=p1.real();
    scalar minI=p1.imag();
    if (iteration==2) {
      complexS p2=condPow(coef,2,row);
      scalar maxR=p2.real();
      scalar maxI=p2.imag();
      fillLinearSupportFromPoints(row,row2,minR,maxR,minI,maxI,iteration);
      if (func::isPositive(minR-maxR)) swapValues(minR,maxR);
      if (func::isPositive(minI-maxI)) swapValues(minI,maxI);
      fillDirection(row,minR,maxR);
      fillDirection(row2,minI,maxI);
    }
    else {
      fillDirection(row,minR,minR);
      fillDirection(row2,minI,minI);
    }
    return;
  }  
  scalar mag=func::norm2(coef);
  if (ms_continuous) {
    fillSupportsFromIter(row,row2,mag,mag,iteration,precision);
    return;
  }
  scalar angle=func::invtan(coef.imag(),coef.real());
  scalar quartFreq=abs(func::const_pi(this->ms_half)/angle);
  powerS offset=func::toInt(trunc(4*func::toLower(quartFreq)));
  offset+=m_jordanIndex[row]+1;
  powerS start=(func::isPositive(mag-ms_one)) ? iteration : 1;
  powerS end=func::isPositive(mag-ms_one) ? ((iteration>offset) ? iteration-offset : 0) : ((iteration>offset) ? offset : iteration);
  int dir=((end-start)>0) ? 1 : -1;
  precision=(1<<precision);//Number of faces grows geometrically
  powerS step=(end-start)/precision;
  if (step==0) step=dir;
  complexS ext=condPow(coef,start+2*dir,row);
  complexS p1=condPow(coef,start,row);
  complexS p2=condPow(coef,start+dir,row);
  fillConjugateSupportFromPoints(row,row2,p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag(),start);
  start+=step;
  ext=condPow(coef,func::isPositive(mag-ms_one) ? iteration : 1,row2);
  while (abs(end-start)>=abs(step)) {
    p1=condPow(coef,start,row);
    p2=condPow(coef,start+dir,row);
    if (!fillConjugateSupportFromPoints(row,row2,p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag(),start)) break;
    start+=step;
  }
  if (abs(end-start)<abs(step)) {
    p1=condPow(coef,end,row);
    p2=condPow(coef,end-dir,row);
    if ((abs(end-start)<=abs(dir)) || fillConjugateSupportFromPoints(row,row2,p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag(),end)) {
      start=end;
      p1=condPow(coef,start,row);
      p2=ext;
      ext=condPow(coef,start-dir,row);
      if (fillLastConjugateSupportFromPoints(row,row2,p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag(),iteration>func::toInt(trunc(3*func::toLower(quartFreq))),start)) return;
      ext=p2;
    }
  }
  powerS base=start-step;
  end=start;
  while (abs(end-base)>1) {
    start=(base+end)/2;
    p1=condPow(coef,start,row);
    p2=condPow(coef,start+dir,row);
    if (testConjugateSupportFromPoints(p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag())) {
      base=start;
    }
    else {
      end=start;
    }
  }
  p1=condPow(coef,base,row);
  p2=condPow(coef,base-dir,row);
  if (testConjugateSupportFromPoints(p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag())) base+=dir;
  p1=condPow(coef,base,row);
  fillSupportFromPoints(row,row2,p1.real(),p1.imag(),ext.real(),ext.imag(),0,0,base);
}

template <class scalar>
void AbstractMatrix<scalar>::wrapUp()
{
  m_directions.conservativeResize(m_pos,m_directions.cols());
  m_supports.conservativeResize(m_pos,1);
  m_iterations.resize(m_pos);
  m_pos=0;
}

/// Finds the point at which each jordan column is maximum
template <class scalar>
void AbstractMatrix<scalar>::findZeniths()
{
  //y_n=binomial(n,k)x^n-k = y_{n-1}*nx/(n-k) -> zenith=k/(1-x)
  m_zeniths.resize(2*m_dimension);
  for (int row=0;row<m_dimension;row++) {
    scalar mag=func::norm2(m_eigenValues.coeff(row,row));
    if ((m_jordanIndex[row]>0) && (func::isNegative(mag-ms_one))) {
      scalar zenith=m_jordanIndex[row];
      zenith/=(ms_one-mag);
      m_zeniths[row]=func::toInt(func::toLower(zenith));
    }
    else m_zeniths[row]=0;
  }
  for (int row=m_dimension;row<2*m_dimension;row++) m_zeniths[row]=0;
}

/// lists the first source row for a folded set of dimensions
template <class scalar>
void AbstractMatrix<scalar>::findUnfolded()
{
  m_unfolded.resize(m_dimension);
  int pos=0;
  for (int i=0;i<m_dimension;i++) {
    if (m_jordanIndex[i]>0) continue;
    if (m_conjugatePair[i]>=0) {
      m_unfolded[pos++]=i;
      i++;
    }
    else if (m_jordanIndex[i+1]>0) m_unfolded[pos++]=i;
  }
  m_unfolded.resize(pos);
}

/// Finds the frequency of rotation of each conjugate pair
template <class scalar>
void AbstractMatrix<scalar>::findFrequencies()
{
  m_freq.assign(2*m_dimension,0);
  for (int row=0;row<m_dimension;row++) {
    if (m_conjugatePair[row]>row) {
      complexS coef=m_eigenValues.coeff(row,row);
      scalar angle=func::invtan(coef.imag(),coef.real());
      m_freq[row++]=func::toInt(2*func::toUpper(abs(func::const_pi(ms_one)/angle)));
      m_freq[row]=m_freq[row-1];
    }
  }
}

/// Indicates if the matrix dynamics are divergent
/// @param strict if true returns only true if no eigenvalues are convergent
template <class scalar>
bool AbstractMatrix<scalar>::isDivergent(const bool strict,scalar speed)
{
  for (int i=0;i<m_dimension;i++) {
    scalar eigenNorm=func::normsq(m_eigenValues.coeff(i,i));
    char sign=func::hardSign(eigenNorm-speed);
    if (strict && (sign<0)) return false;
    else if (!strict && (sign>=0)) return true;
  }
  return strict;
}

/// Retrieves the largest eigenvalue norm
template <class scalar>
scalar AbstractMatrix<scalar>::largestEigenNorm()
{
  scalar max=0;
  for (int i=0;i<m_dimension;i++) {
    scalar eigenNorm=func::norm2(m_eigenValues.coeff(i,i));
    char sign=func::hardSign(eigenNorm-max);
    if (sign>0) max=eigenNorm;
  }
  return max;
}

/// Finds the coefficient, magnitude, maximum, and minimum for the abstract vector at row
template <class scalar>
void AbstractMatrix<scalar>::findCoeffBounds(int row,powerS iteration,complexS &coef,scalar &mag,scalar &min,scalar &max)
{
  if (row<m_dimension) coef=m_eigenValues.coeff(row,row);
  else {
    int transRow=(m_inputType>=eVariableInputs) ? m_unfolded[row-m_dimension] : row-m_dimension;
    coef=m_eigenValues.coeff(transRow,transRow);
    if (m_inputType>=eVariableInputs) {// && (func::isPositive(func::norm2(coef)-ms_one))) {
      coef=m_foldedEigenValues(transRow,transRow);
    }
  }
  if ((row>=m_dimension) && (m_inputType>=eVariableInputs)) {
    scalar rad=func::norm2(coef);
    min=condPow(rad,1,row);
    max=condPow(rad,iteration,row);
  }
  else if (m_conjugatePair[row]<0) {
    min=condPow(coef.real(),1,row);
    max=condPow(coef.real(),iteration,row);
  }
  else if (iteration>2) {
    min=func::norm2(condPow(coef,1,row));
    max=func::norm2(condPow(coef,iteration,row));
  }
  else if (m_conjugatePair[row]>row) {
    min=condPow(coef,1,row).real();
    max=condPow(coef,iteration,row).real();
  }
  else {
    min=-condPow(coef,1,row).imag();
    max=-condPow(coef,iteration,row).imag();
  }
  mag=func::norm2(coef);
  if ((m_conjugatePair[row]<0) && ((row<m_dimension) || (m_inputType<eVariableInputs)) && (func::isNegative(coef.real()))) {
    scalar sum=min+max;
    char sign=func::hardSign(sum);
    if (max<min) sign=-sign;
    if (sign>0) min=-max;
    else if (sign<0) max=-min;
  }
}

/// Retrieves the last calculated dynamics
template <class scalar>
AbstractPolyhedra<scalar>& AbstractMatrix<scalar>::getAbstractDynamics(const inputType_t inputType)
{
  if (inputType>=eVariableInputs) return m_abstractRoundDynamics;
  if (this->m_hasOnes && inputType==eParametricInputs) return m_abstractInputDynamics;
  return m_abstractDynamics;
}

/// retrieves the abstract dynamics matrix for a given iteration (n)
template <class scalar>
AbstractPolyhedra<scalar>& AbstractMatrix<scalar>::getAbstractDynamics(const powerS iteration,int precision,const inputType_t inputType,const bool normalised)
{
  boost::timer timer;
  if (precision<1) precision=1;
  int dimension=m_dimension;
  m_inputType=inputType;
  if (inputType>=eVariableInputs) dimension+=m_foldedEigenValues.rows();
  else if (this->m_hasOnes && (inputType==eParametricInputs)) dimension+=m_dimension;
  m_maxIterations=iteration;
  powerS trueMaxIterations=calculateMaxIterations(iteration);
  if (m_hasMultiplicities) this->calculateBoundedEigenError(trueMaxIterations);
  findUnfolded();
  findZeniths();
  findFrequencies();
  AbstractPolyhedra<scalar>& result=getAbstractDynamics(inputType);
  result.changeDimension(dimension);
  m_eigenCloud.resize(0,0);
  m_roundEigenCloud.resize(0,0);
  m_supports.resize((1<<precision)*dimension*dimension,1);
  m_directions.resize((1<<precision)*dimension*dimension,dimension);
  m_iterations.resize(m_supports.rows());
  //if (precision>2) getEigenCloud(trueMaxIterations);
  m_pos=0;
  m_firstVarBlock=-1;
  complexS coef,coef2;
  for (int row=0;row<dimension;row++)
  {
    if (row==m_dimension) m_firstVarBlock=m_pos;
    scalar mag,min1,max1;
    findCoeffBounds(row,iteration,coef,mag,min1,max1);
    scalar min=min1;
    scalar max=max1;
    checkRange(row,iteration,func::norm2(coef),min,max);
    if (m_conjugatePair[row]>=0) findConjugateSupports(row,coef,iteration,precision);
    else {
      if (func::isNegative(coef.real())) {
        scalar sum=min+max;
        char sign=func::hardSign(sum);
        if (sign>0) min=-max;
        else if (sign<0) max=-min;
      }
      fillDirection(row,min,max);
    }
    if ((iteration<2) || (precision<2)) continue;
    if (func::isZero(mag)) continue;
    if (func::isZero(max-min)) continue;
    if ((row<m_dimension) && (func::isZero(mag-func::ms_1))) continue;
    int maxDim=((inputType==eVariableOnlyInputs) && (row<m_dimension)) ? m_dimension : dimension;
    for (int row2=row+((m_conjugatePair[row]>row) ? 2 : 1);row2<maxDim;row2++) {
      if (row2<m_dimension) coef2=m_eigenValues.coeff(row2,row2);
      else {
        int transRow2=(inputType>=eVariableInputs) ? m_unfolded[row2-m_dimension]: row2-m_dimension;
        coef2=m_eigenValues.coeff(transRow2,transRow2);//TODO: the rotations and dilations are wrong at the row value
        if ((inputType>=eVariableInputs) && (func::isPositive(func::norm2(coef2)-ms_one))) {
          coef=m_foldedEigenValues(transRow2,transRow2);
        }
      }
      scalar mag2,min2,max2;
      findCoeffBounds(row2,iteration,coef2,mag2,min2,max2);
      if (ms_continuous) {
        fillSupportsFromIter(row,row2,mag,mag2,iteration,precision);
      }
      else if ((m_conjugatePair[row]>=0) || m_isNegative[row]) {
        if (m_conjugatePair[row2]<0) {
          fillQuadraticConjugateSupport(row,row2,func::norm2(coef),func::norm2(coef2),iteration,precision);
        }
        else fillCrossConjugateSupports(row,row2);
      }
      else if ((m_conjugatePair[row2]>=0) || m_isNegative[row2]) {
        fillQuadraticConjugateSupport(row2,row,func::norm2(coef2),func::norm2(coef),iteration,precision);
      }
      else if ((iteration==2) || func::isZero(max1-max2)) {
        fillLinearSupportFromPoints(row,row2,min1,max1,min2,max2,iteration);
      }
      else {
        scalar out1=condPow(min1,2,row);
        scalar out2=condPow(min2,2,row2);
        fillSupportFromPoints(row,row2,min1,min2,max1,max2,out1,out2,2);
        fillQuadraticSupport(row,row2,func::norm2(coef),func::norm2(coef2),iteration,precision);
      }
    }
  }
  wrapUp();
  if (m_hasMultiplicities) {
    scalar high=func::pow(ms_one+m_error,iteration);
    scalar low=func::pow(ms_one-m_error,iteration);
    scalar relaxation=func::getHull(high,low);
    m_supports*=relaxation;
  }
  result.loadTagged(m_directions,m_supports,m_iterations);
  if (normalised) result.normalise();
  result.setCalculationTime(timer.elapsed()*1000);
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Abstract Dynamics Time",true);
  if (ms_trace_dynamics>=eTraceAbstraction) {
    std::stringstream stream;
    stream << "s=" << iteration << ",l=" << precision;
    result.logTableau(stream.str(),true);
  }
  return result;
}

/// Adds a set of supports at the given iteration in order to refine the abstraction
template <class scalar>
bool AbstractMatrix<scalar>::addSupportsAtIteration(AbstractPolyhedra<scalar>& dynamics,powerS iteration,powerS max)
{
  boost::timer timer;
  complexS coef,coef2;
  int dimension=m_dimension;
  if (m_inputType>=eVariableInputs) dimension+=m_foldedEigenValues.rows();
  else if (this->m_hasOnes && (m_inputType==eParametricInputs)) dimension+=m_dimension;

  m_supports.resize(dimension*dimension,1);
  m_directions.resize(dimension*dimension,dimension);
  m_pos=0;
  for (int row=0;row<dimension;row++)
  {
    if (row<m_dimension) coef=m_eigenValues.coeff(row,row);
    else {
      int transRow=(m_inputType>=eVariableInputs) ? m_unfolded[row-m_dimension] : row-m_dimension;
      coef=m_eigenValues.coeff(transRow,transRow);
      if ((m_inputType>=eVariableInputs) && (func::isPositive(func::norm2(coef)-ms_one))) {
        coef=m_foldedEigenValues(transRow,transRow);
      }
    }
    if (m_conjugatePair[row]>row) {
      scalar mag=func::norm2(coef);
      int dir=(func::isPositive(mag-ms_one)) ? -1 : 1;
      complexS ext=condPow(coef,func::isPositive(mag-ms_one) ? max : 1,row+1);
      complexS p1=condPow(coef,iteration,row);
      complexS p2=condPow(coef,iteration+dir,row);
      fillConjugateSupportFromPoints(row,row+1,p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag(),iteration);
    }
    for (int row2=row+((m_conjugatePair[row]>row) ? 2 : 1);row2<dimension;row2++) {
      if (row2<m_dimension) coef2=m_eigenValues.coeff(row2,row2);
      else {
        int transRow2=(m_inputType>=eVariableInputs) ? m_unfolded[row2-m_dimension]: row2-m_dimension;
        coef2=m_eigenValues.coeff(transRow2,transRow2);//TODO: the rotations and dilations are wrong at the row value
        if ((m_inputType>=eVariableInputs) && (func::isPositive(func::norm2(coef2)-ms_one))) {
          coef2=m_foldedEigenValues(transRow2,transRow2);
        }
      }
      if (m_conjugatePair[row]>=0) {
        if (m_conjugatePair[row2]<0) {
          fillSemiConjugateSupportFromIter(row,row2,func::norm2(coef),func::norm2(coef2),iteration);
        }
      }
      else if (m_conjugatePair[row2]>=0) {
        fillSemiConjugateSupportFromIter(row2,row,func::norm2(coef2),func::norm2(coef),iteration);
      }
      else {
        fillSupportFromIter(row,row2,func::norm2(coef),func::norm2(coef2),iteration);
      }
    }
  }
  wrapUp();
  if (m_hasMultiplicities) {
    scalar high=func::pow(ms_one+m_error,iteration);
    scalar low=func::pow(ms_one-m_error,iteration);
    scalar relaxation=func::getHull(high,low);
    m_supports*=relaxation;
  }
  dynamics.addTaggedDirection(m_directions,m_supports,m_iterations);
  dynamics.addCalculationTime(timer.elapsed()*1000);
  if (ms_trace_dynamics>=eTraceAbstraction) {
    std::stringstream stream;
    stream << "abs supports n=" << iteration;
    dynamics.logTableau(stream.str());
  }
  return true;
}

/// Adds a set of supports at the given iterations in order to refine the abstraction
template <class scalar>
bool AbstractMatrix<scalar>::addSupportsAtIterations(AbstractPolyhedra<scalar>& dynamics,powerList &iterations,const MatrixS &source)
{
  boost::timer timer;
  complexS coef,coef2;
  int dimension=m_dimension;
  if (m_eigenCloud.rows()<=0) {
    powerS trueMaxIterations=calculateMaxIterations(m_maxIterations);
    if (trueMaxIterations<1000) getEigenCloud(trueMaxIterations);
  }
  if (m_inputType>=eVariableInputs) {
    dimension+=m_foldedEigenValues.rows();
  }
  else if (this->m_hasOnes && (m_inputType==eParametricInputs)) dimension+=m_dimension;

  m_supports.resize(dimension*dimension*iterations.size(),1);
  m_directions.resize(dimension*dimension*(iterations.size()+1),dimension);
  m_iterations.resize(m_supports.rows());
  m_pos=0;
  powerS maxIteration=0;
  typename powerList::iterator it;
  for (it=iterations.begin();it!=iterations.end();it++) {
    powerS iteration=it->first;
    /*int row=it->second.second;
    int pair=m_conjugatePair[row];
    if (pair<row) pair=row;
    for (;row<=pair;row++)*/
    for (int row=0;row<dimension;row++)
    {
      if (row<m_dimension) coef=m_eigenValues.coeff(row,row);
      else {
        int transRow=(m_inputType>=eVariableInputs) ? m_unfolded[row-m_dimension] : row-m_dimension;
        coef=m_eigenValues.coeff(transRow,transRow);
        if ((m_inputType>=eVariableInputs) && (func::isPositive(func::norm2(coef)-ms_one))) {
          coef=m_foldedEigenValues(transRow,transRow);
        }
      }
      if (m_conjugatePair[row]>row) {
        scalar mag=func::norm2(coef);
        powerS iter=iteration;
        int dir=(func::isPositive(mag-ms_one)) ? -1 : 1;
        if (dir>0) {
          powerS count=iter/m_freq[row];
          count*=m_freq[row];
          iter-=count;
          while(iter>m_freq[row]) iter-=m_freq[row];
          if (iter<=0) iter+=m_freq[row];
        }
        complexS ext=condPow(coef,func::isPositive(mag-ms_one) ? m_maxIterations : 1,row+1);
        complexS p1=condPow(coef,iter,row);
        complexS p2=condPow(coef,iter+dir,row);
        fillConjugateSupportFromPoints(row,row+1,p1.real(),p1.imag(),p2.real(),p2.imag(),ext.real(),ext.imag(),iter);
      }

//      for (int row2=0;row2<dimension;row2++) {
      for (int row2=row+((m_conjugatePair[row]>row) ? 2 : 1);row2<dimension;row2++) {
        if ((row2==row) || (row2==m_conjugatePair[row])) continue;
        if (row2<m_dimension) coef2=m_eigenValues.coeff(row2,row2);
        else {
          int transRow2=(m_inputType>=eVariableInputs) ? m_unfolded[row2-m_dimension]: row2-m_dimension;
          coef2=m_eigenValues.coeff(transRow2,transRow2);//TODO: the rotations and dilations are wrong at the row value
          if ((m_inputType>=eVariableInputs) && (func::isPositive(func::norm2(coef2)-ms_one))) {
            coef2=m_foldedEigenValues(transRow2,transRow2);
          }
        }
        if (m_conjugatePair[row]>=0) {
          if (m_conjugatePair[row2]<0) {
            fillSemiConjugateSupportFromIter(row,row2,func::norm2(coef),func::norm2(coef2),iteration);
          }
          else {
            fillCrossConjugateSupportFromIter(row,row2,iteration);
            if (it==iterations.begin()) {
              scalar weight1=source.coeff(0,row);
              scalar weight2=source.coeff(0,row2);
              scalar norm=sqrt(weight1*weight1+weight2*weight2);
              weight1/=norm;
              weight2/=norm;
              fillCrossConjugateSupports(row,row2,weight1,weight2,0);
            }
          }
        }
        else if (m_conjugatePair[row2]>=0) {
          fillSemiConjugateSupportFromIter(row2,row,func::norm2(coef2),func::norm2(coef),iteration);
        }
        else {
          fillSupportFromIter(row,row2,func::norm2(coef),func::norm2(coef2),iteration);
        }
      }
    }
    if (maxIteration<iteration) maxIteration=iteration;
  }

  if (source.cols()>=dimension) {
    MatrixS resource=source.rightCols(dimension);
    wrapUp();
    int size=m_pos;
    m_pos=0;
    for (int i=0;i<size;i++) {
      SVectorS &data=m_directions[i];
      scalar support=func::ms_0;
      for (typename SVectorS::iterator it=data.begin();it!=data.end();it++) {
        support+=it->second*resource.coeff(0,it->first);
      }
      if (func::isNegative(m_supports.coeff(i,0)-support)) {
        m_directions[m_pos]=m_directions[i];
        m_supports.coeffRef(m_pos++,0)=m_supports.coeffRef(i,0);
      }
    }
  }
  wrapUp();
  if (m_hasMultiplicities) {
    scalar high=func::pow(ms_one+m_error,maxIteration);
    scalar low=func::pow(ms_one-m_error,maxIteration);
    scalar relaxation=func::getHull(high,low);
    m_supports*=relaxation;
  }
  dynamics.addTaggedDirection(m_directions,m_supports,m_iterations,true);
  dynamics.addCalculationTime(timer.elapsed()*1000);
  if (ms_trace_dynamics>=eTraceAbstraction) {
    std::stringstream stream;
    it=iterations.begin();
    stream << "abs supports n=" << it->first;
    it++;
    for (;it!=iterations.end();it++) stream << "," << it->first;
    dynamics.logTableau(stream.str());
  }
  return (m_iterations.size()>0);
}

/// Calculates the number of iterations necessary to reacha fixpoint
template <class scalar>
typename AbstractMatrix<scalar>::powerS AbstractMatrix<scalar>::calculateMaxIterations(powerS max)
{
  powerS result=0;
  findZeniths();
  findFrequencies();
  for (int i=0;i<m_dimension;i++) {
    complexS coef=m_eigenValues.coeff(i,i);
    if (func::isPositive(func::norm2(coef)-ms_one)) return (max<func::ms_infPower) ? max: func::ms_infPower;
    if (m_zeniths[i]+m_freq[i]>result) result=m_zeniths[i]+m_freq[i];
  }
  return (max<result) ? max : result;
}

/// Finds the corresponding iteration that generates dynamics close to the given point
template <class scalar>
void AbstractMatrix<scalar>::findIterations(const MatrixS &point,powerList &iterations,bool isVector)
{
  complexS coef;
  powerS range;
  for (int col=0;col<point.cols();col++) {
    if (col<m_dimension) coef=m_eigenValues.coeff(col,col);
    else {
      int transCol=(m_inputType>=eVariableInputs) ? m_unfolded[col-m_dimension] : col-m_dimension;
      coef=m_eigenValues.coeff(transCol,transCol);
      if ((m_inputType>=eVariableInputs) && (func::isPositive(func::norm2(coef)-ms_one))) {
        coef=m_foldedEigenValues(transCol,transCol);
      }
    }
    refScalar rad=func::toCentre(func::norm2(coef));
    powerS iteration;
    if (m_conjugatePair[col]>=0) {
      range=0;
      scalar coeffAngle=func::invtan(coef.imag(),coef.real());
      scalar angle=func::invtan(point.coeff(0,col+1),point.coeff(0,col));
      char dir=func::hardSign(coeffAngle);
      char sign=func::hardSign(angle);
      if (sign!=dir) {
        if (sign<0) angle+=func::ms_2_pi;
        else        angle-=func::ms_2_pi;
      }
      refScalar finalSteps=func::toCentre(angle/coeffAngle);
      iteration=func::toInt(finalSteps);
      if (rad>func::ms_1) {
        refScalar tau=func::toCentre(coeffAngle/func::ms_2_pi);
        tau*=m_maxIterations;
        powerS mult=func::toInt(tau);
        mult*=m_freq[col];
        iteration+=mult;
      }
      col++;
    }
    else if (((rad>func::ms_1) || (!func::isZero(point.coeff(0,col)))) && !isVector) {
      iteration=condLog(rad,func::toCentre(point.coeff(0,col)),col,range);
    }
    else {
      iteration=0;
      range=0;
    }
    while ((iteration<2) && (range>0)) {
      range--;
      iteration++;
    }
    if (iteration>1) iterations[iteration]=std::pair<int,powerS>(col,range);
  }
}

/// Finds the corresponding iteration that generates dynamics in between existing supports
template <class scalar>
void AbstractMatrix<scalar>::findIterations(AbstractPolyhedra<scalar> &dynamics,powerList &iterations)
{
  const std::vector<int>& rows=dynamics.getSupportRows();
  const std::vector<iteration_pair> &sourceIterations=dynamics.m_iterations;
  for (int i=0;i<m_dimension;i++) {
    int row=rows[i];
    if (row>sourceIterations.size()) continue;
    powerS iter=sourceIterations[row].iteration;
    if (iter==0) continue;
    powerS min=iter;
    powerS max=iter;
    for (int j=0;j<sourceIterations.size();j++) {
      if ((sourceIterations[row].col1==sourceIterations[j].col1)
      && (sourceIterations[row].col2==sourceIterations[j].col2))
      {
        if (sourceIterations[j].iteration<min) min=sourceIterations[j].iteration;
        if (sourceIterations[j].iteration>max) max=sourceIterations[j].iteration;
      }
    }
    if (min<iter) {
      min+=iter;
      min/=2;
      if (min>0) iterations[min]=std::pair<int,powerS>(-1,0);
    }
    if (max>iter) {
      max+=iter;
      max/=2;
      iterations[max]=std::pair<int,powerS>(-1,0);
    }
    else {
      max+=iter;
      iterations[max]=std::pair<int,powerS>(-1,0);
    }
  }
}

/// Builds a list of eigenvalues for each iteration up to maxIteration
template <class scalar>
typename AbstractMatrix<scalar>::MatrixS& AbstractMatrix<scalar>::getEigenCloud(powerS maxIteration,bool conjugateOnly)
{
  if (maxIteration<=0) return m_eigenCloud;
  boost::timer timer;
  MatrixC eigenCloud(maxIteration,m_dimension);
  eigenCloud.row(0)=m_eigenValues.diagonal();
  for (int col=0;col<eigenCloud.cols();col++) {
    if (conjugateOnly && m_conjugatePair[col]<0) continue;
    if (m_jordanIndex[col]>0) {
      if (ms_continuous)
      {
        int den=m_jordanIndex[col];
        for (int i=2;i<m_jordanIndex[col];i++) den*=i;
        eigenCloud.coeffRef(0,col)*=func::pow(m_sampleTime,m_jordanIndex[col])*scalar(den);
        for (int iteration=m_jordanIndex[col];iteration<maxIteration;iteration++)
        {
          eigenCloud.coeffRef(iteration,col)=eigenCloud.coeff(iteration-1,col)*eigenCloud.coeff(0,col-m_jordanIndex[col])*m_sampleTime;
        }
      }
      else {
        for (int iteration=0;iteration<m_jordanIndex[col]-1;iteration++) eigenCloud.coeffRef(0,col)=0;
        eigenCloud.coeffRef(m_jordanIndex[col]-1,col)=1;
        for (int iteration=m_jordanIndex[col];iteration<maxIteration;iteration++)
        {
          eigenCloud.coeffRef(iteration,col)=eigenCloud.coeff(iteration-1,col)*eigenCloud.coeff(0,col-m_jordanIndex[col])+eigenCloud.coeff(iteration-1,col-1);
        }
      }
    }
    else for (int iteration=1;iteration<maxIteration;iteration++)
    {
      eigenCloud.coeffRef(iteration,col)=eigenCloud.coeff(iteration-1,col)*eigenCloud.coeff(0,col);
    }
  }
  m_eigenCloud=jordanToPseudoJordan(eigenCloud,this->eToEigenVectors);
  //if (ms_trace_time && (ms_trace_dynamics>=eTraceAbstraction)) ms_logger.logData(timer.elapsed()*1000,"eigenCloud time",true);
  return m_eigenCloud;
}

/// Builds a list of eigenvalue norms (rounded directions) for each iteration up to maxIteration
template <class scalar>
typename AbstractMatrix<scalar>::MatrixS& AbstractMatrix<scalar>::getRoundEigenCloud()
{
  if (m_eigenCloud.rows()>0) return getRoundedDirections(m_roundEigenCloud,m_eigenCloud,true);
}

/// Retrieves the number of non-correlated dimensions in the eigenspace
template <class scalar>
int AbstractMatrix<scalar>::getRoundedDimension()
{
  int dimension=m_dimension;
  int roundDimension=0;
  for (int col=0;col<m_dimension;col++)
  {
    if ((ms_roundJordanBlocks && (m_jordanIndex[col+1]>0)) || (m_conjugatePair[col]>col)) dimension--;
    else if (roundIndex(col)>=0) roundDimension++;
  }
  return dimension;
}

/// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
template <class scalar>
typename AbstractMatrix<scalar>::MatrixS& AbstractMatrix<scalar>::getRoundedDirections(MatrixS &result,const MatrixS &vectors,bool transposed)
{
  if (transposed) {
    result.resize(vectors.rows(),getRoundedDimension());
    int pos=0;
    for (int col=0;col<vectors.cols();col++)
    {
      if (roundIndex(col)<0) {
        result.col(pos)=vectors.col(col);
      }
      else {
        for (int row=0;row<vectors.rows();row++) {
          scalar value=func::squared(vectors.coeff(row,col));
          for (int col2=col+1;roundIndex(col2)==col;col2++) {
            value+=func::squared(vectors.coeff(row,col2));
//            func::madd(value,vectors.coeff(row,col2),vectors.coeff(row,col2));
          }
          result.coeffRef(row,pos)=sqrt(value);
        }
        col++;
        while ((roundIndex(col)>=0) && (roundIndex(col)!=col)) col++;
        col--;
      }
      pos++;
    }
    return result;
  }
  result.resize(getRoundedDimension(),vectors.cols());
  int pos=0;
  for (int row=0;row<vectors.rows();row++)
  {
    if (roundIndex(row)<0) {
      result.row(pos)=vectors.row(row);
    }
    else {
      for (int col=0;col<vectors.cols();col++) {
        scalar value=func::squared(vectors.coeff(row,col));//*vectors.coeff(row,col);
        for (int row2=row+1;roundIndex(row2)==row;row2++) {
          value+=func::squared(vectors.coeff(row2,col));
//          func::madd(value,vectors.coeff(row2,col),vectors.coeff(row2,col));
        }
        result.coeffRef(pos,col)=sqrt(value);
      }
      row++;
      while ((roundIndex(row)>=0) && (roundIndex(row)!=row)) row++;
      row--;
    }
    pos++;
  }
  return result;
}

/// Retrieve an upper bound to the support given by the eigen cloud
template <class scalar>
typename AbstractMatrix<scalar>::refScalar AbstractMatrix<scalar>::eigenCloudSupport(MatrixS &vector,powerS &iter)
{
  MatrixS supports;
  boost::timer timer;
  if (m_eigenCloud.rows()==0) getEigenCloud(calculateMaxIterations(1000),false);
  if (m_inputType==eVariableInputs) {
    supports=m_eigenCloud*vector.topRows(m_eigenCloud.cols());
    if (m_roundEigenCloud.rows()<=0) getRoundEigenCloud();
    supports+=m_roundEigenCloud*vector.bottomRows(m_roundEigenCloud.cols());
  }
  else supports=m_eigenCloud*vector;
  refScalar maxSupport=-func::ms_infinity;
  for (int i=0;i<m_eigenCloud.rows();i++) {
    if (func::toUpper(supports.coeff(i,0))>maxSupport) {
      iter=i;
      maxSupport=func::toUpper(supports.coeff(i,0));
    }
  }
  int lastRow=m_eigenCloud.rows()-1;
  scalar lastSupport=0;
  for (int i=0;i<m_dimension;i++) {
    if (m_conjugatePair[i]<0) lastSupport+=vector.coeff(i,0)*m_eigenCloud.coeff(lastRow,i);
    else {
      scalar eigenNorm=m_eigenCloud.coeff(lastRow,i)*m_eigenCloud.coeff(lastRow,i)+m_eigenCloud.coeff(lastRow,i+1)*m_eigenCloud.coeff(lastRow,i+1);
      eigenNorm*=vector.coeff(i,0)*vector.coeff(i,0)+vector.coeff(i+1,0)*vector.coeff(i+1,0);
      lastSupport+=sqrt(eigenNorm);
      i++;
    }
  }
  if (m_inputType==eVariableInputs) {
    for (int i=m_dimension;i<vector.rows();i++){
      lastSupport+=vector.coeff(i,0)*m_eigenCloud.coeff(lastRow,i-m_dimension);
    }
  }
  if (ms_continuous) maxSupport*=func::toUpper(m_cosFactors.coeff(m_dimension,0));
  if (func::toUpper(lastSupport)>maxSupport) {
    maxSupport=func::toUpper(lastSupport);
    iter=lastRow;
  }
  if (ms_trace_time && (ms_trace_dynamics>=eTraceAbstraction)) ms_logger.logData(timer.elapsed()*1000,"eigenCloud support time",true);
  return maxSupport;
}

/// Creates conjugate supports for unequal eigenvalues
template <class scalar>
void AbstractMatrix<scalar>::fillCrossConjugateSupports(int col1,int col2)
{
  if (m_eigenCloud.rows()<=0) return;
  if ((m_jordanIndex[col1]>0) || (m_jordanIndex[col2]>0)) return;
  if ((m_conjugatePair[col1]<0) || (m_conjugatePair[col2]<0)) return;
  scalar value,value2;
  refScalar min=func::ms_infinity,max=-func::ms_infinity;
  refScalar xmin=min,xmax=max;
  for (int row=0;row<m_eigenCloud.rows();row++)
  {
    value=m_eigenCloud.coeff(row,col1)+m_eigenCloud.coeff(row,col2);
    if (func::toUpper(value)>max) max=func::toUpper(value);
    if (func::toLower(value)<min) min=func::toLower(value);
    value2=m_eigenCloud.coeff(row,col1)-m_eigenCloud.coeff(row,col2);
    if (func::toUpper(value2)>xmax) xmax=func::toUpper(value2);
    if (func::toLower(value2)<xmin) xmin=func::toLower(value2);
  }
  fillDirections(col1,col2,ms_one,ms_one,min,max,0);
  fillDirections(col1,col2,ms_one,-ms_one,xmin,xmax,0);
}

/// Creates conjugate supports for unequal eigenvalues
template <class scalar>
void AbstractMatrix<scalar>::fillCrossConjugateSupports(int col1,int col2,const scalar& dir1,const scalar& dir2,const powerS iter)
{
  if (m_eigenCloud.rows()<=0) return;
  if ((m_jordanIndex[col1]>0) || (m_jordanIndex[col2]>0)) return;
  if ((m_conjugatePair[col1]<0) || (m_conjugatePair[col2]<0)) return;
  //TODO: missing the divergent case. Replace below for iters on the outer circle
  if (func::isPositive(func::normsq(m_eigenValues.coeff(col1,col1))-func::ms_1)) return;
  if (func::isPositive(func::normsq(m_eigenValues.coeff(col2,col2))-func::ms_1)) return;
  scalar value;
  refScalar max=-func::ms_infinity;
  for (int row=0;row<m_eigenCloud.rows();row++)
  {
    value=dir1*m_eigenCloud.coeff(row,col1)+dir2*m_eigenCloud.coeff(row,col2);
    if (func::toUpper(value)>max) max=func::toUpper(value);
  }
  int lastRow=m_eigenCloud.rows()-1;
  refScalar last=func::toUpper(dir1*func::norm2(m_eigenCloud.coeff(lastRow,col1))
                              +dir2*func::norm2(m_eigenCloud.coeff(lastRow,col2)));
  if (last>max) max=last;
  if (m_pos<m_iterations.size()) m_iterations[m_pos]=iteration_pair(col1,col2,iter);
  m_supports.coeffRef(m_pos,0)=max;
  if (ms_continuous) m_supports.coeffRef(m_pos,0)*=m_cosFactors.coeff(col1,0)*m_cosFactors.coeff(col2,0);
  m_directions.coeffRef(m_pos,col1)=dir1;
  m_directions.coeffRef(m_pos++,col2)=dir2;
}

/// Creates conjugate supports for unequal eigenvalues
template <class scalar>
void AbstractMatrix<scalar>::fillCrossConjugateSupportFromIter(int col1,int col2,powerS iter)
{
  scalar weight1,weight2;
  if (iter<m_eigenCloud.rows())
  {
    weight1=m_eigenCloud.coeff(iter,col1);
    weight2=m_eigenCloud.coeff(iter,col2);
    fillCrossConjugateSupports(col1,col2,weight1,weight2,iter);
  }
}

#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class AbstractMatrix<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class AbstractMatrix<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class AbstractMatrix<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class AbstractMatrix<mpinterval>;
  #endif
#endif

}
