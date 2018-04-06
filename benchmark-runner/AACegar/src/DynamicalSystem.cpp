//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#include <fstream>
#include <boost/timer.hpp>

#include "DynamicalSystem.h"

namespace abstract{

template <class scalar>
bool DynamicalSystem<scalar>::ms_fullAnswers=true;

/// Constructs an empty buffer
template <class scalar>
DynamicalSystem<scalar>::DynamicalSystem(const int dimension,const int idimension,const int odimension,bool trace) :
  AbstractMatrix<scalar>(dimension),
  m_idimension(idimension),
  m_odimension(odimension>0 ? odimension : dimension),
  m_fdimension(0),
  m_inputs(idimension),
  m_reach(dimension),
  m_subReach(dimension),
  m_initialState("Initial State",dimension),
  m_transformedInputs("Transformed Inputs",dimension),
  m_guard("Guard",dimension),
  m_safeReachTube("Safe Reach Tube",dimension),
  m_outputGuard(odimension),
  m_templates(dimension,0),
  m_eigenTemplates(dimension,0),
  m_sensitivity(dimension,idimension)
{
  if (trace) {
    ms_logger.logData("Loading System: ",false);
    if (func::getDefaultPrec()>=128) {
      std::stringstream buffer;
      buffer << func::getDefaultPrec();
      ms_logger.logData(interval_def<scalar>::ms_name,false);
      ms_logger.logData(buffer.str());
    }
    else ms_logger.logData(interval_def<scalar>::ms_name);
  }
  m_inputs.setName("Inputs");
  m_inputs.useVertices();
  m_initialState.getPolyhedra().useVertices();
  m_outputs.setName("Outputs");
  m_safeReachTube.setName("Safe Region");
  m_pReachSet=new EigenPolyhedra<scalar>("Reach Set",dimension);
  m_pReachTube=new EigenPolyhedra<scalar>("Reach Tube",dimension);
  m_pAbstractReachTube=new EigenPolyhedra<scalar>("Abstract Reach Tube",dimension);
}

/// deletes the array of CalibrationSamples that represent the file
template <class scalar>
DynamicalSystem<scalar>::~DynamicalSystem(void)
{
  delete m_pReachSet;
  delete m_pReachTube;
  delete m_pAbstractReachTube;
}

/// Changes the default dimension of the system
template <class scalar>
void DynamicalSystem<scalar>::changeDimensions(int dimension,int idimension,int odimension,int fdimension)
{
  if (dimension!=m_dimension) {
    AbstractMatrix<scalar>::changeDimensions(dimension);
    m_reach.changeDimension(dimension);
    m_guard.changeDimension(dimension);
    m_safeReachTube.changeDimension(dimension);
    m_initialState.changeDimension(dimension);
    m_transformedInputs.changeDimension(dimension);
    m_pReachSet->changeDimension(dimension);
    m_pReachTube->changeDimension(dimension);
    m_pAbstractReachTube->changeDimension(dimension);
    m_templates.resize(dimension,0);
    m_eigenTemplates.resize(dimension,0);
  }
  if (m_idimension!=idimension) {
    m_inputs.changeDimension(idimension);
    m_idimension=idimension;
    m_sensitivity.conservativeResize(dimension,idimension);
  }
  if (m_odimension!=odimension) {
    if (odimension!=dimension) {
      m_outputSensitivity.conservativeResize(odimension,dimension);
      m_ioSensitivity.conservativeResize(odimension,idimension);
    }
    m_outputGuard.changeDimension(odimension);
    m_odimension=odimension;
  }
  m_fdimension=fdimension;
}

// Sets the system parameters
template <class scalar>
void DynamicalSystem<scalar>::setParams(ParamMatrix& params)
{
  m_paramValues=params;
  if (m_paramValues.coeff(eNumBits,0)>0) {
    func::setDefaultPrec(m_paramValues.coeff(eNumBits,0));
  }
  if (m_paramValues.coeff(eNumStates,0)>0) changeDimensions(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0),m_paramValues.coeff(eNumOutputs,0),m_paramValues.coeff(eNumFeedbacks,0));
}

/// Loads a full dynamic description
template <class scalar>
int DynamicalSystem<scalar>::load(std::string &data,size_t pos)
{
  m_loadTime=-1;
  boost::timer timer;
  int result=ms_logger.StringToDim(m_paramValues,data,pos);
  if (result<0) return result;
  if (m_paramValues.coeff(eNumBits,0)>0) {
    functions<mpfr::mpreal>::setDefaultPrec(m_paramValues.coeff(eNumBits,0));
  }
  else func::ms_isImprecise=false;
  if (m_paramValues.coeff(eNumStates,0)>0) changeDimensions(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0),m_paramValues.coeff(eNumOutputs,0),m_paramValues.coeff(eNumFeedbacks,0));
  m_feedback.resize(0,m_odimension);
  m_sensitivity.resize(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0));
  m_inputType=(m_paramValues.coeff(eNumVarInputs,0)>0) ? eVariableInputs : ((m_paramValues.coeff(eNumInputs,0)>0) ? eParametricInputs : eNoInputs);
  if (m_paramValues.coeff(eNumInputs,2)+m_paramValues.coeff(eNumVarInputs,1)>0) m_inputType=eVariableOnlyInputs;
  if (ms_trace_dynamics[eTraceTime]) {
    ms_logger.logData(m_paramValues.coeff(eNumStates,0),"Full load",true);
    ms_logger.logData(timer.elapsed()*1000,"Header time:",true);
  }
  result=loadGuard(data,result);
  if (result<0) return result;
  result=loadDynamics(data,result);
  if (result<0) return result;
  result=loadInitialState(data,false,result);
  if (result<0) return result;
  commands_t command;
  ms_logger.getCommand(command,data,result);
  if (command==ePlusCmd) {
    result=loadSensitivities(data,result);
    if (result<0) return result;
    result=loadInputs(data,false,result);
    if (result<0) return result;
  }
  ms_logger.getCommand(command,data,result);
  if (command==eGivenCmd) {
    result=ms_logger.getCommand(command,data,result);
    result=loadOutputGuard(data,result);
    if (result<0) return result;
    result=loadOutputSensitivities(data,result);
    if (result<0) return result;
  }
  else m_outputSensitivity=ms_emptyMatrix;
  ms_logger.getCommand(command,data,result);
  if (command==eEqualsCmd) {
    result=loadSafeReachTube(data,result);
    if (result<0) return result;
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Safe Tube time:",true);
  }
  else {
    m_templates.resize(m_dimension,0);
    m_safeReachTube.clear();
  }
  m_loadTime=timer.elapsed()*1000;
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Load time:",true);
  return result;
}

/// Loads a full dynamic description
template <class scalar>
int DynamicalSystem<scalar>::load(std::string &guard,std::string &dynamics,std::string &init,std::string &sensitivity,std::string &inputs,std::string &templates,bool vertices)
{
  m_loadTime=-1;
  boost::timer timer;
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_dimension,"Load",true);
  int result=loadGuard(guard,0,vertices);
  if (result<0) return result;
  result=loadDynamics(dynamics);
  if (result<0) return result;
  result=loadInitialState(init,vertices);
  if (result<0) return result;
  result=loadSensitivities(sensitivity);
  if (result<0) return result;
  result=loadInputs(inputs,vertices);
  if (result<0) return result;
  result=loadSafeReachTube(templates);
  if (result<0) return result;
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Template time:",true);
  m_loadTime=timer.elapsed()*1000;
  return result;
}

/// Loads a system from known structures
template <class scalar>
bool DynamicalSystem<scalar>::load(const MatrixS &dynamics,const MatrixS &sensitivity,AbstractPolyhedra<scalar> &guard,AbstractPolyhedra<scalar> &init,AbstractPolyhedra<scalar> &inputs,AbstractPolyhedra<scalar>& safeSpace,AbstractPolyhedra<scalar> *pOutputs)
{
  if (JordanMatrix<scalar>::load(dynamics)) setEigenSpace();
  m_sensitivity=sensitivity;
  m_guard.load(guard);
  m_initialState.load(init);
  m_inputs.copy(inputs);
  processInputs();
  m_safeReachTube.load(safeSpace);
  if (pOutputs) m_outputGuard.copy(*pOutputs);
  return true;
}

/// Saves a description of the analysis onto a file
template <class scalar>
bool DynamicalSystem<scalar>::save(displayType_t displayType,space_t space,bool interval,bool append)
{
  std::ofstream file;
  std::string fileName=m_name;
  bool noSolution=ms_fullAnswers && getAbstractDynamics(m_inputType).isEmpty();
  if (noSolution) {
    fileName+=".txt";
  }
  else {
    fileName+="."+interval_def<scalar>::ms_name;
    if (func::getDefaultPrec()>=128) {
      std::stringstream buffer;
      buffer << func::getDefaultPrec();
      fileName+=buffer.str();
    }
  }
  if (append)   file.open(fileName.data(),std::ofstream::app);
  else          file.open(fileName.data());
  if (!file.is_open()) return false;
  std::string data=getDescription(displayType,space,interval);
  if (append) file << "\n|\n\n";
  file.write(data.data(),data.size());
  file.close();
  return true;
}

/// returns a description of the processed system
template <class scalar>
std::string DynamicalSystem<scalar>::getDescription(displayType_t displayType,space_t space,bool interval,bool useBrackets)
{
  bool noSolution=getAbstractDynamics(m_inputType).isEmpty();
  std::string result;
  if (!noSolution) result+="Axelerator "+version+"\n";
  result+=ms_logger.DimToString(&m_paramValues,func::toUpper(this->m_error),func::toUpper(this->m_verror));
  if (func::ms_isImprecise) result+=func::ms_imprecise+"\n";
  if (ms_fullAnswers) {
    result+=m_guard.getPolyhedra(space).getDescription(displayType,interval,useBrackets);
    result+="->\n";
    if (noSolution) {
      result+=ms_logger.MatToString(this->m_dynamics,interval);
    }
    else {
      if (space==eNormalSpace) result+=ms_logger.MatToString(m_pseudoEigenVectors,interval);
      result+=getAbstractDynamics(m_inputType).getDescription(displayType,interval,useBrackets);
      if (space==eNormalSpace) result+=ms_logger.MatToString(m_invPseudoEigenVectors,interval);
    }
    result+=m_initialState.getPolyhedra(space).getDescription(displayType,interval,useBrackets);
    if (space>eNormalSpace) result+=ms_logger.MatToString(m_invPseudoEigenVectors,interval);
    if (m_inputType>eNoInputs) {
      result+="+\n";
      result+=ms_logger.MatToString(this->m_sensitivity,interval);
      result+=m_inputs.getDescription(displayType,interval,useBrackets);
    }
    result+="=\n";
  }
  else m_pAbstractReachTube->getPolyhedra(space).toOuter(true);
  if (noSolution) return result;
  if (m_dynamicParams.cols()>0) {
    MatrixS row=m_dynamicParams.row(eFinalIterations);
    result+="Iterations: "+ms_decoder.MatToString(row);
    row=m_dynamicParams.row(eFinalPrecision);
    result+="Precision: "+ms_decoder.MatToString(row);
    row=m_dynamicParams.row(eFinalLoadTime);
    result+="Load Time: "+ms_decoder.MatToString(row);
    row=m_dynamicParams.row(eFinalReachTime);
    result+="Reach Time: "+ms_decoder.MatToString(row);
  }
  result+=m_pAbstractReachTube->getPolyhedra(space).getDescription(displayType,interval,useBrackets);
  if (m_outputSensitivity.rows()*m_outputSensitivity.cols()>0) {
    result+="|\n";
    getOutputReachTube(m_pAbstractReachTube->getPolyhedra(eNormalSpace),0);
    result+=m_outputs.getDescription(displayType,interval,useBrackets);
  }
  return result;
}

