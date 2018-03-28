#include "RefinedDynamicalSystem.h"
#include <boost/timer.hpp>
#include <set>
#include <Eigen/QR>
#include <Eigen/Eigenvalues>

namespace abstract{

template <class scalar>
bool CegarSystem<scalar>::ms_aggressive=false;

/// Constructs an empty buffer
template<class scalar>
CegarSystem<scalar>::CegarSystem(int dimension,int idimension,int odimension,bool trace) :
  CanonicalSystem<scalar>(dimension,idimension,odimension,trace),
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

  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Dynamics time:",true);
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
  sample(sample_time,0,false);
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

template <class scalar>
int CegarSystem<scalar>::loadOutputGuard(const std::string &data,bool vertices,size_t pos,size_t end)
{
  int result=DynamicalSystem<scalar>::loadOutputGuard(data,vertices,pos,end);
  if ((result>0) && m_safeReachTube.isEmpty() && !m_outputGuard.isEmpty()) calculateGuardFromOutput();
  return result;
}

/// Copies an existing object
template<class scalar>
void CegarSystem<scalar>::copy(const CegarSystem &source)
{
  CanonicalSystem<scalar>::copy(source);
  m_incOrderType=source.m_incOrderType;
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

/// Retrieves the reach tube at the given iteration
template <class scalar>
/// Retrieves refined dynamics given a safety specification
AbstractPolyhedra<scalar>& CegarSystem<scalar>::getRefinedDynamics(powerS iterations,powerS iteration,int directions)
{
  boost::timer timer;
  int precision=m_paramValues.coeff(eLogFaces,0);
  if (precision<=0) precision=2;
  AbstractPolyhedra<scalar> &dynamics=getAbstractDynamics(func::ms_infPower,precision,m_inputType);
  if (ms_trace_dynamics[eTraceAbstraction]) {
    AbstractPolyhedra<scalar>&reachTube=(!m_safeReachTube.isEmpty() && ms_incremental) ? getRefinedAbstractReachTube(iteration,precision,directions,m_inputType) : getAbstractReachTube(iteration,precision,directions,m_inputType);
    reachTube.logTableau("PreCegar:",true);
    if (ms_trace_dynamics[eTraceAbstraction]) reachTube.logVertices(true);
  }
  if (!m_safeReachTube.isEmpty()) {
    AbstractPolyhedra<scalar> bounds;
    synthesiseDynamicBounds(bounds,m_inputType,m_safeReachTube.getPolyhedra(eEigenSpace));
    if (ms_trace_dynamics[eTraceBounds]) {
      bounds.logTableau("Projected Bounds: ",true);
    }
    powerS maxIter=calculateMaxIterations(100);
    if (maxIter>0) {
      int minFreq=maxIter;
      for (int i=0;i<m_dimension;i++) {
        if ((m_freq[i]>0) && (m_freq[i]<minFreq)) minFreq=m_freq[i];
      }
      if (!m_hasNegatives && (minFreq<8)) {
        if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData("rotation too wide: resampling");
        resample(0.25);
        maxIter=calculateMaxIterations(100);
      }
    }
    if (maxIter==0) maxIter=1;
    dynamics.m_spaceSize=boundingHyperBox(iterations);
    if (ms_aggressive) {
      if (ms_trace_dynamics[eTraceAbstractDynamics]) dynamics.logTableau("original",true);
      getEigenCloud(maxIter,false);
      bounds.normalise();
      MatrixS vectors=bounds.getDirections();
      MatrixS supports(vectors.cols(),3);
      powerS iter;
      bool refined=false;
      bool sat=true;
      for (int i=0;i<vectors.cols();i++) {
        MatrixS vector=vectors.col(i);
        scalar support=dynamics.maximise(vector,Tableau<scalar>::eResetBasis,true);
        supports.coeffRef(i,0)=support;
        if (func::isPositive(support-bounds.getSupport(i))) {
          support=eigenCloudSupport(vector,iter);
          if (func::isNegative(support-bounds.getSupport(i))) {
            dynamics.addTaggedDirection(vector,support,iteration_pair(-1,-1,iter));
            refined=true;
          }
          else sat=false;
        }
        supports.coeffRef(i,1)=support;
      }
      if (ms_trace_dynamics[eTraceAbstractDynamics]) {
        supports.col(2)=bounds.getSupports();
        ms_logger.logData(vectors,supports,"Aggressive:",true);
        if (ms_trace_dynamics[eTraceBounds]) {
          MatrixS supports;
          dynamics.maximiseAll(vectors,supports);
        }
      }
      if (refined && ms_trace_dynamics[eTraceAbstractDynamics]) dynamics.logTableau("refined",true);
      if (ms_trace_dynamics[eTraceTime]) {
        ms_logger.logData(timer.elapsed()*1000,"Explicit Refinement time:",true);
      }
      /*if (sat)*/ return dynamics;
    }
    refineAbstractDynamics(bounds,false);
    if (ms_trace_dynamics[eTraceAbstractDynamics]) {
      AbstractPolyhedra<scalar>& result=getRefinedAbstractReachTube(eNormalSpace);
      result.logTableau("PosCegar:",true);
      if (ms_trace_dynamics[eTraceAbstraction]) result.logVertices(true);
    }
  }
  return getAbstractDynamics(m_inputType);
}

/// Retrieves a list of iterations whose reach set fails the specification
template<class scalar>
bool CegarSystem<scalar>::findCounterExampleIterations(powerList &iterations,AbstractPolyhedra<scalar> &bounds)
{
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);
  MatrixS &vertices=dynamics.getVertices(true);
  if (ms_trace_dynamics[eTraceAbstractDynamics]) {
    dynamics.logTableau("Abstract Dynamics",true);
    ms_logger.logData(vertices,"Abstract Dynamics Vertices");
  }
  bool found=false;
  for (int i=0;i<vertices.rows();i++) {
    MatrixS point=vertices.row(i);
    if (!bounds.isInside(point)) {
      if (ms_trace_dynamics[eTraceAbstractDynamics]) ms_logger.logData(i,"Violating abstract vertex",true);
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
  if (findCounterExampleIterations(iterations,bounds)) {
    AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);
    typename powerList::iterator it;
    for (it=iterations.begin();it!=iterations.end();it++) {
      addSupportsAtIteration(dynamics,it->first,m_maxIterations);
    }
    return true;
  }
  return false;
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
    if (ms_trace_dynamics[eTraceAbstraction]) ms_logger.logData(m_accelInSupports,"Input Supports",true);
  }
  return m_accelInSupports;
}

/// Retrieves the reach tube at the given iteration
template <class scalar>
AbstractPolyhedra<scalar>& CegarSystem<scalar>::getRefinedAbstractReachTube(space_t space,bool guarded)
{
  boost::timer timer;
  m_reachTime=-1;
  if (m_idimension==0) m_inputType=eNoInputs;
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);

