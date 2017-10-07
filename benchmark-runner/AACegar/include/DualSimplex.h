//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is based on Komei Fukuda's ccd implementation and as such supplied under the GPL license agreement (see license.txt)

#include <time.h>
#include <vector>
#include "Tableau.h"

#ifndef DUAL_SIMPLEX_H
#define DUAL_SIMPLEX_H

namespace abstract{

template <class scalar> class DualSimplex : public Tableau<scalar> {
public:
    using typename Tableau<scalar>::refScalar;
    using typename Tableau<scalar>::type;
    using typename Tableau<scalar>::func;
    using typename Tableau<scalar>::MatrixS;
    using typename Tableau<scalar>::ResetType_t;
    using Tableau<scalar>::eResetBasis;
    using Tableau<scalar>::eRebaseBasis;
    using Tableau<scalar>::eUseDefaultBasis;
    using Tableau<scalar>::eKeepBasis;
    using Tableau<scalar>::eCheckBasis;

    using Tableau<scalar>::m_dimension;
    using Tableau<scalar>::m_size;
    using Tableau<scalar>::m_pSortedTableau;
    using Tableau<scalar>::m_auxiliaryRow;
    using Tableau<scalar>::m_basisInverse;
    using Tableau<scalar>::m_objectiveRow;
    using Tableau<scalar>::m_nonBasicRow;
    using Tableau<scalar>::m_basicVars;
    using Tableau<scalar>::m_feasBasisInverse;
    using Tableau<scalar>::m_feasNonBasicRow;
    using Tableau<scalar>::m_feasBasicVars;
    using Tableau<scalar>::m_faces;
    using Tableau<scalar>::m_supports;
    using Tableau<scalar>::m_zero;
    using Tableau<scalar>::m_rank;
    using Tableau<scalar>::m_evidenceCol;
    using Tableau<scalar>::m_lastPivot;

    using Tableau<scalar>::ms_useBasis;
    using Tableau<scalar>::ms_logger;
    using Tableau<scalar>::ms_trace_tableau;
    using Tableau<scalar>::ms_trace_pivots;
    using Tableau<scalar>::ms_trace_time;
    using Tableau<scalar>::ms_trace_errors;

    using Tableau<scalar>::getDimension;
    using Tableau<scalar>::Rebase;
    using Tableau<scalar>::ResetTableau;
    using Tableau<scalar>::logTableau;
    using Tableau<scalar>::logBasis;
    using Tableau<scalar>::FindFeasBasis;
    using Tableau<scalar>::ColumnPivotAndUpdate;

    typedef enum { eUnderAprox, eNoAprox, eOverAprox } AproxType_t;
    typedef enum { eUndecided, eOptimal, eInconsistent, eDualInconsistent, eStrucInconsistent, eStrucDualInconsistent, eUnbounded, eDualUnbounded } LPStatusType_t;

    DualSimplex(const int size,const int dimension);

    /// Loads a description into the tableau (Ax<b) and clears cached data
    /// @param faces (A-Matrix) normal to the half-spaces describing the problem
    /// @param supports (b-vector) boundaries of the half-spaces (given as support functions)
    /// @param transpose, directions are col vectors when true and row vectors when false
    /// @return true if successful
    virtual bool load(const MatrixS &faces,const MatrixS &supports,const bool transpose=false);

    /// Selects a pivot for the dual solution (find an optimal solution whilst remaining fasible)
    /// @param pivot return row and column to pivot on
    /// @return true if a pivot is found (if no pivot is found, m_status indicates the reason
    bool SelectPrimalSimplexPivot(pivot_t &pivot);

    /// Selects a pivot for the dual solution (find a feasible solution whilst remaining optimal)
    /// @param Phase1 indicates if the problem is on the initial phase
    /// @param pivot return row and column to pivot on
    /// @return true if a pivot is found (if no pivot is found, m_status indicates the reason
    bool SelectDualSimplexPivot(const bool Phase1,pivot_t &pivot);

    /// Selects a pivot for the dual solution (find a feasible solution whilst remaining optimal)
    /// @param pivot return row and column to pivot on
    /// @return true if the pivot is found (if no pivot is found, m_status indicates the reason
    bool SelectIncrementalSimplexPivot(pivot_t &pivot);

    /// Selects a pivot for the dual solution (find a feasible solution whilst remaining optimal)
    /// @param pivot return row and column to pivot on
    /// @return true if a pivot is found (if no pivot is found, m_status indicates the reason
    bool SelectCrissCrossPivot(pivot_t &pivot);

    /// Selects a pivot row and column based on the first available all negative block entry
    /// @param rowmax maximum available row for pivot
    /// @param noPivotRow set of restricted rows that cannot pivot
    /// @param noPivotCol set of restricted columns that cannot pivot
    /// @param pivot return row and column to pivot on
    bool SelectOredPivot(const long rowmax, const Set &noPivotRow, const Set &noPivotCol, pivot_t &pivot);

    /// Performs a pivot around the auxiliary row
    /// @param col column to pivot on
    bool AuxiliaryPivotAndUpdate(const long col);

    /// Find the corresponding row with the minimum entry value for a given column
    int findMinRow(int col);

    /// Find the corresponding row with the maximum entry value for a given column
    int findMaxRow(int col);

    /// Finds the dual feasible basis for a supplied problem
    /// @return number of iterations used to find the basis
    int FindDualFeasibleBasis();

    /// Creates a list of redundant/non-redundant rows of the tableau
    /// @param isRedundant vector to fill with redundant flag for each row
    /// @return number of found redundancies
    int findRedundancies(std::vector<bool> &isRedundant, refScalar tolerance);

    /// Clears redundant faces in the polyhedra (caused by intersections and reductions)
    /// @return true if successful
    virtual bool removeRedundancies(refScalar tolerance=0,bool recompute=false);

    /// Maximises a vector direction.
    /// @param vector vector data to be maximised
    /// @param resetType indicates if the algorithm should use a precalculated feasible solution, rebase or reset
    /// @return support function of the vector
    scalar maximise(const std::vector<scalar> &vector,const ResetType_t resetType=eResetBasis);

    /// Maximises a vector direction (ie finds the support function for the given vector)
    /// @param vector vector to be maximised
    /// @param resetType indicates if the algorithm should use a precalculated feasible solution, rebase or reset
    /// @return support function of the vector
    scalar maximise(const MatrixS &vector,const ResetType_t resetType=eResetBasis,bool transpose=false);

    /// Maximises a set of directions (ie finds the support function for each direction)
    /// @param vectors column vectors to be maximised
    /// @param pSupports array to place the results in (row based)
    /// @param overapprox if true the simplex will use the outer skin of the polyhedra (upper supports), otherwise the inside layer(lower supports)
    /// @param incremental indicates if the simplex should find the directions vertices incrementally
    /// @return true if successful
    virtual bool maximiseAll(const MatrixS &vectors, MatrixS &supports,AproxType_t aprox=eOverAprox,OrderType order=LexNone);

    int ceMaximise(SortedMatrix<scalar> &sortedVectors, MatrixS &supports, MatrixS &inSupports,refScalar &max,MatrixS &ce,scalar &result,int start=0);

    /// Normalises the directions of the faces
    /// @param reload if true updates related data to the new faces
    void normalise(const bool reload=true);

    /// Retrieves an overapproximation support function related to the last solution
    scalar getOverSupport(MatrixS &vector);

    /// Retrieves the largest support related to the last solution
    scalar getMaxSupport(scalar &ceiling);

    /// Retrieves the smallest support related to the last solution
    scalar getMinSupport();

    /// finds the maximum for the selected problem (tableau)
    /// @param resetType indicates if the algorithm should use a precalculated feasible solution, rebase or reset
    /// @return maximum of the last loaded objective function
    virtual scalar processMaximize(ResetType_t resetType=eResetBasis);

    /// finds the maximum for the selected problem given an added restriction(tableau)
    /// @return maximum of the last loaded objective function
    scalar processIncremental();

    /// Finds a [possibly] feasible basis to start solving from
    /// @param resetType indicates if the algorithm should use a precalculated feasible solution, rebase or reset
    /// @return number of iterations used to find the basis
    int FindFeasOrBasis(int orBlockSize,const ResetType_t resetType=eResetBasis);

    /// Finds a [possibly] feasible basis to start the maximise process
    int FindOrLPBasis();

    /// Finds the objective row costs
    bool FindCosts();

    /// Saves the time and iteration count data for the given process
    /// @param time time in ms used to perform all pivots until this call
    /// @param process calling the logger
    void logPivotCount(const int time,const std::string process);

protected:
    /// Retrieves the value of a tableau entry for a given row an column (see revised simplex algorithm)
    scalar auxEntry(const int col);
public:
    LPStatusType_t      m_status;               //Indicates the status of the simplex
    MatrixS             m_costs;                //Saves the objective function costs
    int                 m_iterations;           //Number of iterations performed on the last operation
    int                 m_orBlockSize;          //Size of each block that corresponds to an or constraint
    static bool         ms_incremental;
    refScalar           m_max;
  };
}
#endif//DUAL_SIMPLEX_H
