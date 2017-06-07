#include "RefinedDynamicalSystem.h"
#include <boost/timer.hpp>
#include <set>
#include <Eigen/QR>
#include <Eigen/Eigenvalues>

namespace abstract{

/// Constructs an empty buffer
template<class scalar>
CegarSystem<scalar>::CegarSystem(int dimension,int idimension) :
  DynamicalSystem<scalar>(dimension,idimension),
  m_incOrderType(LexCos)
{}

/// Finds the statespace guard given an output guard
template <class scalar>
AbstractPolyhedra<scalar>& CegarSystem<scalar>::calculateGuardFromOutput()
{
  AbstractPolyhedra<scalar>& polyhedra=m_safeReachTube.getPolyhedra();
  m_outputGuard.getTransformedPolyhedra(polyhedra,ms_emptyMatrix,m_outputSensitivity);
  return m_safeReachTube.getPolyhedra(eEigenSpace,true);
}

template <class scalar>
void CegarSystem<scalar>::getXYUSections(std::string &description,
                                        size_t pos,size_t end,
                                        size_t &x_pos,size_t &x_end,
                                        size_t &y_pos,size_t &y_end,
                                        size_t &u_pos,size_t &u_end,
                                        size_t &t_pos,size_t &t_end)
{
  if (end==std::string::npos) end=description.length();
  x_pos=description.find('x',pos);
  y_pos=description.find('y',pos);
  u_pos=description.find('u',pos);
  t_pos=description.find('t',pos);
  const char* pData=description.data();
  while ((x_pos!=std::string::npos) && (x_pos>pos) && (pData[x_pos-1]=='*')) x_pos=description.find('x',x_pos+1);
  while ((u_pos!=std::string::npos) && (u_pos>pos) && (pData[u_pos-1]=='*')) u_pos=description.find('u',u_pos+1);
  if (x_pos>end) x_pos=std::string::npos;
  if (y_pos>end) y_pos=std::string::npos;
  if (u_pos>end) u_pos=std::string::npos;
  if (t_pos>end) t_pos=std::string::npos;
  if (x_pos!=std::string::npos) {
    while ((x_pos>pos) && (pData[x_pos]!='&')) x_pos--;
    if (pData[x_pos]=='&') x_pos++;
  }
  if (y_pos!=std::string::npos) {
    while ((y_pos>pos) && (pData[y_pos]!='&')) y_pos--;
    if (pData[y_pos]=='&') y_pos++;
  }
  if ((u_pos<end) && (u_pos!=std::string::npos)) {
    while ((u_pos>pos) && (pData[u_pos]!='&')) u_pos--;
    if (pData[u_pos]=='&') u_pos++;
  }
  if ((t_pos<end) && (t_pos!=std::string::npos)) {
    while ((t_pos>pos) && (pData[t_pos]!='&')) t_pos--;
    if (pData[t_pos]=='&') t_pos++;
  }
  if (x_pos!=std::string::npos) {
    x_end=((y_pos>x_pos) && (y_pos<end)) ? y_pos : end;
    if ((u_pos>x_pos) && (u_pos<x_end)) x_end=u_pos;
    if ((t_pos>x_pos) && (t_pos<x_end)) x_end=t_pos;
  }
  if (y_pos!=std::string::npos) {
    y_end=((x_pos>y_pos) && (x_pos<end)) ? x_pos : end;
    if ((u_pos>y_pos) && (u_pos<y_end)) y_end=u_pos;
    if ((t_pos>y_pos) && (t_pos<y_end)) y_end=t_pos;
  }
  if ((u_pos<end) && (u_pos!=std::string::npos)) {
    u_end=((x_pos>u_pos) && (x_pos<end)) ? x_pos : end;
    if ((y_pos>u_pos) && (y_pos<u_end)) u_end=y_pos;
    if ((t_pos>u_pos) && (t_pos<u_end)) u_end=t_pos;
  }
}

/// Loads a combined constraint description for inputs, outputs and state-space
template <class scalar>
int CegarSystem<scalar>::loadIneConstraints(std::string &constraints,size_t pos,size_t end)
{
  if (end==std::string::npos) end=constraints.length();
  size_t x_start,x_end,y_start,y_end,u_start,u_end,t_start,t_end;
  getXYUSections(constraints,pos,end,x_start,x_end,y_start,y_end,u_start,u_end,t_start,t_end);
  if (x_start!=std::string::npos) loadInitialState(constraints,false,x_start,x_end);
  if (y_start!=std::string::npos) loadOutputGuard(constraints,false,y_start,y_end);
  if (u_start!=std::string::npos) loadInputs(constraints,false,u_start,u_end);
}

/// Loads a system descrition from and ARCH file
template <class scalar>
int CegarSystem<scalar>::loadFromSpaceX(std::string dynamics,std::string settings)
{
  boost::timer timer;
  std::string flow_start="<flow>";
  std::string inv_start="<invariant>";
  size_t flow_pos=dynamics.find(flow_start)+flow_start.length();
  size_t flow_end=dynamics.find("</flow>");
  size_t inv_pos=dynamics.find(inv_start)+inv_start.length();
  size_t inv_end=dynamics.find("</invariant>");

  std::string xml_and="&amp;";
  std::string norm_and="&    ";
  std::string xml_lt="&lt;";
  std::string norm_lt="<   ";
  std::string xml_gt="&gt;";
  std::string norm_gt=">   ";
  size_t pos=dynamics.find(xml_and);
  while(pos!=std::string::npos) {
    dynamics.replace(pos,xml_and.length(),norm_and);
    pos=dynamics.find(xml_and,pos);
  }
  pos=dynamics.find(xml_lt);
  while(pos!=std::string::npos) {
    dynamics.replace(pos,xml_lt.length(),norm_lt);
    pos=dynamics.find(xml_lt,pos);
  }
  pos=dynamics.find(xml_gt);
  while(pos!=std::string::npos) {
    dynamics.replace(pos,xml_gt.length(),norm_gt);
    pos=dynamics.find(xml_gt,pos);
  }
  size_t x_start,x_end,y_start,y_end,u_start,u_end,t_start,t_end;
  getXYUSections(dynamics,inv_pos,inv_end,x_start,x_end,y_start,y_end,u_start,u_end,t_start,t_end);
  int result=ms_logger.StringToDynamics(m_dynamics,m_sensitivity,dynamics,flow_pos,flow_end);
  if (result<0) return result;
  if (!calculateJordanForm()) return -1;
  setEigenSpace();

  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Dynamics time:",true);
  if ((m_odimension>0) && (y_start!=std::string::npos)) {
    result=ms_logger.StringToDynamics(m_outputSensitivity,m_ioSensitivity,dynamics,inv_pos,inv_end);
  }

  std::string sample_start="sampling-time = ";
  std::string horizon_start="time-horizon = ";
  size_t sample_pos=settings.find(sample_start)+sample_start.length();
  size_t horizon_pos=settings.find(horizon_start)+horizon_start.length();
  scalar sample_time,time_horizon;
  powerS iteration=0;
  func::toScalar(settings.data()+sample_pos,sample_time);
  if (horizon_pos!=std::string::npos) {
    const char *pBegin=settings.data()+horizon_pos;
    char *pEnd=func::toScalar(pBegin,time_horizon);
    if (pEnd!=pBegin) {
      time_horizon/=sample_time;
      iteration=func::toInt(func::toUpper(time_horizon));
    }
  }
  sample(sample_time);
  if (m_paramValues.coeff(eNumStates,0)==0) {
    m_paramValues.coeffRef(eNumStates,0)=iteration;
  }

  std::string const_start="initially = \"";
  size_t const_pos=settings.find(const_start)+const_start.length();
  size_t const_end=settings.find("\"\n",const_pos);
  result=loadIneConstraints(settings,const_pos,const_end);
  if (u_start!=std::string::npos) if (u_start!=std::string::npos) loadInputs(dynamics,false,u_start,u_end);
  if (m_safeReachTube.isEmpty() && !m_outputGuard.isEmpty()) calculateGuardFromOutput();

/*  save();
  ms_logger.logData(m_dynamics,"A");
  ms_logger.logData(m_sensitivity,"B");
  ms_logger.logData(m_outputSensitivity,"C");
  ms_logger.logData(m_ioSensitivity,"D");
  m_initialState.getPolyhedra().logTableau("init",true);
  m_inputs.logTableau("inputs",true);
  m_outputGuard.logTableau("outputs",true);*/
}

/// Loads a system description from SpaceX files
template <class scalar>
int CegarSystem<scalar>::loadFromSpaceXFiles(std::string &modelName)
{
  std::string XMLfileName=modelName+".xml";
  std::string CFGfileName=modelName+".cfg";
  std::stringstream xml_buffer,cfg_buffer;
  std::ifstream xml_file,cfg_file;
  ms_logger.logData("Loading model: ",false);
  ms_logger.logData(modelName);
  xml_file.open(XMLfileName.data());
  if (!xml_file.is_open()) {
    ms_logger.logData("Unable to load file: ",false);
    ms_logger.logData(XMLfileName);
    return -1;
  }
  xml_buffer << xml_file.rdbuf();
  xml_file.close();
  cfg_file.open(CFGfileName.data());
  if (!cfg_file.is_open()) {
    ms_logger.logData("Unable to load file: ",false);
    ms_logger.logData(CFGfileName);
    return -1;
  }
  cfg_buffer << cfg_file.rdbuf();
  cfg_file.close();
  m_name=modelName;
  return loadFromSpaceX(xml_buffer.str(),cfg_buffer.str());
}

/// turns a continuous time system into a discrete
template<class scalar>
void CegarSystem<scalar>::sample(scalar sampleTime)
{
  m_sampleTime=sampleTime;
  m_cosFactors.coeffRef(m_dimension,0)=func::ms_1;
  for (int i=0;i<m_dimension;i++) {
    complexS power=m_eigenValues.coeffRef(i,i)*sampleTime;
    scalar mag=exp(power.real());
    scalar real=mag*func::cosine(power.imag());
    scalar imag=mag*func::sine(power.imag());
    complexS value=complexS(real,imag);
    m_eigenValues.coeffRef(i,i)=value;
    m_eigenNorms.coeffRef(i,0)=func::norm2(value);
    if (m_conjugatePair[i]>=0) {
      m_cosFactors.coeffRef(i,0)=m_eigenNorms.coeffRef(i,0)/value.real();
      m_cosFactors.coeffRef(m_dimension,0)*=m_cosFactors.coeffRef(i,0);
    }
  }
  m_pseudoEigenValues=jordanToPseudoJordan(m_eigenValues,this->eToEigenValues);
  MatrixS discrete_dynamics=m_pseudoEigenVectors*m_pseudoEigenValues*m_invPseudoEigenVectors;
  MatrixS integrator=discrete_dynamics-MatrixS::Identity(m_dimension,m_dimension);
  integrator=m_dynamics.inverse()*integrator;
  if (ms_trace_dynamics>=eTraceDynamics) {
    ms_logger.logData(m_dynamics,"Dynamics");
    ms_logger.logData(m_sensitivity,"Sensitivity");
    ms_logger.logData(discrete_dynamics,"Discrete Dynamics");
    ms_logger.logData(integrator,"Integrator");
    ms_logger.logData(m_pseudoEigenValues,"Discrete PseudoEigenValues");
    ms_logger.logData(m_pseudoEigenVectors,"Discrete PseudoEigenVectors");
    ms_logger.logData(m_invPseudoEigenVectors,"Discrete InvPseudoEigenVectors");
  }

  m_sensitivity=integrator*m_sensitivity;
  m_dynamics=discrete_dynamics;
  if (ms_trace_dynamics>=eTraceDynamics) {
    ms_logger.logData(m_sensitivity,"Discrete Sensitivity");
  }
}

template<class scalar>
bool CegarSystem<scalar>::sample(std::string &sampleTime)
{
  scalar time;
  if (func::toScalar(sampleTime.data(),time)==sampleTime.data()) return false;
  sample(time);
  return true;
}

/// Solves the Sylvester equation AX+XB=C for X
template<class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::solveSylvester(const MatrixS &A,const MatrixS &B,const MatrixS &C,bool BisDiagonal)
{
  MatrixS U,V;
  SolverMatrixType refA,refB;
  interToRef(refA,A);
  interToRef(refB,B);
  Eigen::RealSchur<SolverMatrixType> realSchur(refA.transpose());
  refToInter(U,realSchur.matrixU());//We want transposed so keep it this way
  refA=realSchur.matrixT().transpose();//Lower triangular
  if (BisDiagonal) {
    V=MatrixS::Identity(C.rows(),refB.rows());
  }
  else {
    interToRef(refB,B);
    realSchur.compute(refB);
    refToInter(V,realSchur.matrixU());
    refB=realSchur.matrixT();
  }
  MatrixS result=U*C*V;
  for (int row=0;row<result.rows();row++) {
    for (int col=0;col<result.cols();col++) {
      for (int i=0;i<row;i++) {
        result.coeffRef(row,col)-=refA.coeff(row,i)*result.coeff(i,col);
      }
      for (int i=0;i<col;i++) {
        result.coeffRef(row,col)-=result.coeff(row,i)*refB.coeff(i,col);
      }
      result.coeffRef(row,col)/=refA.coeff(row,row)+refB.coeff(col,col);
    }
  }
  return result;
}

/// Retrieves the characteristic polynomial coefficients of the dynamics
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getDynamicPolynomialCoefficients()
{
  MatrixC result=MatrixC::Zero(2,m_dimension+1);
  result.coeffRef(0,0)=ms_one;
  result.coeffRef(0,1)=-m_eigenValues.coeff(0,0);
  for (int i=1;i<m_dimension;i++) {
    result.row(1)=-result.row(0)*m_eigenValues.coeff(i,i);
    result.block(0,1,1,i+1)+=result.block(1,0,1,i+1);
  }
  return result.real();
}

/// Retrieves the reachability matrix [B AB A^2B ...A^{n-1}B]
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getReachabilityMatrix()
{
  MatrixS result(m_sensitivity.rows(),m_dimension*m_sensitivity.cols());
  result.block(0,0,m_sensitivity.rows(),m_sensitivity.cols())=m_sensitivity;
  MatrixS multiplier=m_dynamics;
  for (int i=1;i<m_dimension;i++)
  {
    result.block(0,i*m_sensitivity.cols(),m_sensitivity.rows(),m_sensitivity.cols())=multiplier*m_sensitivity;
    multiplier*=m_dynamics;
  }
  if (ms_trace_dynamics) ms_logger.logData(result,"Reachability Matrix");
  return result;
}

/// Retrieves the reachability matrix [1 a1 a2...a_{n-1};0 1 a1 ... a_{n-2}...]
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getCanonicalReachabilityMatrix()
{
  //TODO: not sure how this works on MIMO
  MatrixS result=MatrixS::Identity(m_sensitivity.rows(),m_dimension*m_sensitivity.cols());
  MatrixS coefficients=getDynamicPolynomialCoefficients();
  if (ms_trace_dynamics>=eTraceDynamics) {
    MatrixS matrix=coefficients.row(0);
    ms_logger.logData(matrix,"Coefficients");
  }
  for (int i=1;i<m_dimension;i++) result.block(i-1,i,1,m_dimension-i)=coefficients.block(0,1,1,m_dimension-i);
  if (ms_trace_dynamics>=eTraceDynamics) ms_logger.logData(result,"Canonical Reachability Matrix");
  return result;
}

/// Retrieves the transform matrix T : z=T^{-1}x turns A,B,C into controllable canonical form
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getReachableCanonicalTransformMatrix()
{
  MatrixS result=getReachabilityMatrix()*getCanonicalReachabilityMatrix();
  return result.inverse();
}

/// Retrieves the observability matrix [C CA CA^2 ...CA^{n-1}]^T
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getObservabilityMatrix()
{
  MatrixS result(m_dimension*m_outputSensitivity.rows(),m_outputSensitivity.cols());
  result.block(0,0,m_outputSensitivity.rows(),m_outputSensitivity.cols())=m_outputSensitivity;
  MatrixS multiplier=m_dynamics;
  for (int i=1;i<m_dimension;i++)
  {
    result.block(i*m_outputSensitivity.rows(),0,m_outputSensitivity.rows(),m_outputSensitivity.cols())=m_outputSensitivity*multiplier;
    multiplier*=m_dynamics;
  }
  return result;
}

/// Retrieves the observability matrix [1 0 ...;a1 1 0 ...;...;a_{n-1}...a1 1]^-1
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getInverseCanonicalObservabilityMatrix()
{
  //TODO: not sure how this works on MIMO
  MatrixS result=MatrixS::Identity(m_dimension*m_outputSensitivity.rows(),m_outputSensitivity.cols());
  MatrixS coefficients=getDynamicPolynomialCoefficients();
  for (int i=0;i<m_dimension;i++) {
    for (int j=0;j<i;j++) {
      result.coeffRef(i,j)=coefficients.coeff(0,m_dimension-i-j-1);
    }
  }
  return result;
}

/// Retrieves the transform matrix T : z=T^{-1}x turns A,B,C into observable canonical form
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getObservableCanonicalTransformMatrix()
{
  return getObservabilityMatrix().inverse()*getInverseCanonicalObservabilityMatrix();
}

/// Retrieves the reference gain
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getReferenceGain()
{
  return m_outputSensitivity*((m_dynamics-(m_sensitivity*m_feedback)).inverse()*m_sensitivity);
}

/// Retrieves the reach tube at the given iteration
template <class scalar>
/// Retrieves refined dynamics given a safety specification
AbstractPolyhedra<scalar>& CegarSystem<scalar>::getRefinedDynamics(int refinements,powerS iteration,int directions,inputType_t inputType)
{
  AbstractPolyhedra<scalar>&reachTube=getAbstractReachTube(iteration,2,directions,inputType);
  if (ms_trace_dynamics>=eTraceDynamics) {
    reachTube.logTableau("PreCegar:",true);
    reachTube.logVertices(true);
  }
  //if (m_safeReachTube.getPolyhedra().contains(reachTube)) return getAbstractDynamics(inputType);
  if (!m_safeReachTube.isEmpty()) {
    AbstractPolyhedra<scalar> bounds=synthesiseDynamicBounds(m_inputType,m_safeReachTube.getPolyhedra(eEigenSpace));
    if (ms_trace_dynamics>=eTraceDynamics) {
      bounds.logTableau("Projected Bounds: ",true);
    }
    for(int i=0;(i<refinements) && refineAbstractDynamics(bounds);i++);
    if (ms_trace_dynamics>=eTraceDynamics) {
      AbstractPolyhedra<scalar>& result=getRefinedAbstractReachTube(eNormalSpace);
      result.logTableau("PosCegar:",true);
      result.logVertices(true);
    }
  }
  return getAbstractDynamics(inputType);
}

/// Synthesises a bound on the dynamics given a known guard and eigenvectors.
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::synthesiseDynamicBounds(inputType_t inputType,AbstractPolyhedra<scalar> &end)
{
  m_inputType=inputType;
  MatrixS vectors;
  int numVertices;
  getAbstractVertices(end.getDirections(),vectors,numVertices);
  vectors.transposeInPlace();
  MatrixS supports(vectors.rows(),1);
  MatrixS endSupports=end.getSupports();
  int perTemplate=supports.rows()/endSupports.rows();
  for (int i=0;i<endSupports.rows();i++)
  {
    for (int j=0;j<perTemplate;j++) {
      supports.coeffRef(i*perTemplate+j,0)=endSupports.coeff(i,0);
    }
  }
  if (m_inputType>eNoInputs) {
    MatrixS inSupports=m_accelVertices*end.getDirections();
    demergeAccelInSupports(supports,inSupports,endSupports.rows());
  }
  AbstractPolyhedra<scalar> bounds;
  bounds.load(vectors,supports);
  if (ms_trace_dynamics>=eTraceAll) {
    bounds.logTableau("Full Bounds",true);
  }
  bounds.removeRedundancies();
  return bounds;
}

/// Creates a model for the quantization noise as an input specification
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::generateNoiseInput()
{
  int odimension=(m_odimension>0) ? m_odimension : m_dimension;
  int ndimension=1;
  AbstractPolyhedra<scalar> result(ndimension);
  int fbits=m_paramValues.coeff(eNumBits,1)-m_paramValues.coeff(eNumBits,2);
  if (fbits<=0) fbits=m_paramValues.coeff(eNumBits,0);
  if (fbits<=0) fbits=func::getDefaultPrec();
  scalar lsb=func::pow(this->ms_two,-fbits);
  MatrixS faces(2*ndimension,ndimension);
  MatrixS supports(2*ndimension,1);
  faces.block(0,0,ndimension,ndimension)=MatrixS::Identity(ndimension,ndimension);
  faces.block(ndimension,0,ndimension,ndimension)=-MatrixS::Identity(ndimension,ndimension);
  scalar fb_noise=m_feedback.cwiseAbs().sum()/*lpNorm<1>()*/+this->ms_one;//|Noise|<(|K|_1+1)lsb assuming q1,q2=1lsb,(q3:=q1->K) = (|K|_1q1+q2)
  supports.coeffRef(0,0)=lsb*(fb_noise);
  supports.coeffRef(1,0)=supports.coeff(0,0);
  result.load(faces,supports);
  return result;
}

/// Creates a model for the input of the closed loop
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::generateFeedbackInput(int fdimension,bool makeNoise,MatrixS &sensitivity)
{
  AbstractPolyhedra<scalar> inputs(0);
  if (m_reference.getDimension()>0) {
    inputs.copy(m_reference);
    fdimension=m_reference.getDimension();
  }
  if (m_idimension>fdimension) {
    MatrixS inputFaces=m_inputs.getFaceDirections().rightCols(m_idimension-fdimension);
    MatrixS inSupports=m_inputs.getSupports();
    inputs.concatenate(inputFaces,inSupports);
  }
  if (makeNoise) {
    //m_closedLoop.setInputType(eVariableInputs);
    AbstractPolyhedra<scalar> noiseInputs=generateNoiseInput();
    inputs.concatenate(noiseInputs);
    sensitivity.conservativeResize(m_dimension,inputs.getDimension());
    sensitivity.block(0,inputs.getDimension()-noiseInputs.getDimension(),m_dimension,noiseInputs.getDimension())=MatrixS::Ones(m_dimension,noiseInputs.getDimension());
  }
  return inputs;
}

/// Retrieves a list of iterations whose reach set fails the specification
template<class scalar>
bool CegarSystem<scalar>::findCounterExampleIterations(powerList &iterations,AbstractPolyhedra<scalar> &bounds)
{
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);
  MatrixS &vertices=dynamics.getVertices(true);
  bool found=false;
  for (int i=0;i<vertices.rows();i++) {
    MatrixS point=vertices.row(i);
    if (!bounds.isInside(point)) {
      findIterations(point,iterations);
      found=true;
    }
  }
  return found;
}

