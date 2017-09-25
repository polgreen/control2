//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#include "RowSort.h"
#include <map>
#include <set>
#include <math.h>
#include <boost/timer.hpp>
#include "MatrixToString.h"

namespace abstract {


template <class scalar>
void SortedTableau<scalar>::ComputeRowOrderVector(const OrderType &type)
{
  int rowCount=numRows()+1;
  if (m_order.size()<rowCount+1) m_order.resize(rowCount+1);
  switch(type) {
  case MaxIndex:
    for(int i=1; i<=rowCount; i++) m_order[i]=rowCount-i;
    break;
  case MinIndex:
    for(int i=1; i<=rowCount; i++) m_order[i]=i;
    break;
  case LexMin:
    for(int i=0; i<=rowCount; i++) m_order[i]=i;
    QuickMatrixSort(m_order, 1, numRows());
    break;
  case LexMax:
    for(int i=0; i<=rowCount; i++) m_order[i]=i;
    QuickMatrixSort(m_order, 1, numRows());
    for(int i=1; i<=numRows()/2;i++){   /* just reverse the order */
      int temp=m_order[i];
      m_order[i]=m_order[rowCount-i];
      m_order[rowCount-i]=temp;
    }
    break;
  case LexAngle:
    QuickAngleSort();
    break;
  case LexCos:
    cosineSort();
    break;
  }
}

template <class scalar>
void SortedTableau<scalar>::UpdateRowOrderVector(const Set &priorityRows)
// Update the RowOrder vector to shift selected rows in highest order.
{
  bool found=true;
  long rr=priorityRows.cardinality();
  for (int i=1; i<=rr; i++){
    found=false;
    for (int j=i; j<m_order.size() && !found; j++){
      int oj=m_order[j];
      if (priorityRows.member(oj-1)){//TODO: zero index
        found=true;
        if (j>i) {
          /* shift everything lower: pOrder[i]->pOrder[i+1]..pOrder[j1-1]->pOrder[j1] */
          for (int k=j; k>=i; k--) m_order[k]=m_order[k-1];
          m_order[i]=oj;
        }
      }
    }
    if (!found) return;
  }
}

template <class scalar>
bool SortedTableau<scalar>::contains(const MatrixS& vector,int offset,bool fast)
{
  if (vector.cols()<numCols()+offset) return false;
  if (fast)
  {}
  for (int row=0;row<numRows();row++) {
    int col;
    for (col=0;col<numCols();col++) {
      if (!func::isZero(vector.coeff(0,col+offset)-getCoeff(row,col))) break;
    }
    if (col==numCols()) return true;
  }
  return false;
}

template <class scalar>
long SortedTableau<scalar>::subPartition(std::vector<int> &order, const long p, const long r)
{
  long i,j,tmp;
  i=p-1;
  j=r+1;
  while (true){
    while (LargerRow(order[--j]-1,order[p]-1));
    while (SmallerRow(order[++i]-1,order[p]-1));
    if (i<j){
      tmp=order[i];
      order[i]=order[j];
      order[j]=tmp;
    }
    else return j;
  }
}

template <class scalar>
long SortedTableau<scalar>::anglePartition(std::vector<int> &order, const long p, const long r)
{
  long i,j,temp;
  i=p-1;
  j=r+1;
  while (true){
    while (LargerAngleRow(order[--j]-1,order[p]-1));
    while (SmallerAngleRow(order[++i]-1,order[p]-1));
    if (i<j){
      temp=order[i];
      order[i]=order[j];
      order[j]=temp;
    }
    else return j;
  }
}

template <class scalar>
void SortedTableau<scalar>::QuickMatrixSort(std::vector<int> &order, const long p, const long r)
{
  if (p < r){
    long q = subPartition(order, p, r);
    QuickMatrixSort(order, p, q);
    QuickMatrixSort(order, q+1, r);
  }
}

/// Pivots the tableau in place on the given pivot
template <class scalar>
void SortedTableau<scalar>::pivot(MatrixS &auxiliary,pivot_t pivot)
{
  int dimension=numCols();
  MatrixS epsMatrix(dimension,1);
  for (int col=0;col<numCols();col++) epsMatrix.coeffRef(col,0)=-getCoeff(pivot.row,col);
  epsMatrix.coeffRef(pivot.col,0)=func::ms_1;
  epsMatrix*=func::ms_1/((pivot.row>=numRows()) ? auxiliary.coeff(0,pivot.col) : getCoeff(pivot.row,pivot.col));
  m_dirty=false;
  for (int row = 0; row < numRows(); row++) setCoeff(row,pivot.col,entry(epsMatrix,row,0));
  if (auxiliary.cols()>0) auxiliary.coeffRef(0,pivot.col)=(auxiliary*epsMatrix).coeff(0,0);
  m_dirty=true;
}