  MatrixS templates=m_safeReachTube.isEmpty() ? getTemplates(eEigenSpace) : m_safeReachTube.getPolyhedra(eEigenSpace).getDirections();
  MatrixS supports;
  if (m_dimension+m_idimension>10) {
    init.getVertices(true);
    if (m_idimension>0) getAccelVertices(true);
     supports.resize(templates.cols(),1);
     for (int i=0;i<templates.cols();i++) {
      if (ms_trace_dynamics[eTraceTime]) {
        std::stringstream buffer;
        buffer << i << " of " << templates.cols();
        ms_logger.logData(buffer.str());
      }
      MatrixS localSupport=getAbstractReachTubeSupports(dynamics,templates.col(i));
      supports.coeffRef(i,0)=localSupport.coeff(0,0);
    }
  }
  else {
    MatrixS &vectors=getAbstractVertices(templates);
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Abstract Vertices: ",true);
    if (!dynamics.maximiseAll(vectors,supports)) processError(dynamics.getName());
    if (m_inputType>eNoInputs) getAccelInSupports(templates); // getRefinedAccelInSupports();?
    if (ms_trace_dynamics[eTraceAbstractVertices]) {
      traceSupports(templates,supports,dynamics,vectors);
    }
    if (m_inputType>eNoInputs) {
      mergeAccelInSupports(supports,templates.cols());
      if (this->ms_trace_dynamics[eTraceAbstractVertices]) {
        ms_logger.logData(vectors,supports,"Combined",true);
      }
    }
    mergeAbstractSupports(templates,supports);
  }
  MatrixS faces=templates.transpose();
  m_pAbstractReachTube->mergeLoad(init,faces,supports,eEigenSpace);
  AbstractPolyhedra<scalar>& result=m_pAbstractReachTube->getPolyhedra(space);
  if (guarded) getGuardedReachTube(result,space);
  if (ms_trace_dynamics[eTraceAbstraction]) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
  getOutputReachTube(result, -1);
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
    if (ms_trace_dynamics[eTraceTime]) {
      std::stringstream buffer;
      buffer << i << " of " << numTemplates;
      ms_logger.logData(buffer.str());
    }
    MatrixS localSupport=getRefinedAbstractReachTubeSupports(iteration,precision,dynamics,i);
    supports.coeffRef(i,0)=localSupport.coeff(0,0);
  }
  MatrixS faces=templates.transpose();
  m_pAbstractReachTube->mergeLoad(init,faces,supports,eEigenSpace);
  AbstractPolyhedra<scalar>& result=m_pAbstractReachTube->getPolyhedra(space);
  if (guarded) getGuardedReachTube(result,space);
  if (ms_trace_dynamics[eTraceAbstraction]) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
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
          if (ms_trace_dynamics[eTraceAbstraction]) ms_logger.logData(maxSupport,"New support",true);
          return true;
        }
        else if (iter<m_eigenCloud.rows()) return false;
      }
    }
    findIterations(point,iterations,true);
  }
  if (iterations.size()>0) {
    if (ms_trace_dynamics[eTraceAbstraction]) ms_logger.logData(iterations.size(),"Refining",true);
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
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Sort Time",true);
  sortedVectors.block(0,0,sortedVectors.rows(),sortedVectors.cols())=vectors.transpose();
  for (int index=0;index<=supports.rows();) {
    newIndex=dynamics.ceMaximise(sortedVectors,supports,inSupports,max,ce,result,index);
    if (ms_trace_dynamics[eTraceDynamics]) ms_logger.logData(newIndex,"refining index",true);
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
    int numInputVertices=getRoundedAbstractVertices(in_vectors,templates,true);
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
    if (ms_trace_dynamics[eTraceAbstractVertices]) ms_logger.logData(vectors,supports,"Partial Combined",true);
  }

  mergeAbstractSupports(templates,supports);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Abstract Tube Support: ",true);
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

template <class scalar>
bool CegarSystem<scalar>::makeClosedSystem(CegarSystem<scalar> &closedSystem)
{
  int dimension=(m_inputType>eParametricInputs) ? 4*m_dimension : 2*m_dimension;
  closedSystem.setParams(m_paramValues);
  closedSystem.m_paramValues.coeffRef(eNumStates,0)=dimension;
  for (int i=0;i<3;i++) {
    closedSystem.m_paramValues.coeffRef(eNumInputs,i)=0;
    closedSystem.m_paramValues.coeffRef(eNumVarInputs,i)=0;
  }
  MatrixS dynamics(dimension,dimension);
  AbstractPolyhedra<scalar> guard;
  AbstractPolyhedra<scalar> safeReachTube;
  AbstractPolyhedra<scalar> inputs(m_transformedInputs.getPolyhedra());
  AbstractPolyhedra<scalar> initialState(m_initialState.getPolyhedra());
  if (m_inputType>eParametricInputs) {
    dynamics.block(0,0,dimension,m_dimension)=MatrixS::Zero(dimension,m_dimension);
    dynamics.block(0,m_dimension,m_dimension,m_dimension)=MatrixS::Identity(m_dimension,m_dimension);
    dynamics.block(m_dimension,m_dimension,m_dimension,m_dimension)=m_dynamics;
    dynamics.block(2*m_dimension,m_dimension,2*m_dimension,m_dimension)=MatrixS::Zero(2*m_dimension,m_dimension);
    dynamics.block(0,2*m_dimension,m_dimension,m_dimension)=MatrixS::Identity(m_dimension,m_dimension);
    dynamics.block(m_dimension,2*m_dimension,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
    dynamics.block(2*m_dimension,2*m_dimension,m_dimension,m_dimension)=MatrixS::Identity(m_dimension,m_dimension);
    dynamics.block(3*m_dimension,2*m_dimension,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
    dynamics.block(0,3*m_dimension,2*m_dimension,m_dimension)=MatrixS::Zero(2*m_dimension,m_dimension);
    dynamics.block(2*m_dimension,3*m_dimension,m_dimension,m_dimension)=MatrixS::Identity(m_dimension,m_dimension);
    for (int row=0;row<m_dimension;row++) {
      for (int col=0;col<m_dimension;col++) {
        if (func::isPositive(m_dynamics.coeff(row,col))) dynamics.coeffRef(3*m_dimension+row,3*m_dimension+col)=m_dynamics.coeff(row,col);
        else dynamics.coeffRef(3*m_dimension+row,3*m_dimension+col)=-m_dynamics.coeff(row,col);
      }
    }

    m_transformedInputs.getPolyhedra().getSquareAbstraction(inputs,true);
    AbstractPolyhedra<scalar> secondState;
    AbstractPolyhedra<scalar> secondInput;
    initialState.getTransformedPolyhedra(secondState,m_dynamics);
    initialState.concatenate(secondState);
    inputs.getTransformedPolyhedra(secondInput,m_dynamics);
    initialState.concatenate(inputs);
    initialState.concatenate(secondInput);
  }
  else {
    dynamics.block(0,0,m_dimension,m_dimension)=m_dynamics;
    dynamics.block(0,m_dimension,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
    dynamics.block(m_dimension,0,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
    dynamics.block(m_dimension,m_dimension,m_dimension,m_dimension)=MatrixS::Identity(m_dimension,m_dimension);
    initialState.concatenate(inputs);
  }
  inputs.clear();
  MatrixS sensitivity=MatrixS(0,0);
  closedSystem.setInputType(eNoInputs);
  closedSystem.changeDimensions(dynamics.rows(),sensitivity.cols(),0,0);
  bool result=closedSystem.load(dynamics,sensitivity,guard,initialState,inputs,safeReachTube);
  return result;
}

/// Explicitly calculates the vertex progression up to step and checks if it remains inside guard
template <class scalar>
typename CegarSystem<scalar>::powerS CegarSystem<scalar>::checkExplicitReachability(powerS step,const MatrixS &transform)
{
  MatrixS truevertices=m_initialState.getPolyhedra().getVertices();
  MatrixS vertices=m_initialState.getPolyhedra(eEigenSpace).getVertices();
  MatrixS reachDynamics=transform*m_dynamics*makeInverse(transform);
  MatrixS &dynamics=getEigenCloud(step,false);
  AbstractPolyhedra<scalar>& safe=m_safeReachTube.getPolyhedra(eEigenSpace);
  if (ms_trace_dynamics[eTraceTime]) {
    m_safeReachTube.getPolyhedra().logTableau("safe", true);
    ms_logger.logData(reachDynamics,"reach dynamics");
  }
  for (int row=0;row<vertices.rows();row++) {
    MatrixS newVertices=dynamics;
    for (int col=0;col<vertices.cols();col++) newVertices.col(col)*=vertices.coeff(row,col);
    for (int col=0;col<vertices.cols();col++) {
      if (m_conjugatePair[col]>col) {
        MatrixS temp=newVertices.col(col);
        newVertices.col(col)+=newVertices.col(m_conjugatePair[col]);
        newVertices.col(m_conjugatePair[col])=temp-newVertices.col(m_conjugatePair[col]);
      }
    }
    std::pair<int,int> iter=safe.violatingSupport(newVertices);
    if (ms_trace_dynamics[eTraceDynamics]) {
      newVertices.row(0)=truevertices.row(row);
      for (int i=1;i<newVertices.rows();i++) {
        newVertices.row(i)=newVertices.row(i-1)*m_dynamics.transpose();
      }
      ms_logger.logData(newVertices," progression: ");
      newVertices*=transform.transpose();
      ms_logger.logData(newVertices," reach-progression: ");
      newVertices.row(0)=truevertices.row(row)*transform.transpose();
      for (int i=1;i<newVertices.rows();i++) {
        newVertices.row(i)=newVertices.row(i-1)*reachDynamics.transpose();
      }
      ms_logger.logData(newVertices," reach-prog: ");
    }
    if (iter.second>=0) {
      ms_logger.logData(row,"failed explict check ");
      ms_logger.logData(iter.second+1," on iteration ",true);
      return iter.second+1;
    }
  }
  ms_logger.logData("explict check passed");
  return 0;
}

/// Loads a polyhedral description for the initial state
template <class scalar>
int CegarSystem<scalar>::loadOutputInitialState(const std::string &data,bool vertices,size_t pos,size_t end)
{
  boost::timer timer;
  AbstractPolyhedra<scalar> polyhedra(m_odimension);
  int result=polyhedra.loadData(data,vertices,pos,end);
  m_initialOutputs.copy(polyhedra);
  polyhedra.transform(ms_emptyMatrix,m_outputSensitivity);
  if (m_initialState.getPolyhedra().isEmpty()) polyhedra.maxConstrain(1000000);
  m_initialState.getPolyhedra().intersect(polyhedra);
  m_initialState.clear(false);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Output State time:",true);
  return result;
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