/// Refines the abstraction in order to meet the safety specification
template<class scalar>
bool CegarSystem<scalar>::refineAbstractDynamics(AbstractPolyhedra<scalar> &bounds,powerList &iterations)
{
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);
  if (findCounterExampleIterations(iterations,bounds)) {
    typename powerList::iterator it;
    for (it=iterations.begin();it!=iterations.end();it++) {
      addSupportsAtIteration(dynamics,it->first,m_maxIterations);
    }
    return true;
  }
  return false;
}

/// Corrects the support set by the input offset
template <class scalar>
void CegarSystem<scalar>::demergeAccelInSupports(MatrixS &supports,MatrixS &inSupports,int numTemplates)
{
  if (!m_hasOnes || (m_inputType>=eVariableInputs))  {
    for (int row=0;row<numTemplates;row++) {
      int pos=row*m_numVertices;
      supports.coeffRef(pos,0)-=inSupports.coeff(0,row);
      for (int point=1;point<m_numVertices;point++) {
        supports.coeffRef(pos+point,0)-=inSupports.coeff(point%inSupports.rows(),row);
      }
    }
  }
}


/// Retrieves the support set for the inputs
template <class scalar>
typename JordanMatrix<scalar>::MatrixS& CegarSystem<scalar>::getRefinedAccelInSupports()
{
  if (m_hasOnes && (m_inputType>=eVariableInputs)) {
    AbstractPolyhedra<scalar>& inputDynamics=getAbstractDynamics(eParametricInputs);
    MatrixS supports;
    inputDynamics.maximiseAll(m_abstractInputVertices,supports);
    m_accelInSupports=supports.transpose();
    if (ms_trace_dynamics>=eTraceAbstraction) ms_logger.logData(m_accelInSupports,"Input Supports",true);
  }
  return m_accelInSupports;
}

