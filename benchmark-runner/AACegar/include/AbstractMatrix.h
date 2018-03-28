//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#ifndef ABTRACT_MATRIX_H
#define ABTRACT_MATRIX_H

#include <map>
#include "AccelMatrix.h"
#include "AbstractPolyhedra.h"

namespace abstract
{

/// Implements the interpolation algorithms for a given profile
template <class scalar> class AbstractMatrix : public AccelMatrix<scalar>
{
public:
    using typename JordanMatrix<scalar>::refScalar;
    using typename JordanMatrix<scalar>::type;
    using typename JordanMatrix<scalar>::func;
    using typename JordanMatrix<scalar>::complexS;
    using typename JordanMatrix<scalar>::MatrixS;
    using typename JordanMatrix<scalar>::MatrixC;
    using typename AccelMatrix<scalar>::powerS;

    typedef typename type::sparseMatrix SMatrixS;
    typedef typename type::sparseVector SVectorS;
    typedef std::map<powerS,std::pair<int,powerS> > powerList;
    typedef std::map<powerS,MatrixS> counterexampleList;
    typedef typename type::iteration_pair iteration_pair;
    typedef std::vector<iteration_pair> iteration_vector;


    using JordanMatrix<scalar>::m_dimension;
    using JordanMatrix<scalar>::m_error;
    using JordanMatrix<scalar>::m_isNegative;
    using JordanMatrix<scalar>::m_jordanIndex;
    using JordanMatrix<scalar>::m_conjugatePair;
    using JordanMatrix<scalar>::m_roundings;
    using JordanMatrix<scalar>::m_isOne;
    using JordanMatrix<scalar>::m_hasMultiplicities;
    using JordanMatrix<scalar>::m_eigenValues;
    using JordanMatrix<scalar>::m_eigenNorms;
    using JordanMatrix<scalar>::m_cosFactors;
    using AccelMatrix<scalar>::m_foldedEigenValues;
    using AccelMatrix<scalar>::ms_roundJordanBlocks;
    using JordanMatrix<scalar>::m_zero;
    using JordanMatrix<scalar>::ms_one;
    using JordanMatrix<scalar>::ms_complexOne;
    using JordanMatrix<scalar>::ms_logger;
    using JordanMatrix<scalar>::ms_decoder;
    using JordanMatrix<scalar>::ms_trace_dynamics;

    using JordanMatrix<scalar>::jordanToPseudoJordan;
    using JordanMatrix<scalar>::rotates;
    using AccelMatrix<scalar>::binomial;
    using AccelMatrix<scalar>::roundIndex;

    /// Constructs an empty buffer
    /// @param pParent owner of the system
    AbstractMatrix(const int dimension);

    /// retrieves the dynamics matrix for a given iteration (n)
    /// @param iteration number of iterations since the initial state
    /// @param precision number of faces expressed as a power of 2
    /// @param inputType indicates the type of inputs to process
    /// @param normalised indicates if we are looking for normalised dynamics for input transformations
    AbstractPolyhedra<scalar>& getAbstractDynamics(const powerS iteration,int precision,const inputType_t inputType=eNoInputs,const bool normalised=false);

    /// Retrieves the last calculated dynamics
    /// @param inputType identifies the type of dynamics
    AbstractPolyhedra<scalar>& getAbstractDynamics(const inputType_t inputType=eNoInputs);

    /// Adds a set of supports at the given iteration in order to refine the abstraction
    bool addSupportsAtIteration(AbstractPolyhedra<scalar>& dynamics,powerS iteration,powerS max);

    /// Adds a set of supports at the given iterations in order to refine the abstraction
    bool addSupportsAtIterations(AbstractPolyhedra<scalar>& dynamics,powerList &iterations,const MatrixS &source);

    /// Changes the default dimension of the system
    /// @param dimension dimension of the statespace
    virtual void changeDimensions(const int dimension);

    /// Indicates if the matrix dynamics are divergent
    /// @param strict if true returns only true if no eigenvalues are convergent
    bool isDivergent(const bool strict=false, scalar speed=func::ms_1);

    /// Retrieves the largest eigenvalue norm
    scalar largestEigenNorm();

protected:
    /// Retrieves the nth power of coeff in the given row of the jordan matrix
    /// Not that in a jordan block this corresponds to the kth column of J_s^n
    /// @param coef eigenvalue to exonentiate
    /// @param n power to raise coeff to
    /// @param row eigenvalue row identifying the location of the eigenvalue
    complexS condPow(complexS coef,const powerS n,int row);

    /// Retrieves the nth power of coeff in the given row of the jordan matrix
    /// Not that in a jordan block this corresponds to the kth column of J_s^n
    /// @param coef pseudoeigenvalue to exonentiate
    /// @param n power to raise coef to
    /// @param row pseudoeigenvalue row identifying the location of the eigenvalue
    scalar condPow(scalar coef,const powerS n,const int row);

    /// Retrieves the difference between the nth and nth+1 powers of coeff in the given row of the jordan matrix
    /// Not that in a jordan block this corresponds to the kth column of J_s^n
    /// @param coef pseudoeigenvalue to exonentiate
    /// @param n power to raise coef to
    /// @param row pseudoeigenvalue row identifying the location of the eigenvalue
    scalar diffPow(scalar coef,const powerS n,int row);

    /// Calculates the expected iteration of coefficient to obtain value
    /// @param coef pseudoeigenvalue to exonentiate
    /// @param value expected result of exponentiation
    /// @param range width of the power interval that matches the point
    /// @return n power to raise coef to
    powerS condLog(const refScalar &coef,refScalar value,int row,powerS &range);
    powerS binomialCondLog(const refScalar &coef,refScalar value,int row,powerS &range);

    /// Finds the coefficient, magnitude, maximum, and minimum for the abstract vector at row
    void findCoeffBounds(int row,powerS iteration,complexS &coef,scalar &mag,scalar &min,scalar &max);

    /// low=high and high=low
    /// @param low presumed low value (which is in fact high)
    /// @param low presumed high value (which is in fact low)
    void swapValues(scalar &low,scalar &high);

    void checkRange(const int row,const powerS iteration,const scalar mag,scalar &min,scalar &max);

    void fillConjugateSupport(const int row1,const int row2,const scalar &angle,const scalar &max,const powerS iter);

    void findConjugateSupports(const int row,const complexS &coef,const powerS iteration,int precision);

    void fillQuadraticConjugateSupport(const int row1,const int row2,scalar mag1,scalar mag2,powerS iteration,int precision);

    bool fillLastConjugateSupportFromPoints(const int row1,const int row2,const scalar x1,const scalar y1,const scalar x2,const scalar y2,const scalar xRef,const scalar yRef,const bool hasLastQuarter,const powerS iter);

    /// Given 2 points and a reference point, creates a support function perpendicular to the plane that joins the 2 points and that has the reference on the 'inside'
    void fillSupportFromPoints(const int row1,const int row2,const scalar &x1,const scalar &y1,const scalar &x2,const scalar &y2,const scalar &xRef,const scalar &yRef,const powerS iter);

    ///Finds the maximum and minimum iterations whose supports enclose a conjugate pair
    ///@return true if the envelope is incomplete (ie it needs a cut from start to end)
    bool findConjugateBounds(const int row, powerS iter, powerS &start, powerS &end);

    /// Given a conjugate pair, fills a support tangent to the point at iteration.
    void fillConjugateSupportFromIter(const int row1,const int row2,powerS iter);

    /// Given a conjugate pair, fills a support set tangent to enveloping ellipse up to iteration.
    void fillConjugateSupportsFromIter(const int row1,const int row2,powerS iter,int precision);

    /// Fills a support for the chord of a halfmoon created by two eigenvalue norms.
    scalar fillChordSupportFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter);