 /*  quicksorts matrix rows based on the column order (first column is most significant)
 */
template <class scalar>
SortedMatrix<scalar>::SortedMatrix(int rows,int cols) : Eigen::Matrix<scalar,Eigen::Dynamic,Eigen::Dynamic>(rows,cols) {}

template <class scalar>
SortedMatrix<scalar>::SortedMatrix(const MatrixS &source,const OrderType &type,bool transpose,bool norm) : Eigen::Matrix<scalar,Eigen::Dynamic,Eigen::Dynamic>(transpose ? source.cols() : source.rows(),transpose ? source.rows() : source.cols())
{
  if (transpose) this->block(0,0,rows(),cols())=source.transpose();
  else this->block(0,0,rows(),cols())=source;
  if (type==LexCos) normalize();
  if (type!=LexNone) ComputeRowOrderVector(type);
}

template <class scalar>
char SortedMatrix<scalar>::compareZeroOrderRows(int row1,int row2)
{
  int trueRow1=zeroOrder(row1);
  int trueRow2=zeroOrder(row2);
  for (int col=0;col<cols();col++) {
    char sign=func::hardSign(coeff(trueRow1,col)-coeff(trueRow2,col));
    if (sign!=0) return sign;
  }
  return 0;
}

template <class scalar>
bool SortedMatrix<scalar>::SmallerCos(std::vector<scalar> &cosines, const int row1,const int row2)
{
  scalar result=cosines[row1]-cosines[row2];
  char sign=func::hardSign(result);
  if (sign!=0) return (sign<0);
  return false;
}

template <class scalar>
bool SortedMatrix<scalar>::LargerCos(std::vector<scalar> &cosines, const int row1,const int row2)
{
  scalar result=cosines[row1]-cosines[row2];
  char sign=func::hardSign(result);
  if (sign!=0) return (sign > 0);
  return false;
}

template <class scalar>
long SortedMatrix<scalar>::subCosPartition(std::vector<int> &order, std::vector<scalar> &cosines, const long p, const long r)
{
  long i,j,tmp;
  i=p-1;
  j=r+1;
  while (true){
    while (LargerCos(cosines,order[--j]-1,order[p]-1));
    while (SmallerCos(cosines,order[++i]-1,order[p]-1));
    if (i<j){
      tmp=order[i];
      order[i]=order[j];
      order[j]=tmp;
    }
    else return j;
  }
}

template <class scalar>
void SortedMatrix<scalar>::QuickCosSort(std::vector<int> &order, std::vector<scalar> &cosines, const long p, const long r)
{
  if (p < r){
    long q = subCosPartition(order, cosines, p, r);
    QuickCosSort(order, cosines, p, q);
    QuickCosSort(order, cosines, q+1, r);
  }
}

template <class scalar>
void SortedMatrix<scalar>::cosSort(std::vector<int> &order, std::vector<scalar> &cosines)
{
  int numRows=rows()+1;
  for(int i=0; i<=numRows; i++) order[i]=i;
  for (int row=1;row<rows();row++) {
    scalar value=coeff(0,0)*coeff(row,0);
    for (int col=1;col<cols();col++) func::madd(value,coeff(0,col),coeff(row,col));
    cosines[row]=value;
  }
  QuickCosSort(order, cosines, 1, rows());
  for(int i=1; i<=rows()/2;i++){   /* reverse the order */
    int temp=order[i];
    order[i]=order[numRows-i];
    order[numRows-i]=temp;
  }
}

template <class scalar>
bool SortedMatrix<scalar>::SmallerAngleRow(const int row1,const int row2)
{
  for (int j=0;j<cols()-1;j++) {
    scalar angle1=coeff(row1,j)/coeff(row1,j+1);
    angle1=atan(angle1);
    if (func::isNegative(coeff(row1,j))) angle1=func::const_pi(func::ms_1)-angle1;
    if (func::isNegative(coeff(row1,j+1))) angle1+=func::const_pi(func::ms_1);
    scalar angle2=coeff(row2,j)/coeff(row2,j+1);
    angle2=atan(angle2);
    if (func::isNegative(coeff(row2,j))) angle2=func::const_pi(func::ms_1)-angle2;
    if (func::isNegative(coeff(row2,j+1))) angle2+=func::const_pi(func::ms_1);
    angle1-=angle2;
    char sign=func::hardSign(angle1);
    if (sign!=0) return (sign<0);
  }
  return false;
}

template <class scalar>
bool SortedMatrix<scalar>::LargerAngleRow(const int row1,const int row2)
{
  for (int j=0;j<cols()-1;j++) {
    scalar angle1=coeff(row1,j)/coeff(row1,j+1);
    angle1=atan(angle1);
    if (coeff(row1,j)<func::ms_hardZero) angle1+=func::const_pi(func::ms_1);
    scalar angle2=coeff(row2,j)/coeff(row2,j+1);
    angle2=atan(angle2);
    if (func::isNegative(coeff(row2,j))) angle2+=func::const_pi(func::ms_1);
    angle1-=angle2;
    char sign=func::hardSign(angle1);
    if (sign!=0) return (sign>0);
  }
  return false;
}

template <class scalar>
bool SortedMatrix<scalar>::SmallerRow(const int row1,const int row2)
{
  for (int j=0;j<cols();j++) {
    scalar result=coeff(row1,j)-coeff(row2,j);
    char sign=func::hardSign(result);
    if (sign!=0) return (sign<0);
  }
  return false;
}

template <class scalar>
bool SortedMatrix<scalar>::LargerRow(const int row1,const int row2)
{
  for (int j=0;j<cols();j++) {
    scalar result=coeff(row1,j)-coeff(row2,j);
    char sign=func::hardSign(result);
    if (sign!=0) return (sign > 0);
  }
  return false;
}


template <class scalar>
void SortedMatrix<scalar>::QuickAngleSort()
{
  std::multimap<refScalar,int> preorder;
  MatrixS centre=this->colwise().sum()/rows();
  for (int row=0;row<rows();row++) {
    scalar angle=(coeff(row,1)-centre.coeff(0,1))/(coeff(row,0)-centre.coeff(0,0));
    angle=atan(angle);
    scalar dif=coeff(row,0)-centre.coeff(0,0);
    if (func::isNegative(dif)) angle+=func::const_pi(func::ms_1);
    preorder.insert(std::pair<refScalar,int>(func::toCentre(angle),row));
  }
  m_order.resize(rows());
  typename std::map<refScalar,int>::iterator it=preorder.begin();
  for (unsigned int row=0;row<rows() && row<preorder.size();row++,it++) {
    m_order[row]=it->second;
  }
}

template <class scalar>
void SortedMatrix<scalar>::setRow(int row,int col,const MatrixS &src)
{
  this->block(row,col,1,cols()-col)=src;
}

template <class scalar>
void SortedMatrix<scalar>::negRow(int row,int col,const MatrixS &src)
{
  this->block(row,col,1,cols()-col)=-src;
}

template <class scalar>
void SortedMatrix<scalar>::subRow(MatrixS &dest,int row)
{
  dest-=this->row(row);
}

template <class scalar>
void SortedMatrix<scalar>::normalize()
{
  m_norms.resize(rows(),1);
  for (int row=0;row<rows();row++) {
    scalar value=coeff(row,0)*coeff(row,0);
    for (int col=1;col<cols();col++) func::madd(value,coeff(row,col),coeff(row,col));
    m_norms.coeffRef(row)=sqrt(value);
    this->row(row)/=func::toCentre(m_norms.coeff(row));
  }
}

template <class scalar>
void SortedMatrix<scalar>::cosineSort()
{
  int pos=1;
  int row=1;
  std::set<int> remaining;
  std::vector<refScalar> cosines;
  cosines.resize(rows()+1,func::ms_1);
  cosines[rows()]=0;
  m_order.resize(rows()+1);
  m_cosines.resize(rows()+1);
  m_cosines[pos]=func::ms_1;
  m_order[pos++]=row;
  for (int row=1;row<rows();row++) remaining.insert(row);

  while (pos<=rows()) {
    m_order[pos]=rows();  
    refScalar max=-func::ms_infinity;
    refScalar invCos=func::ms_1/cosines[row];
    refScalar lastCosine=func::ms_hardZero;
    for (std::set<int>::iterator it=remaining.begin();it!=remaining.end();it++) {
      int row2=*it;
      if ((pos>2) && (!func::isNegative(lastCosine-cosines[row2]))) {
        if (cosines[row2]>func::ms_hardZero) cosines[row2]*=invCos;
        else cosines[row2]+=func::ms_1-cosines[row];
        continue;
      }
      scalar value=coeff(row,0)*coeff(row2,0);
      for (int col=1;col<cols();col++) {
        func::madd(value,coeff(row,col),coeff(row2,col));
      }
      cosines[row2]=func::toCentre(value);
      if (func::toLower(value)>max) {
        max=func::toLower(value);
        m_cosines[pos]=max;
        m_order[pos]=row2;
        lastCosine=cosines[row2]*cosines[row];
      }
    }
    if (m_order[pos]==rows()) {
      if (remaining.size()<=0) break;
      int row2=*(remaining.begin());
      cosines[row2]=func::ms_1;
      continue;
    }
    row=m_order[pos++]++;
    remaining.erase(row);
  }
}

template <class scalar>
bool SortedMatrix<scalar>::copyOrder(SortedMatrix<scalar> &src)
{
  if (src.m_order.size()!=rows()) return false;
  m_order.clear();
  m_order.insert(m_order.begin(),src.m_order.begin(),src.m_order.end());
}

/// Retrieves the value of a tableau entry for a given row an column (see revised simplex algorithm)
template <class scalar>
scalar SortedMatrix<scalar>::entry(MatrixS &basis,const int row, const int col)
{
  if (m_dirty) return coeff(row,col);
  scalar temp(coeff(row,0) * basis.coeff(0,col));
  refScalar width,maxWidth=func::toWidth(temp);
  int dimension=cols();
  for (int j=1; j< dimension; j++) {
    width=func::madd(temp,coeff(row,j),basis.coeff(j,col));
    if (width>maxWidth) maxWidth=width;
  }
  if (type::isInterval()) {
    char sign=func::hardSign(temp);
    if ((sign==0) && (maxWidth>0)) {
      maxWidth/=2;
      if ((func::toUpper(temp)<maxWidth) || (-func::toLower(temp)<maxWidth)) {
        maxWidth=maxTightWidth(basis,row,col);
        if ((func::toUpper(temp)<maxWidth) || (-func::toLower(temp)<maxWidth)) {
          if (maxWidth<func::ms_zero) {
            relaxBasis(basis,maxWidth,col);
            return tightEntry(basis,row,col);
          }
          func::imprecise(temp,maxWidth,"Imprecise width");
        }
      }
    }
  }
  return temp;
}

/// Pivots the tableau in place on the given pivot
template <class scalar>
void SortedMatrix<scalar>::pivot(MatrixS &auxiliary,pivot_t pivot)
{
  if (pivot.row<rows()) {
    refScalar invXtemp0 = func::toCentre(func::ms_1/getCoeff(pivot.row,pivot.col));
    scalar Xtemp;
    for (int col=0;col<numCols();col++) {
      if ((col!=pivot.col) && !func::isZero(getCoeff(pivot.row,col))) {
        Xtemp = coeff(pivot.row,col)*invXtemp0;
        for (int row = 0; row < numRows(); row++) {
          func::msub(coeffRef(row,col),coeff(row,pivot.col),Xtemp);
        }
      }
    }
    col(pivot.col)*=invXtemp0;
  }
  else if (auxiliary.cols()!=numCols()) return;
  else {
    refScalar invXtemp0 = func::toCentre(func::ms_1/auxiliary.coeff(0,pivot.col));
    scalar Xtemp;
    for (int col=0;col<numCols();col++) {
      if ((col!=pivot.col) && !func::isZero(auxiliary.coeff(0,col))) {
        Xtemp = auxiliary.coeff(0,col)*invXtemp0;
        for (int row = 0; row < numRows(); row++) {
          func::msub(coeffRef(row,col),coeff(row,pivot.col),Xtemp);
        }
        func::msub(auxiliary.coeffRef(0,col),auxiliary.coeff(0,pivot.col),Xtemp);
      }
    }
    col(pivot.col)*=invXtemp0;
  }
}

template <class scalar>
inline scalar SortedMatrix<scalar>::tightEntry(MatrixS &basis,const int row, const int col,const int iteration)
/* Computes Tableau(row)*B^-1(col) */
{
  scalar temp(coeff(row,0) * basis.coeff(0,col));
  refScalar width,maxWidth=func::tightWidth(coeff(row,0),basis.coeff(0,col));
  int dimension=cols();
  for (int j=1; j< dimension; j++) {
    width=func::tightMadd(temp,coeff(row,j),basis.coeff(j,col));
    if (width>maxWidth) maxWidth=width;
  }
  if (type::isInterval()) {
    char sign=func::hardSign(temp);
    if (sign==0) {
      maxWidth/=2;
      maxWidth=maxTightWidth(basis,row,col);
      if ((func::toUpper(temp)<maxWidth) || (-func::toLower(temp)<maxWidth)) {
        if (maxWidth<func::ms_weakEpsilon) {
          relaxBasis(basis,maxWidth,col);
          return tightEntry(basis,row,col,iteration+1);
        }
        func::imprecise(temp,maxWidth,"tight width");
      }
    }
  }
  return temp;
}

template <class scalar>
inline scalar SortedMatrix<scalar>::entry(const MatrixS &vector, const int row)
{ /*return the ith component of the vector  A x vector */
  scalar temp(coeff(row,0)*vector.coeff(0,0));
  refScalar width,maxWidth=func::toWidth(temp);
  int dimension=cols();
  for (int j = 1; j < dimension; j++) {
    width=func::madd(temp,coeff(row,j),vector.coeff(0,j));
    if (width>maxWidth) maxWidth=width;
  }
  if (type::isInterval()) {
    char sign=func::hardSign(temp);
    if (sign==0) {
      maxWidth-=func::ms_epsilon;
      if ((func::toUpper(temp)<maxWidth) || (-func::toLower(temp)<maxWidth)) {
        maxWidth=maxTightWidth(vector,row);
        if ((func::toUpper(temp)<maxWidth) || (-func::toLower(temp)<maxWidth)) {
          /*if (maxWidth<func::ms_weakEpsilon) {
            scalar mult=func::ms_1+func::setpm(maxWidth);
            vector*=mult;
            return ATightValue(vector,row);
          }*/
          func::imprecise(temp,maxWidth,"vertex width");
        }
      }
    }
  }
  return temp;
}

template <class scalar>
inline scalar SortedMatrix<scalar>::tightEntry(const MatrixS &vector, const long row)
{ /*return the ith component of the vector  A x vector */
  scalar temp(coeff(row,0)*vector.coeff(0,0));
  refScalar width,maxWidth=func::tightWidth(coeff(row,0),vector.coeff(0,0));
  int dimension=cols();
  for (int j = 1; j < dimension; j++) {
    width=func::tightMadd(temp,coeff(row,j),vector.coeff(0,j));
    if (width>maxWidth) maxWidth=width;
  }
  if (type::isInterval()) {
    char sign=func::hardSign(temp);
    if (sign==0) {
      maxWidth/=2;
      if ((func::toUpper(temp)<maxWidth) || (-func::toLower(temp)<maxWidth)) {
        func::imprecise(temp,maxWidth,"tight vertex width");
      }
    }
  }
  return temp;
}

template <class scalar>
inline typename SortedMatrix<scalar>::refScalar SortedMatrix<scalar>::maxTightWidth(const MatrixS &vector, const int row)
{ /*return the minimum required width for full inclusion */
  refScalar width,maxWidth=func::tightWidth(coeff(row,0),vector.coeff(0,0));
  for (int j = 1; j < cols(); j++) {
    width=func::tightWidth(coeff(row,j),vector.coeff(0,j));
    if (width>maxWidth) maxWidth=width;
  }
  return maxWidth/2;
}

template <class scalar>
inline typename SortedMatrix<scalar>::refScalar SortedMatrix<scalar>::maxTightWidth(const MatrixS &basis,const int row, const int col)
/* Computes Tableau(row)*B^-1(col) */
{
  int nonzero=func::isZero(coeff(row,0)*basis.coeff(0,col)) ? 0 : 1;
  refScalar width,maxWidth=func::tightWidth(coeff(row,0),basis.coeff(0,col));
  int dimension=cols();
  for (int j=1; j< dimension; j++) {
    width=func::tightWidth(coeff(row,j),basis.coeff(j,col));
    nonzero+=func::isZero(coeff(row,j)*basis.coeff(j,col)) ? 0 : 1;
    if (width>maxWidth) maxWidth=width;
  }
  if (nonzero<=1) return 0;
  return maxWidth/2;
}

///Relaxes the current basis by the given interval to cope with imprecisions
template <class scalar>
void SortedMatrix<scalar>::relaxBasis(MatrixS &basis,scalar width,int col)
{
  if (!type::isInterval()) return;
  scalar mult=func::setpm(width);
  if (col>=0) {
    refScalar magOrder=10;
    for (int row=0;row<basis.rows();row++) {
      basis.coeffRef(row,col)+=mult*basis.coeff(row,col);
      basis.coeffRef(row,col)+=magOrder*(basis.coeff(row,col)-func::toCentre(basis.coeff(row,col)));
    }
  }
  else basis+=mult*basis;
}


#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class SortedTableau<long double>;
    template class SortedMatrix<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class SortedTableau<ldinterval>;
    template class SortedMatrix<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class SortedTableau<mpfr::mpreal>;
    template class SortedMatrix<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class SortedTableau<mpinterval>;
    template class SortedMatrix<mpinterval>;
  #endif
#endif

}