/// Retrieves the reach tube at the given iteration
template <class scalar>
AbstractPolyhedra<scalar>& CegarSystem<scalar>::getRefinedAbstractReachTube(space_t space,bool guarded)
{
  boost::timer timer;
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);

  MatrixS& templates=getTemplates(eEigenSpace);
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Abstract Vertices: ",true);
  MatrixS supports;
  if (!dynamics.maximiseAll(m_abstractVertices,supports)) processError(dynamics.getName());

  if (m_inputType>eNoInputs) getRefinedAccelInSupports();
  if (ms_trace_dynamics>=eTraceAll) {
    traceSupports(templates,supports,dynamics,m_abstractVertices);
  }
  if (m_inputType>eNoInputs) {
    mergeAccelInSupports(supports,templates.cols());
    if (ms_trace_dynamics>=eTraceAll) {
      ms_logger.logData(m_abstractVertices,supports,"Combined",true);
    }
  }
  mergeAbstractSupports(templates,supports);
  MatrixS faces=templates.transpose();
  m_pAbstractReachTube->mergeLoad(init,faces,supports,eEigenSpace);
  AbstractPolyhedra<scalar>& result=m_pAbstractReachTube->getPolyhedra(space);
  if (guarded) getGuardedReachTube(result,space);
  if (ms_trace_dynamics>=eTraceAbstraction) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_time) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
  return result;
}

