//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is based on Komei Fukuda's ccd implementation and as such supplied under the GPL license agreement (see license.txt)

#ifndef TABLEAU_H
#define TABLEAU_H

#include <vector>
#include <fstream>

#include "Set.h"
#include "Scalar.h"
#include "MatrixToString.h"
#include "RowSort.h"
#include "SparseRowSort.h"

namespace abstract{
typedef enum { IneToExt, ExtToIne, LPMax, LPMin } ConversionType_t;

template <class scalar> class Tableau {
public:
    typedef interval_def<scalar> type;
    typedef typename type::scalar_type refScalar;
    typedef typename type::complexS complexS;
    typedef typename type::MatrixS  MatrixS;
    typedef typename type::MatrixC  MatrixC;
    typedef typename type::complexR complexR;
    typedef typename type::MatrixR  MatrixR;
    typedef typename type::MatrixRC MatrixRC;

    typedef functions<refScalar> func;

    typedef enum { eResetBasis, eRebaseBasis, eUseDefaultBasis, eKeepBasis, eCheckBasis } ResetType_t;

    Tableau(const int size,const int dimension);
    ~Tableau();
protected:
    /// Selects a pivot row and column based on the first available non-zero entry
    /// @param rowmax maximum available row for pivot
    /// @param noPivotRow set of restricted rows that cannot pivot
    /// @param noPivotCol set of restricted columns that cannot pivot
    /// @param pivot return row and column to pivot on
    bool SelectPivot(const long rowmax, const Set &noPivotRow, const Set &noPivotCol, pivot_t &pivot);

    /// Performs a pivot around a given row and column
    /// @param pivot return row and column to pivot on
    void ColumnPivot(const pivot_t &pivot);

    /// Performs a pivot around a given row and column
    /// updates the basic and non-basic variables
    /// @param pivot return row and column to pivot on
    bool ColumnPivotAndUpdate(const pivot_t &pivot);

    /// Finds a basis for vertex enumeration
    /// @param pRowSelected set of selected rows to find basis
    /// @param pivotRows corresponding pivot row of each selected column in the enumeration
    int FindEnumerationBasis(Set &rowSelected,std::vector<int> &pivotRows);

    /// Finds a [possibly] feasible basis to start the maximise process
    int FindLPBasis();

    /// Finds a [possibly] feasible basis to start solving from
    /// @param resetType indicates if the algorithm should use a precalculated feasible solution, rebase or reset
    /// @return number of iterations used to find the basis
    int FindFeasBasis(const ResetType_t resetType=eResetBasis);

    /// Restarts the Simplex process at the current vertex
    int Rebase();

    /// Creates a set of the row inequalities (in Av=b) that are equal to zero
    /// @param vector vector to check for equality
    /// @param ZeroSet resulting set for the inequalities
    void ZeroIndexSet(const MatrixS &vector, Set &ZeroSet);

    /// normalizes a vector so that the largest coefficient is 1
    /// @param pVector pointer to the vector data to normalize
    void Normalize(MatrixS &vector);

    /// Initializes all basic and non-basic variables and sets the basis to identity
    void ResetTableau();

    /// Loads the tableau from the face and supprot description
    bool loadTableau(bool clearObjective);

    /// Sets an order for the Tableau given the OrderType
    /// @param type order to use for the tableau. It can be a simple index order or by column member magnitude
    void ComputeRowOrderVector(const OrderType &type);
public:
    /// Loads a description into the tableau (Ax<b)
    /// @param faces (A-Matrix) normal to the half-spaces describing the problem
    /// @param supports (b-vector) boundaries of the half-spaces (given as support functions)
    /// @param transpose, directions are col vectors when true and row vectors when false
    /// @return false if failed
    virtual bool load(const MatrixS &faces,const MatrixS &supports,const bool transpose=false);

    /// Relaxes the polyhedra to its outer supports (when using interval representations)
    void toOuter(bool force=false);

    /// Constrains the polyhedra to its inner supports (when using interval representations)
    void toInner(bool force=false);

    /// Removes the intervals on each vector, modifying the support by adding a calculated maximum interval given the range
    /// this function is only used with intervals
    /// @param ranges intervals ensured to contain any possible valuation of each variable.
    void toCentralAngle(const MatrixS &ranges);

    /// retrieves the name of the tableau used for debugging and display purposes
    virtual std::string getName()           { return "Tableau"; }

    /// Indicates if the tableau is empty
    bool isEmpty() const;

    ///Logs the tableau contents into trace.txt when debugging is set
    virtual void logTableau(const std::string parameters="",bool force=false);

    ///Logs the basis inverse contents into trace.txt when debugging is set
    void logBasis(const int row,const int col);

    ///Logs the current basic variable set into trace.txt when debugging is set
    void logBasic();

    ///Logs the current non-basic variable set into trace.txt when debugging is set
    void logNonBasic();

    //void logData(const std::string data);

    /// Retrieves the number of variables in the linear problem
    inline int getDimension() const             { return m_dimension-1; }

    ///Retrieves the ordered element at the given position
    /// @param row position to search in the ordered set
    /// @return corresponding row of the tableau at the given position
    inline int order(const int row)             { return m_pSortedTableau->order(row); }

    const std::vector<int>& getSupportRows()    { return m_nonBasicRow; }

    SparseSortedMatrix<scalar>& getSparseTableau()  { return m_sparseTableau; }
protected:
    int                         m_dimension;            //Size of the problem (number of variables including the support function)
    int                         m_size;                 //Number of inequalities/vertices in the tableau
    bool                        m_isNormalised;         //Indicates if the inequalities have been normalized
    refScalar                   m_zero;                 //Expected error for zero values
    int                         m_objectiveRow;         //0-based row numbe of the objective function
    int                         m_evidenceRow;          //If non-negative indicates the row at which the solution was found unfeasible
    int                         m_evidenceCol;          //If non-negative indicates the column for which the solution was found unfeasible
    int                         m_rank;                 //Number of iterations performed on the last section
    ConversionType_t            Conversion;
    MatrixS                     m_faces;                //Inequality vectors
    MatrixS                     m_supports;             //Corresponding values of each inequality vector (support function)
    SortedMatrix<scalar>        m_tableau;              //Full inequality set [m_supports m_faces ; 0 max]
    SparseSortedMatrix<scalar>  m_sparseTableau;        //Full inequality set [m_supports m_faces ; 0 max]
    SortedTableau<scalar>      *m_pSortedTableau;
    MatrixS                     m_basisInverse;         //Inverse of the basis for the dual simplex problem
    MatrixS                     m_auxiliaryRow;         //Saves the auxiliary row data for the dual simplex
    std::vector<int>            m_basicVars;            //Vector containig the basic variable corresponding to each row (-1 if none)
    std::vector<int>            m_nonBasicRow;          //Vector containing the row that corresponds to each basic variable
    MatrixS                     m_feasBasisInverse;     //Stores a pre-calculated feasible basis
    std::vector<int>            m_feasBasicVars;        //Stores the precalculated state of the basicVars
    std::vector<int>            m_feasNonBasicRow;      //Stores the precalculated state of the nonBasicRow
    pivot_t                     m_lastPivot;
    std::ofstream               ms_trace;
    static MatToStr<scalar>     ms_logger;
    static MatToStr<scalar>     ms_decoder;
public:
    static bool                 ms_trace_pivots[eMaxTracePivots];
    static bool                 ms_useBasis;
};
}

#endif//TABLEAU_H