/// Loads a system description from file
template <class scalar>
int DynamicalSystem<scalar>::loadFromFile(std::string &fileName)
{
  std::stringstream buffer;
  std::ifstream file;
  ms_logger.logData("Loading file: ",false);
  ms_logger.logData(fileName);
  file.open(fileName.data());
  if (!file.is_open()) {
    ms_logger.logData("Unable to load file: ",false);
    ms_logger.logData(fileName);
    return -1;
  }
  buffer << file.rdbuf();
  file.close();
  m_source=buffer.str();
  m_name=fileName;
  return load(m_source);
}

template <class scalar>
int DynamicalSystem<scalar>::loadGuard(const std::string &data,size_t pos,bool vertices)
{
  boost::timer timer;
  commands_t command;
  int result=ms_logger.getCommand(command,data,pos);
  if (command==eArrowCmd) {
    m_guard.clear();
    return result;
  }
  result=m_guard.load(data,vertices,pos);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Guard time:",true);
  return result;
}

template <class scalar>
int DynamicalSystem<scalar>::loadOutputGuard(const std::string &data,bool vertices,size_t pos,size_t end)
{
  commands_t command;
  ms_logger.getCommand(command,data,pos);
  if (command==eArrowCmd) {
    m_outputGuard.clear();
    return pos;
  }
  return m_outputGuard.loadData(data,vertices,pos,end);
}

/// Loads a polyhedral description for the initial state
template <class scalar>
int DynamicalSystem<scalar>::loadInitialState(const std::string &data,bool vertices,size_t pos,size_t end)
{
  boost::timer timer;
  int result=m_initialState.load(data,vertices,pos,end);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"State time:",true);
  return result;
}

/// Processes the transformed inputs
template <class scalar>
void DynamicalSystem<scalar>::processInputs(bool useVertices)
{
  if (useVertices) m_inputs.makeVertices();
  m_transformedInputs.load(m_inputs,this->m_sensitivity);
  if (m_inputs.ms_trace_pivots[eTraceTransforms]) {
    m_inputs.logTableau();
    m_transformedInputs.getPolyhedra().logTableau();
    m_transformedInputs.getPolyhedra(eEigenSpace).logTableau();
  }
}

/// Loads a polyhedral description for the inputs
template <class scalar>
int DynamicalSystem<scalar>::loadInputs(const std::string &data,bool vertices,size_t pos,size_t end)
{
  boost::timer timer;
  int result=m_inputs.loadData(data,vertices,pos,end);
  if (result>0) processInputs();
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Inputs time:",true);
  return result;
}

template <class scalar>
int DynamicalSystem<scalar>::loadSafeReachTube(const std::string &data,size_t pos,bool vertices)
{
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  if (ms_logger.hasInequalities(data,pos)) return m_safeReachTube.load(data,vertices,pos);
  m_safeReachTube.clear();
  return loadTemplates(data,pos);
}

/// Sets a number of template directions for polyhedra representation
template <class scalar>
int DynamicalSystem<scalar>::loadTemplates(const std::string &data,size_t pos)
{
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  if (data.compare(pos,7,"[ortho]")==0) {
    m_templates=MatrixS::Zero(m_dimension,2*m_dimension);
    for (int i=0;i<m_dimension;i++) {
      m_templates.coeffRef(i,2*i)=1;
      m_templates.coeffRef(i,2*i+1)=-1;
    }
    m_eigenTemplates=m_pseudoEigenVectors.transpose()*m_templates;
  }
  else if (data.compare(pos,7,"[eigen]")==0) {
    m_eigenTemplates=MatrixS::Zero(m_dimension,2*m_dimension);
    for (int i=0;i<m_dimension;i++) {
      m_eigenTemplates.coeffRef(i,2*i)=1;
      m_eigenTemplates.coeffRef(i,2*i+1)=-1;
    }
    m_templates=m_invPseudoEigenVectors*m_eigenTemplates;
  }
  else if (data.compare(pos,6,"[init]")==0) {
    m_templates=m_initialState.getPolyhedra().getDirections();
    m_eigenTemplates=m_pseudoEigenVectors.transpose()*m_templates;
    return 6;
  }
  else {
    int lines=ms_logger.lines(data,pos);
    MatrixS templates(lines,m_dimension);
    int result=ms_logger.StringToMat(templates,data,pos);
    if (result<0) return result;
    m_templates=templates.transpose();
    m_eigenTemplates=m_pseudoEigenVectors.transpose()*m_templates;
    return result;
  }
  return 7;
}

/// Retrieves the reach set at the given iteration
template <class scalar>
AbstractPolyhedra<scalar>& DynamicalSystem<scalar>::getReachSet(powerS iteration,AbstractPolyhedra<scalar> &init,inputType_t inputType,bool accelerated,bool inEigenSpace,int directions,bool retemplate,bool keep)
{
  if (&init==&m_reach) {
    m_subReach.copy(init);
    return getReachSet(iteration,m_subReach,inputType,accelerated,inEigenSpace,directions,retemplate,keep);
  }
  if (m_hasMultiplicities) this->calculateBoundedEigenError(calculateMaxIterations(iteration));
  space_t space=(inEigenSpace || (accelerated && (iteration>0) && (inputType>=eVariableInputs))) ? eEigenSpace : eNormalSpace;
  AbstractPolyhedra<scalar>& input=m_transformedInputs.getPolyhedra(space);
  int tag=init.getTag();
  m_reach.setTag(tag+iteration);
  std::stringstream buffer;
  if (inEigenSpace) buffer << "Eigen";
  buffer << "Reach Set " << m_reach.getTag();
  if (tag>0) buffer << "(from " << tag << ")";
  m_reach.setName(buffer.str());
  m_pReachSet->setName(buffer.str());
  if (!accelerated && (inputType>eParametricInputs)) {
    m_reach.copy(init);
    if (!m_hasOnes) {
      MatrixS& templates=getTemplates(space,directions);
      MatrixS vectors=(templates.cols()>0) ? templates : init.getDirections();//TODO: makeLogahedral?
      MatrixS faces=vectors.transpose();
      MatrixS supports(vectors.cols(),1);
      MatrixS dynamics=(space==eNormalSpace) ? this->m_dynamics.transpose() : m_pseudoEigenValues.transpose();
      AbstractPolyhedra<scalar>& input=m_transformedInputs.getPolyhedra(space);
      MatrixS inSupports=input.getSupports();
      MatrixS accumInSupports=MatrixS::Zero(supports.rows(),1);
      for (int i=1;i<=iteration;i++) {
        if (!input.maximiseAll(vectors,inSupports)) processError(input.getName() + " maximise");
        accumInSupports+=inSupports;
        vectors=dynamics*vectors;
        if (!init.maximiseAll(vectors,supports)) processError(init.getName() + " maximise");
        supports+=accumInSupports;
      }
      m_reach.load(faces,supports);
    }
    else if (retemplate) {
      MatrixS& templates=getTemplates(space,directions);
      MatrixS vectors=templates;
      MatrixS supports;
      MatrixS inSupports=MatrixS::Zero(vectors.cols(),1);
      MatrixS dynamics=getPseudoDynamics(1,false,space).transpose();
      for (int i=1;i<=iteration;i++) {
        if (!input.maximiseAll(vectors,supports)) processError(input.getName() + " retemplate");
        inSupports+=supports;
        vectors=dynamics*vectors;
      }
      if (!init.maximiseAll(vectors,supports)) processError(init.getName() + " retemplate");
      supports+=inSupports;
      MatrixS faces=templates.transpose();
      m_reach.load(faces,supports);
    }
    else {
      MatrixS matrix=getPseudoDynamics(1,false,space);
      for (int i=1;i<=iteration;i++) {
        m_reach.transform(matrix);
        m_reach.add(input);
      }
//      MatrixS& templates=getTemplates(space,directions);
//      if (retemplate && templates.cols()>0) m_reach.retemplate(templates);
    }
    if (keep) m_pReachSet->load(m_reach,Polyhedra<scalar>::ms_emptyMatrix,Polyhedra<scalar>::ms_emptyMatrix,space);
    if (ms_trace_dynamics[eTraceDynamics]) m_reach.logTableau();
    return m_reach;
  }
  MatrixS matrix=getPseudoDynamics(iteration,false,space);
  AbstractPolyhedra<scalar>& result=init.getTransformedPolyhedra(m_reach,matrix,Polyhedra<scalar>::ms_emptyMatrix);
  if (ms_trace_dynamics[eTraceDynamics]) {
    buffer << " Dynamics";
    ms_logger.logData(matrix,buffer.str());
  }

  if ((iteration>0) && (inputType>eNoInputs)) {
    if (inputType==eParametricInputs) {
      matrix=getPseudoDynamics(iteration,true,space);
      AbstractPolyhedra<scalar> uPrime(input,matrix);
      result.add(uPrime);
      if (result.ms_trace_pivots[eTraceTransforms]) {
        uPrime.setName("+Inputs");
        uPrime.logVertices(true);
        result.logVertices(true);
        uPrime.logTableau();
        result.logTableau();
      }
    }
    else {
      AbstractPolyhedra<scalar>& input=m_transformedInputs.getPolyhedra(eSingularSpace,m_roundings);
      matrix=getPseudoDynamics(iteration,true,eSingularSpace);
      AbstractPolyhedra<scalar> uPrime(input,matrix);
      result.addRounded(uPrime,m_roundings);
      if (!inEigenSpace) result.transform(m_pseudoEigenVectors,m_invPseudoEigenVectors);
    }
  }
  MatrixS& templates=getTemplates(space);
  if (retemplate && templates.cols()>0) result.retemplate(templates);
  if (keep) m_pReachSet->load(result,Polyhedra<scalar>::ms_emptyMatrix,Polyhedra<scalar>::ms_emptyMatrix,space);
  if (result.ms_trace_pivots[eTraceTableau]) result.logTableau();
  return result;
}

/// Creates a combinatorial matrix A-B
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS DynamicalSystem<scalar>::combineAminB(const MatrixS& A,const MatrixS& B,bool isVector)
{
  if (isVector) {
    if ((A.rows()!=B.rows()) || (A.rows()!=m_dimension)) return A;
    int col=0;
    MatrixS result(m_dimension,A.cols()*B.cols());
    for (int col1=0;col1<A.cols();col1++) {
      for (int col2=0;col2<B.cols();col2++) {
        result.col(col++)=A.col(col1)-B.col(col2);
      }
    }
    return result;
  }
  if ((A.cols()!=B.cols()) || (A.cols()!=m_dimension)) return A;
  int row=0;
  MatrixS result(A.rows()*B.rows(),m_dimension);
  for (int row1=0;row1<A.rows();row1++) {
    for (int row2=0;row2<B.rows();row2++) {
      result.row(row++)=A.row(row1)-B.row(row2);
    }
  }
  return result;
}