/// Retrieves the reach tube at the given iteration
template <class scalar>
AbstractPolyhedra<scalar>& CegarSystem<scalar>::getRefinedAbstractReachTube(powerS iteration,int precision,int directions,inputType_t inputType,space_t space,bool guarded)
{
  m_reachTime=-1;
  boost::timer timer;
  if (m_idimension==0) inputType=eNoInputs;
  setInputType(inputType);
  if (iteration<0) iteration=-iteration;
  if (iteration==0) iteration=calculateIterations(m_initialState.getPolyhedra(eEigenSpace),inputType);
  if (m_safeReachTube.isEmpty() || (iteration<=2)) return getAbstractReachTube(iteration,precision,directions,inputType,space,guarded);
  if (m_hasMultiplicities) this->calculateBoundedEigenError(calculateMaxIterations());
  if (guarded) iteration--;
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(iteration,precision,inputType);
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);

  MatrixS templates=m_safeReachTube.getPolyhedra(eEigenSpace).getDirections();//getTemplates(eEigenSpace,directions);
  MatrixS supports(templates.cols(),1);
  init.getVertices(true);
  getAccelVertices(true);
  int numTemplates=templates.cols();
  for (int i=0;i<numTemplates;i++) {
    MatrixS localSupport=getRefinedAbstractReachTubeSupports(iteration,precision,dynamics,i);
    supports.coeffRef(i,0)=localSupport.coeff(0,0);
  }
  MatrixS faces=templates.transpose();
  m_pAbstractReachTube->mergeLoad(init,faces,supports,eEigenSpace);
  AbstractPolyhedra<scalar>& result=m_pAbstractReachTube->getPolyhedra(space);
  if (guarded) getGuardedReachTube(result,space);
  if (this->ms_trace_dynamics>=eTraceAbstraction) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_time) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
  getOutputReachTube(result, directions);
  return result;
}