    /// Finds the expected support iteration for a given eigenvalue pair and angle
    powerS findAngleIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,scalar angle);

    /// Given a row pair and an angle, creates a support function in the direction of the angle for the given pair of eigenvalues
    bool fillSupportFromAngle(const int row1,const int row2,const scalar &mag1,const scalar &mag2,scalar angle);

    ///Given a row pair and an iteration number, creates a support function perpendicular to the plane that joins the nth and nth+1 iterations and that has the original point on the 'inside'
    void fillSupportFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter);

    /// Fills a set of supports given a pair and an iteration number
    void fillSupportsFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter,int precision);

    ///Given a row pair (one conjugate, one real) and an iteration number, creates a support function perpendicular to the plane that joins the nth and nth+1 iterations and that has the original point on the 'inside'
    void fillSemiConjugateSupportFromIter(const int row1,const int row2,const scalar &mag1,const scalar &mag2,powerS iter);

    /// Given 2 points and a reference point, creates a support function perpendicular to the plane that joins the 2 points and that has the reference on the 'inside'
    /// It also checks for the extreme point (largest magnitude) to see if the support includes it otherwise returns false
    bool testConjugateSupportFromPoints(const scalar &x1,const scalar &y1,const scalar &x2,const scalar &y2,const scalar &xExt,const scalar &yExt);

    /// Given 2 points and a reference point, creates a support function perpendicular to the plane that joins the 2 points and that has the reference on the 'inside'
    /// It also checks for the extreme point (largest magnitude) to see if the support includes it otherwise returns false
    bool fillConjugateSupportFromPoints(const int row1,const int row2,const scalar &x1,const scalar &y1,const scalar &x2,const scalar &y2,const scalar &xExt,const scalar &yExt,const powerS iter);

    /// Given a range of points that stand in a line, creates two support functions representing that line (if eigenvalues are complex, then it creates lines tangent to the circle)
    void fillLinearSupportFromPoints(const int row1,const int row2,const scalar &min1,const scalar &max1,const scalar &min2,const scalar &max2,const powerS iter);

    void fillQuadraticSupport(const int row1,const int row2,scalar mag1,scalar mag2,powerS iteration,int precision);

    /// Sets two support functions in the positive (max) and negative (min) directions of the 1D vector of row, mapped on R^n (all other values set to 0)
    void fillDirection(const int row,const scalar &min,const scalar &max);

    /// Sets two support functions in the positive (max) and negative (min) directions of the 2D vector (dir1,dir2), mapped on R^n (all other values set to 0)
    void fillDirections(const int row1,const int row2,const scalar &dir1,const scalar &dir2,const scalar &min,const scalar &max,const powerS iter);

    /// Cleans recently generated supports eliminating redundant ones.
    void wrapUp();

    /// Finds the points at which each jordan column is maximum and fills the corresponding vector
    void findZeniths();

    /// lists the first source row for a folded set of dimensions
    void findUnfolded();

    /// Finds the frequency of rotation of each conjugate pair and fills the corresponding vector
    void findFrequencies();

    /// Calculates the number of iterations necessary to reacha fixpoint
    powerS calculateMaxIterations(powerS max=func::ms_infPower);

    /// Finds the corresponding iterations that may generate dynamics violating the given bounds and creates faces for these iterations
    bool refineAbstractDynamics(AbstractPolyhedra<scalar> &bounds,bool useEigenCloud);

    /// Finds the corresponding iteration that generates dynamics in the direction of the given vector
    bool findIterations(AbstractPolyhedra<scalar> &bounds,std::map<int,iteration_vector>& iterations,MatrixS &supports,bool minOnly,int outerMerge=-1,int innerMerge=1);

    /// Finds the corresponding iteration that generates dynamics close to the given point
    void findIterations(const MatrixS &point,powerList &iterations,bool isVector=false);

    /// Finds the corresponding iteration that generates dynamics in between existing supports
    void findIterations(AbstractPolyhedra<scalar> &dynamics,powerList &iterations);

    int firstVarBlock()         { return m_firstVarBlock; }

    /// Retrieves the number of non-correlated dimensions in the eigenspace
    int getRoundedDimension();

    /// Retrieves the corresponding circular vectors for a given set of vectors
    /// @param result container for the resulting directions
    /// @param vectors origianl directions to transform
    /// @param transposed indicates if the supplied vectors are row oriented
    MatrixS& getRoundedDirections(MatrixS &result,const MatrixS &vectors,bool transposed=false);

    /// Builds a list of eigenvalues for each iteration up to maxIteration
    /// @param maxIteration number of iterations to evaluate (evaluates first item of jordan block only)
    /// @param conjugateOnly evaluates only conjugate points
    MatrixS& getEigenCloud(powerS maxIteration,bool conjugateOnly=true);

    /// Builds a list of eigenvalue norms (rounded directions) for each iteration up to maxIteration
    MatrixS& getRoundEigenCloud();

    /// Retrieve an upper bound to the support given by the eigen cloud
    /// @param vector vector to find the support for.
    refScalar eigenCloudSupport(MatrixS &vector,powerS &iter);

    /// Creates conjugate supports for unequal eigenvalues
    /// @param col1 column number of first direction
    /// @param col2 column number of second direction
    void fillCrossConjugateSupports(int col1,int col2);

    /// Creates conjugate supports for unequal eigenvalues
    /// @param col1 column number of first direction
    /// @param col2 column number of second direction
    /// @param dir1 weight of first direction
    /// @param dir2 weight of second direction
    void fillCrossConjugateSupports(int col1,int col2,const scalar& dir1,const scalar& dir2,const powerS iter);

    /// Creates conjugate supports for unequal eigenvalues
    /// @param col1 column number of first direction
    /// @param col2 column number of second direction
    /// @param iter iteration at which the support should be found (determines the vector angle)
    void fillCrossConjugateSupportFromIter(int col1,int col2,powerS iter);

    ///Retrieves a hyperbox ensured to contain all powers of eigenvalues
    /// if intervals are not used, it contains the maximum norm of each powered eigenvalue
    /// @param iter maximum iteration to evaluate
    MatrixS boundingHyperBox(powerS iter);
protected:
    inputType_t                 m_inputType;
    int                         m_precision;
    powerS                      m_maxIterations;
    int                         m_pos;
    int                         m_firstVarBlock;
    std::vector<int>            m_zeniths;
    std::vector<int>            m_freq;
    std::vector<int>            m_unfolded;
    scalar                      m_sampleTime;
    scalar                      m_delayTime;
    iteration_vector            m_iterations;
public:
    MatrixS                     m_supports;
    SMatrixS                    m_directions;
    MatrixS                     m_eigenCloud;
    MatrixS                     m_roundEigenCloud;
    AbstractPolyhedra<scalar>   m_abstractDynamics;
    AbstractPolyhedra<scalar>   m_abstractInputDynamics;
    AbstractPolyhedra<scalar>   m_abstractRoundDynamics;
    static bool                 ms_continuous;
    static bool                 ms_incremental;
    static bool                 ms_sparse;
};

}

#endif