/// Creates a combinatorial matrix with rows/cols A_i B_j ordered by templates
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS DynamicalSystem<scalar>::combineAB(const MatrixS& A,const MatrixS& B,const int templateSz,const int AvertexSz,const int BvertexSz,const bool isVector)
{
  if (isVector) {
    MatrixS result(A.rows()+B.rows(),A.cols()*BvertexSz);
    for (int i=0;i<templateSz;i++) {
      for (int j=0;j<AvertexSz;j++) {
        int col=i*AvertexSz+j;
        for (int k=0;k<BvertexSz;k++) {
          result.block(0,col*BvertexSz+k,A.rows(),1)=A.col(col);
        }
        result.block(A.rows(),col*BvertexSz,B.rows(),BvertexSz)=B.block(0,i*BvertexSz,B.rows(),BvertexSz);
      }
    }
    return result;
  }
  MatrixS result(A.rows()*BvertexSz,A.cols()+B.cols());
  for (int i=0;i<templateSz;i++) {
    for (int j=0;j<AvertexSz;j++) {
      int row=i*AvertexSz+j;
      for (int k=0;k<BvertexSz;k++) {
        result.block(row*BvertexSz+k,0,1,A.cols())=A.row(row);
      }
      result.block(row*BvertexSz,A.cols(),BvertexSz,B.cols())=B.block(i*BvertexSz,0,BvertexSz,B.rows());
    }
  }
  return result;
}

/// Creates a combinatorial matrix with rows A_i \cdot B_i
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS DynamicalSystem<scalar>::combineAB(const MatrixS& A,const MatrixS& B)
{
  if (A.cols()!=B.cols()) return MatrixS(0,0);
  MatrixS result(A.rows()*B.rows(),A.cols());
  for (int i=0;i<A.rows();i++) {
    for (int j=0;j<B.rows();j++) {
      int row=i*B.rows()+j;
      for (int col=0;col<A.cols();col++) {
        result.coeffRef(row,col)=A.coeff(i,col)*B.coeff(j,col);
      }
    }
  }
  return result;
}

/// retrieve the kronecker product of A and B
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS DynamicalSystem<scalar>::kronecker(const MatrixS& A,const MatrixS& B,const bool transA,const bool transB)
{
  int arows=transA ? A.cols() : A.rows();
  int acols=transA ? A.rows() : A.cols();
  int brows=transB ? B.cols() : B.rows();
  int bcols=transB ? B.rows() : B.cols();

  MatrixS result(arows*brows,acols*bcols);
  for (int i=0;i<arows;i++) {
    for (int j=0;j<brows;j++) {
      int row=i*brows+j;
      for (int k=0;k<acols;k++) {
        for (int l=0;l<bcols;l++) {
          int col=k*bcols+l;
          if (transA)
            result.coeffRef(row,col)=transB ? A.coeff(k,i)*B.coeff(l,j) : A.coeff(k,i)*B.coeff(j,l);
          else
            result.coeffRef(row,col)=transB ? A.coeff(i,k)*B.coeff(l,j) : A.coeff(i,k)*B.coeff(j,l);
        }
      }
    }
  }
  return result;
}

/// Creates a template matrix for the given logahedral dimension
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS& DynamicalSystem<scalar>::makeLogahedralTemplates(int precision,space_t space,int dimension,MatrixS &logTemplates)
{
  precision++;
  if (precision<=1) logTemplates.resize(dimension,2*dimension+2*precision*(dimension-1)*dimension);
  else              logTemplates.resize(dimension,2*dimension+(4*precision-2)*(dimension-1)*dimension);
  logTemplates.block(0,0,dimension,dimension)=MatrixS::Identity(dimension,dimension);
  logTemplates.block(0,dimension,dimension,dimension)=-MatrixS::Identity(dimension,dimension);
  if (precision<=0) return logTemplates;
  int pos=2*dimension;
  for (int row=0;row<dimension-1;row++) {
    int size=dimension-row-1;
    logTemplates.block(row,pos,1,2*size)=MatrixS::Ones(1,2*size);
    logTemplates.block(row+1,pos,size,size)=MatrixS::Identity(size,size);
    pos+=size;
    logTemplates.block(row+1,pos,size,size)=-MatrixS::Identity(size,size);
    pos+=size;
    logTemplates.block(row,pos,1,2*size)=-MatrixS::Ones(1,2*size);
    logTemplates.block(row+1,pos,size,size)=MatrixS::Identity(size,size);
    pos+=size;
    logTemplates.block(row+1,pos,size,size)=-MatrixS::Identity(size,size);
    pos+=size;
    if (pos<logTemplates.cols()) logTemplates.block(row,pos,1,logTemplates.cols()-pos)=MatrixS::Zero(1,logTemplates.cols()-pos);
  }
  for (int i=2;i<=precision;i++) {
    for (int row=0;row<dimension-1;row++) {
      int size=dimension-row-1;
      logTemplates.block(row,pos,1,2*size)=i*MatrixS::Ones(1,2*size);
      logTemplates.block(row+1,pos,size,size)=MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row+1,pos,size,size)=-MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row,pos,1,2*size)=-i*MatrixS::Ones(1,2*size);
      logTemplates.block(row+1,pos,size,size)=MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row+1,pos,size,size)=-MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row,pos,1,2*size)=MatrixS::Ones(1,2*size);
      logTemplates.block(row+1,pos,size,size)=i*MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row+1,pos,size,size)=-i*MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row,pos,1,2*size)=-MatrixS::Ones(1,2*size);
      logTemplates.block(row+1,pos,size,size)=i*MatrixS::Identity(size,size);
      pos+=size;
      logTemplates.block(row+1,pos,size,size)=-i*MatrixS::Identity(size,size);
      pos+=size;
      if (pos<logTemplates.cols()) logTemplates.block(row,pos,1,logTemplates.cols()-pos)=MatrixS::Zero(1,logTemplates.cols()-pos);
    }
  }
  if (ms_trace_dynamics[eTraceTemplates]) ms_logger.logData(logTemplates,"Template base");
  if (space==eNormalSpace) {
    MatrixS transformedTemplates=m_pseudoEigenVectors.transpose()*logTemplates;
    if (ms_trace_dynamics[eTraceTemplates]) {
      ms_logger.logData(m_pseudoEigenVectors,"Template Transform");
      ms_logger.logData(transformedTemplates,"Transformed Templates");
    }
    logTemplates=transformedTemplates;
  }
  return logTemplates;
}

/// Creates a template matrix for the given logahedral dimension
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS& DynamicalSystem<scalar>::makeSphericalTemplates(int precision,int dimension,MatrixS &logTemplates,bool normalized)
{
  if (precision<2) precision=2;
  if ((m_dimension==2) && (precision<3)) precision=3;
  if (precision>30) precision=30;
  precision=(2<<precision);
  if (dimension==2) {
    logTemplates.resize(dimension,precision);
    for (int i=0;i<precision;i++) {
      logTemplates.coeffRef(0,i)=func::cosine(i*func::ms_2_pi/precision);
      logTemplates.coeffRef(1,i)=func::sine(i*func::ms_2_pi/precision);
    }
    if (normalized) logTemplates/=func::toLower(func::cosine(func::ms_pi/precision));
  }
  else if ((dimension>2) && (dimension<6)) {
    logTemplates.resize(dimension,130);
    std::stringstream fileName;
    std::stringstream buffer;
    std::ifstream file;
    fileName << "SphericalPoints" << dimension << "D.h";
    file.open(fileName.str().data());
    if (!file.is_open()) return logTemplates;
    buffer << file.rdbuf();
    file.close();
    std::string str=buffer.str();
    MatrixS load;
    ms_logger.StringToMat(load,str);
    logTemplates=load.transpose();
    if (normalized) logTemplates/=func::cosine(func::ms_pi/9);//The files have a minimum angle of 20 between points
  }
  return logTemplates;
}

/// Retrieves the number of radii dimensions in the eigenspace (only one per conjugate pair)
template <class scalar>
int DynamicalSystem<scalar>::getNormedDimension()
{
  int dimension=m_dimension;
  for (int col=0;col<m_dimension;col++)
  {
    if (m_conjugatePair[col]>col) dimension--;
  }
  m_normedJordanIndex.resize(2*dimension);
  m_normedOnes.resize(2*dimension);
  int pos=0;
  for (int col=0;col<m_dimension;col++)
  {
    if (m_conjugatePair[col]>col) continue;
    m_normedJordanIndex[pos]=m_jordanIndex[col];
    m_normedJordanIndex[pos+dimension]=m_jordanIndex[col];
    m_normedOnes[pos]=m_isOne[col];
    m_normedOnes[pos+dimension]=m_isOne[col];
    pos++;
  }
  return dimension;
}

/// Retrieves an abstraction that has circular faces in the rotating axis and jordan blocks
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS& DynamicalSystem<scalar>::getNormedDirections(MatrixS &result,const MatrixS &vectors,bool transposed)
{
  if (transposed) {
    result.resize(vectors.rows(),getNormedDimension());
    int pos=0;
    for (int col=0;col<vectors.cols();col++)
    {
      if (m_conjugatePair[col]<0) {
        result.col(pos)=vectors.col(col);
      }
      else {
        for (int row=0;row<vectors.rows();row++) {
          scalar value=func::squared(vectors.coeff(row,col))+func::squared(vectors.coeff(row,col+1));
          result.coeffRef(row,pos)=sqrt(value);
        }
        col++;
      }
      pos++;
    }
    return result;
  }
  result.resize(getNormedDimension(),vectors.cols());
  int pos=0;
  for (int row=0;row<vectors.rows();row++)
  {
    if (m_conjugatePair[row]<0) {
      result.row(pos)=vectors.row(row);
    }
    else {
      for (int col=0;col<vectors.cols();col++) {
        scalar value=func::squared(vectors.coeff(row,col))+func::squared(vectors.coeff(row+1,col));
        result.coeffRef(pos,col)=sqrt(value);
      }
      row++;
    }
    pos++;
  }
  return result;
}

/// Creates a template matrix for the reach set directions at the given iteration
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS& DynamicalSystem<scalar>::makeInverseTemplates(int iteration,space_t space)
{
    MatrixS matrix=this->getPoweredPseudoEigenValues(iteration);
    MatrixS inverse=makeInverse(matrix);
    if (space==eNormalSpace) {
      inverse=m_invPseudoEigenVectors*(inverse*m_pseudoEigenVectors);
    }
    m_logTemplates=inverse.transpose()*m_initialState.getPolyhedra(space).getDirections();
    return m_logTemplates;
}