/// Retrieves the support functions for the reach tube in the given directions
template <class scalar>
bool CegarSystem<scalar>::refineDynamics(AbstractPolyhedra<scalar>& dynamics,MatrixS &point,MatrixS &ce,scalar &support,bool next,int &newIndex)
{
  powerList iterations;
  if (next) {
    findIterations(ce,iterations);
  }
  else {
    if (!m_hasMultiplicities && !isDivergent()) {
      if (m_eigenCloud.rows()<=0) {
        powerS trueMaxIterations=calculateMaxIterations(m_maxIterations);
        if (trueMaxIterations>1000) trueMaxIterations=1000;
        getEigenCloud(trueMaxIterations);
      }
      if (m_eigenCloud.rows()>0) {
        MatrixS vector=point.transpose();
        powerS iter=0;
        refScalar maxSupport=eigenCloudSupport(vector,iter);
        if (maxSupport<func::toLower(support)) {
          MatrixS supports(1,1);
          supports.coeffRef(0,0)=maxSupport;
          support=maxSupport;
          //newIndex++;
          std::vector<iteration_pair> iterPair;
          iterPair.resize(1);
          iterPair[0]=iteration_pair(-1,-1,iter);
          dynamics.addTaggedDirection(vector,supports,iterPair,true);
          if (ms_trace_dynamics>=eTraceAbstraction) ms_logger.logData(maxSupport,"New support",true);
          return true;
        }
        else if (iter<m_eigenCloud.rows()) return false;
      }
    }
    findIterations(point,iterations,true);
  }
  if (iterations.size()>0) {
    if (ms_trace_dynamics>=eTraceAbstraction) ms_logger.logData(iterations.size(),"Refining",true);
    if (m_inputType==eVariableOnlyInputs) return false;
    return addSupportsAtIterations(dynamics,iterations,ce);
  }
  return false;
}

