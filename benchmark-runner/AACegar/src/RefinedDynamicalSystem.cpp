#include "RefinedDynamicalSystem.h"
#include <boost/timer.hpp>
#include <set>
#include <Eigen/QR>
#include <Eigen/Eigenvalues>

namespace abstract{

template <class scalar>
bool CegarSystem<scalar>::ms_fixedBVs=false;

template <class scalar>
bool CegarSystem<scalar>::ms_canonical=false;

/// Constructs an empty buffer
template<class scalar>
CegarSystem<scalar>::CegarSystem(int dimension,int idimension) :
  DynamicalSystem<scalar>(dimension,idimension),
  m_eigenValueCap(func::ms_1),
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
  DynamicalSystem<scalar>::copy(source);
  m_observer=source.m_observer;
  m_observerDynamics=source.m_observerDynamics;
  m_observerSensitivity=source.m_observerOutputSensitivity;
  m_observerOutputSensitivity=source.m_observerOutputSensitivity;
  m_eigenValueCap=source.m_eigenValueCap;
  m_observerDynamicsError=source.m_observerDynamicsError;
  m_observerSensitivityError=source.m_observerSensitivityError;
  m_observerOutputSensitivityError=source.m_observerOutputSensitivityError;
  m_incOrderType=source.m_incOrderType;
}

/// retrieves the Jordan form of the system sampled at SampleTime
template<class scalar>
typename CegarSystem<scalar>::MatrixC CegarSystem<scalar>::getSampledJordanForm(scalar sampleTime)
{
  MatrixC eigenValues=m_eigenValues;
  for (int i=0;i<m_dimension;i++) {
    complexS power=eigenValues.coeffRef(i,i)*sampleTime;
    scalar mag=exp(power.real());
    scalar real=mag*func::cosine(power.imag());
    scalar imag=mag*func::sine(power.imag());
    complexS value=complexS(real,imag);
    eigenValues.coeffRef(i,i)=value;
    powerS div=1;
    for (int j=1;j<m_jordanIndex[i];j++) {
      div*=j;
      eigenValues.coeffRef(i-j,i)=eigenValues.coeffRef(i,i)*func::pow(sampleTime,j)/scalar(div);
    }
  }
  return eigenValues;
}

/// retrieves the dynamics of the system sampled at SampleTime
template<class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getSampledDynamics(scalar sampleTime)
{
  MatrixS pseudoEigenValues=jordanToPseudoJordan(getSampledJordanForm(sampleTime),this->eToEigenValues);
  return m_pseudoEigenVectors*pseudoEigenValues*m_invPseudoEigenVectors;
}

/// retrieves the delay noise matrix
template<class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getDelayNoise(scalar sampleTime, scalar maxDelay)
{
  MatrixS discreteDynamics=getSampledDynamics(sampleTime);
  MatrixS delayDynamics=getSampledDynamics(maxDelay);
  MatrixS finalDynamics=getSampledDynamics(sampleTime-maxDelay);
  MatrixS reverseDynamics=makeInverse(m_dynamics);
  MatrixS vectors(2*m_outputSensitivity.rows(),m_sensitivity.cols());
  vectors.block(0,0,m_outputSensitivity.rows(),m_sensitivity.cols())=m_outputSensitivity*reverseDynamics*(discreteDynamics-finalDynamics)*m_sensitivity;
  vectors.block(m_outputSensitivity.rows(),0,m_outputSensitivity.rows(),m_sensitivity.cols())=m_outputSensitivity*finalDynamics*reverseDynamics*(delayDynamics-MatrixS::Identity(m_dimension,m_dimension))*m_sensitivity;
  vectors.transposeInPlace();
  MatrixS result;
  m_inputs.maximiseAll(vectors,result);
  return result;
}

/// turns a continuous time system into a discrete
template<class scalar>
void CegarSystem<scalar>::sample(scalar sampleTime,scalar delayTime)
{
  m_sampleTime=sampleTime;
  m_delayTime=delayTime;
  if (m_cosFactors.rows()<=m_dimension) m_cosFactors.conservativeResize(m_dimension+1,1);
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
    powerS div=1;
    for (int j=1;j<m_jordanIndex[i];j++) {
      div*=j;
      m_eigenValues.coeffRef(i-j,i)=m_eigenValues.coeffRef(i,i)*func::pow(sampleTime,j)/scalar(div);
    }
  }
  m_pseudoEigenValues=jordanToPseudoJordan(m_eigenValues,this->eToEigenValues);
  MatrixS discrete_dynamics=m_pseudoEigenVectors*m_pseudoEigenValues*m_invPseudoEigenVectors;
  MatrixS integrator=discrete_dynamics-MatrixS::Identity(m_dimension,m_dimension);
  integrator=makeInverse(m_dynamics)*integrator;
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
  findFrequencies();
  findZeniths();
  if (ms_trace_dynamics>=eTraceDynamics) {
    ms_logger.logData(m_sensitivity,"Discrete Sensitivity");
  }
}