/// Retrieves the round abstract vector set for a given template set
template <class scalar>
int DynamicalSystem<scalar>::getRoundedAbstractVertices(MatrixS &vectors,const MatrixS& templates,bool fromSource)
{
  AbstractPolyhedra<scalar> &inputs=m_transformedInputs.getPolyhedra(eEigenSpace);
  AbstractPolyhedra<scalar> inputCopy(inputs);
  AbstractPolyhedra<scalar> roundInputs;
  if (fromSource) {
    MatrixS vertices=m_inputs.getVertices()*m_sensitivity.transpose();
    vertices*=m_invPseudoEigenVectors.transpose();
    inputCopy.setVertices(vertices,getInputVertices(eEigenSpace,fromSource));
  }
  inputCopy.getRounded(m_roundings,roundInputs,fromSource);
  roundInputs.transform(this->m_invIminF,this->m_IminF);
  MatrixS varTemplates=roundInputs.getRoundedDirections(templates,m_roundings);
  std::vector<int> jordanIndex(m_jordanIndex.begin()+m_dimension,m_jordanIndex.end());
  std::vector<int> conjugatePair(m_conjugatePair.begin()+m_dimension,m_conjugatePair.end());
  vectors=roundInputs.getAbstractVertices(varTemplates,conjugatePair,jordanIndex);
  if (ms_trace_dynamics[eTraceAbstraction]) {
    ms_logger.logData(roundInputs.getVertices(),"var inputs");
  }
  return roundInputs.getVertices().rows();
}

/// Retrieves the abstract vector set for a given template set
template <class scalar>
typename JordanMatrix<scalar>::MatrixS DynamicalSystem<scalar>::getCombinedVectors(MatrixS &vectors,const MatrixS& templates,bool fromSource,const MatrixS &inputVertices)
{
  AbstractPolyhedra<scalar> &inputs=m_transformedInputs.getPolyhedra(eEigenSpace);
  int nV=m_numVertices;
  if (m_inputType==eVariableInputs) {
    boost::timer timer;
    MatrixS inputVectors;
    int numInputVertices=getRoundedAbstractVertices(inputVectors,templates,fromSource);
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Input Rounding Time: ",true);
    m_numVertices*=numInputVertices;
    return combineAB(vectors,inputVectors,templates.cols(),nV,numInputVertices,true);
  }
  else if (m_hasOnes) {
    MatrixS inputVectors=inputs.getAbstractVertices(templates,m_conjugatePair,m_jordanIndex,inputVertices);
    int numInputVertices=inputVertices.rows();
    m_numVertices*=numInputVertices;
    return combineAB(vectors,inputVectors,templates.cols(),nV,numInputVertices,true);
  }
  return vectors;
}

/// Retrieves the parametric input vertices for the current problem configuration
template <class scalar>
const typename JordanMatrix<scalar>::MatrixS DynamicalSystem<scalar>::getInputVertices(space_t space,bool fromSource)
{
  if (fromSource) {
    MatrixS inputVertices=(m_inputType==eParametricInputs) ? m_inputs.getVertices() : m_inputs.getCentre();
    if (inputVertices.rows()>0) {
      inputVertices*=m_sensitivity.transpose();
      if (space>eNormalSpace) inputVertices*=m_invPseudoEigenVectors.transpose();
      if (ms_trace_dynamics[eTraceAbstraction]) ms_logger.logData(inputVertices,"parametric verices");
      return inputVertices;
    }
    else if (ms_trace_dynamics[eTraceAbstraction]) ms_logger.logData("ünable to load inputs from source");
  }
  AbstractPolyhedra<scalar> &inputsSource=m_transformedInputs.getPolyhedra(space);
  const MatrixS& inputVertices=(m_inputType==eParametricInputs) ? inputsSource.getVertices() : inputsSource.getCentre();
  if (inputVertices.rows()<=0) processError(inputsSource.getName());
  return inputVertices;
}

/// Retrieves the parametric accelerated input vertices for the current problem configuration
template <class scalar>
typename JordanMatrix<scalar>::MatrixS& DynamicalSystem<scalar>::getAccelVertices(bool load)
{
  if (load) m_accelVertices=getInputVertices(eEigenSpace,true)*this->m_pseudoInvIminJ.transpose();
  if (m_hasOnes && (m_inputType>=eVariableInputs)) {
    for (int i=0;i<m_accelVertices.cols();i++) {
      if (m_isOne[i]) m_accelVertices.coeffRef(i,0)=0;
    }
  }
}

/// Retrieves the support set for the inputs
template <class scalar>
typename JordanMatrix<scalar>::MatrixS& DynamicalSystem<scalar>::getAccelInSupports(const MatrixS& templates)
{
  //getAccelVertices() must be called first (not called here for optimization)
  AbstractPolyhedra<scalar> &inputsSource=m_transformedInputs.getPolyhedra(eEigenSpace);
  if (m_hasOnes && (m_inputType>=eVariableInputs)) {
    const MatrixS& inputVertices=getInputVertices(eEigenSpace,true);
    for (int i=0;i<m_accelVertices.cols();i++) {
      if (m_isOne[i]) {
        m_accelVertices.coeffRef(0,i)=inputVertices.coeff(0,i);
      }
    }
    m_abstractInputVertices=MatrixS(2*m_dimension,templates.cols());
    m_abstractInputVertices.topRows(m_dimension)=MatrixS::Zero(m_dimension,templates.cols());
    m_abstractInputVertices.bottomRows(m_dimension)=inputsSource.getAbstractVertices(templates,m_conjugatePair,m_jordanIndex,m_accelVertices);
    inputType_t inputType=m_inputType;
    AbstractPolyhedra<scalar>& inputDynamics=getAbstractDynamics(eParametricInputs);
    m_inputType=inputType;
    MatrixS supports;
    inputDynamics.maximiseAll(m_abstractInputVertices,supports);
    m_accelInSupports=supports.transpose();
  }
  else m_accelInSupports=m_accelVertices*templates;
  if (ms_trace_dynamics[eTraceAbstraction]) ms_logger.logData(m_accelInSupports,"Input Supports",true);
  return m_accelInSupports;
}

/// Retrieves the support set for the inputs
template <class scalar>
typename JordanMatrix<scalar>::MatrixS& DynamicalSystem<scalar>::getAccelInSupports(powerS iteration, int precision,const MatrixS& templates)
{
  if (m_hasOnes && (m_inputType>=eVariableInputs)) getAbstractDynamics(iteration,precision,eParametricInputs);
  return getAccelInSupports(templates);
}

/// Retrieves the support set for the inputs
template <class scalar>
void DynamicalSystem<scalar>::mergeAccelInSupports(MatrixS &supports,int numTemplates)
{
  if (!m_hasOnes || (m_inputType>=eVariableInputs))  {
    for (int row=0;row<numTemplates;row++) {
      int pos=row*m_numVertices;
      for (int point=0;point<m_numVertices;point++) {
        supports.coeffRef(pos+point,0)+=m_accelInSupports.coeff(point%m_accelInSupports.rows(),row);
      }
    }
  }
}

/// Retrieves the abstract vector set for a given template set
template <class scalar>
typename JordanMatrix<scalar>::MatrixS& DynamicalSystem<scalar>::getAbstractVertices(const MatrixS& templates,MatrixS &vectors,int &numVertices,bool force)
{
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);
  const MatrixS& vertices=init.getVertices(force);
  if (vertices.rows()<=0) processError(init.getName() + " vertices");
  switch (m_inputType) {
    case eNoInputs:
      vectors=init.getAbstractVertices(templates,m_conjugatePair,m_jordanIndex);
      numVertices=vertices.rows();
      if (this->ms_trace_dynamics[eTraceAbstractVertices]) {
        ms_logger.logData(templates,"Templates",true);
        ms_logger.logData(vertices,"Init Vertices");
        ms_logger.logData(vectors,"FullVectors",true);
      }
      break;
  default: {
    getAccelVertices(force);
    MatrixS combinedVertices=m_hasOnes ? vertices : combineAminB(vertices,m_accelVertices,false);
    if (this->ms_trace_dynamics[eTraceAbstraction]) {
      ms_logger.logData(templates,"Templates",true);
      ms_logger.logData(vertices,"Init Vertices");
      ms_logger.logData(getInputVertices(eEigenSpace,true),"Input Vertices",true);
      ms_logger.logData(m_accelVertices,"Accel Vertices");
      ms_logger.logData(combinedVertices,"Vertices");
    }
    MatrixS initVectors=init.getAbstractVertices(templates,m_conjugatePair,m_jordanIndex,combinedVertices);
    numVertices=combinedVertices.rows();
    if (this->ms_trace_dynamics[eTraceAbstraction]) {
      ms_logger.logData(initVectors,"PreVectors",true);
    }
    vectors=getCombinedVectors(initVectors,templates,true,m_accelVertices);
    if (this->ms_trace_dynamics[eTraceAbstraction]) {
      ms_logger.logData(vectors,"FullVectors",true);
    }
  }
  }
  return vectors;
}

template <class scalar>
void DynamicalSystem<scalar>::traceSupports(const MatrixS &templates,MatrixS &supports,AbstractPolyhedra<scalar>& dynamics,const MatrixS &vectors)
{
  if (m_inputType==eNoInputs) {
    ms_logger.logData(vectors,supports,"Combined No Inputs:",true);
    return;
  }
  supports.conservativeResize(supports.rows(),(m_inputType==eParametricInputs) ? 4 : 3);
  supports.col(1)=supports.col(0);
  MatrixS vertexSupports=dynamics.vertexMaximize(vectors);
  if (vertexSupports.rows()==supports.rows()) {
    supports.col(2)=vertexSupports;
  }
  else {
    supports.col(2)=MatrixS::Zero(supports.rows(),1);
    ms_logger.logData("Failed to find Vertex Supports");
  }
  if (m_inputType==eParametricInputs) {
    for (int row=0;row<templates.cols();row++) {
      int pos=row*m_numVertices;
      supports.coeffRef(pos,3)+=m_accelInSupports.coeff(0,row);
      for (int point=1;point<m_numVertices;point++) {
        supports.coeffRef(pos+point,3)+=m_accelInSupports.coeff(point%m_accelInSupports.rows(),row);
      }
    }
  }
}

template <class scalar>
void DynamicalSystem<scalar>::mergeAbstractSupports(const MatrixS &templates,MatrixS &supports)
{
  if (m_inputType==eNoInputs) {
    for (int row=0;row<templates.cols();row++) {
      scalar value=supports.coeff(row*m_numVertices,0);
      for (int vRow=1;vRow<m_numVertices;vRow++) {
        if (value<supports.coeff(row*m_numVertices+vRow,0)) value=supports.coeff(row*m_numVertices+vRow,0);
      }
      supports.coeffRef(row,0)=value;
    }
  }
  else {
    for (int row=0;row<templates.cols();row++) {
      int pos=row*m_numVertices;
      for (int point=1;point<m_numVertices;point++) {
        if (func::toUpper(supports.coeff(pos+point,0))>func::toUpper(supports.coeff(pos,0))) {
          supports.coeffRef(pos,0)=supports.coeff(pos+point,0);
        }
      }
      supports.coeffRef(row,0)=supports.coeff(row*m_numVertices,0);
    }
  }
  supports.conservativeResize(templates.cols(),1);
}