/// Retrieves the refined supports for the reach tube in the given directions
template <class scalar>
bool CegarSystem<scalar>::refinedMaximise(AbstractPolyhedra<scalar>& dynamics,MatrixS &vectors,MatrixS &supports,MatrixS &inSupports,refScalar &max)
{
  MatrixS ce;
  scalar result;
  int newIndex=0;
  boost::timer timer;
  SortedMatrix<scalar> sortedVectors(vectors,m_incOrderType,true);
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Sort Time",true);
  sortedVectors.block(0,0,sortedVectors.rows(),sortedVectors.cols())=vectors.transpose();
  for (int index=0;index<=supports.rows();) {
    newIndex=dynamics.ceMaximise(sortedVectors,supports,inSupports,max,ce,result,index);
    if (ms_trace_dynamics>=eTraceDynamics) ms_logger.logData(newIndex,"refining index",true);
    if (newIndex==0) return false;
    if (newIndex<0) processError(dynamics.getName());
    int trueIndex=sortedVectors.zeroOrder(newIndex);
    MatrixS point=sortedVectors.row(trueIndex);
    if (!refineDynamics(dynamics,point,ce,supports.coeffRef(trueIndex,0),index==newIndex,newIndex)) {
      max=1.001*func::toUpper(abs(inSupports.coeffRef(newIndex++,0))+result);
    }
    index=newIndex;
  }
  return true;
}

