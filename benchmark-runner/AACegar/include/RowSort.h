//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#ifndef SORTEDMATRIX_H
#define SORTEDMATRIX_H

#include "Scalar.h"
#include "Set.h"
#include <vector>

namespace abstract{
#define RHSCol 0    //Right Hand Side Column
typedef enum { MaxIndex, MinIndex, LexMin, LexMax, LexAngle, LexCos, LexNone } OrderType;

template <class scalar>
class SortedTableau {
public:
    typedef interval_def<scalar> type;
    typedef typename type::scalar_type refScalar;
    typedef typename type::MatrixS  MatrixS;
    typedef functions<refScalar> func;

    void ComputeRowOrderVector(const OrderType &type);

    void UpdateRowOrderVector(const Set &priorityRows);

    inline int order(const int row)       { return m_order[row]; }
    inline int zeroOrder(const int row)   { return m_order[row]-1; }//TODO: zero index

    virtual void QuickAngleSort()=0;

    virtual char compareZeroOrderRows(int row1,int row2)=0;

    virtual int numRows()=0;

    // Sets the size of the tableau
    virtual void setSize(int rows,int cols)=0;

    // Sets a given coefficient in the sorted Tableau
    virtual void setCoeff(int row,int col,const scalar &src)=0;

    // Sets the given row to src starting at col
    virtual void setRow(int row,int col,const MatrixS &src)=0;

    // Sets the given row to -src starting at col
    virtual void negRow(int row,int col,const MatrixS &src)=0;

    // Substracts the given row from dest
    virtual void subRow(MatrixS &dest,int row)=0;

    virtual void normalize()=0;

    /// Retrieves the value of a tableau entry for a given row and basis column (see revised simplex algorithm)
    virtual scalar entry(MatrixS &basis,const int row, const int col)=0;

    ///Retrieves the magnitude of the vector in the direction normal to the given halfspace
    ///@param vector vector to verify
    ///@param row halfspace to check against
    virtual scalar entry(const MatrixS &vector,const int row)=0;
protected:
    long subPartition(std::vector<int> &order, const long p, const long r);

    long anglePartition(std::vector<int> &order, const long p, const long r);

    void QuickMatrixSort(std::vector<int> &order, const long p, const long r);

    virtual void cosineSort()=0;

    /// Checks if row1<row2 ordered by adjacent column angle
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is smaller than row2 by angle
    virtual bool SmallerAngleRow(const int row1,const int row2)=0;

    /// Checks if row1>row2 ordered by adjacent column angle
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is larger than row2 by angle
    virtual bool LargerAngleRow(const int row1,const int row2)=0;

    /// Checks if row1<row2 ordered by column
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is smaller than row2
    virtual bool SmallerRow(const int row1,const int row2)=0;

    /// Checks if row1>row2 ordered by column
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is larger than row2
    virtual bool LargerRow(const int row1,const int row2)=0;

    std::vector<int>            m_order;
};

template <class scalar>
class SortedMatrix : public Eigen::Matrix<scalar,Eigen::Dynamic,Eigen::Dynamic>, public SortedTableau<scalar> {
public:
    typedef interval_def<scalar> type;
    typedef typename type::scalar_type refScalar;
    typedef typename type::MatrixS  MatrixS;
    typedef functions<refScalar> func;

    using MatrixS::coeff;
    using MatrixS::coeffRef;
    using MatrixS::rows;
    using MatrixS::cols;
    using MatrixS::resize;

    using SortedTableau<scalar>::m_order;
    using SortedTableau<scalar>::order;
    using SortedTableau<scalar>::zeroOrder;
    using SortedTableau<scalar>::ComputeRowOrderVector;

    SortedMatrix(int rows,int cols);

    SortedMatrix(const MatrixS &source,const OrderType &type=LexNone,bool transpose=false,bool norm=false);

    char compareZeroOrderRows(int row1,int row2);

    void QuickAngleSort();

    int numRows()                       { return rows(); }

    // Sets the size of the tableau
    void setSize(int rows,int cols)     { resize(rows,cols); }

    // Sets a given coefficient in the sorted Tableau
    void setCoeff(int row,int col,const scalar &src)    { coeffRef(row,col)=src; }

    // Sets the given row to src starting at col
    void setRow(int row,int col,const MatrixS &src);

    // Sets the given row to -src starting at col
    void negRow(int row,int col,const MatrixS &src);

    // Substracts the given row from dest
    void subRow(MatrixS &dest,int row);

    // Normalizes each row
    void normalize();

    /// Takes the ordering from  a different sort (eg a normalized one)
    bool copyOrder(SortedMatrix<scalar> &src);

    /// Retrieves the value of a tableau entry for a given row and basis column (see revised simplex algorithm)
    scalar entry(MatrixS &basis,const int row, const int col);

    ///Retrieves the magnitude of the vector in the direction normal to the given halfspace
    ///@param vector vector to verify
    ///@param row halfspace to check against
    scalar entry(const MatrixS &vector,const int row);

protected:
    /// Checks if row1<row2 ordered by adjacent column angle
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is smaller than row2 by angle
    bool SmallerAngleRow(const int row1,const int row2);

    /// Checks if row1>row2 ordered by adjacent column angle
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is larger than row2 by angle
    bool LargerAngleRow(const int row1,const int row2);

    /// Checks if row1<row2 ordered by column
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is smaller than row2
    bool SmallerRow(const int row1,const int row2);

    /// Checks if row1>row2 ordered by column
    /// @param row1 row to check for
    /// @param row2 row to check against
    /// @return true if row1 is larger than row2
    bool LargerRow(const int row1,const int row2);

    void cosineSort();

    bool SmallerCos(std::vector<scalar> &cosines,const int row1,const int row2);

    bool LargerCos(std::vector<scalar> &cosines,const int row1,const int row2);

    long subCosPartition(std::vector<int> &order, std::vector<scalar> &cosines, const long p, const long r);

    void QuickCosSort(std::vector<int> &order, std::vector<scalar> &cosines, const long p, const long r);

    void cosSort(std::vector<int> &order, std::vector<scalar> &cosines);

    refScalar maxTightWidth(const MatrixS &vector, const int row);

    refScalar maxTightWidth(const MatrixS &basis, const int row,const int col);

    /// Same as above but with tighter bounds
    scalar tightEntry(MatrixS &basis,const int row, const int col,const int iteration=0);

    ///Retrieves the magnitude of the vector in the direction normal to the given halfspace
    ///@param vector vector to verify
    ///@param row halfspace to check against
    inline scalar tightEntry(const MatrixS &vector, const long row);

    ///Relaxes the current basis by the given interval to cope with imprecisions
    void relaxBasis(MatrixS &basis,scalar width,int col);

public:
    std::vector<refScalar>      m_cosines;
    MatrixS                     m_norms;
};

}
#endif