/// Retrieves an abstractreachtube projected across a guard
template <class scalar>
void DynamicalSystem<scalar>::getGuardedReachTube(AbstractPolyhedra<scalar>& reachTube,space_t space)
{
  reachTube.intersect(m_guard.getPolyhedra(space));
  Polyhedra<scalar> next;
  reachTube.getTransformedPolyhedra(next,this->getBaseDynamics(space));
  next.add(m_transformedInputs.getPolyhedra(space));
  reachTube.merge(next);
}

/// Retrieves the reach tube for the precalculated dynamics
template <class scalar>
AbstractPolyhedra<scalar>& DynamicalSystem<scalar>::getAbstractReachTube(int directions,inputType_t inputType,space_t space,bool guarded)
{
  boost::timer timer;
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(inputType);
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);

  MatrixS templates=(m_safeReachTube.isEmpty() || (directions>0)) ? getTemplates(eEigenSpace,directions) : m_safeReachTube.getPolyhedra(eEigenSpace).getDirections();
  MatrixS supports;

  if (m_dimension+m_idimension+directions>10) {
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
    if (inputType>eNoInputs) getAccelInSupports(templates);
    if (ms_trace_dynamics[eTraceAbstractVertices]) {
      traceSupports(templates,supports,dynamics,vectors);
    }
    if (inputType>eNoInputs) {
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
  if (this->ms_trace_dynamics[eTraceAbstraction]) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
  getOutputReachTube(result, directions);
  return result;
}

/// Retrieves the reach tube at the given iteration
template <class scalar>
AbstractPolyhedra<scalar>& DynamicalSystem<scalar>::getAbstractReachTube(powerS iteration,int precision,int directions,inputType_t inputType,space_t space,bool guarded)
{
  m_reachTime=-1;
  boost::timer timer;
  if (m_idimension==0) inputType=eNoInputs;
  setInputType(inputType);
  if (iteration<0) iteration=-iteration;
  if (iteration==0) iteration=calculateIterations(m_initialState.getPolyhedra(eEigenSpace),inputType);
  if (m_hasMultiplicities) this->calculateBoundedEigenError(calculateMaxIterations());
  if (guarded) iteration--;
  if (iteration<=0) {
    m_pAbstractReachTube->load(m_initialState.getPolyhedra(),Polyhedra<scalar>::ms_emptyMatrix);
    AbstractPolyhedra<scalar>& result=m_pAbstractReachTube->getPolyhedra(space);
    if (guarded) getGuardedReachTube(result,space);
    m_reachTime=timer.elapsed()*1000;
    result.setCalculationTime(m_reachTime);
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
    if (m_outputSensitivity.cols()==0) m_outputs.copy(result);
    else result.getTransformedPolyhedra(m_outputs,m_outputSensitivity);
    return result;
  }
  if (m_hasNegatives && (iteration&1)) iteration++;
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(iteration,precision,inputType);
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);

  MatrixS& templates=getTemplates(eEigenSpace,directions);
  MatrixS supports;

  if (m_dimension+m_idimension+directions>10) {
    init.getVertices(true);
    if (m_idimension>0) getAccelVertices(true);
    supports.resize(templates.cols(),1);
    for (int i=0;i<templates.cols();i++) {
      if (ms_trace_dynamics[eTraceTime]) {
        std::stringstream buffer;
        buffer << i << " of " << templates.cols();
        ms_logger.logData(buffer.str());
      }
      MatrixS localSupport=getAbstractReachTubeSupports(iteration,precision,dynamics,templates.col(i));
      supports.coeffRef(i,0)=localSupport.coeff(0,0);
    }
  }
  else {
    MatrixS &vectors=getAbstractVertices(templates);
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Abstract Vertices: ",true);
    if (!dynamics.maximiseAll(vectors,supports)) processError(dynamics.getName());

    if (inputType>eNoInputs) getAccelInSupports(iteration,precision,templates);
    if (this->ms_trace_dynamics[eTraceAbstractVertices]) {
      traceSupports(templates,supports,dynamics,vectors);
    }
    if (inputType>eNoInputs) {
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
  if (this->ms_trace_dynamics[eTraceAbstraction]) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
  getOutputReachTube(result, directions);
  return result;
}

/// Retrieves the support functions for the reach tube in the given directions
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS DynamicalSystem<scalar>::getAbstractReachTubeSupports(AbstractPolyhedra<scalar>& dynamics,const MatrixS &templates)
{
  boost::timer timer;
  MatrixS supports;
  if (m_inputType>eNoInputs) getAccelInSupports(templates);
  MatrixS &vectors=getAbstractVertices(templates,false);
  if (m_inputType==eVariableOnlyInputs) {
    AbstractPolyhedra<scalar> state_dynamics(0);
    AbstractPolyhedra<scalar> in_dynamics(0);
    dynamics.slice(state_dynamics,m_dimension,0,firstVarBlock());
    dynamics.slice(in_dynamics,-m_dimension,m_dimension,-firstVarBlock(),firstVarBlock());
    MatrixS state_vectors=vectors.topRows(m_dimension);
    MatrixS inSupports(state_vectors.cols(),1);
  /*    MatrixS in_vectors=vectors.bottomRows(dynamics.getDimension()-m_dimension);
      if (!in_dynamics.maximiseAll(in_vectors,inSupports,dynamics.eOverAprox,ms_incremental ? m_incOrderType : LexNone)) processError(dynamics.getName());
  */
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
    if (!state_dynamics.maximiseAll(state_vectors,supports,dynamics.eOverAprox,ms_incremental ? LexCos : LexNone )) processError(dynamics.getName());
    supports+=inSupports;
  }
  else if (!dynamics.maximiseAll(vectors,supports,dynamics.eOverAprox,ms_incremental ? LexCos : LexNone)) processError(dynamics.getName());
  if (ms_trace_dynamics[eTraceAbstractVertices]) traceSupports(templates,supports,dynamics,vectors);
  if (m_inputType>eNoInputs) {
    mergeAccelInSupports(supports,templates.cols());
    if (ms_trace_dynamics[eTraceAbstractVertices]) ms_logger.logData(vectors,supports,"Partial Combined",true);
  }
  mergeAbstractSupports(templates,supports);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Abstract Tube Support: ",true);
  return supports;
}

/// Retrieves the support functions for the reach tube in the given directions
template <class scalar>
typename DynamicalSystem<scalar>::MatrixS DynamicalSystem<scalar>::getAbstractReachTubeSupports(powerS iteration,int precision,AbstractPolyhedra<scalar>& dynamics,const MatrixS &templates)
{
  if (m_hasOnes && (m_inputType>=eVariableInputs)) getAbstractDynamics(iteration,precision,eParametricInputs);
  return getAbstractReachTubeSupports(dynamics,templates);
}

/// Retrieves the output reach tube given a state-space reach tube
template <class scalar>
AbstractPolyhedra<scalar>& DynamicalSystem<scalar>::getOutputReachTube(AbstractPolyhedra<scalar>& reachTube, int precision)
{
  if (m_outputSensitivity.cols()==0) m_outputs.copy(reachTube);
  else if (m_outputSensitivity.rows()<m_dimension) {
    if (!m_outputGuard.isEmpty()) {
      MatrixS outFaces= m_outputGuard.getFaceDirections();
      MatrixS outSupports=reachTube.getSupports();
      if (outFaces.rows()==outSupports.rows()) {
        m_outputs.load(outFaces,outSupports);
        return m_outputs;
      }
    }
    MatrixS outTemplates;
    int outDimension=m_outputSensitivity.rows();
    if (outDimension==1) {
      outTemplates=MatrixS::Ones(1,2);
      outTemplates.coeffRef(0,1)=-ms_one;
      MatrixS directions(m_dimension,2);
      directions.col(0)=m_outputSensitivity.transpose();
      directions.col(1)=-directions.col(0);
      MatrixS supports;
      reachTube.maximiseAll(directions,supports);
      m_outputs.load(outTemplates.transpose(),supports);
      return m_outputs;
    }
    else {
      reachTube.getTransformedPolyhedra(m_outputs,m_outputSensitivity);
      return m_outputs;

//      makeLogahedralTemplates(precision,eEigenSpace,outDimension,outTemplates);
    }
    m_outputs.copy(reachTube);
    if (!m_outputs.vertexTransform(m_outputSensitivity,outTemplates))
    {
      ms_logger.logData("Error Transforming Reach Tube");
    }
  }
  else reachTube.getTransformedPolyhedra(m_outputs,m_outputSensitivity);
  return m_outputs;
}


/// Retrieves the reach tube at the given iteration
template <class scalar>
AbstractPolyhedra<scalar>& DynamicalSystem<scalar>::getIterativeReachTube(powerS iteration,inputType_t inputType,space_t space,int directions)
{
  m_reachTime=-1;
  boost::timer timer;
  if (m_hasMultiplicities) this->calculateBoundedEigenError(calculateMaxIterations(iteration));
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(space);
  AbstractPolyhedra<scalar>& result=init.getTransformedPolyhedra(Polyhedra<scalar>::ms_emptyMatrix);
  result.setName("Reach Tube");
  MatrixS& templates=getTemplates(space,directions);
  MatrixS vectors=templates.cols()>0 ? templates : init.getDirections();
  MatrixS faces=vectors.transpose();
  MatrixS supports(vectors.cols(),1);
  MatrixS accumSupports;
  init.maximiseAll(vectors,accumSupports);
  MatrixS dynamics=(space==eNormalSpace) ? this->m_dynamics.transpose() : m_pseudoEigenValues.transpose();
  switch (inputType) {
  case eNoInputs: {
    for (int i=1;i<=iteration;i++) {
      vectors=dynamics*vectors;
      if (!init.maximiseAll(vectors,supports)) processError(init.getName() + " iterative maximise");
      if (ms_trace_dynamics[eTraceAll]) {
        ms_logger.logData(i,"Iteration",true);
        ms_logger.logData(supports);
      }
      for (int j=0;j<supports.rows();j++) {
        if (func::toUpper(supports.coeff(j,0))>func::toUpper(accumSupports.coeff(j,0))) {
          accumSupports.coeffRef(j,0)=supports.coeff(j,0);
        }
      }
    }
    break;
  }
  case eVariableInputs:
  case eVariableOnlyInputs: {
    AbstractPolyhedra<scalar> &input=m_transformedInputs.getPolyhedra(space);
    MatrixS inSupports=input.getSupports();
    MatrixS accumInSupports=MatrixS::Zero(supports.rows(),1);
    for (int i=1;i<=iteration;i++) {
      if (!input.maximiseAll(vectors,inSupports)) processError(input.getName() + " variable maximise");
      accumInSupports+=inSupports;
      vectors=dynamics*vectors;
      if (!init.maximiseAll(vectors,supports)) processError(init.getName() + " variable maximise");
      supports+=accumInSupports;
      for (int j=0;j<supports.rows();j++) {
        if (func::toUpper(supports.coeff(j,0))>func::toUpper(accumSupports.coeff(j,0))) {
          accumSupports.coeffRef(j,0)=supports.coeff(j,0);
        }
      }
    }
    break;
  }
  case eParametricInputs: {
    if (!m_hasOnes) {
      AbstractPolyhedra<scalar> input;
      m_transformedInputs.getTransformedPolyhedra(input,space,(space==eNormalSpace) ? m_invIminA : m_pseudoInvIminJ,(space==eNormalSpace) ? m_IminA : m_pseudoIminJ);
      MatrixS inSupports(vectors.cols(),1);
      MatrixS origVectors=vectors;
      for (int i=1;i<=iteration;i++) {
        vectors=dynamics*vectors;
        if (!init.maximiseAll(vectors,supports)) processError(init.getName() + " parametric maximise");
        MatrixS inVectors=origVectors-vectors;
        if (!input.maximiseAll(inVectors,inSupports)) processError(input.getName() + " parametric maximise");
        supports+=inSupports;
        for (int j=0;j<supports.rows();j++) {
          if (func::toUpper(supports.coeff(j,0))>func::toUpper(accumSupports.coeff(j,0))) {
            accumSupports.coeffRef(j,0)=supports.coeff(j,0);
          }
        }
      }
      break;
    }
  }
  default: {
    m_subReach.copy(m_initialState.getPolyhedra(eEigenSpace));
    MatrixS& templates=getTemplates(eEigenSpace,directions);
    result.retemplate(templates);
    for (int i=1;i<=iteration;i++) {
      getReachSet(i,m_initialState.getPolyhedra(eEigenSpace),inputType,false,true,directions,true,false);
      m_subReach.copy(m_reach);
      result.merge(m_reach,false);
    }
    if (space==eNormalSpace) {
      result.transform(m_pseudoEigenVectors,m_invPseudoEigenVectors);
    }
    vectors=result.getDirections();
    accumSupports=result.getSupports();
  }
  }
  result.load(faces,accumSupports);
  AbstractPolyhedra<scalar>& reachTube=m_pReachTube->load(result,Polyhedra<scalar>::ms_emptyMatrix,Polyhedra<scalar>::ms_emptyMatrix,space);
  m_reachTime=timer.elapsed()*1000;
  reachTube.setCalculationTime(m_reachTime);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"LGG Reach Time: ",true);
  return reachTube;
}

template <class scalar>
int DynamicalSystem<scalar>::findBrokenOverapproximation()
{
  Polyhedra<scalar> &abstract=m_pAbstractReachTube->getPolyhedra();
  MatrixS templates=abstract.getDirections();
  MatrixS inSupports;
  m_pReachTube->getPolyhedra().maximiseAll(templates,inSupports);
  MatrixS outSupports=abstract.getSupports();
  if (outSupports.rows()<inSupports.rows()) return 0;
  for (int i=0;i<inSupports.rows();i++) {
    if (func::toUpper(inSupports.coeff(i,0))>func::toUpper(outSupports.coeff(i,0))) {
      return i;
    }
  }
  if (outSupports.rows()>inSupports.rows()) return inSupports.rows();
  return -1;
}

template <class scalar>
int DynamicalSystem<scalar>::loadSensitivities(std::string &data,size_t pos)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  m_sensitivity.resize(m_dimension,m_idimension);
  int result=ms_logger.StringToMat(m_sensitivity,data,pos);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Sensitivity time:",true);
  return result;
}

