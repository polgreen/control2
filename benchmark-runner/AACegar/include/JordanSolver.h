//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#ifndef JORDAN_SOLVER_H
#define JORDAN_SOLVER_H

#include "Scalar.h"
#include <limits>
#include "MatrixToString.h"

namespace abstract
{

/// Calculates the Jordan and SVD decomposition of a matrix
template <class scalar> class  JordanSolver : public Eigen::EigenSolver<typename interval_def<scalar>::MatrixS>
{
public:
    typedef interval_def<scalar> type;
    typedef typename type::scalar_type refScalar;
    typedef typename type::complexS complexType;
    typedef typename type::MatrixS MatrixType;
    typedef typename type::MatrixC ComplexMatrixType;
    typedef functions<refScalar> func;

    /// Constructs an empty buffer
    /// @param dimension dimension of the matrix
    JordanSolver(const int dimension);

    /// Changes the default dimension of the system
    /// @param dimension dimension of the statespace
    virtual void changeDimensions(const int dimension);

    void computeJordan(const MatrixType &matrix);
protected:
    /// Transforms the matrix to Row Echelon Form
    /// @param matrix matrix to transform to REF
    /// @ret number of zero rows of the REF
    int toREF(ComplexMatrixType &matrix);

    /// Transforms the matrix to Reduced Row Echelon Form
    int toRREF(ComplexMatrixType &matrix);

    /// calculates the estimated roundoff error of a matrix operation
    refScalar calculateEpsilon(const MatrixType &matrix);
    refScalar calculateEpsilon(const ComplexMatrixType &matrix);

    /// calculates the dotProduct of two vectors
    scalar dotProduct(ComplexMatrixType &matrix1, int col1, ComplexMatrixType &matrix2, int col2, bool normed=false);

    /// Indicates if the given eigenvectors at col1 and col2 are orthogonal
    bool isOrthogonal(int col1,int col2)
    {
      return func::isZero(dotProduct(m_eigenVectors,col1,m_eigenVectors,col2));
    }

    /// Indicates if the given eigenvectors at col1 and col2 are orthogonal
    bool isMultiple(ComplexMatrixType &matrix1,int col1,ComplexMatrixType &matrix2,int col2)
    {
      return func::isZero(func::ms_1-dotProduct(matrix1,col1,matrix2,col2,true));
    }

    /// Checks if the given row pair belongs to the same jordan block
    bool isJordanBlock(const int row1,const int row2);

    /// Calculates the Jordan block and generalised eigenvector for the row pair
    int makeJordanBlock(int row1,const int row2);

    /// Orders the eigenvectors of the set of equal eigenvalues starting at col, by row major
    void sortEigenvectors(const int col);

    /// Returns the nullSpace vectors of M
    ComplexMatrixType getNullSpace(const ComplexMatrixType &matrixBase,bool normalized=false);

    virtual bool calculateJordanForm();

public:
    /// Returns the complex eigenvalue matrix (S)
    ComplexMatrixType& getEigenValues()            { return m_eigenValues; }

    /// Returns the complex eigenvector matrix (S)
    ComplexMatrixType& getEigenVectors()           { return m_eigenVectors; }

    std::vector<int>& getJordanIndeces()           { return m_jordanIndex; }
    std::vector<int>& getConjugatePairs()          { return m_conjugatePair; }
    std::vector<bool>& getOnes()                   { return m_isOne; }
    std::vector<bool>& getNegatives()              { return m_isNegative; }
    bool hasOnes()                                 { return m_hasOnes; }
    bool hasNegatives()                            { return m_hasNegatives; }
    bool hasMultiplicities()                       { return m_hasMultiplicities; }

    MatrixType& getSchur()                         { return this->m_matT; }

protected:
    int                         m_dimension;
    refScalar                   m_zero;
    refScalar                   m_largeZero;
    MatrixType                  m_dynamics;
    MatrixType                  m_inverse;
    ComplexMatrixType           m_eigenValues;
    ComplexMatrixType           m_eigenVectors;
    std::vector<int>            m_jordanIndex;
    std::vector<int>            m_conjugatePair;
    std::vector<bool>           m_isOne;
    std::vector<bool>           m_isNegative;
    int                         m_numZeros;
    bool                        m_hasOnes;
    bool                        m_hasNegatives;
    bool                        m_hasMultiplicities;
    int                         m_leadingZeroColumns;
    static complexType          ms_complexOne;
    static MatToStr<scalar>     ms_logger;
    static MatToStr<scalar>     ms_decoder;
public:
    static bool                 ms_trace_dynamics[eMaxTraceDynamics];
};

}

#endif
