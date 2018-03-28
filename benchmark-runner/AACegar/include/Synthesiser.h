#ifndef SYNTHESISER_H
#define SYNTHESISER_H

#include <map>
#include <list>
#include "RefinedDynamicalSystem.h"

namespace abstract
{

struct Implementation
{
  int intbits;
  int fracbits;
  long double scale;
  long double max;
  long long fxp_one;
};

template <class scalar> class Synthesiser : public CegarSystem<scalar>
{
public:
    using typename JordanMatrix<scalar>::refScalar;
    using typename JordanMatrix<scalar>::func;
    using typename JordanMatrix<scalar>::complexS;
    using typename JordanMatrix<scalar>::MatrixS;
    using typename JordanMatrix<scalar>::MatrixC;
    using typename JordanMatrix<scalar>::SolverMatrixType;
    using typename JordanMatrix<scalar>::SolverComplexMatrixType;
    using typename AccelMatrix<scalar>::powerS;
    using typename AbstractMatrix<scalar>::powerList;
    using typename AbstractMatrix<scalar>::iteration_pair;
    using typename AbstractMatrix<scalar>::iteration_vector;

    using JordanMatrix<scalar>::m_dimension;
    using JordanMatrix<scalar>::m_isOne;
    using JordanMatrix<scalar>::m_hasOnes;
    using JordanMatrix<scalar>::m_hasMultiplicities;
    using JordanMatrix<scalar>::m_hasNegatives;
    using JordanMatrix<scalar>::m_jordanIndex;
    using JordanMatrix<scalar>::m_conjugatePair;
    using JordanMatrix<scalar>::m_roundings;
    using DynamicalSystem<scalar>::m_idimension;
    using DynamicalSystem<scalar>::m_fdimension;
    using DynamicalSystem<scalar>::m_odimension;
    using DynamicalSystem<scalar>::m_reachTime;
    using DynamicalSystem<scalar>::m_inputType;
    using DynamicalSystem<scalar>::m_initialState;
    using DynamicalSystem<scalar>::m_transformedInputs;
    using DynamicalSystem<scalar>::m_eigenVectors;
    using DynamicalSystem<scalar>::m_invEigenVectors;
    using DynamicalSystem<scalar>::m_pseudoEigenVectors;
    using DynamicalSystem<scalar>::m_invPseudoEigenVectors;
    using DynamicalSystem<scalar>::m_name;
    using DynamicalSystem<scalar>::m_source;
    using DynamicalSystem<scalar>::m_guard;
    using DynamicalSystem<scalar>::m_dynamics;
    using DynamicalSystem<scalar>::m_sensitivity;
    using DynamicalSystem<scalar>::m_inputs;
    using DynamicalSystem<scalar>::m_reference;
    using DynamicalSystem<scalar>::m_outputSensitivity;
    using DynamicalSystem<scalar>::m_outputGuard;
    using DynamicalSystem<scalar>::m_outputs;
    using DynamicalSystem<scalar>::m_safeReachTube;
    using DynamicalSystem<scalar>::m_templates;
    using DynamicalSystem<scalar>::m_feedback;
    using DynamicalSystem<scalar>::m_numVertices;
    using DynamicalSystem<scalar>::m_accelVertices;
    using DynamicalSystem<scalar>::m_abstractVertices;
    using DynamicalSystem<scalar>::m_abstractInputVertices;
    using DynamicalSystem<scalar>::m_accelInSupports;
    using DynamicalSystem<scalar>::m_paramValues;
    using DynamicalSystem<scalar>::m_dynamicParams;
    using DynamicalSystem<scalar>::m_pAbstractReachTube;
    using DynamicalSystem<scalar>::m_maxIterations;
    using DynamicalSystem<scalar>::m_loadTime;
    using DigitalSystem<scalar>::m_eigenValueCap;
    using CegarSystem<scalar>::m_initialOutputs;
    using CegarSystem<scalar>::m_observer;
    using CegarSystem<scalar>::m_observerDynamics;
    using CegarSystem<scalar>::m_observerSensitivity;
    using CegarSystem<scalar>::m_observerOutputSensitivity;
    using CegarSystem<scalar>::m_observerDynamicsError;
    using CegarSystem<scalar>::m_observerSensitivityError;
    using CegarSystem<scalar>::m_observerOutputSensitivityError;

    using DynamicalSystem<scalar>::ms_one;
    using DynamicalSystem<scalar>::ms_incremental;
    using DynamicalSystem<scalar>::ms_logger;
    using DynamicalSystem<scalar>::ms_trace_dynamics;
    using DynamicalSystem<scalar>::ms_emptyMatrix;
    using DynamicalSystem<scalar>::ms_fullAnswers;
    using CegarSystem<scalar>::ms_bvType;
    using CegarSystem<scalar>::ms_canonical;

    using JordanMatrix<scalar>::interToRef;
    using JordanMatrix<scalar>::refToInter;
    using JordanMatrix<scalar>::makeInverse;
    using JordanMatrix<scalar>::jordanToPseudoJordan;
    using JordanMatrix<scalar>::swapEigenvalues;
    using AbstractMatrix<scalar>::findIterations;
    using AbstractMatrix<scalar>::addSupportsAtIteration;
    using DynamicalSystem<scalar>::setName;
    using DynamicalSystem<scalar>::getTemplates;
    using DynamicalSystem<scalar>::getGuardPoly;
    using DynamicalSystem<scalar>::getInitPoly;
    using DynamicalSystem<scalar>::getInputPoly;
    using DynamicalSystem<scalar>::getReachPoly;
    using DynamicalSystem<scalar>::getTubePoly;
    using DynamicalSystem<scalar>::getAbsTubePoly;
    using DynamicalSystem<scalar>::getRoundedDirections;
    using DynamicalSystem<scalar>::makeLogahedralTemplates;
    using DynamicalSystem<scalar>::getAbstractReachTube;
    using DynamicalSystem<scalar>::getAbstractDynamics;
    using DynamicalSystem<scalar>::getAbstractVertices;
    using DynamicalSystem<scalar>::getInputVertices;
    using DynamicalSystem<scalar>::addSupportsAtIteration;
    using DynamicalSystem<scalar>::getAccelInSupports;
    using DynamicalSystem<scalar>::mergeAccelInSupports;
    using DynamicalSystem<scalar>::mergeAbstractSupports;
    using DynamicalSystem<scalar>::traceSupports;
    using DynamicalSystem<scalar>::getGuardedReachTube;
    using DynamicalSystem<scalar>::getOutputReachTube;
    using DynamicalSystem<scalar>::getDescription;
    using DynamicalSystem<scalar>::loadFromFile;
    using DynamicalSystem<scalar>::load;
    using DynamicalSystem<scalar>::save;
    using DynamicalSystem<scalar>::kronecker;
    using DynamicalSystem<scalar>::traceDebug;
    using DynamicalSystem<scalar>::changeDimensions;
    using DynamicalSystem<scalar>::setInputType;
    using DynamicalSystem<scalar>::loadGuard;
    using DynamicalSystem<scalar>::loadOutputGuard;
    using DynamicalSystem<scalar>::loadDynamics;
    using DynamicalSystem<scalar>::loadInitialState;
    using DynamicalSystem<scalar>::loadSensitivities;
    using DynamicalSystem<scalar>::loadOutputSensitivities;
    using DynamicalSystem<scalar>::loadIOSensitivities;
    using DynamicalSystem<scalar>::loadInputs;
    using DynamicalSystem<scalar>::loadSafeReachTube;
    using DynamicalSystem<scalar>::loadTemplates;
    using DynamicalSystem<scalar>::loadARMAXModel;
    using DynamicalSystem<scalar>::processError;
    using DynamicalSystem<scalar>::combineAB;
    using DigitalSystem<scalar>::sample;
    using DigitalSystem<scalar>::setSpeed;
    using DigitalSystem<scalar>::getSpeed;
    using DigitalSystem<scalar>::findMaxValue;
    using DigitalSystem<scalar>::findScale;
    using DigitalSystem<scalar>::getBits;
    using DigitalSystem<scalar>::fitToSpec;
    using CanonicalSystem<scalar>::capEigenValues;
    using CanonicalSystem<scalar>::makeReachabilityMatrices;
    using CanonicalSystem<scalar>::getDynamicPolynomialCoefficients;
    using CanonicalSystem<scalar>::updateFeedback;
    using CegarSystem<scalar>::loadFromSpaceXFiles;
    using CegarSystem<scalar>::loadOutputInitialState;
    using CegarSystem<scalar>::getRefinedDynamics;
    using CegarSystem<scalar>::getRefinedAbstractReachTube;
    using CegarSystem<scalar>::generateNoiseInput;
    using CegarSystem<scalar>::generateFeedbackInput;
    using CegarSystem<scalar>::refineAbstractDynamics;
    using CegarSystem<scalar>::findCounterExampleIterations;
    using CegarSystem<scalar>::calculateGuardFromOutput;
    using CegarSystem<scalar>::setIncrementalOrder;
    using CegarSystem<scalar>::makeObserver;
    using CegarSystem<scalar>::makeConvergentSystem;
    using CegarSystem<scalar>::makeClosedSystem;
    using CegarSystem<scalar>::getControllerDynBounds;
    using CegarSystem<scalar>::synthesiseDynamicBounds;
    using CegarSystem<scalar>::makeControlBounds;
    using CegarSystem<scalar>::checkExplicitReachability;
    using CegarSystem<scalar>::copy;

    typedef enum { eRefineNone, eRefinePhase, eRefineMagnitude, eRefineController, eMaxRefine } RefineType_t;

    /// Constructs an empty buffer
    /// @param dimension dimension of the space
    Synthesiser(int dimension=0,int idimension=0,int odimension=0);

    /// Synthetises an input vector
    AbstractPolyhedra<scalar> synthesiseInputs(inputType_t inputType,int precision,AbstractPolyhedra<scalar> &init,AbstractPolyhedra<scalar> &end,AbstractPolyhedra<scalar> &dynamics,MatrixS& templates,refScalar tightness);

    /// Maximises the vector interval
    AbstractPolyhedra<scalar> synthesiseInitialState(inputType_t inputType,AbstractPolyhedra<scalar> &input,AbstractPolyhedra<scalar> &end,AbstractPolyhedra<scalar> &dynamics);

    /// Synthetises the eigenstructure of a pole location
    AbstractPolyhedra<scalar> synthesiseEigenStructure(inputType_t inputType,int precision,int directions,AbstractPolyhedra<scalar> &end,AbstractPolyhedra<scalar> &dynamics);

    /// Retrieves the support set for the inputs
    MatrixS& getRefinedAccelInSupports();

    /// Corrects the support set by the input offset
    void demergeAccelInSupports(MatrixS &supports,MatrixS &inSupports,int numTemplates);

    /// Retrieves the reach tube given the refined dnamics
    AbstractPolyhedra<scalar>& getRefinedAbstractReachTube(space_t space,bool guarded=false);

    /// Loads a controller candidate for the system
    int loadController(const std::string &data,size_t pos=0,bool close=true);

    /// Loads an observer candidate for the system
    int loadObserver(const std::string &data,size_t pos=0);

    /// Loads a reference input set for the system
    int loadReference(const std::string &data,size_t pos=0,bool vertices=false);

    /// Loads and cleans up a state space synthesis result into the corresponding set
    bool loadSynthesisedResult(synthesisType_t type, AbstractPolyhedra<scalar> &result,MatrixS& templates,refScalar tightness,int time);

    /// Synthetises an input/state polyhedra given a set of conditions
    bool synthesiseAll(synthesisType_t type,powerS iteration,int precision,int directions,inputType_t inputType,space_t space,refScalar tightness);

    /// Processes a set of problems
    void processFiles(stringList &files,displayType_t displayType=eInequalities,space_t space=eNormalSpace,bool interval=false,optionList_t &options=optionList_t());

    /// Processes/modifies a problem stated by the input options
    int processOptions(optionList_t &options,displayType_t displayType=eInequalities,space_t space=eNormalSpace,bool interval=false,bool run=false);

    /// Processes a problems with varying parameters
    bool process(const displayType_t displayType=eInequalities,const space_t space=eNormalSpace,const bool interval=false,const bool append=false);

    /// Loads a pole placement description
    int loadPoles(const std::string &data,size_t pos=0);

    /// Calculates the closed loop dynamics given a plant and a controller
    bool makeClosedLoop(CegarSystem<scalar> &source,CegarSystem<scalar> &closedLoop,bool useObserver=false,bool makeReference=false,bool makeNoise=false);

    /// Calculates the closed loop dynamics given a plant and a controller
    bool makeClosedLoop(bool useObserver=false,bool makeReference=false,bool makeNoise=false)
    { return makeClosedLoop((m_sampled.m_dimension==m_dimension) ? m_sampled : *this,m_closedLoop,useObserver,makeReference,makeNoise); }

    /// Retrieves closed loop the dynamics matrix (A_c)
    MatrixS& getClosedLoopDynamics()        { return m_closedLoop.getBasicDynamics(); }

    /// Returns the complex poles matrix (J_c)
    MatrixC& getComplexPoles()              { return m_closedLoop.getEigenValues(); }

    /// Returns the pole matrix (J_c)
    MatrixS& getPoles()                     { return m_closedLoop.getPseudoEigenValues(); }

    /// Returns the nullSpace vectors of U_1^T(A-\lambda_iI) where B=[U_0 U_1][Z,0]
    std::vector<MatrixS> getNullSpace(const MatrixC &eigenValues);

    /// Returns a tranformation of the eigenvector inequalities into their corresponding nullSpace coefficients
    MatrixS getNullSpaceFaces(MatrixS &faces,std::vector<MatrixS> &nullSpace);

    /// Solves the Sylvester equation AX+XB=C for X
    /// @return X
    MatrixS solveSylvester(const MatrixS &A,const MatrixS &B,const MatrixS &C,bool BisDiagonal=false);

    /// Retrieves a set of viable Left Eigenvectors closest to a desired set
    MatrixS getValidLeftEigenVectors(const MatrixS &pseudoEigenValues,const MatrixS &desired);

    /// Retrieves a set of viable Left Eigenvectors for given eigenvalues
    MatrixS getLeftEigenVectors(const MatrixS &pseudoEigenValues,AbstractPolyhedra<scalar> &eigenVectorSpace);

    AbstractPolyhedra<scalar>& getAbstractClosedLoopDynamics(const inputType_t inputType)
                                            { return m_closedLoop.getAbstractDynamics(inputType); }

    ///Creates a c header (defines and data types) for CEGIS
    std::string makeCEGISHeader(bool observer,bool intervals=true,bool scaling=false);

    ///Adds a transformt element to t he stream
    void maketransformt(std::stringstream &stream, std::string name,const MatrixS &matrix, const scalar &scale, bool intervals);

    ///Adds a implt element to the stream
    void makeimplt(std::stringstream &stream, std::string name,int int_bits,int frac_bits,int spec_int_bits);

    ///Adds a set of vertices, vectors and supports that describe a closed safety spec
    void makeVertexSupportCombo(std::stringstream &stream, std::string name, MatrixS vertices, MatrixS inputs, AbstractPolyhedra<scalar> &bounds, bool normalize=true);

    ///Creates a c header file for CEGIS
    bool makeCEGISFiles(bool observer=false);

protected:
    ///Creates a c specification for CEGIS
    std::string makeCEGISDescription(bool observer,bool intervals=true,bool scaling=false);

    ///Creates a list of iterations for CEGIS
    std::string makeCEGISIterations(CegarSystem<scalar> &closedLoop,int &existing,int max,RefineType_t stage=eRefineNone,int pass=0,refScalar largestError=func::ms_infinity);
    std::string makeCEGISIterations(int &existing,int max,RefineType_t stage=eRefineNone,int pass=0,refScalar largestError=func::ms_infinity)
    { return makeCEGISIterations(m_closedLoop,existing,max,stage,pass,largestError); }

    ///Creates a list of violating state-input pairs with their lowest corresponding iteration
    void getIterationPairs(std::vector<iteration_pair>& result, powerList &iterations,AbstractPolyhedra<scalar> &safe,const MatrixS &vertices,const MatrixS &inVertices);

    /// Retrieves the index of the eigenvalue with the largest angle
    int dominantRotation(MatrixC eigenvalues,std::vector<int> &conjugatePairs);

    /// Retrieves the index of the eigenvalue with the largest magnitude
    int dominantEigenvalue(MatrixC &eigenvalues,std::vector<int> &conjugatePairs,int count=0);

    /// Refines the sampling of the plant based on the closed loop resampling
    bool refineSampling(CegarSystem<scalar> &source,CegarSystem<scalar> &closedLoop,bool observer);

    /// Refines the synthesised control to obtain a minimal phase on all eigenvalues within the spec
    bool refinePhase(MatrixC &eigenvalues,AbstractPolyhedra<scalar> &bounds,std::vector<int> &conjugatePairs);

    /// Refines the synthesised control to obtain a better set of eigenvalues within the spec
    bool refineEigenvalues(CegarSystem<scalar> &source,CegarSystem<scalar> &closedLoop,bool observer,RefineType_t type,int pass,int count);

    /// Refines the synthesised control to obtain a minimal magnitude on all eigenvalues within the spec
    bool refineMagnitude(MatrixC &eigenvalues,AbstractPolyhedra<scalar> &bounds,std::vector<int> &conjugatePairs,int pass);

    ///Explicitly checks the reachability for a bounded time horizon
    powerS checkExplicitReachability(powerS steps,bool useObserver);

    std::map<std::string, Implementation> m_implementation;
public:
    CegarSystem<scalar>     m_closedLoop;
    CegarSystem<scalar>     m_sampled;
    synthesisType_t         m_synthType;
    refScalar               m_factor;
    bool                    m_ioFeedback;
    int                     m_refineCount;
};

}

#endif //SYNTHESISER_H