template <class scalar>
int DynamicalSystem<scalar>::loadOutputSensitivities(std::string &data,size_t pos)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  m_outputSensitivity.resize(m_odimension,m_dimension);
  int result=ms_logger.StringToMat(m_outputSensitivity,data,pos);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Output Sensitivity time:",true);
  return result;
}

template <class scalar>
int DynamicalSystem<scalar>::loadIOSensitivities(std::string &data,size_t pos)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  m_ioSensitivity.resize(m_odimension,m_idimension);
  int result=ms_logger.StringToMat(m_ioSensitivity,data,pos);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"IO Sensitivity time:",true);
  return result;
}

template <class scalar>
void DynamicalSystem<scalar>::setEigenSpace()
{
  m_initialState.setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
  m_transformedInputs.setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
  m_guard.setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
  m_safeReachTube.setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
  m_pReachSet->setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
  m_pReachTube->setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
  m_pAbstractReachTube->setEigenSpace(m_pseudoEigenVectors,m_invPseudoEigenVectors);
}

/// Processes a calculation error either executing a throw or tagging an imprecision
template <class scalar>
void DynamicalSystem<scalar>::processError(std::string source)
{
  ms_logger.logData("Error processing ",false);
  ms_logger.logData(source);
  if (func::ms_formal) throw processingError;
  func::ms_isImprecise=true;
}

template <class scalar>
bool DynamicalSystem<scalar>::loadDynamics(const MatrixS &dynamics)
{
  boost::timer timer;
  bool result=load(dynamics);
  if (result) setEigenSpace();
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Dynamics time:",true);
  return result;
}

template <class scalar>
int DynamicalSystem<scalar>::loadDynamics(const std::string &data,size_t pos)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  if (command==eMinusCmd) pos--;
  int result=JordanMatrix<scalar>::load(data,pos);
  if (result>0) setEigenSpace();
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Dynamics time:",true);
  return result;
}

/// Loads the LTI dynamics of an armax model
template <class scalar>
int DynamicalSystem<scalar>::loadARMAXModel(std::string &data,size_t pos)
{
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  MatrixS ARMAX(2,m_dimension+1);
  bool reverse=(data.at(pos)=='r');
  if (reverse) pos++;
  int result=ms_logger.StringToMat(ARMAX,data,pos);
  if (result<0) return result;
  if (reverse) {
    ARMAX.row(0).reverseInPlace();
    scalar temp;
    for (int i=0;i<((m_dimension+1)>>1);i++) {
      temp=ARMAX.coeff(1,i);
      ARMAX.coeffRef(1,i)=ARMAX.coeff(1,m_dimension-i);
      ARMAX.coeffRef(1,m_dimension-i)=temp;
    }
  }
  if (ARMAX.coeff(0,m_dimension)==func::ms_0) ARMAX.coeffRef(0,m_dimension)=ms_one;
  else if (ARMAX.coeff(0,m_dimension)!=ms_one) ARMAX/=ARMAX.coeff(0,m_dimension);
  m_dynamics.block(0,1,m_dimension-1,m_dimension-1)=MatrixS::Identity(m_dimension-1,m_dimension-1);
  m_dynamics.block(m_dimension-1,0,1,m_dimension)=-ARMAX.block(0,0,1,m_dimension);
  m_sensitivity=MatrixS::Zero(m_dimension,1);//(m_idimension>0) ? m_idimension : 1);
  m_sensitivity.coeffRef(m_dimension-1,0)=ms_one;
  m_outputSensitivity.resize(1,m_dimension);
  for (int i=0;i<m_dimension;i++) {
    m_outputSensitivity.row(0)=ARMAX.block(1,0,1,m_dimension)+m_dynamics.row(m_dimension-1)*ARMAX.coeff(1,0);
  }
  if (!calculateJordanForm()) return -1;
  if (result>0) setEigenSpace();
  return result;
}

/// Copies an existing object
template <class scalar>
void DynamicalSystem<scalar>::copy(const DynamicalSystem &source)
{
  AccelMatrix<scalar>::copy(source);
  m_idimension=source.m_idimension;
  m_fdimension=source.m_fdimension;
  m_odimension=source.m_odimension;
  m_numVertices=source.m_numVertices;
  m_inputType=source.m_inputType;
  m_inputs.copy(source.m_inputs);
  m_reference.copy(source.m_reference);
  m_outputs.copy(source.m_outputs);
  m_reach.copy(source.m_reach);
  m_subReach.copy(source.m_subReach);
  m_initialState.copy(source.m_initialState);
  m_transformedInputs.copy(source.m_transformedInputs);
  m_guard.copy(source.m_guard);
  m_safeReachTube.copy(source.m_safeReachTube);
  m_outputGuard.copy(source.m_outputGuard);
  m_templates=source.m_templates;
  m_eigenTemplates=source.m_eigenTemplates;
  m_logTemplates=source.m_logTemplates;
  m_sensitivity=source.m_sensitivity;
  m_outputSensitivity=source.m_outputSensitivity;
  m_ioSensitivity=source.m_ioSensitivity;
  m_feedback=source.m_feedback;
  m_abstractVertices=source.m_abstractVertices;
  m_abstractInputVertices=source.m_abstractInputVertices;
  m_accelVertices=source.m_accelVertices;
  m_accelInSupports=source.m_accelInSupports;
  m_name=source.m_name;
  m_source=source.m_source;
  m_paramValues=source.m_paramValues;
  m_dynamicParams=source.m_dynamicParams;
  m_normedJordanIndex=source.m_normedJordanIndex;
  m_normedOnes=source.m_normedOnes;
}

template <class scalar>
typename DynamicalSystem<scalar>::MatrixS& DynamicalSystem<scalar>::getTemplates(space_t space,int precision)
{
  if (m_templates.cols()<=0) {
    if (precision>-2) return makeLogahedralTemplates(precision,(space>eNormalSpace) ? eNormalSpace : eEigenSpace);//TODO: check the space
    return m_logTemplates;
  }
  if (space>eNormalSpace) return m_eigenTemplates;
  return m_templates;
}

template <class scalar>
void DynamicalSystem<scalar>::processFiles(stringList &files,displayType_t displayType,space_t space,bool interval,optionList_t &options)
{
  for (stringList::iterator i=files.begin();i!=files.end();i++) {
    int pos=loadFromFile(*i);
    if (pos<0) continue;
    if (options.size()>0) processOptions(options,displayType,space,interval,false);
    process(displayType,space,interval);
    while (pos<m_source.length()) {
      pos=m_source.find('|',pos);
      if (pos<0) break;
      pos=load(m_source,pos+1);
      if (pos<0) break;
      process(displayType,space,interval,true);
    }
  }
}

// Processes a problem stated by the inut options
template <class scalar>
int DynamicalSystem<scalar>::processOptions(optionList_t &options,displayType_t displayType,space_t space,bool interval,bool run)
{
  if (options.size()<=0) return 0;
  if (options[eDebugStr].size()>0) {
    std::istringstream s(options[eDebugStr]);
    traceDebug(s);
  }
  if (options[eParamStr].size()>0) {
    if (ms_logger.StringToDim(m_paramValues,options[eParamStr])<0) return -1;
    if (m_paramValues.coeff(eNumBits,0)>0) {
      functions<mpfr::mpreal>::setDefaultPrec(m_paramValues.coeff(eNumBits,0));
    }
    if (m_paramValues.coeff(eNumStates,0)>0) changeDimensions(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0),m_paramValues.coeff(eNumOutputs,0),m_paramValues.coeff(eNumFeedbacks,0));
    m_sensitivity.conservativeResize(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0));
    m_inputType=(m_paramValues.coeff(eNumVarInputs,0)>0) ? eVariableInputs : ((m_paramValues.coeff(eNumInputs,0)>0) ? eParametricInputs : eNoInputs);
  }
  if ((options[eARMAXStr].size()>0) && (loadARMAXModel(options[eARMAXStr])<0))      return -1;
  if ((options[eGuardStr].size()>0) && (loadGuard(options[eGuardStr])<0))           return -1;
  if ((options[sGuardStr].size()>0) && (loadSafeReachTube(options[sGuardStr])<0))   return -1;
  if ((options[oGuardStr].size()>0) && (loadOutputGuard(options[oGuardStr])<0))     return -1;
  if ((options[eDynamicsStr].size()>0) && (loadDynamics(options[eDynamicsStr])<0))  return -1;
  if ((options[eInitStr].size()>0) && (loadInitialState(options[eInitStr])<0))      return -1;
  if ((options[iSenseStr].size()>0) && (loadSensitivities(options[iSenseStr])<0))   return -1;
  if ((options[eInputStr].size()>0) && (loadInputs(options[eInputStr])<0))          return -1;
  if ((options[eTemplateStr].size()>0) && (loadTemplates(options[eTemplateStr])<0)) return -1;
  if (run) process(displayType,space,interval);
  return 0;
}