/// turns a discrete time system into a continuous one
template<class scalar>
void CegarSystem<scalar>::unsample(scalar sampleTime)
{
  m_sampleTime=sampleTime;
  /*if (m_cosFactors.rows()<=m_dimension) m_cosFactors.conservativeResize(m_dimension+1,1);
  m_cosFactors.coeffRef(m_dimension,0)=func::ms_1;*/
  for (int i=0;i<m_dimension;i++) {
    complexS coef=m_eigenValues.coeffRef(i,i);
    scalar mag=log(func::norm2(coef));
    scalar angle=func::invtan(coef.imag(),coef.real());
    complexS value=complexS(mag,angle)/sampleTime;
    m_eigenValues.coeffRef(i,i)=value;
    m_eigenNorms.coeffRef(i,0)=func::norm2(value);
    /*if (m_conjugatePair[i]>=0) {
      m_cosFactors.coeffRef(i,0)=m_eigenNorms.coeffRef(i,0)/value.real();
      m_cosFactors.coeffRef(m_dimension,0)*=m_cosFactors.coeffRef(i,0);
    }
    powerS div=1;
    for (int j=1;j<m_jordanIndex[i];j++) {
      div*=j;
      m_eigenValues.coeffRef(i-j,i)=m_eigenValues.coeffRef(i,i)*func::pow(sampleTime,j)/scalar(div);
    }*/
  }
  m_pseudoEigenValues=jordanToPseudoJordan(m_eigenValues,this->eToEigenValues);
  MatrixS continuous_dynamics=m_pseudoEigenVectors*m_pseudoEigenValues*m_invPseudoEigenVectors;
  MatrixS derivator=m_dynamics-MatrixS::Identity(m_dimension,m_dimension);
  derivator=makeInverse(derivator)*continuous_dynamics;
  if (ms_trace_dynamics>=eTraceDynamics) {
    ms_logger.logData(m_dynamics,"Discrete Dynamics");
    ms_logger.logData(m_sensitivity,"Discrete Sensitivity");
    ms_logger.logData(continuous_dynamics,"Dynamics");
    ms_logger.logData(derivator,"Derivator");
    ms_logger.logData(m_pseudoEigenValues,"PseudoEigenValues");
    ms_logger.logData(m_pseudoEigenVectors,"PseudoEigenVectors");
    ms_logger.logData(m_invPseudoEigenVectors,"InvPseudoEigenVectors");
  }
  m_sensitivity=derivator*m_sensitivity;
  m_dynamics=continuous_dynamics;
  if (ms_trace_dynamics>=eTraceDynamics)
  {
    ms_logger.logData(m_sensitivity,"Continuous Sensitivity");
  }
  sample(sampleTime,0);
}

template<class scalar>
bool CegarSystem<scalar>::sample(std::string &sampleTime)
{
  scalar time,delay=0;
  char* pEnd=func::toScalar(sampleTime.data(),time);
  if (pEnd==sampleTime.data()) return false;
  if (pEnd[0]==':') {
    pEnd++;
    char *pStart=pEnd;
    if (pEnd[0]!=':') pEnd=func::toScalar(pEnd,delay);
    if (pEnd==pStart) return false;
  }
  char sign=func::hardSign(time);
  if ((sign>0) && (pEnd[0]==':')) {
    pEnd++;
    scalar max,min=time;
    if (pEnd==func::toScalar(pEnd,max)) return false;
    MatrixC eigenValues=m_eigenValues;
    MatrixS sensitivity=m_sensitivity;
    sample(min,delay);
    refScalar minCap=findMaxValue(true,false,true);
    m_eigenValues=eigenValues;
    m_sensitivity=sensitivity;
    sample(max,delay);
    refScalar maxCap=findMaxValue(true,false,true);
    scalar m3=3;
    scalar d4=4;
    scalar m100=100;
    while(func::isPositive(max-min-delay*m100)) {
      scalar midmin=(m3*min+max)/d4;
      m_eigenValues=eigenValues;
      m_sensitivity=sensitivity;
      sample(midmin,delay);
      refScalar midminCap=findMaxValue(true,false,true);
      scalar midmax=(min+m3*max)/d4;
      m_eigenValues=eigenValues;
      m_sensitivity=sensitivity;
      sample(midmax,delay);
      refScalar midmaxCap=findMaxValue(true,false,true);
      if (minCap<midminCap) {
        maxCap=midminCap;
        max=midmin;
      }
      else if (maxCap<midmaxCap) {
        minCap=midmaxCap;
        min=midmax;
      }
      else if (midminCap<midmaxCap) {
        maxCap=midmaxCap;
        max=midmax;
        if (minCap>midmaxCap) {
          minCap=midminCap;
          min=midmin;
        }
      }
      else {
        minCap=midminCap;
        min=midmin;
        if (maxCap>midminCap) {
          maxCap=midmaxCap;
          max=midmax;
        }
      }
    }
    m_eigenValues=eigenValues;
    m_sensitivity=sensitivity;
    time=(max+min)/scalar(2);
  }
  if (sign>0)       sample(time,delay);
  else if (sign<0)  unsample(-time);
  else              return false;
  return true;
}

