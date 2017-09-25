//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#include "AbstractPolyhedra.h"

namespace abstract{

template <class scalar>
bool AbstractPolyhedra<scalar>::ms_trace_abstraction=false;

/// Constructs an empty buffer
template <class scalar>
AbstractPolyhedra<scalar>::AbstractPolyhedra(int dimension,bool sparse) :
    Polyhedra<scalar>(dimension)
{
  if (sparse) this->m_pSortedTableau=&this->m_sparseTableau;
}

/// Constructs transformed polyhedra
template <class scalar>
AbstractPolyhedra<scalar>::AbstractPolyhedra(const AbstractPolyhedra &source,const MatrixS &transform,const MatrixS &inverse) :
    Polyhedra<scalar>(source,transform,inverse)
{
}

/// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
template <class scalar>
typename Tableau<scalar>::MatrixS AbstractPolyhedra<scalar>::getRoundedDirections(const MatrixS &vectors,const std::vector<int> &roundings)
{
  if (roundings.size()<vectors.rows()) {
    return MatrixS(0,0);
  }
  MatrixS result(getDimension(),vectors.cols());
  int pos=0;
  for (int row=0;row<vectors.rows();row++)
  {
    if (roundings[row]<0) {
      result.row(pos)=vectors.row(row);
    }
    else {
      for (int col=0;col<vectors.cols();col++) {
        scalar value=func::squared(vectors.coeff(row,col));//*vectors.coeff(row,col);
        for (int row2=row+1;roundings[row2]==row;row2++) {
          value+=func::squared(vectors.coeff(row2,col));
//          func::madd(value,vectors.coeff(row2,col),vectors.coeff(row2,col));
        }
        result.coeffRef(pos,col)=sqrt(value);
      }
      int base=row;
      while (roundings[row]==base) row++;
      row--;
    }
    pos++;
  }
  return result;
}

/// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
template <class scalar>
bool AbstractPolyhedra<scalar>::getRoundAbstraction(int dimension,int roundDimension,const std::vector<int> &roundings,AbstractPolyhedra<scalar> &roundAbstraction)
{
/*  if (dimension==getDimension()) {
    roundAbstraction.copy(*this);
    return false;
  }*/
  roundAbstraction.changeDimension(dimension);
  roundAbstraction.m_vertices.resize(m_vertices.rows(),dimension);
  roundAbstraction.m_faces.resize(m_faces.rows()+roundDimension,dimension);
  roundAbstraction.m_faces.block(m_faces.rows(),0,roundDimension,dimension)=MatrixS::Zero(roundDimension,dimension);
  int pos=0;
  roundDimension=m_faces.rows();
  for (int col=0;col<m_faces.cols();col++)
  {
    int subDim=1;
    while (roundings[col+subDim]==col) subDim++;
    if (roundings[col]==col) {
      for (int row=0;row<m_vertices.rows();row++) {
        roundAbstraction.m_vertices.coeffRef(row,pos)=m_vertices.block(row,col,1,subDim).norm();
      }
      for (int row=0;row<m_faces.rows();row++) {
        roundAbstraction.m_faces.coeffRef(row,pos)=m_faces.block(row,col,1,subDim).norm();
      }
      roundAbstraction.m_faces.coeffRef(roundDimension++,pos)=-1;
      col+=subDim-1;
    }
    else {
      roundAbstraction.m_vertices.col(pos)=m_vertices.col(col);
      roundAbstraction.m_faces.block(0,pos,m_faces.rows(),1)=m_faces.col(col);
    }
    pos++;
  }
  //roundAbstraction.m_supports.resize(roundAbstraction.m_faces.rows()+roundDimension,1);
  MatrixS matrix=roundAbstraction.m_faces*roundAbstraction.m_vertices.transpose();
  roundAbstraction.m_supports=matrix.col(0);
  for (int row=0;row<matrix.rows();row++) {
    for (int col=1;col<matrix.cols();col++) {
      if (func::toUpper(matrix.coeff(row,col))>func::toUpper(roundAbstraction.m_supports.coeff(row,0))) {
        roundAbstraction.m_supports.coeffRef(row,0)=matrix.coeff(row,col);
      }
    }
  }
  //roundAbstraction.m_supports=matrix.rowwise().maxCoeff();
  roundAbstraction.m_supports.block(m_faces.rows(),0,roundDimension-m_faces.rows(),1)=MatrixS::Zero(roundDimension-m_faces.rows(),1);
  roundAbstraction.Tableau<scalar>::load(roundAbstraction.m_faces,roundAbstraction.m_supports);
  roundAbstraction.removeRedundancies();
  return true;
}

/// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
template <class scalar>
AbstractPolyhedra<scalar>& AbstractPolyhedra<scalar>::getRounded(const std::vector<int> &roundings,AbstractPolyhedra<scalar> &roundAbstraction,bool preCentralized)
{
  int dimension=getDimension();
  int roundDimension=0;
  for (int col=0;col<m_faces.cols();col++)
  {
    if (roundings[col]>=0) {
      if (roundings[col]!=col) dimension--;
      else roundDimension++;
    }
  }
  if (!preCentralized) centralize();
  if (dimension!=getDimension() && !makeVertices()) {
    roundAbstraction.clear();
    if (!preCentralized) decentralize();
    return roundAbstraction;
  }
  getRoundAbstraction(dimension,roundDimension,roundings,roundAbstraction);
  if (!preCentralized) decentralize();
  return roundAbstraction;
  }

/// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
template <class scalar>
bool AbstractPolyhedra<scalar>::getSquareAbstraction(AbstractPolyhedra<scalar> &squareAbstraction,bool symmetric)
{
  int dimension=getDimension();
  MatrixS boxVertices=boundingHyperBox();
  if (boxVertices.rows()!=dimension) return false;
  if (symmetric) {
    for (int i=0;i<dimension;i++) {
      if (func::isNegative(boxVertices.coeff(i,0)+boxVertices.coeff(i,1))) boxVertices.coeffRef(i,1)=-boxVertices.coeff(i,0);
      else boxVertices.coeffRef(i,0)=-boxVertices.coeff(i,1);
    }
  }
  squareAbstraction.changeDimension(dimension);
  squareAbstraction.m_faces.resize(2*dimension,dimension);
  squareAbstraction.m_faces.block(0,0,dimension,dimension)=MatrixS::Identity(dimension,dimension);
  squareAbstraction.m_faces.block(dimension,0,dimension,dimension)=-MatrixS::Identity(dimension,dimension);
  squareAbstraction.m_supports.resize(2*dimension,1);
  squareAbstraction.m_supports.block(0,0,dimension,1)=-boxVertices.col(0);
  squareAbstraction.m_supports.block(dimension,0,dimension,1)=boxVertices.col(1);
  squareAbstraction.Tableau<scalar>::load(squareAbstraction.m_faces,squareAbstraction.m_supports);
  return true;
}

/// Performs the Minkowski sum of this polyhedra to another
template <class scalar>
bool AbstractPolyhedra<scalar>::addRounded(Polyhedra<scalar> &polyhedra,const std::vector<int> &roundings)
{
  if (roundings.size()<m_faces.cols()) return false;
  MatrixS vectors(polyhedra.getDimension(),m_faces.rows());
  int col2=0;
  for (int row=0;row<m_faces.rows();row++) {
    for (int col=m_faces.cols()-1;col>=0;col--) {
      if (roundings[col]>=0) {
        scalar coeff=0;
        while (roundings[col]!=col) {
          func::madd(coeff,m_faces.coeff(row,col),m_faces.coeff(row,col));
          col--;
        }
        func::madd(coeff,m_faces.coeff(row,col),m_faces.coeff(row,col));
        vectors.coeffRef(col2++,row)=sqrt(coeff);
      }
      else vectors.coeffRef(col2++,row)=m_faces.coeff(row,col);
    }
  }
  MatrixS supports(m_supports.rows(),1);
  if (polyhedra.maximiseAll(vectors,supports)) {
    m_supports+=supports;
    return true;
  }
  return false;
}

/// Retrives the vertices mapped into an abstract domain of a linear matrix
template <class scalar>
typename Tableau<scalar>::MatrixS AbstractPolyhedra<scalar>::getAbstractVertices(MatrixS &vector,const int row,const std::vector<int> &rotations,const std::vector<int> &dilations,const MatrixS& vertices) {
  /// sup<v.xy>=sup(sum_i(v_ix_iy_i))=sup<vx.y>
  /// vector is after transformation thus v1(ax1+bx2)+v2(ax2-bx1)=a(v1x1+v2x2)+b(v1x2-v2x1)
  /// for real jordan =a(v1x1+v2x2)+b(v1x2) on the previous col (series=a(sum(vi xi))+b(sum(v{i-1} xi))+c(sum(v{i-2} xi))...)
  /// for complex jordan

  int rows=vertices.rows();
  MatrixS result(vertices.rows(),vertices.cols());
  if ((rotations.size()<vertices.cols()) || (dilations.size()<vertices.cols())) {
    ms_logger.logData("Dimension error");
    throw dimensionMismatch;
  }
  for (int col=0;col<vertices.cols();col++){
    result.col(col)=vertices.col(col)*vector.coeff(row,col);
    if (rotations[col]>col) {
      col++;
      result.col(col-1)+=vertices.col(col)*vector.coeff(row,col);
      result.col(col)=vertices.col(col)*vector.coeff(row,col-1)-vertices.col(col-1)*vector.coeff(row,col);
      if (dilations[col]>0) {
        result.block(0,col-2*dilations[col]-1,rows,2)+=result.block(0,col-1,rows,2);
        result.col(col-1)=vertices.col(col-1)*vector.coeff(row,2*dilations[col]-1)+vector.coeff(row,col-2*dilations[col])*vertices.col(col);
        result.col(col)=vector.coeff(row,col-2*dilations[col]-1)*vertices.col(col)-vector.coeff(row,col-2*dilations[col])*vertices.col(col-1);
        for (int offset=1;offset<dilations[col];offset++) {
          result.col(col-2*offset-1)+=vector.coeff(row,col-2*(dilations[col]-offset)-1)*vertices.col(col-1)+vector.coeff(row,col-2*(dilations[col]-offset))*vertices.block(0,col,rows,1);
          result.col(col-2*offset  )+=vector.coeff(row,col-2*(dilations[col]-offset)-1)*vertices.col(col  )-vector.coeff(row,col-2*(dilations[col]-offset))*vertices.block(0,col-1,rows,1);
        }
      }
    }
    else if (dilations[col]>0) {
      result.col(col-dilations[col])+=result.col(col);
      result.col(col)=vector.coeff(row,col-dilations[col])*vertices.col(col);
      for (int offset=1;offset<dilations[col];offset++) {
        result.col(col-offset)+=vector.coeff(row,col-dilations[col]+offset)*vertices.col(col);
      }
    }
  }
  return result;
}

/// Retrives the vertices mapped into an abstract domain of a linear matrix
template <class scalar>
typename Tableau<scalar>::MatrixS AbstractPolyhedra<scalar>::getAbstractVertices(const MatrixS &vectors,const std::vector<int> &rotations,const std::vector<int> &dilations,const MatrixS &vertices)
{
  /// sup<v.xy>=sup(sum_i(v_ix_iy_i))=sup<vx.y>
  /// vector is after transformation thus v1(ax1+bx2)+v2(ax2-bx1)=a(v1x1+v2x2)+b(v1x2-v2x1)
  /// for real jordan =a(v1x1+v2x2)+b(v1x2) on the previous col (series=a(sum(vi xi))+b(sum(v{i-1} xi))+c(sum(v{i-2} xi))...)
  /// for complex jordan (series=a(sum(vi xi))+b(sum(v{2j-2} x{2j+1}-v{2j} x{2j+1}))+c(sum(v{i-2} xi))...)
  MatrixS result(vectors.cols()*vertices.rows(),vertices.cols());
  if ((rotations.size()<vertices.cols()) || (dilations.size()<vertices.cols())) {
    ms_logger.logData("Dimension error");
    throw dimensionMismatch;
  }
  int rows=vertices.rows();
  for (int vectorNum=0;vectorNum<vectors.cols();vectorNum++) {
    int blockNum=vectorNum*rows;
    for (int col=0;col<vertices.cols();col++){
      result.block(blockNum,col,rows,1)=vertices.block(0,col,rows,1)*vectors.coeff(col,vectorNum);
      if (rotations[col]>col) {
        col++;
        result.block(blockNum,col-1,rows,1)+=vertices.col(col)*vectors.coeff(col  ,vectorNum);
        result.block(blockNum,col,rows,1)=   vertices.col(col)*vectors.coeff(col-1,vectorNum)-vertices.col(col-1)*vectors.coeff(col,vectorNum);
        if (dilations[col]>0) {
          result.block(blockNum,col-2*dilations[col]-1,rows,2)+=result.block(blockNum,col-1,rows,2);
          result.block(blockNum,col-1,rows,1)=vectors.coeff(col-2*dilations[col]-1,vectorNum)*vertices.col(col-1)+vectors.coeff(col-2*dilations[col],vectorNum)*vertices.col(col);
          result.block(blockNum,col  ,rows,1)=vectors.coeff(col-2*dilations[col]-1,vectorNum)*vertices.col(col  )-vectors.coeff(col-2*dilations[col],vectorNum)*vertices.col(col-1);
          for (int offset=1;offset<dilations[col];offset++) {
            int voff=2*(dilations[col]-offset);
            result.block(blockNum,col-2*offset-1,rows,1)+=vectors.coeff(col-voff-1,vectorNum)*vertices.col(col-1)+vectors.coeff(col-voff,vectorNum)*vertices.col(col);
            result.block(blockNum,col-2*offset  ,rows,1)+=vectors.coeff(col-voff-1,vectorNum)*vertices.col(col  )-vectors.coeff(col-voff,vectorNum)*vertices.col(col-1);
          }
        }
      }
      else if (dilations[col]>0) {
        result.block(blockNum,col-dilations[col],rows,1)+=result.block(blockNum,col,rows,1);
        result.block(blockNum,col,rows,1)=vectors.coeff(col-dilations[col],vectorNum)*vertices.col(col);
        for (int offset=1;offset<dilations[col];offset++) {
          result.block(blockNum,col-offset,rows,1)+=vectors.coeff(col-dilations[col]+offset,vectorNum)*vertices.col(col);
        }
      }
    }
  }
  if (this->ms_trace_abstraction) {
    ms_logger.logData(this->m_name);
    ms_logger.logData(vertices,"Vertices:");
    ms_logger.logData(vectors,"Vectors:");
    ms_logger.logData(result,"Abstract Vertices:");
  }
  return result.transpose();
}

template<class scalar>
typename Tableau<scalar>::MatrixS AbstractPolyhedra<scalar>::getSynthVertices(const MatrixS &vectors,const std::vector<int> &rotations,const std::vector<int> &dilations,const std::vector<int> &roundings,const MatrixS &vertices)
{
  /// sup<v.xy>=sup(sum_i(v_ix_iy_i))=sup<vx.y>
  /// vector is after transformation thus v1(ax1+bx2)+v2(ax2-bx1)=x1(av1-bv2)+x2(av2+bv1)
  /// for real jordan =x1(av1)+x2(av2+bv1)+... xn(avn+bv{n-1}...+nv{1})
  /// for complex jordan
  int cols=vertices.cols();
  if (vectors.rows()<cols) cols=vectors.rows();
  MatrixS result(vectors.cols()*vertices.rows(),cols);
  int rows=vertices.rows();
  for (int vectorNum=0;vectorNum<vectors.cols();vectorNum++) {
    int blockNum=vectorNum*rows;
    for (int col=0;col<cols;col++) {
      result.block(blockNum,col,rows,1)=vectors.coeff(col,vectorNum)*vertices.col(col);
      if (rotations[col]>=0) {
        col++;
        result.block(blockNum,col-1,rows,1)-=vectors.coeff(col,vectorNum)*vertices.col(col);
        result.block(blockNum,col,rows,1)=vectors.coeff(col-1,vectorNum)*vertices.col(col)+vectors.coeff(col,vectorNum)*vertices.col(col-1);
        if (dilations[col]>0) {
          result.block(blockNum,col,rows,1)=MatrixS::Zero(rows,1);
          if (rotations[col]>col) {
            for (int offset=-1;offset<2*dilations[col];offset++) {
              if (offset&1) result.block(blockNum,col,rows,1)-=vectors.coeff(col-2*dilations[col]+offset,vectorNum)*vertices.col(col-offset);
              else result.block(blockNum,col,rows,1)+=vectors.coeff(col-2*dilations[col]+offset,vectorNum)*vertices.col(col-offset);
            }
          }
          else {
            for (int offset=0;offset<2*dilations[col];offset++) {
              result.block(blockNum,col,rows,1)+=vectors.coeff(col-2*dilations[col]+offset,vectorNum)*vertices.col(col-offset);
            }
          }
        }
      }
      else if (dilations[col]>0) {
        result.block(blockNum,col,rows,1)=MatrixS::Zero(rows,1);
        for (int offset=0;offset<dilations[col];offset++) {
          result.block(blockNum,col,rows,1)+=vectors.coeff(col-dilations[col]+offset,vectorNum)*vertices.col(col-offset);
        }
      }
    }
  }
  if (this->ms_trace_abstraction) {
    ms_logger.logData(this->m_name);
    ms_logger.logData(vertices,"Vertices:");
    ms_logger.logData(vectors,"Vectors:");
    ms_logger.logData(result,"Synth Vertices:");
  }
  return result;
}

/// Sets the vertices of the polyhedra from a precalculated set
template <class scalar>
bool AbstractPolyhedra<scalar>::setVertices(MatrixS &vertices,const MatrixS &centre)
{
  m_vertices.resize(vertices.rows(),vertices.cols());
  m_vertices.block(0,0,vertices.rows(),vertices.cols())=vertices;
  if (centre.rows()>0) {
    m_centre=centre;
    translate(m_centre);
  }
}

/// Retrieves a copy of this polyhedra transformed by the given matrix
template <class scalar>
AbstractPolyhedra<scalar>& AbstractPolyhedra<scalar>::getTransformedPolyhedra(Polyhedra<scalar> &polyhedra,const MatrixS &transform,const MatrixS &inverse,const MatrixS &templates)
{
  return dynamic_cast<AbstractPolyhedra&>(Polyhedra<scalar>::getTransformedPolyhedra(polyhedra,transform,inverse,templates));
}

/// Retrieves a slice of the polyhedra for the size dimensions starting at offset
template <class scalar>
bool AbstractPolyhedra<scalar>::slice(AbstractPolyhedra<scalar>&target,int size,int offset,int rowSize,int rowOffset)
{
  target.clear();
  if (size<0) size+=getDimension();
  if (rowSize<0) rowSize+=m_faces.rows();
  target.changeDimension(size);
  if (rowSize>0) {
    return target.load(m_faces.block(rowOffset,offset,rowSize,size),m_supports.block(rowOffset,0,rowSize,1));
  }
  target.m_faces=m_faces.block(rowOffset,offset,m_faces.rows(),size);
  target.m_supports=m_supports;
  return target.removeRedundancies();
}

/// Retrieves a slice of the polyhedra for the size dimensions starting at offset
template <class scalar>
bool AbstractPolyhedra<scalar>::getPlane(AbstractPolyhedra<scalar>&target,int col1,int col2,MatrixS &centre)
{
  target.clear();
  target.changeDimension(2);
  target.m_faces.resize(m_faces.rows(),2);
  target.m_faces.col(0)=m_faces.col(col1);
  target.m_faces.col(1)=m_faces.col(col2);
  target.m_supports=m_supports-m_faces*centre;
  bool only=true;
  int pos=0;
  if (only) {
    for (int row=0;row<m_faces.rows();row++) {
      bool maybe=true;
      for (int col=0;col<m_faces.cols();col++) {
        if ((col==col1) || (col==col2)) continue;
        if (!func::isZero(m_faces.coeff(row,col))) maybe=false;
      }
      if (maybe) {
        target.m_faces.row(pos)=target.m_faces.row(row);
        target.m_supports.row(pos++)=target.m_supports.row(row);
      }
    }
  }
  else {
    for (int row=0;row<m_faces.rows();row++) {
      if (!func::isZero(m_faces.coeff(row,col1)) || !func::isZero(m_faces.coeff(row,col2))) {
        target.m_faces.row(pos)=target.m_faces.row(row);
        target.m_supports.row(pos++)=target.m_supports.row(row);
      }
    }
  }
  target.m_faces.conservativeResize(pos,2);
  target.m_supports.conservativeResize(pos,1);
  target.load(target.m_faces,target.m_supports);
  return target.removeRedundancies();
}

/// Clears redundant faces in the polyhedra (caused by intersections and reductions)
template <class scalar>
bool AbstractPolyhedra<scalar>::removeRedundancies()
{
  if (m_faces.rows()<=0) return false;
  std::vector<bool> isRedundant;
  isRedundant.resize(m_faces.rows());
  int redundant=findRedundancies(isRedundant);
  if (redundant>0) {
    int pos=0;
    for (int i=0;i<m_faces.rows();i++) {
      if (isRedundant[i]) continue;
      m_faces.row(pos)=m_faces.row(i);
      m_supports.coeffRef(pos,0)=m_supports.coeff(i,0);
      if (m_iterations.size()>0) m_iterations[pos]=m_iterations[i];
      pos++;
    }
    m_faces.conservativeResize(pos,m_faces.cols());
    m_supports.conservativeResize(pos,1);
    if (m_iterations.size()>0) m_iterations.resize(pos);
    Tableau<scalar>::load(m_faces,m_supports);
    return true;
  }
  Tableau<scalar>::load(m_faces,m_supports);
  return false;
}

/// Loads a description into the tableau (Ax<b)
template <class scalar>
bool AbstractPolyhedra<scalar>::loadTagged(const MatrixS &faces,const MatrixS &supports,std::vector<iteration_pair>  &iterations,const bool transpose)
{
  m_iterations.resize(0);
  m_iterations.insert(m_iterations.end(),iterations.begin(),iterations.end());
  return load(faces,supports,transpose);
}

/// Loads a description into the tableau (Ax<b)
template <class scalar>
bool AbstractPolyhedra<scalar>::loadTagged(SMatrixS &faces,const MatrixS &supports,std::vector<iteration_pair>  &iterations)
{
  m_iterations.resize(0);
  m_iterations.insert(m_iterations.end(),iterations.begin(),iterations.end());
  m_faces=MatrixS::Zero(faces.rows(),faces.cols());
  for (int row=0;row<faces.rows();row++) {
    sparseVector &data=faces[row];
    for (typename sparseVector::iterator it=data.begin();it!=data.end();it++) {
      m_faces.coeffRef(row,it->first)=it->second;
    }
  }
  return load(m_faces,supports);
}

/// Adds a number of directions to the template of the polhedra
template <class scalar>
bool AbstractPolyhedra<scalar>::addTaggedDirection(const MatrixS &directions,MatrixS &supports,std::vector<iteration_pair> &iterations,bool keepBasis)
{
  m_iterations.insert(m_iterations.end(),iterations.begin(),iterations.end());
  return addDirection(directions,supports,keepBasis);
}

/// Adds a number of directions to the template of the polhedra
template <class scalar>
bool AbstractPolyhedra<scalar>::addTaggedDirection(SMatrixS &faces,MatrixS &supports,std::vector<iteration_pair> &iterations,bool keepBasis)
{
  m_iterations.insert(m_iterations.end(),iterations.begin(),iterations.end());
  MatrixS directions=MatrixS::Zero(faces.cols(),faces.rows());
  for (int row=0;row<faces.rows();row++) {
    sparseVector &data=faces[row];
    for (typename sparseVector::iterator it=data.begin();it!=data.end();it++) {
      directions.coeffRef(it->first,row)=it->second;
    }
  }
  return addDirection(directions,supports,keepBasis);
}

#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class AbstractPolyhedra<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class AbstractPolyhedra<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class AbstractPolyhedra<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class AbstractPolyhedra<mpinterval>;
  #endif
#endif

}