/// Retrieves the support functions for the reach tube in the given directions
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getRefinedAbstractReachTubeSupports(powerS iteration,int precision,AbstractPolyhedra<scalar>& dynamics,int direction)
{
  boost::timer timer;
  AbstractPolyhedra<scalar> &safe=m_safeReachTube.getPolyhedra(eEigenSpace);
  MatrixS face=safe.getFaceDirection(direction);
  refScalar max=func::toUpper(safe.getSupport(direction));
  MatrixS templates=face.transpose();
  MatrixS &vectors=getAbstractVertices(templates,false);
  MatrixS supports(vectors.cols(),1);
  MatrixS inSupports=MatrixS::Zero(vectors.cols(),1);
  if (m_inputType>eNoInputs) {
    getAccelInSupports(iteration,precision,templates);
    mergeAccelInSupports(inSupports,templates.cols());
  }

  if (m_inputType==eVariableOnlyInputs) {
    AbstractPolyhedra<scalar> state_dynamics(0,ms_sparse);
    AbstractPolyhedra<scalar> in_dynamics(0);
    dynamics.slice(state_dynamics,m_dimension,0,firstVarBlock());
    dynamics.slice(in_dynamics,-m_dimension,m_dimension,-firstVarBlock(),firstVarBlock());
    MatrixS state_vectors=vectors.topRows(m_dimension);
    MatrixS inSupports(state_vectors.cols(),1);
    MatrixS in_vectors,in_supports;
    int numInputVertices=this->getRoundedAbstractVertices(in_vectors,templates,true);
    if (!in_dynamics.maximiseAll(in_vectors,in_supports,dynamics.eOverAprox,ms_incremental ? LexMin : LexNone)) processError(dynamics.getName());

    for (int i=0;i<templates.cols();i++) {
      refScalar max=-func::ms_infinity;
      for (int j=0;j<numInputVertices;j++) {
        int pos=i*numInputVertices+j;
        if (func::toUpper(in_supports.coeff(pos,0))>max) max=func::toUpper(in_supports.coeff(pos,0));
      }
      for (int j=0;j<m_numVertices;j++) {
        int pos=i*m_numVertices+j;
        inSupports.coeffRef(pos,0)=max;
      }
    }
    refinedMaximise(state_dynamics,state_vectors,supports,inSupports,max);//TODO: issue with inSupports?
    supports+=inSupports;
  }
  else
  {
    refinedMaximise(dynamics,vectors,supports,inSupports,max);
  }

  if (m_inputType>eNoInputs) {
    mergeAccelInSupports(supports,templates.cols());
    if (ms_trace_dynamics>=eTraceAll) ms_logger.logData(vectors,supports,"Partial Combined",true);
  }

  mergeAbstractSupports(templates,supports);
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Abstract Tube Support: ",true);
  return supports;
}