template <class scalar>
bool DynamicalSystem<scalar>::process(const displayType_t displayType,const space_t space,const bool interval,const bool append)
{
  try {
    int iter=m_paramValues.coeff(eNumSteps,0);
    int maxIter=m_paramValues.coeff(eNumSteps,1);
    int stepIter=m_paramValues.coeff(eNumSteps,2);
    if (maxIter<=0) maxIter=iter+1;
    if (stepIter<=0) stepIter=1;
    int minPrecision=m_paramValues.coeff(eLogFaces,0);
    int maxPrecision=m_paramValues.coeff(eLogFaces,1);
    int stepPrecision=m_paramValues.coeff(eLogFaces,2);
    if ((minPrecision|maxPrecision|stepPrecision)==0) minPrecision=2;
    if (maxPrecision<=0) maxPrecision=minPrecision;
    if (stepPrecision<=0) stepPrecision=1;
    int directions=m_paramValues.coeff(eLogDirections,0);
    int maxDirections=m_paramValues.coeff(eLogDirections,1);
    int stepDirections=m_paramValues.coeff(eLogDirections,2);
    if (maxDirections<=0) maxDirections=directions;
    if (stepDirections<=0) stepDirections=1;
    int width=((maxIter-iter)/stepIter)*((maxPrecision-minPrecision+1)/stepPrecision);
    for (;directions<=maxDirections;directions+=stepDirections) {
      MatrixS faces=makeLogahedralTemplates(directions,eEigenSpace).transpose();//TODO: the space in makelogahedral looks counterintuitive
      MatrixS supports(faces.rows(),width);
      //MatrixS dynamicSupports(0,width);
      m_dynamicParams.resize(eNumFinalParameters,width);
      int col=0;
      for (iter=m_paramValues.coeff(eNumSteps,0);iter<maxIter;iter+=stepIter) {
        for (int precision=minPrecision;precision<=maxPrecision;precision+=stepPrecision) {  
          powerS iteration=iter;
          if (iter==0) iteration=calculateIterations(m_initialState.getPolyhedra(eEigenSpace),m_inputType);
          refScalar longIter=iteration;
          getAbstractReachTube(iteration,precision,directions,m_inputType,space);
          m_dynamicParams.coeffRef(eFinalIterations,col)=longIter;
          m_dynamicParams.coeffRef(eFinalPrecision,col)=precision;
          m_dynamicParams.coeffRef(eFinalLoadTime,col)=scalar(m_loadTime);
          m_dynamicParams.coeffRef(eFinalReachTime,col)=scalar(m_reachTime);
          supports.col(col++)=m_pAbstractReachTube->getPolyhedra(space).getSupports();
        }
      }
      m_pAbstractReachTube->load(faces,supports,space);
      save(displayType,space,interval,(directions>m_paramValues.coeff(eLogDirections,0)) || append);
    }
  }
  catch(std::string error) {
    ms_logger.logData("Error processing "+m_name);
    ms_logger.logData(error);
  }
}

template <class scalar>
void DynamicalSystem<scalar>::setName(const std::string name)
{
  m_name=name;
}

/// Calculates the number of iterations necessary to supersede the guard
template <class scalar>
typename DynamicalSystem<scalar>::powerS DynamicalSystem<scalar>::calculateIterations(AbstractPolyhedra<scalar> &init,inputType_t inputType)
{
    //Xn=J^nX0 + (J^n-I)U'
    //p_Xn(-v)=p_X0(-J^nT v) + p_U'(-(J^n-I)^T v) <-h
    //p_X0(-J^nT v) + p_U'(-(J^n-I)^T v) <-h
    // \sum l^n (p_X0(-g_l)+p_U'( -g_l )) <-h+p_U'( g_l )
    boost::timer timer;
    findFrequencies();
    if (isDivergent(true)) {
      powerS result=calculateDivergentIterations(init,inputType);
      if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Calculate Iterations, Time",true);
      return result;
    }
    MatrixS limits=m_guard.getPolyhedra(eEigenSpace).getSupports();
    if (limits.rows()<=0) {
      if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Calculate Iterations, Time",true);
      return func::ms_infPower;
    }
    MatrixS templates,roundVertices;
    MatrixS faces=m_guard.getPolyhedra(eEigenSpace).getDirections();
    getRoundedDirections(templates,faces);
    if (templates.cols()==0) {
      if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Calculate Iterations, Time",true);
      return func::ms_infPower;
    }
    const MatrixS& vertices=init.getVertices();
    if (vertices.rows()<=0) processError(init.getName()+" vertices");
    powerS low=0,high=func::ms_infPower;
    refScalar logSigma=log10(this->m_maxSigma);
    MatrixS lambdas=this->m_foldedEigenValues/this->m_maxSigma;
    MatrixS poweredLambdas(1,lambdas.rows());
    MatrixS supports;
    int minPoints[templates.cols()];
    if (inputType==eNoInputs) {
      getRoundedDirections(roundVertices,vertices,true);
    }
    else {
      AbstractPolyhedra<scalar>& inputs=m_transformedInputs.getPolyhedra(eEigenSpace);
      const MatrixS& inputVertices=(inputType==eParametricInputs) ? inputs.getVertices() : inputs.getCentre();
      if (inputVertices.rows()<=0) return func::ms_infPower;
      MatrixS accelInputVertices=inputVertices*this->m_pseudoInvIminJ.transpose();
      MatrixS combinedVertices=combineAminB(vertices,accelInputVertices,false);
      getRoundedDirections(roundVertices,combinedVertices,true);
    }
    supports=roundVertices*templates;
    for (int col=0;col<supports.cols();col++) {
      refScalar min=func::toLower(limits.coeff(col,0));
      minPoints[col]=-1;
      for (int row=0;row<supports.rows();row++) {
        if (func::toLower(supports.coeff(row,col))<min) {
          min=func::toLower(supports.coeff(row,col));
          minPoints[col]=row;
        }
      }
      if (min<0) minPoints[col]=-1;
    }
    MatrixS coefficients(templates.rows(),1);
    for (int col=0;col<templates.cols();col++) {
      int row=minPoints[col];
      if (row<0) continue;
      low=0;
      while(low<high) {
        for (int pos=0;pos<coefficients.rows();pos++) {
          coefficients.coeffRef(pos,0)=roundVertices.coeff(row,pos)*templates.coeff(pos,col);
        }
        ms_logger.logData(roundVertices,"vertices");
        ms_logger.logData(templates,"templates");

        for (int i=0;i<lambdas.cols();i++) {
          poweredLambdas.coeffRef(0,i)=func::pow(lambdas.coeff(i,0),low);
        }
        supports=poweredLambdas*coefficients;
        if (func::isZero(supports.coeff(0,0))) return func::ms_infPower;
        refScalar power=func::toLower(limits.coeff(col,0)/supports.coeff(0,0));
        refScalar iter=log10(power)/logSigma;
        powerS n=func::toInt(iter);
        if (n>low+1) low=n;
        else break;
      }
      if (low<high) high=low;
    }
    int rotations=0;
    for (int i=0;i<m_dimension;i++) {
      if (m_freq[i]>rotations) rotations=m_freq[i];
    }
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Calculate Iterations, Time",true);
    return high+rotations;
}

/// Calculates the number of iterations necessary for a point to supersede a specific guard
template <class scalar>
typename DynamicalSystem<scalar>::powerS DynamicalSystem<scalar>::calculateDivergentIterations(const MatrixS& direction,const MatrixS& point,const MatrixS& inpoint,const scalar &guard,const scalar &inguard,const MatrixS &normedLambdas,const refScalar logSigma,const inputType_t inputType)
{
  powerS base=0,power=func::ms_infPower,step=1;
  MatrixS baseLambdas=MatrixS::Zero(1,normedLambdas.cols());
  MatrixS poweredLambdas=normedLambdas;
  MatrixS jordanLambdas=MatrixS::Ones(1,normedLambdas.cols());
  for (int col=0;col<poweredLambdas.cols();col++) {
    if (m_normedJordanIndex[col]>0) {
      jordanLambdas.coeffRef(0,col)=ms_one/normedLambdas.coeff(0,col);
    }
  }
  while((2*step>0) && (2*step<power)) {
    scalar sum=inguard;
    for (int col=0;col<poweredLambdas.cols();col++) {
      poweredLambdas.coeffRef(0,col)*=poweredLambdas.coeffRef(0,col);
      scalar mult=ms_one*direction.coeff(col,0);
      if (m_normedOnes[col]) {
        scalar n=base+step;
        scalar multo=mult;
        mult*=n;
        for (int i=1;i<=m_normedJordanIndex[col];i++) {
          multo+=direction.coeff(col-i,0)*binomial(base+step,i);
          mult+=direction.coeff(col-i,0)*binomial(base+step,i+1);
        }
        sum+=multo*point.coeff(0,col)-mult*inpoint.coeff(0,col);
      }
      else {
        for (int i=1;i<=m_normedJordanIndex[col];i++) {
          mult+=direction.coeff(col-i,0)*binomial(base+step,i)*func::pow(jordanLambdas.coeff(0,col),i);
        }
        mult*=baseLambdas.coeffRef(0,col)+poweredLambdas.coeffRef(0,col);
        sum+=mult*(point.coeff(0,col)-inpoint.coeff(0,col));
      }
    }
    if (sum>guard) {
      if (power<=base+step) return power;
      power=base+step;
      base+=step/2;
      step=1;
      for (int col=0;col<baseLambdas.cols();col++) {
        baseLambdas.coeffRef(0,col)+=sqrt(poweredLambdas.coeffRef(0,col));
      }
      poweredLambdas=normedLambdas;
    }
    else step*=2;
  }
  return power;
}

