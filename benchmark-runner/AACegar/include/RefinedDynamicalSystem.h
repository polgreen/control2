#ifndef CEGARSYSTEM_H
#define CEGARSYSTEM_H

#include <map>
#include <boost/timer.hpp>

#include "CanonicalSystem.h"

namespace abstract
{
template <class scalar> class CegarSystem : public CanonicalSystem<scalar>
{
public:
    using typename JordanMatrix<scalar>::refScalar;
    using typename JordanMatrix<scalar>::type;
    using typename JordanMatrix<scalar>::func;
    using typename JordanMatrix<scalar>::complexS;
    using typename JordanMatrix<scalar>::MatrixS;
    using typename JordanMatrix<scalar>::MatrixC;
    using typename JordanMatrix<scalar>::SolverMatrixType;
    using typename JordanMatrix<scalar>::SolverComplexMatrixType;
    using typename JordanMatrix<scalar>::pseudoType_t;
    using typename AccelMatrix<scalar>::powerS;
    using typename AbstractMatrix<scalar>::powerList;
    using typename AbstractMatrix<scalar>::iteration_pair;

    using JordanMatrix<scalar>::m_dimension;
    using JordanMatrix<scalar>::m_isOne;
    using JordanMatrix<scalar>::m_hasOnes;
    using JordanMatrix<scalar>::m_hasMultiplicities;
    using JordanMatrix<scalar>::m_hasNegatives;
    using JordanMatrix<scalar>::m_jordanIndex;
    using JordanMatrix<scalar>::m_conjugatePair;
    using JordanMatrix<scalar>::m_eigenNorms;
    using JordanMatrix<scalar>::m_cosFactors;
    using AbstractMatrix<scalar>::m_eigenCloud;
    using AbstractMatrix<scalar>::m_sampleTime;
    using AbstractMatrix<scalar>::m_delayTime;
    using AbstractMatrix<scalar>::m_freq;
    using DynamicalSystem<scalar>::m_idimension;
    using DynamicalSystem<scalar>::m_fdimension;
    using DynamicalSystem<scalar>::m_odimension;
    using DynamicalSystem<scalar>::m_reachTime;
    using DynamicalSystem<scalar>::m_inputType;
    using DynamicalSystem<scalar>::m_initialState;
    using DynamicalSystem<scalar>::m_transformedInputs;
    using DynamicalSystem<scalar>::m_eigenValues;
    using DynamicalSystem<scalar>::m_eigenVectors;
    using DynamicalSystem<scalar>::m_invEigenVectors;
    using DynamicalSystem<scalar>::m_pseudoEigenValues;
    using DynamicalSystem<scalar>::m_pseudoEigenVectors;
    using DynamicalSystem<scalar>::m_invPseudoEigenVectors;
    using DynamicalSystem<scalar>::m_source;
    using DynamicalSystem<scalar>::m_name;
    using DynamicalSystem<scalar>::m_guard;
    using DynamicalSystem<scalar>::m_dynamics;
    using DynamicalSystem<scalar>::m_sensitivity;
    using DynamicalSystem<scalar>::m_inputs;
    using DynamicalSystem<scalar>::m_reference;
    using DynamicalSystem<scalar>::m_outputs;
    using DynamicalSystem<scalar>::m_outputSensitivity;
    using DynamicalSystem<scalar>::m_ioSensitivity;
    using DynamicalSystem<scalar>::m_outputGuard;
    using DynamicalSystem<scalar>::m_safeReachTube;
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


    using AbstractMatrix<scalar>::ms_sparse;
    using DynamicalSystem<scalar>::ms_one;
    using DynamicalSystem<scalar>::ms_logger;
    using DynamicalSystem<scalar>::ms_incremental;
    using DynamicalSystem<scalar>::ms_trace_dynamics;
    using DynamicalSystem<scalar>::ms_emptyMatrix;
    using DynamicalSystem<scalar>::ms_fullAnswers;

    using JordanMatrix<scalar>::interToRef;
    using JordanMatrix<scalar>::refToInter;
    using JordanMatrix<scalar>::makeInverse;
    using JordanMatrix<scalar>::jordanToPseudoJordan;
    using AbstractMatrix<scalar>::findIterations;
    using AbstractMatrix<scalar>::findFrequencies;
    using AbstractMatrix<scalar>::findZeniths;
    using AbstractMatrix<scalar>::addSupportsAtIteration;
    using AbstractMatrix<scalar>::addSupportsAtIterations;
    using AbstractMatrix<scalar>::isDivergent;
    using AbstractMatrix<scalar>::eigenCloudSupport;
    using AbstractMatrix<scalar>::getEigenCloud;
    using AbstractMatrix<scalar>::firstVarBlock;
    using AbstractMatrix<scalar>::binomial;
    using AbstractMatrix<scalar>::refineAbstractDynamics;
    using AbstractMatrix<scalar>::boundingHyperBox;
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
    using DynamicalSystem<scalar>::getRoundedAbstractVertices;
    using DynamicalSystem<scalar>::getAccelInSupports;
    using DynamicalSystem<scalar>::getAbstractReachTubeSupports;
    using DynamicalSystem<scalar>::mergeAccelInSupports;
    using DynamicalSystem<scalar>::mergeAbstractSupports;
    using DynamicalSystem<scalar>::traceSupports;
    using DynamicalSystem<scalar>::getGuardedReachTube;
    using DynamicalSystem<scalar>::loadFromFile;
    using DynamicalSystem<scalar>::load;
    using DynamicalSystem<scalar>::save;
    using DynamicalSystem<scalar>::kronecker;
    using DynamicalSystem<scalar>::changeDimensions;
    using DynamicalSystem<scalar>::loadGuard;
    using DynamicalSystem<scalar>::loadOutputGuard;
    using DynamicalSystem<scalar>::loadDynamics;
    using DynamicalSystem<scalar>::loadInitialState;
    using DynamicalSystem<scalar>::loadSensitivities;
    using DynamicalSystem<scalar>::loadInputs;
    using DynamicalSystem<scalar>::loadSafeReachTube;
    using DynamicalSystem<scalar>::loadTemplates;
    using DynamicalSystem<scalar>::loadARMAXModel;
    using DynamicalSystem<scalar>::processError;
    using DynamicalSystem<scalar>::calculateJordanForm;
    using DynamicalSystem<scalar>::calculateMaxIterations;
    using DynamicalSystem<scalar>::calculateIterations;
    using DynamicalSystem<scalar>::setEigenSpace;
    using DynamicalSystem<scalar>::setInputType;
    using DynamicalSystem<scalar>::getAccelVertices;
    using DynamicalSystem<scalar>::getOutputReachTube;
    using DynamicalSystem<scalar>::process;
    using DigitalSystem<scalar>::sample;
    using DigitalSystem<scalar>::resample;
    using CanonicalSystem<scalar>::resample;
    using CanonicalSystem<scalar>::synthesiseDynamicBounds;

    /// Constructs an empty buffer
    /// @param dimension dimension of the space
    CegarSystem(int dimension=0,int idimension=0,int odimension=0,bool trace=false);

    /// Gets the start and end position of the state, input and output description blocks
    void getXYUSections(std::string &description,
                        size_t pos,size_t end,
                        size_t &x_pos,size_t &x_end,
                        size_t &y_pos,size_t &y_end,
                        size_t &u_pos,size_t &u_end,
                        size_t &t_pos,size_t &t_end);

    /// Loads a combined constraint description for inputs, outputs and state-space
    int loadIneConstraints(std::string &constraints,size_t pos=0,size_t end=std::string::npos);

    /// Loads a system descrition from a SpaceX representation
    int loadFromSpaceX(std::string dynamics,std::string settings);

    /// Loads a system descrition from SpaceX files
    int loadFromSpaceXFiles(std::string &modelName);

    /// Loads a polyhedral description for the output guard
    /// @param data buffer containing the polyhedra description in the form
    /**
     g_11,g_12, ... ,g_1p, h_1
     g_21,g_22, ... ,g_2p, h_2
     ...
     g_r1,g_r2, ... ,g_rp, h_r
     **/
    /// @param vertices indicates if the description is vertex or inequality oriented
    /// @param pos position to start parsing from
    /// @return position after parsing, negative if failed
    virtual int loadOutputGuard(const std::string &data,bool vertices=false,size_t pos=0,size_t end=std::string::npos);

    /// Loads a polyhedral description for the initial state
    int loadOutputInitialState(const std::string &data,bool vertices=false,size_t pos=0,size_t end=std::string::npos);

    /// Copies an existing object
    virtual void copy(const CegarSystem &source);

    /// Retrieves a list of iterations whose reach set fails the specification
    bool findCounterExampleIterations(powerList &iterations,AbstractPolyhedra<scalar> &bounds);

    /// Refines the abstraction in order to meet the safety specification
    bool refineAbstractDynamics(AbstractPolyhedra<scalar> &bounds,powerList &iterations);

    /// Refines the abstraction in order to meet the safety specification
    bool refineAbstractDynamics(AbstractPolyhedra<scalar> &bounds)
    {
      powerList iterations;
      boost::timer timer;
      refineAbstractDynamics(bounds,iterations);
      if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Refinement time:",true);
      return !iterations.empty();
    }

    /// Retrieves the support set for the inputs
    MatrixS& getRefinedAccelInSupports();

    /// Retrieves the reach tube given the refined dnamics
    AbstractPolyhedra<scalar>& getRefinedAbstractReachTube(space_t space,bool guarded=false);

    /// Retrieves the reach tube at the given iteration
    AbstractPolyhedra<scalar>& getRefinedAbstractReachTube(powerS iteration,int precision=2,int directions=0,inputType_t inputType=eParametricInputs,space_t space=eNormalSpace,bool guarded=false);

    /// Retrieves the support functions for the reach tube in the given directions
    MatrixS getRefinedAbstractReachTubeSupports(powerS iteration,int precision,AbstractPolyhedra<scalar>& dynamics,int direction);

    /// Retrieves the support functions for the reach tube in the given directions
    bool refineDynamics(AbstractPolyhedra<scalar>& dynamics,MatrixS &point,MatrixS &ce,scalar &support,bool next,int &newIndex);

    /// Retrieves the refined supports for the reach tube in the given directions
    bool refinedMaximise(AbstractPolyhedra<scalar>& dynamics,MatrixS &vectors,MatrixS &supports,MatrixS &inSupports,refScalar &max);

    /// Retrieves refined dynamics given a safety specification
    AbstractPolyhedra<scalar>& getRefinedDynamics(powerS iterations,powerS iteration=0,int directions=0);

    /// Sets the vector ordering scheme for incremental simplex calls
    void setIncrementalOrder(std::string &order);

    void makeConvergentSystem(ParamMatrix &params,bool run=true,bool save=true);

    /// Creates a closed dynamical system that overapproximates the system with inputs
    bool makeClosedSystem(CegarSystem<scalar> &closedSystem);

    /// Explicitly calculates the vertex progression up to step and checks if it remains inside guard
    powerS checkExplicitReachability(powerS step,const MatrixS &transform);
protected:
    /// Finds the statespace guard given an output guard
    AbstractPolyhedra<scalar>& calculateGuardFromOutput();

    /// Solves the Sylvester equation AX+XB=C for X
    /// @return X
    MatrixS solveSylvester(const MatrixS &A,const MatrixS &B,const MatrixS &C,bool BisDiagonal=false);

public:
    AbstractPolyhedra<scalar>   m_initialOutputs;
    OrderType                   m_incOrderType;
public:
    static bool                 ms_aggressive;

};

}

#endif //CEGARSYSTEM_H