/// Sets the vector ordering scheme for incremental simplex calls
template <class scalar>
void CegarSystem<scalar>::setIncrementalOrder(std::string &order)
{
  if (order=="cosine") m_incOrderType=LexCos;
  else if (order=="min") m_incOrderType=LexMin;
  else if (order=="max") m_incOrderType=LexMax;
  else m_incOrderType=LexCos;
}

template <class scalar>
void CegarSystem<scalar>::makeConvergentSystem(ParamMatrix &params,bool run,bool save)
{
  if (params.coeff(eNumStates,1)<params.coeff(eNumStates,0)) params.coeffRef(eNumStates,1)=params.coeff(eNumStates,0);
  int maxStates=params.coeff(eNumStates,1)-params.coeff(eNumStates,0)+1;
  int dimension=(rand()%maxStates)+params.coeff(eNumStates,0);
  int minInputs=params.coeff(eNumInputs,0)+params.coeff(eNumVarInputs,0);
  int maxInputs=params.coeff(eNumInputs,1)+params.coeff(eNumVarInputs,1);
  if (maxInputs>dimension) maxInputs=dimension;
  if (maxInputs<minInputs) maxInputs=minInputs;
  maxInputs-=minInputs-1;
  int idimension=(rand()%maxInputs)+minInputs;
  m_inputType=eNoInputs;
  if (params.coeff(eNumVarInputs,0)>0) m_inputType=eVariableInputs;
  else if (params.coeff(eNumInputs,0)>0) m_inputType=eParametricInputs;
  this->changeDimensions(dimension,idimension,0,0);
  MatrixS dynamics(dimension,dimension);
  MatrixS sensitivity(dimension,idimension);
  std::stringstream init;
  std::stringstream input;
  for (int row=0;row<dimension;row++) {
    for (int col=0;col<dimension;col++) {
      dynamics.coeffRef(row,col)=static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-1;
    }
    for (int col=0;col<idimension;col++) {
      sensitivity.coeffRef(row,col)=static_cast <float> (rand()) / static_cast <float> (RAND_MAX)-1;
    }
    if (row>0) init << ";";
    init << "x" << row+1 << "<1;-x" << row+1 << "<1";
  }
  for (int row=0;row<idimension;row++) {
    if (row>0) input << ";";
    input << "x" << row+1 << "<1;-x" << row+1 << "<1";
  }
  loadDynamics(dynamics);
  loadInitialState(init.str());
  m_sensitivity=sensitivity;
  loadInputs(input.str());
  m_paramValues=ParamMatrix::Zero();
  m_paramValues.coeffRef(eNumStates,0)=dimension;
  if (m_inputType>=eVariableInputs) m_paramValues.coeffRef(eNumVarInputs,0)=idimension;
  else m_paramValues.coeffRef(eNumInputs,0)=idimension;
  m_paramValues.row(eLogFaces)=params.row(eLogFaces);
  m_paramValues.row(eNumSteps)=params.row(eNumSteps);
  bool ans=ms_fullAnswers;
  ms_fullAnswers=true;
  getAbstractDynamics(m_inputType).clear();
  if (save) DynamicalSystem<scalar>::save();
  ms_fullAnswers=ans;
  if (run) process();
}

#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class CegarSystem<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class CegarSystem<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class CegarSystem<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class CegarSystem<mpinterval>;
  #endif
#endif

}