/// Calculates the number of iterations necessary to supersede the guard
/// @param pInit initial polyhedra to apply the dynamics on
/// @param inputType type of inputs to use
template <class scalar>
typename DynamicalSystem<scalar>::powerS DynamicalSystem<scalar>::calculateDivergentIterations(AbstractPolyhedra<scalar> &init,inputType_t inputType)
{
  MatrixS limits=m_guard.getPolyhedra(eEigenSpace).getSupports();
  if (limits.rows()<=0) return func::ms_infPower;
  MatrixS faces=-m_guard.getPolyhedra(eEigenSpace).getDirections();
  if (faces.cols()==0) return func::ms_infPower;
  MatrixS templates,normedVertices,normedInputs=ms_emptyMatrix;
  const MatrixS& vertices=init.getVertices();
  if (vertices.rows()<=0) {
    processError(init.getName()+" vertices");
    return func::ms_infPower;
  }
  int normedDim=getNormedDimension();
  getNormedDirections(templates,faces);
  getNormedDirections(normedVertices,vertices,true);
  MatrixS incoefficients=MatrixS::Zero(1,normedDim);
  refScalar logSigma=log10(this->m_maxSigma);
  MatrixS normedLambdas(1,normedDim);
  int pos=0;
  for (int i=0;i<m_dimension;i++) {
    if (m_conjugatePair[i]>i) continue;
    normedLambdas.coeffRef(0,pos++)=this->m_eigenNorms.coeff(i,0);
  }
  if (inputType==eParametricInputs) {
    const MatrixS& inputVertices=m_transformedInputs.getPolyhedra(eEigenSpace).getVertices();
    if (inputVertices.rows()<=0) processError(m_transformedInputs.getPolyhedra(eEigenSpace).getName());
    getNormedDirections(normedInputs,inputVertices,true);
    MatrixS IminJ=MatrixS::Identity(normedDim,normedDim);
    for (int i=0;i<normedDim;i++) {
      if (!m_normedOnes[i]) IminJ.coeffRef(i,i)-=normedLambdas.coeff(0,i);
      if (m_normedJordanIndex[i]>0) IminJ.coeffRef(i-1,i)=-ms_one;
    }
    MatrixS invIminJ=makeInverse(IminJ);
    normedInputs*=invIminJ.transpose();
  }
  powerS finalPower=func::ms_infPower;
  for (int i=0;i<templates.cols();i++) {
    powerS guardPower=0;
    for (int j=0;j<normedVertices.rows();j++) {
      if (normedInputs.rows()>0) {
        for (int k=0;k<normedInputs.rows();k++) {
          scalar inguard=(normedInputs.row(k)*templates.col(i)).coeff(0,0);
          powerS power=calculateDivergentIterations(templates.col(i),normedVertices.row(j),normedInputs.row(k),limits.coeff(0,i),inguard,normedLambdas,logSigma,inputType);
          if (power>guardPower) guardPower=power;
        }
      }
      else {
        powerS power=calculateDivergentIterations(templates.col(i),normedVertices.row(j),incoefficients,limits.coeff(0,i),0,normedLambdas,logSigma,inputType);
        if (power>guardPower) guardPower=power;
      }
    }
    if (guardPower<finalPower) finalPower=guardPower;
  }
  int rotations=0;
  for (int i=0;i<m_dimension;i++) {
    if (m_freq[i]>rotations) rotations=m_freq[i];
  }
  return finalPower+rotations;
}

/// Calculates the number of iterations necessary for a point to supersede a specific guard
template <class scalar>
typename DynamicalSystem<scalar>::powerS DynamicalSystem<scalar>::calculateNormedIterations(const MatrixS& point,const scalar &guard,const scalar &inguard,const MatrixS &normedLambdas,const refScalar logSigma,const inputType_t inputType)
{
  powerS power=0;
  powerS n=0;
  MatrixS poweredLambdas=MatrixS::Ones(1,normedLambdas.cols());
  do {
    power=n;
    scalar sum=0;
    for (int col=0;col<normedLambdas.cols();col++) {
      poweredLambdas.coeffRef(0,col)=func::pow(normedLambdas.coeff(0,col),power);
      if (m_normedJordanIndex[col]>0) poweredLambdas.coeffRef(0,col)*=binomial(power,m_normedJordanIndex[col])/func::pow(normedLambdas.coeff(0,col),m_normedJordanIndex[col]);;
      sum+=poweredLambdas.coeffRef(0,col)*point.coeff(0,col);
    }
    if (func::isZero(sum)) return func::ms_infPower;
    refScalar poweredMax=func::toLower((guard+inguard)/sum);
    if (poweredMax<logSigma) return func::ms_infPower;
    refScalar iter=log10(poweredMax)/logSigma;
    n=func::toInt(iter);
  } while(abs(power-n)>1);
  return power+1;
}

/// Calculates the number of iterations necessary to supersede the guard
template <class scalar>
typename DynamicalSystem<scalar>::powerS DynamicalSystem<scalar>::calculateNormedIterations(AbstractPolyhedra<scalar> &init,inputType_t inputType)
{
  if (isDivergent(true)) return calculateDivergentIterations(init,inputType);
  if (m_hasMultiplicities) this->calculateBoundedEigenError(calculateMaxIterations());
  MatrixS limits=m_guard.getPolyhedra(eEigenSpace).getSupports();
  if (limits.rows()<=0) return func::ms_infPower;
  MatrixS faces=-m_guard.getPolyhedra(eEigenSpace).getDirections();
  if (faces.cols()==0) return func::ms_infPower;
  MatrixS templates,normedVertices,normedInputs=ms_emptyMatrix;
  const MatrixS& vertices=init.getVertices();
  if (vertices.rows()<=0) processError(init.getName() + " vertices");
  int normedDim=getNormedDimension();
  getNormedDirections(templates,faces);
  getNormedDirections(normedVertices,vertices,true);
  MatrixS coefficients(1,normedDim);
  refScalar logSigma=log10(this->m_maxSigma);
  MatrixS normedLambdas(1,normedDim);
  int pos=0;
  for (int i=0;i<m_dimension;i++) {
    if (m_conjugatePair[i]>i) continue;
    if (m_isOne[i]) normedLambdas.coeffRef(0,pos++)=ms_one-scalar(2e-6);
    else normedLambdas.coeffRef(0,pos++)=func::norm2(m_eigenValues.coeff(i,i));
  }
  if (inputType==eParametricInputs) {
    const MatrixS& inputVertices=m_transformedInputs.getPolyhedra(eEigenSpace).getVertices();
    if (inputVertices.rows()<=0) processError(m_transformedInputs.getPolyhedra(eEigenSpace).getName());
    getNormedDirections(normedInputs,inputVertices,true);
    MatrixS IminJ=MatrixS::Identity(normedDim,normedDim);
    for (int i=0;i<normedDim;i++) {
      IminJ.coeffRef(i,i)-=normedLambdas.coeff(0,i);
      if (m_normedJordanIndex[i]>0) IminJ.coeffRef(i-1,i)=-ms_one;
    }
    MatrixS invIminJ=makeInverse(IminJ);
    normedInputs*=invIminJ.transpose();
  }
  powerS finalPower=func::ms_infPower;
  for (int i=0;i<templates.cols();i++) {
    for (int j=0;j<normedVertices.rows();j++) {
      if (normedInputs.rows()>0) {
        for (int k=0;k<normedInputs.rows();k++) {
          for (int col=0;col<templates.rows();col++) {
            coefficients.coeffRef(0,col)=templates.coeff(col,i)*(normedVertices(j,col)-normedInputs.coeff(k,col));
          }
          powerS power=calculateNormedIterations(coefficients,limits.coeff(0,i),(normedInputs.row(k)*templates.col(i)).coeff(0,0),normedLambdas,logSigma,inputType);
          if (power<finalPower) finalPower=power;
        }
      }
      else {
        for (int col=0;col<templates.rows();col++) {
          coefficients.coeffRef(0,col)=templates.coeff(col,i)*normedVertices(j,col);
        }
        powerS power=calculateNormedIterations(coefficients,limits.coeff(0,i),0,normedLambdas,logSigma,inputType);
        if (power<finalPower) finalPower=power;
      }
    }
  }
  int rotations=0;
  for (int i=0;i<m_dimension;i++) {
    if (m_freq[i]>rotations) rotations=m_freq[i];
  }
  return finalPower+rotations;
}

template <class scalar>
void DynamicalSystem<scalar>::traceDebug(std::istringstream& trace)
{
  std::string tracePivotOptions[eMaxTracePivots]={"stime","serrors","objective","tableau","transforms","pivots","costs","feasibility","basis","entries","simplex"};
  std::string traceVerticesOptions[eMaxTraceVertices]={"vtime","vcount","vertices","rays","edges","sets"};
  std::string traceDynamicsOptions[eMaxTraceDynamics]={"dtime","dynamics","eigen","pseudo","output","bounds","derrors","sampling","control","abstraction","adynamics","avertices","templates","refinement","all","REF"};
  typedef std::map<std::string,tracePivots_t> tracePivotNames_t;
  tracePivotNames_t tracePivotNames;
  for (int i=0;i<eMaxTracePivots;i++) {
    tracePivotNames.insert(std::pair<std::string,tracePivots_t>(tracePivotOptions[i],(tracePivots_t)i));
  }
  typedef std::map<std::string,traceVertices_t> traceVertexNames_t;
  traceVertexNames_t traceVertexNames;
  for (int i=0;i<eMaxTraceVertices;i++) {
    traceVertexNames.insert(std::pair<std::string,traceVertices_t>(traceVerticesOptions[i],(traceVertices_t)i));
  }
  typedef std::map<std::string,traceDynamics_t> traceDynamicsNames_t;
  traceDynamicsNames_t traceDynamicsNames;
  for (int i=0;i<eMaxTraceDynamics;i++) {
    traceDynamicsNames.insert(std::pair<std::string,traceDynamics_t>(traceDynamicsOptions[i],(traceDynamics_t)i));
  }
  std::string s;
  while (std::getline(trace,s, ';')) {
    traceDynamicsNames_t::iterator it=traceDynamicsNames.find(s);
    if (it!=traceDynamicsNames.end()) {
      ms_trace_dynamics[it->second]=true;
      Polyhedra<scalar>::ms_trace_dynamics[it->second]=true;
      JordanSolver<refScalar>::ms_trace_dynamics[it->second]=true;
      if (it->second==eTraceAll) {
        for (int i=0;i<it->second;i++) {
          ms_trace_dynamics[i]=true;
          Polyhedra<scalar>::ms_trace_dynamics[i]=true;
          JordanSolver<refScalar>::ms_trace_dynamics[i]=true;
        }
      }
    }
    else {
      tracePivotNames_t::iterator its=tracePivotNames.find(s);
      if (its!=tracePivotNames.end()) {
        Tableau<scalar>::ms_trace_pivots[its->second]=true;
        if (it->second==eTraceSimplex) {
          for (int i=0;i<it->second;i++) Tableau<scalar>::ms_trace_pivots[i]=true;
        }
      }
      else {
        traceVertexNames_t::iterator itv=traceVertexNames.find(s);
        if (itv!=traceVertexNames.end()) VertexEnumerator<scalar>::ms_trace_vertices[itv->second]=true;
        else if (s=="time") {
          ms_trace_dynamics[eTraceTime]=true;
          Polyhedra<scalar>::ms_trace_dynamics[eTraceTime]=true;
          JordanSolver<refScalar>::ms_trace_dynamics[eTraceTime]=true;
          Tableau<scalar>::ms_trace_pivots[eTracePivotTimes]=true;
        }
      }
    }
  }
  VertexEnumerator<scalar>::ms_normalised_rays=VertexEnumerator<scalar>::ms_trace_vertices[eTraceEdges];
  Set::ms_trace_set=VertexEnumerator<scalar>::ms_trace_vertices[eTraceSets];
}

#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class DynamicalSystem<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class DynamicalSystem<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class DynamicalSystem<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class DynamicalSystem<mpinterval>;
  #endif
#endif

}