/// Rescales the eigenvalues to change the granularity
template<class scalar>
bool CegarSystem<scalar>::resample(scalar scale)
{
  if (m_hasMultiplicities) return false;
  m_sampleTime*=scale;
  if (m_cosFactors.rows()<=m_dimension) m_cosFactors.conservativeResize(m_dimension+1,1);
  m_cosFactors.coeffRef(m_dimension,0)=func::ms_1;
  for(int i=0;i<m_dimension;i++) {
    scalar mag=exp(log(func::norm2(m_eigenValues.coeffRef(i,i)))*scale);
    scalar arg=scale*func::invtan(m_eigenValues.coeffRef(i,i).imag(),m_eigenValues.coeffRef(i,i).real());
    complexS value(mag*func::cosine(arg),func::sine(arg));
    m_eigenValues.coeffRef(i,i)=value;
    m_eigenNorms.coeffRef(i,0)=func::norm2(m_eigenValues.coeffRef(i,i));
    if (m_conjugatePair[i]>=0) {
      m_cosFactors.coeffRef(i,0)=m_eigenNorms.coeffRef(i,0)/m_eigenValues.coeffRef(i,i).real();
      m_cosFactors.coeffRef(m_dimension,0)*=m_cosFactors.coeffRef(i,0);
    }
  }
  m_pseudoEigenValues=jordanToPseudoJordan(m_eigenValues,this->eToEigenValues);
  MatrixS dynamics=m_pseudoEigenVectors*m_pseudoEigenValues*m_invPseudoEigenVectors;
  MatrixS integrator=(MatrixS::Identity(m_dimension,m_dimension)-dynamics)*(MatrixS::Identity(m_dimension,m_dimension)-m_dynamics).inverse();
  m_sensitivity=integrator*m_sensitivity;
  m_dynamics=dynamics;
  findFrequencies();
  findZeniths();
  return true;
}

template<class scalar>
bool CegarSystem<scalar>::setSpeed(std::string &max)
{
  scalar speed;
  if (func::toScalar(max.data(),speed)==max.data()) return false;
  m_eigenValueCap=speed;
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
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getDynamicPolynomialCoefficients(const MatrixC &eigenValues)
{
  int dimension=eigenValues.rows();
  MatrixC result=MatrixC::Zero(2,dimension+1);
  result.coeffRef(0,0)=ms_one;
  result.coeffRef(0,1)=-eigenValues.coeff(0,0);
  for (int i=1;i<dimension;i++) {
    result.row(1)=-result.row(0)*eigenValues.coeff(i,i);
    result.block(0,1,1,i+1)+=result.block(1,0,1,i+1);
  }
  return result.real();
}

/// Retrieves the characteristic polynomial coefficients of the dynamics
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getDynamicPolynomialCoefficients()
{
  return getDynamicPolynomialCoefficients(m_eigenValues);
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
  return makeInverse(result);
}

/// Retrieves the observability matrix [C CA CA^2 ...CA^{n-1}]^T
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getObservabilityMatrix()
{
  MatrixS outputSensitivity=m_outputSensitivity;
  if (outputSensitivity.cols()==0) {
    outputSensitivity=MatrixS::Zero(1,m_dimension);
    outputSensitivity.coeffRef(0,0)=ms_one;
  }
  MatrixS result(m_dimension*outputSensitivity.rows(),outputSensitivity.cols());
  result.block(0,0,outputSensitivity.rows(),outputSensitivity.cols())=outputSensitivity;
  MatrixS multiplier=m_dynamics;
  for (int i=1;i<m_dimension;i++)
  {
    result.block(i*outputSensitivity.rows(),0,outputSensitivity.rows(),outputSensitivity.cols())=outputSensitivity*multiplier;
    multiplier*=m_dynamics;
  }
  return result;
}

/// Retrieves the transform matrix T : z=T^{-1}x turns A,B,C into observable canonical form
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getObservableCanonicalTransformMatrix()
{
  MatrixS CanonicalObservabilityMatrix=getCanonicalReachabilityMatrix().transpose();
  MatrixS ObservabilityMatrix=getObservabilityMatrix();
  return makeInverse(ObservabilityMatrix)*makeInverse(CanonicalObservabilityMatrix);
  CanonicalObservabilityMatrix*=ObservabilityMatrix;
  return makeInverse(CanonicalObservabilityMatrix);
}

/// Creates matrices T, invT , [W, invW], to make a reachable [observable] system
template <class scalar>
void CegarSystem<scalar>::makeReachabilityMatrices(bool observer)
{
  MatrixS canonical=getCanonicalReachabilityMatrix();
  m_invT=getReachabilityMatrix()*canonical;
  m_T=makeInverse(m_invT);
  if (observer) {
    m_W=canonical*getObservabilityMatrix();
    m_invW=makeInverse(m_W);
  }
  m_T=getReachableCanonicalTransformMatrix();
  m_invT=m_T.inverse();
  if (observer) {
    m_invW=getObservableCanonicalTransformMatrix();
    m_W=makeInverse(m_invW);
  }
}

/// Retrieves the reference gain
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::getReferenceGain()
{
  MatrixS closedLoop=m_dynamics-(m_sensitivity*m_feedback);
  return m_outputSensitivity*makeInverse(closedLoop)*m_sensitivity;
}

/// Retrieves the reach tube at the given iteration
template <class scalar>
/// Retrieves refined dynamics given a safety specification
AbstractPolyhedra<scalar>& CegarSystem<scalar>::getRefinedDynamics(int refinements,bool agressive, powerS iteration,int directions,inputType_t inputType)
{
  int precision=m_paramValues.coeff(eLogFaces,0);
  if (precision<=0) precision=2;
  AbstractPolyhedra<scalar>&reachTube=(!m_safeReachTube.isEmpty() && ms_incremental) ? getRefinedAbstractReachTube(iteration,precision,directions,inputType) : getAbstractReachTube(iteration,precision,directions,inputType);
  if (ms_trace_dynamics>=eTraceDynamics) {
    reachTube.logTableau("PreCegar:",true);
    reachTube.logVertices(true);
  }
  //if (m_safeReachTube.getPolyhedra().contains(reachTube)) return getAbstractDynamics(inputType);
  if (!m_safeReachTube.isEmpty()) {
    AbstractPolyhedra<scalar> bounds;
    synthesiseDynamicBounds(bounds,m_inputType,m_safeReachTube.getPolyhedra(eEigenSpace));
    if (ms_trace_dynamics>=eTraceDynamics) {
      bounds.logTableau("Projected Bounds: ",true);
    }
    if (agressive) {
      powerS maxIter=calculateMaxIterations(100);
      if (maxIter>0) {
        int minFreq=maxIter;
        for (int i=0;i<m_dimension;i++) {
          if ((m_freq[i]>0) && (m_freq[i]<minFreq)) minFreq=m_freq[i];
        }
        if (minFreq<8) {
          resample(0.25);
          maxIter=calculateMaxIterations(100);
        }
      }
      if (maxIter==0) maxIter=1;
      getEigenCloud(maxIter,false);
      bounds.normalise();
      MatrixS vectors=bounds.getDirections();
      MatrixS supports(vectors.cols(),1);
      powerS iter;
      for (int i=0;i<vectors.cols();i++) {
        MatrixS vector=vectors.col(i);
        supports.coeffRef(i,0)=eigenCloudSupport(vector,iter);
      }
      AbstractPolyhedra<scalar> &dynamics=getAbstractDynamics(inputType);
      AbstractPolyhedra<scalar> refined(m_dimension);
      refined.load(vectors,supports,true);
      refined.removeRedundancies(0.001);
      if (ms_trace_dynamics>=eTraceAbstraction) {
        dynamics.logTableau("original",true);
      }
      refined.intersect(dynamics);
      dynamics.copy(refined);
      dynamics.removeRedundancies();
      if (ms_trace_dynamics>=eTraceAbstraction) {
        dynamics.logTableau("refined",true);
      }
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
void CegarSystem<scalar>::synthesiseDynamicBounds(AbstractPolyhedra<scalar> &result,inputType_t inputType,AbstractPolyhedra<scalar> &end)
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
  result.load(vectors,supports);
  if (ms_trace_dynamics>=eTraceAll) {
    result.logTableau("Full Bounds",true);
  }
  result.removeRedundancies();
}

/// Creates a model for the quantization noise as an input specification
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::generateNoiseInput(scalar sampling,scalar delay)
{
  int odimension=(m_odimension>0) ? m_odimension : m_dimension;
  int ndimension=1;
  AbstractPolyhedra<scalar> result(ndimension);
  int fbits;
  fbits=m_paramValues.coeff(eNumBits,2);
  if (fbits<=0) fbits=m_paramValues.coeff(eNumBits,0);
  if (fbits<=0) fbits=func::getDefaultPrec();
  scalar lsb=func::pow(this->ms_two,-fbits);
  MatrixS faces(2*ndimension,ndimension);
  MatrixS supports(2*ndimension,1);
  faces.block(0,0,ndimension,ndimension)=MatrixS::Identity(ndimension,ndimension);
  faces.block(ndimension,0,ndimension,ndimension)=-MatrixS::Identity(ndimension,ndimension);
  scalar fb_noise=m_feedback.cwiseAbs().sum()/*lpNorm<1>()*/+this->ms_one;//|Noise|<(|K|_1+1)lsb assuming q1,q2=1lsb,(q3:=q1->K) = (|K|_1q1+q2)
  supports.coeffRef(0,0)=lsb*(fb_noise);
  if (!func::isZero(delay)) supports.coeffRef(0,0)+=getDelayNoise(sampling,delay).norm();
  supports.coeffRef(1,0)=supports.coeff(0,0);
  result.load(faces,supports);
  return result;
}

/// Creates a model for the input of the closed loop
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::generateFeedbackInput(int fdimension,bool makeNoise,MatrixS &sensitivity,scalar sampling,scalar delay)
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
    AbstractPolyhedra<scalar> noiseInputs=generateNoiseInput(sampling,delay);
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
    if (ms_trace_time) {
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

/// Truncates the value to the current controller precision
template <class scalar>
scalar CegarSystem<scalar>::truncateCoefficient(const scalar& coeff)
{
  int totalbits=m_paramValues.coeff(eNumBits,1);
  long long fracbits=m_paramValues.coeff(eNumBits,2);
  if (totalbits<=0) {
    totalbits=m_paramValues.coeff(eNumBits,0);
    if (totalbits<=0) totalbits=func::getDefaultPrec();
    fracbits=totalbits;
  }
  else if (fracbits==0) fracbits=totalbits>>1;
  refScalar fxp_one = (1 << fracbits);
  if (ms_fixedBVs) {
    int intbits=totalbits-fracbits;
    scalar lower=floor(func::toLower(coeff) * fxp_one)/fxp_one;
    scalar upper=floor(func::toUpper(coeff) * fxp_one)/fxp_one;
    scalar new_coeff=func::getHull(lower,upper);
    scalar fxp_max=(1 << intbits);
    return (func::isPositive(new_coeff-fxp_max)) ? fxp_max : new_coeff;
  }
  int expMask=(1<<(totalbits-fracbits-1))-1;
  fxp_one*=2;
  typename func::exponent exp;
  scalar upper=floor(func::extractExponent(func::toUpper(coeff),exp)*fxp_one);
  if (exp>expMask) upper=(1<<(expMask+1))-(1.0/(1<<expMask));
  else if (exp>=0) upper*=scalar(1<<exp);
  else if (-exp>expMask) upper=0;
  else upper/=scalar(1<<-exp);
  scalar lower=floor(func::extractExponent(func::toLower(coeff),exp)*fxp_one);
  if (exp>expMask) upper=(1<<(expMask+1))-(1.0/(1<<expMask));
  else if (exp>=0) lower*=scalar(1<<exp);
  else if (-exp>expMask) lower=0;
  else lower/=scalar(1<<-exp);
  scalar newCoeff=func::getHull(lower,upper);
  newCoeff/=fxp_one;
  return newCoeff;
}

/// Retrieves constraints on the controller coefficients based on the Dynamic constraints
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::getControllerDynBounds(AbstractPolyhedra<scalar>& reachTube,int &orBlockSize)
{
  //max((I-A-BK)Sv)>max(Rv) -> +p_R+p_S((A-I)^T)<-p_S(BK)
  //(A-I)S-R>-SBK -> -\sum(bji)k_{lj}S_lV_l < (A-I)Sv-B_nR_nv
  MatrixS templates=reachTube.getDirections();

  MatrixS dynamics=m_dynamics;
  for (int i=0;i<m_dimension;i++) dynamics.coeffRef(i,i)-=ms_one;
  MatrixS aDirections=dynamics.transpose()*templates;
  MatrixS inDirections=m_sensitivity.transpose()*templates;
  MatrixS aSupports;
  reachTube.maximiseAll(aDirections,aSupports);

  if (!m_reference.isEmpty()) {
    MatrixS inSupports;
    m_reference.maximiseAll(inDirections,inSupports);
    aSupports-=inSupports;
  }

  MatrixS &vertices=reachTube.getVertices();
  orBlockSize=vertices.rows();
  MatrixS supports(aSupports.rows()*vertices.rows(),1);
  MatrixS faces(supports.rows(),m_feedback.rows()*m_feedback.cols());
  MatrixS coefficients=templates.transpose()*m_sensitivity;
  for (int row=0;row<templates.cols();row++) {
    for (int i=0;i<orBlockSize;i++) {
      for (int j=0;j<m_feedback.rows();j++) {
        faces.block(row*orBlockSize+i,j*m_dimension,1,m_dimension)=coefficients.coeff(row,j)*vertices.row(i);
      }
      supports.coeffRef(row*orBlockSize+i,0)=aSupports.coeff(row,0);
    }
  }
  AbstractPolyhedra<scalar> result(faces.cols());
  result.load(faces,supports);
  return result;
}

/// Retrieves constraints on the controller coefficients based on the I/O constraints
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::getControllerInBounds(AbstractPolyhedra<scalar>& reachTube)
{
  MatrixS &vertices=reachTube.getVertices();
  MatrixS directions=m_inputs.getDirections();
  directions.conservativeResize(m_fdimension,directions.cols());
  MatrixS faces(vertices.rows()*directions.cols(),vertices.cols()*m_fdimension);
  MatrixS supports(vertices.rows()*directions.cols(),1);
  MatrixS inputSupports=m_inputs.getSupports();
  for (int row=0;row<vertices.rows();row++) {
    for (int col=0;col<directions.cols();col++) {
      for (int i=0;i<m_fdimension;i++) {
        for (int j=0;j<vertices.cols();j++) {
          faces.coeffRef(row*directions.cols()+col,i*vertices.cols()+j)=vertices.coeff(row,j)*directions.coeff(i,col);
        }
      }
      supports.coeffRef(row*directions.cols()+col)=inputSupports.coeff(col,0);
    }
  }
  AbstractPolyhedra<scalar> result(vertices.cols()*m_fdimension);
  result.load(faces,supports);
  result.removeRedundancies();
  return result;
}

/// Retrieves constraints on the controller coefficients based on stability
template<class scalar>
AbstractPolyhedra<scalar> CegarSystem<scalar>::getControllerStabilityBounds(const MatrixS &coefficients)
{
  int dimension=coefficients.cols();
  MatrixS faces(2*dimension,dimension);
  faces.block(0,0,dimension,dimension)=MatrixS::Identity(dimension,dimension);
  faces.block(dimension,0,dimension,dimension)=-MatrixS::Identity(dimension,dimension);
  MatrixS supports(2*dimension,1);
  scalar cap=getSpeed();
  for (int row=0;row<dimension-1;row++) {
    supports.coeffRef(row,0)=cap*binomial(dimension,dimension-row-1);
    cap*=getSpeed();
  }
  supports.coeffRef(dimension-1,0)=func::ms_1;
  supports.block(dimension,0,dimension,1)=supports.block(0,0,dimension,1)+coefficients.transpose();
  supports.block(0,0,dimension,1)-=coefficients.transpose();
  AbstractPolyhedra<scalar> result(dimension);
  result.load(faces,supports);
  return result;
}

/// Creates the observer matrices (based on the FWL truncation)
/// and returns the maximum error caused by the truncation
/// for the eigenvalues of the observed system
template <class scalar>
scalar CegarSystem<scalar>::makeObserver(MatrixS &dynamics,MatrixS &sensitivity,bool hasNoise)
{
  m_observerDynamics.resize(m_dynamics.rows(),m_dynamics.cols());
  for (int row=0;row<m_dynamics.rows();row++) {
    for (int col=0;col<m_dynamics.cols();col++) {
      m_observerDynamics.coeffRef(row,col)=truncateCoefficient(m_dynamics.coeff(row,col));
    }
  }
  m_observerDynamicsError=(m_dynamics-m_observerDynamics).norm();
  m_observerSensitivity.resize(m_sensitivity.rows(),m_sensitivity.cols());
  for (int row=0;row<m_sensitivity.rows();row++) {
    for (int col=0;col<m_sensitivity.cols();col++) {
      m_observerSensitivity.coeffRef(row,col)=truncateCoefficient(m_sensitivity.coeff(row,col));
    }
  }
  m_observerSensitivityError=(m_sensitivity-m_observerSensitivity).norm();
  m_observerOutputSensitivity.resize(m_outputSensitivity.rows(),m_outputSensitivity.cols());
  for (int row=0;row<m_outputSensitivity.rows();row++) {
    for (int col=0;col<m_outputSensitivity.cols();col++) {
      m_observerOutputSensitivity.coeffRef(row,col)=truncateCoefficient(m_outputSensitivity.coeff(row,col));
    }
  }
  m_observerOutputSensitivityError=(m_outputSensitivity-m_observerOutputSensitivity).norm();
  int dimension=2*m_dimension;
  if ((m_observer.rows()!=m_dimension) && (m_observer.cols()!=m_fdimension)) m_observer=MatrixS::Zero(m_dimension,m_fdimension);
  if (&dynamics!=&ms_emptyMatrix) {
    dynamics.conservativeResize(dimension,dimension);
    dynamics.block(0,0,m_dimension,m_dimension)=m_dynamics-m_sensitivity.block(0,0,m_dimension,m_fdimension)*m_feedback;
    dynamics.block(0,m_dimension,m_dimension,m_dimension)=m_observerSensitivity.block(0,0,m_dimension,m_fdimension)*m_feedback;
    dynamics.block(m_dimension,0,m_dimension,m_dimension)=m_dynamics-m_observerDynamics-m_observer*(m_outputSensitivity-m_observerOutputSensitivity);
    dynamics.block(m_dimension,m_dimension,m_dimension,m_dimension)=m_dynamics-m_observer*m_observerOutputSensitivity;
    dynamics.block(0,0,m_dimension,m_dimension)+=(m_sensitivity.block(0,0,m_dimension,m_fdimension)-m_observerSensitivity.block(0,0,m_dimension,m_fdimension))*m_feedback;
  }
  if (&sensitivity!=&ms_emptyMatrix) {
    int inputs=sensitivity.cols()-(hasNoise ? m_observer.cols() : 0);
    sensitivity.conservativeResize(dimension,sensitivity.cols());
    if (inputs>0) sensitivity.block(m_dimension,0,m_dimension,inputs)=MatrixS::Zero(m_dimension,inputs);
    if (hasNoise) {
      sensitivity.block(0,inputs,m_dimension,m_observer.cols())=MatrixS::Zero(m_dimension,m_observer.cols());
      sensitivity.block(m_dimension,inputs,m_dimension,m_observer.cols())=-m_observer;
    }
  }
  return m_observerDynamicsError+m_observerSensitivityError+m_observerOutputSensitivityError;
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

/// Retireves the number of bits needed to represent max
template <class scalar>
int CegarSystem<scalar>::getBits(refScalar max)
{
  long long maxNumber=func::toInt(max);
  long long one=1;
  int bits=1;// Minimum 1
  while(maxNumber>(one<<bits)) bits++;
  bits++;// Sign bit;
  return bits;
}

/// Retireves the number of bits needed to represent the vertices of the polyhedra
template <class scalar>
int CegarSystem<scalar>::getBits(AbstractPolyhedra<scalar> polyhedra)
{
  MatrixS box=polyhedra.boundingHyperBox();
  return getBits(findMaxValue(box));
}

/// Clips the matrix to fit the FWL given by bits
template <class scalar>
void CegarSystem<scalar>::fitToSpec(MatrixS &matrix, int intbits,int fracbits)
{
  refScalar max=pow(refScalar(2),intbits-1);
  refScalar min=-max;
  refScalar one=1<<fracbits;
  for (int row=0;row<matrix.rows();row++) {
    for (int col=0;col<matrix.cols();col++) {
      if (func::toUpper(matrix.coeff(row,col))>max) matrix.coeffRef(row,col)=max;
      if (func::toLower(matrix.coeff(row,col))<min) matrix.coeffRef(row,col)=min;
      long double coeff=func::toInt(func::toCentre(matrix.coeff(row,col)*one));
      matrix.coeffRef(row,col)=coeff;
      matrix.coeffRef(row,col)/=one;
    }
  }
}

/// Normalizes the statespace
template <class scalar>
bool CegarSystem<scalar>::scaleSystem(scalar scale)
{
  if (func::isZero(scale-func::ms_1)) {
    MatrixS safe=m_safeReachTube.getPolyhedra().boundingHyperBox();
    if (safe.rows()*safe.cols()<=0) return false;
    scale/=findMaxValue(safe);
  }
  m_safeReachTube.getPolyhedra().transform(scale);
  m_safeReachTube.clear(false);
  m_initialState.getPolyhedra().transform(scale);
  m_initialState.clear(false);
  m_inputs.transform(scale);
  m_transformedInputs.getPolyhedra().transform(scale);
  m_transformedInputs.clear(false);
  m_reference.transform(scale);
  m_outputs.transform(scale);
  return true;
}

/// Limits the eigenvalues to cap and returns the corresponding polynomial
template <class scalar>
typename CegarSystem<scalar>::MatrixS CegarSystem<scalar>::capEigenValues(scalar cap, bool split, bool keep)
{
  MatrixC eigenValues=MatrixC::Zero(m_dimension,m_dimension);
  for (int i=0;i<m_dimension;i++) {
    scalar norm=func::normsq(m_eigenValues.coeff(i,i));
    char sign=func::hardSign(norm-cap);
    if (sign<=0) eigenValues.coeffRef(i,i)=m_eigenValues.coeff(i,i);
    else {
      eigenValues.coeffRef(i,i)=m_eigenValues.coeff(i,i)*cap/norm;
    }
  }
  if (keep) m_eigenValues=eigenValues;
  if (split) {
    int dimension=m_dimension/2;
    MatrixC first=eigenValues.block(0,0,dimension,dimension);
    MatrixC second=eigenValues.block(dimension,dimension,dimension,dimension);
    MatrixS controller=getDynamicPolynomialCoefficients(first);
    MatrixS observer=getDynamicPolynomialCoefficients(second);
    MatrixS result(1,m_dimension);
    result.block(0,0,1,dimension)=controller.block(0,1,1,dimension);
    result.block(0,dimension,1,dimension)=observer.block(0,1,1,dimension);
    return result;
  }
  MatrixS result=getDynamicPolynomialCoefficients(eigenValues);
  return result.block(0,1,1,m_dimension);
}

/// Explicitly calculates the vertex progression up to step and checks if it remains inside guard
template <class scalar>
bool CegarSystem<scalar>::checkExplicitReachability(powerS step,const MatrixS &transform)
{
  MatrixS truevertices=m_initialState.getPolyhedra().getVertices();
  MatrixS vertices=m_initialState.getPolyhedra(eEigenSpace).getVertices();
  MatrixS reachDynamics=transform*m_dynamics*transform.inverse();
  MatrixS &dynamics=getEigenCloud(20,false);
  AbstractPolyhedra<scalar>& safe=m_safeReachTube.getPolyhedra(eEigenSpace);
  if (ms_trace_dynamics>=eTraceTime) {
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
    int iter=safe.violatingSupport(newVertices);
    if (ms_trace_dynamics>=eTraceTime) {
      newVertices.row(0)=truevertices.row(row)*m_dynamics.transpose();
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
    if (iter>=0) {
      ms_logger.logData(row,"failed explict check ");
      ms_logger.logData(iter," on iteration ",true);
      return false;
    }
  }
  ms_logger.logData("explict check passed");
  return true;
}

/// Retireves the largest number that need to represent the matrix
template <class scalar>
typename CegarSystem<scalar>::refScalar CegarSystem<scalar>::findMaxValue(const MatrixS &matrix,refScalar result,refScalar scale)
{
  refScalar max=0;
  for (int row=0;row<matrix.rows();row++) {
    for (int col=0;col<matrix.cols();col++) {
      if (func::toUpper(matrix.coeff(row,col))>max) max=func::toUpper(matrix.coeff(row,col));
      if (-func::toLower(matrix.coeff(row,col))>max) max=-func::toLower(matrix.coeff(row,col));
    }
  }
  if (!func::isZero(scale)) max/=scale;
  if (max>result) result=max;
  return result;
}

/// Retireves the largest difference between any two non-zero numbers in a matrix
template <class scalar>
scalar CegarSystem<scalar>::findRange(const MatrixS &matrix)
{
  refScalar max=findMaxValue(matrix);
  refScalar min=max;
  for (int row=0;row<matrix.rows();row++) {
    for (int col=0;col<matrix.cols();col++) {
      char sign=func::hardSign(matrix.coeff(row,col));
      if (sign>0) {
        if (func::toLower(matrix.coeff(row,col))<min) min=func::toLower(matrix.coeff(row,col));
      }
      else if (sign<0) {
        if (-func::toUpper(matrix.coeff(row,col))<min) min=-func::toUpper(matrix.coeff(row,col));
      }
    }
  }
  return scalar(max)/min;
}

/// Retireves the best scale factor usable to reach target bits
template <class scalar>
scalar CegarSystem<scalar>::findScale(MatrixS &matrix,int targetBits,bool autoScale)
{
  refScalar max=findMaxValue(matrix);
  scalar min=max/findRange(matrix);
  int rangeT=func::toInt(func::toUpper(min));
  int scaleT=1;
  int bits=getBits(max);
  if (bits>targetBits) {
    int range=1<<(bits-targetBits);
    if (rangeT>range) {
      if (autoScale) matrix/=scaleT;
      return range;
    }
    while(rangeT>1) {
      scaleT<<=1;
      rangeT>>=1;
    }
    if (autoScale) matrix/=scaleT;
  }
  return scaleT;
}


/// Retireves the largest number that need to be represented to execute the model
template <class scalar>
typename CegarSystem<scalar>::refScalar CegarSystem<scalar>::findMaxValue(bool observer,bool states,bool transforms)
{
  refScalar result=func::ms_0;
  if (observer) {
    result=findMaxValue(m_dynamics,result);
    result=findMaxValue(m_sensitivity,result);
    result=findMaxValue(m_outputSensitivity,result);
  }
  if (states) {
    if (m_outputGuard.isEmpty() && m_safeReachTube.getPolyhedra().isEmpty()) {
      MatrixS init=m_initialState.getPolyhedra().boundingHyperBox();
      result=findMaxValue(init,result);
    }
    MatrixS inputs=m_inputs.boundingHyperBox();
    result=findMaxValue(inputs,result);
    MatrixS safe=m_outputGuard.isEmpty() ? m_safeReachTube.getPolyhedra().boundingHyperBox() : m_outputGuard.boundingHyperBox();
    result=findMaxValue(safe,result);
  }
  if (transforms) {
    MatrixS T=getReachableCanonicalTransformMatrix();
    MatrixS invT=makeInverse(T);
    result=findMaxValue(T,result);
    result=findMaxValue(invT,result);
    if (observer) {
      MatrixS invW=getObservableCanonicalTransformMatrix();
      MatrixS W=makeInverse(invW);
      result=findMaxValue(W,result);
      result=findMaxValue(invW,result);
    }
  }
  return result;
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
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Output State time:",true);
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
