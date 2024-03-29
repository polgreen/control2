#include "Synthesiser.h"
#include <boost/timer.hpp>
#include <set>
#include <map>
#include <Eigen/QR>
#include <Eigen/Eigenvalues>

namespace abstract{

/// Constructs an empty buffer
template<class scalar>
Synthesiser<scalar>::Synthesiser(int dimension,int idimension,int odimension) :
  CegarSystem<scalar>(dimension,idimension,odimension,true),
  m_closedLoop(dimension),
  m_synthType(eEigenSynth),
  m_factor(0.75),
  m_ioFeedback(false)
{}

/// Returns the nullSpace vectors of U_1^T(A-\lambda_iI) where B=[U_0 U_1][Z,0]
template<class scalar>
std::vector<typename Synthesiser<scalar>::MatrixS> Synthesiser<scalar>::getNullSpace(const MatrixC &eigenValues)
{
  MatrixS B1=m_sensitivity.block(0,0,m_sensitivity.rows(),m_fdimension);
  SolverMatrixType B1ref;
  interToRef(B1ref,B1);
  Eigen::HouseholderQR<SolverMatrixType> senseQR(B1ref);
  SolverMatrixType U0U1=senseQR.householderQ();
  SolverMatrixType U1Tref=U0U1.block(0,m_fdimension,m_dimension,m_dimension-m_fdimension).transpose();
  MatrixC U1T(m_dimension,m_dimension-m_fdimension);
  MatrixS U1Treal;
  refToInter(U1Treal,U1Tref);
  U1T.real()=U1Treal;
  U1T.imag()=MatrixS::Zero(m_dimension,m_dimension-m_fdimension);
  MatrixC complexDynamics(m_dimension,m_dimension);
  complexDynamics.real()=m_dynamics;
  complexDynamics.imag()=MatrixS::Zero(m_dimension,m_dimension);
  std::vector<MatrixS> result(m_dimension);
  for (int i=0;i<m_dimension;i++) {
    MatrixC nullSpace=U1T*(complexDynamics-eigenValues.coeff(i,i)*MatrixC::Identity(m_dimension,m_dimension));
    this->toRREF(nullSpace);
    std::vector<bool> vars(nullSpace.cols());
    int row=0;
    int freeVars=nullSpace.cols();
    for (int col=0;col<nullSpace.cols();col++) {
      vars[col]=true;
      if (!func::isZero(norm(nullSpace.coeff(row,col)))) {
        vars[col]=false;
        row++;
        freeVars--;
      }
    }
    result[i].resize(m_dimension,freeVars);
    int col=0;
    for (int j=0;j<nullSpace.cols();j++) {
      if (vars[j]) {
        result[i].row(j)=MatrixS::Zero(1,freeVars);
        result[i].coeffRef(j,col)=this->ms_one;
      }
      else {
        int pos=0;
        for (int k=0;k<nullSpace.cols();k++) {
          if (vars[k]) result[i].coeffRef(j,pos++)=-nullSpace.coeff(j,k).real();
        }
      }
    }
    if (m_conjugatePair[i]>i) {
      i++;
      result[i].resize(m_dimension,freeVars);
      int col=0;
      for (int j=0;j<nullSpace.cols();j++) {
        if (vars[j]) {
          result[i].row(j)=MatrixS::Zero(1,freeVars);
          result[i].coeffRef(j,col)=this->ms_one;
        }
        else {
          int pos;
          for (int k=0;k<nullSpace.cols();k++) {
            if (vars[k]) result[i].coeffRef(j,pos++)=-nullSpace.coeff(j,k).imag();
          }
        }
      }
    }
  }
  return result;
}

/// Returns a tranformation of the eigenvector inequalities into their corresponding nullSpace coefficients
template<class scalar>
typename Synthesiser<scalar>::MatrixS Synthesiser<scalar>::getNullSpaceFaces(MatrixS &faces,std::vector<MatrixS> &nullSpace)
{
  nullSpace=getNullSpace(m_closedLoop.getEigenValues());
  int nullSpaceDim=0;
  for (int i=0;i<m_dimension;i++) nullSpaceDim+=nullSpace[i].cols();
  MatrixS result=MatrixS::Zero(faces.rows(),nullSpaceDim);
  int pos=0;
  for (int i=0;i<m_dimension;i++) {
    for (int k=0;k<nullSpace[i].cols();k++,pos++)
    {
      for (int j=0;j<m_dimension;j++) {
        result.col(pos)+=faces.col(i*m_dimension+j)*nullSpace[i].coeff(j,k);
      }
    }
  }
  return result;
}

/// Solves the Sylvester equation AX+XB=C for X
template<class scalar>
typename Synthesiser<scalar>::MatrixS Synthesiser<scalar>::solveSylvester(const MatrixS &A,const MatrixS &B,const MatrixS &C,bool BisDiagonal)
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

/// Retrieves a set of viable Left Eigenvectors for given eigenvalues
template<class scalar>
typename Synthesiser<scalar>::MatrixS Synthesiser<scalar>::getValidLeftEigenVectors(const MatrixS &pseudoEigenValues,const MatrixS &desired)
{
  MatrixS S=makeInverse(desired);//TODO:may be transposed
  MatrixS B=m_sensitivity.leftCols(m_fdimension);
  bool hasInverse=false;
  MatrixS invB=this->getSVDpseudoInverse(B,hasInverse);
  MatrixS C=-B*invB*(m_dynamics*S-S*pseudoEigenValues);//-BP
  S=solveSylvester(m_dynamics,pseudoEigenValues,C,true);
  return makeInverse(S);//TODO:may be transposed
}

/// Retrieves a set of viable Left Eigenvectors for given eigenvalues
template<class scalar>
typename Synthesiser<scalar>::MatrixS Synthesiser<scalar>::getLeftEigenVectors(const MatrixS &pseudoEigenValues,AbstractPolyhedra<scalar> &eigenVectorSpace)
{
  UNUSED(pseudoEigenValues);
  UNUSED(eigenVectorSpace);
}

/// Synthetises the input that leads to a given reach tube
template<class scalar>
AbstractPolyhedra<scalar> Synthesiser<scalar>::synthesiseInputs(inputType_t inputType,int precision,AbstractPolyhedra<scalar> &init,AbstractPolyhedra<scalar> &end,AbstractPolyhedra<scalar> &dynamics,MatrixS& templates,refScalar tightness)
{
  const MatrixS vectors=end.getDirections();
  MatrixS preSupports=end.getSupports();
  MatrixS abstractVectors,supports;
  dynamics.toInner(true);
  if (inputType>=eVariableInputs) {
    MatrixS roundVectors;
    getRoundedDirections(roundVectors,vectors);
    MatrixS combinedVectors(vectors.rows()+roundVectors.rows(),vectors.cols());
    combinedVectors.block(0,0,vectors.rows(),vectors.cols())=vectors;
    combinedVectors.block(vectors.rows(),0,roundVectors.rows(),roundVectors.cols())=roundVectors;
    MatrixS abstractRoundedVectors=dynamics.getSynthVertices(combinedVectors,m_conjugatePair,m_jordanIndex,m_roundings);
    abstractVectors=abstractRoundedVectors.block(0,0,abstractRoundedVectors.rows(),m_dimension);
    init.maximiseAll(abstractVectors.transpose(),supports);
    int factor=supports.rows()/vectors.cols();
    for (int row=0;row<supports.rows();row++) {
      supports.coeffRef(row,0)=preSupports.coeff(row/factor,0)-supports.coeff(row,0);
    }
    AbstractPolyhedra<scalar> tempResult(roundVectors.rows());
    int roundDirs=roundVectors.rows();
    int outRows=abstractRoundedVectors.rows();
    tempResult.m_faces=abstractRoundedVectors.block(0,m_dimension,outRows,roundDirs);
    tempResult.m_faces.conservativeResize(outRows+roundDirs,roundDirs);
    supports.conservativeResize(outRows+roundDirs,1);
    tempResult.m_faces.block(outRows,0,roundDirs,roundDirs)=-MatrixS::Identity(roundDirs,roundDirs);
    supports.block(outRows,0,roundDirs,1)=MatrixS::Zero(roundDirs,1);
    tempResult.load(tempResult.m_faces,supports);
    tempResult.toInner(true);
    tempResult.retemplate(templates,-tightness);//templog?
    MatrixS subTemplates;
    std::vector<int> isRound;
    this->findRoundIndices(isRound,false);
    int newRow=0;
    abstractVectors=tempResult.m_faces;
    supports=tempResult.m_supports;
    for (int row=0;row<abstractVectors.rows();row++) {
      bool keep=true;
      for (unsigned col=0;col<isRound.size();col++) {
        if ((isRound[col]>=0) && (func::hardSign(abstractVectors.coeff(row,col))<0)) keep=false;
      }
      if (keep) {
        abstractVectors.row(newRow)=abstractVectors.row(row);
        supports.row(newRow)=supports.row(row);
        newRow++;
      }
    }
    abstractVectors.conservativeResize(newRow,abstractVectors.cols());
    supports.conservativeResize(newRow,1);

    abstractVectors*=this->m_invIminF.transpose();
    ms_logger.logData(abstractVectors,"deccelerated rounded:");//templog
    for (int col=0;col<m_dimension;col++) {
      int mult=(m_conjugatePair[col]<0) ? 1 : 2;
      int subDim=mult;
      while(m_jordanIndex[col+subDim]>0) subDim+=mult;
      if (subDim>1) {
        this->makeSphericalTemplates(precision,subDim,subTemplates,true);
        int oldRows=abstractVectors.rows();
        int oldCols=abstractVectors.cols();
        abstractVectors.conservativeResize(oldRows*subTemplates.cols(),oldCols+subDim-1);
        supports.conservativeResize(oldRows*subTemplates.cols(),1);
        if (col+1<oldCols) {
          abstractVectors.block(0,col+subDim,oldRows,oldCols-col-1)=abstractVectors.block(0,col+1,oldRows,oldCols-col-1);
        }
        for (int i=1;i<subTemplates.cols();i++) {
          abstractVectors.block(i*oldRows,0,oldRows,col)=abstractVectors.block(0,0,oldRows,col);//All columns before this column stay the same
          if (col+1<oldCols) {
            abstractVectors.block(i*oldRows,col+subDim,oldRows,oldCols-col-1)=abstractVectors.block(0,col+subDim,oldRows,oldCols-col-1);//All columns after this block stay the same
          }
          supports.block(i*oldRows,0,oldRows,1)=supports.block(0,0,oldRows,1);
          for (int j=0;j<oldRows;j++)
          {
            abstractVectors.block(i*oldRows+j,col,1,subDim)=subTemplates.col(i).transpose()*abstractVectors.coeff(j,col);
          }
        }
        for (int j=0;j<oldRows;j++)
        {
          abstractVectors.block(j,col,1,subDim)=subTemplates.col(0).transpose()*abstractVectors.coeff(j,col);
        }
        col+=subDim-1;
      }
    }
  }
  else {
    abstractVectors=dynamics.getSynthVertices(vectors,m_conjugatePair,m_jordanIndex,m_roundings);
    init.maximiseAll(abstractVectors.transpose(),supports);
    int factor=supports.rows()/vectors.cols();
    for (int row=0;row<supports.rows();row++) {
      supports.coeffRef(row,0)=preSupports.coeff(row/factor,0)-supports.coeff(row,0);
    }
    for (int row=0;row<supports.rows();row++) {
      abstractVectors.row(row)=vectors.col(row/factor).transpose()-abstractVectors.row(row);
    }
  }
  AbstractPolyhedra<scalar> result(m_dimension);
  result.load(abstractVectors,supports);
  if (inputType==eParametricInputs) result.transform(this->m_pseudoIminJ,this->m_pseudoInvIminJ);

  //result.retemplate(templates,-tightness);
  return result;
}

/// Synthetises the input that leads to a given reach tube
template<class scalar>
AbstractPolyhedra<scalar> Synthesiser<scalar>::synthesiseInitialState(inputType_t inputType,AbstractPolyhedra<scalar> &input,AbstractPolyhedra<scalar> &end,AbstractPolyhedra<scalar> &dynamics)
{
  MatrixS vectors=end.getDirections();
  MatrixS abstractVectors=dynamics.getSynthVertices(vectors,m_conjugatePair,m_jordanIndex,m_roundings);
  MatrixS supports;
  MatrixS preSupports=end.getSupports();
  if(inputType==eNoInputs) {
    for (int row=0;row<abstractVectors.rows();row++) {
      supports.coeffRef(row,0)=preSupports.coeff(row%preSupports.rows(),0);
    }
  }
  else {
    MatrixS abstractInputVectors=-abstractVectors;
    for (int row=0;row<abstractInputVectors.rows();row++) {
      abstractInputVectors.row(row)+=vectors.col(row%vectors.cols()).transpose();
    }
    input.maximiseAll(abstractVectors,supports);
    for (int row=0;row<supports.rows();row++) {
      supports.coeffRef(row,0)=preSupports.coeff(row%preSupports.rows(),0)-supports.coeff(row,0);
    }
  }
  AbstractPolyhedra<scalar> result(m_dimension);
  result.load(abstractVectors,supports);
  return result;
}

/// Synthetises the eigenstructure of a pole location
template<class scalar>
AbstractPolyhedra<scalar> Synthesiser<scalar>::synthesiseEigenStructure(inputType_t inputType,int precision,int directions,AbstractPolyhedra<scalar> &end,AbstractPolyhedra<scalar> &dynamics)
{
  UNUSED(precision);
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra();
  MatrixS& templates=getTemplates(eNormalSpace,directions);
  const MatrixS& vertices=init.getVertices();
  const MatrixS& lambdas=dynamics.getVertices();
  const MatrixS& final=end.getVertices();
  if ((vertices.rows()<=0) || (lambdas.rows()<0) || (final.rows()<0)) processError(end.getName());
  MatrixS abstractVectors,combinedAbstractVectors;
  MatrixS finalVectors=kronecker(templates,final,true);//templates*final
  if (inputType>=eVariableInputs) {
    MatrixS roundVectors;
    getRoundedDirections(roundVectors,templates);
    MatrixS combinedRoundVectors(templates.cols()+roundVectors.rows(),templates.rows());
    combinedRoundVectors.block(0,0,templates.cols(),templates.rows())=templates.transpose();
    combinedRoundVectors.block(templates.cols(),0,roundVectors.rows(),roundVectors.cols())=roundVectors;
    combinedAbstractVectors=dynamics.getSynthVertices(combinedRoundVectors,m_conjugatePair,m_jordanIndex,m_roundings);
    abstractVectors=combinedAbstractVectors.block(0,0,combinedAbstractVectors.rows(),m_dimension);
  }
  else abstractVectors=dynamics.getSynthVertices(templates,m_conjugatePair,m_jordanIndex,m_roundings);//templates*lambdas
  MatrixS combinedVectors=kronecker(abstractVectors,vertices);//templates*lambdas*vertices
  MatrixS combinedInputVectors(0,0);
  int numInputs=1;
  if (inputType>eNoInputs) {
    AbstractPolyhedra<scalar> &inputsSource=m_transformedInputs.getPolyhedra();
    const MatrixS& inputVertices=(inputType==eParametricInputs) ? inputsSource.getVertices() : inputsSource.getCentre();
    numInputs=inputVertices.rows();
    if (inputVertices.rows()<=0) processError(inputsSource.getName());
    //The synth vectors are multiplied by the transpose of the acceleration matrix
    MatrixS accelInputVectors=abstractVectors*this->m_pseudoInvIminJ;
    MatrixS accelInputVertices=inputVertices;
    if (m_hasOnes && (m_inputType>=eVariableInputs)) {
      for (int i=0;i<accelInputVertices.cols();i++) {
        if (m_isOne[i]) accelInputVertices.coeffRef(i,0)=0;
      }
    }
    combinedInputVectors=kronecker(accelInputVectors,accelInputVertices);//templates*lambdas*inputVertices
  }
  int maxValues=finalVectors.cols()*finalVectors.rows();
  MatrixS faces(final.rows()*combinedVectors.rows()*numInputs+2*maxValues,finalVectors.cols());
  for (int i=0;i<templates.cols();i++) {
    for (int j=0;j<final.rows();j++) {
      int finalBlock=i*final.rows()+j;
      for (int k=0;k<lambdas.rows();k++) {
        int lambdaBlock=i*lambdas.rows()+k;
        for (int l=0;l<vertices.rows();l++) {
          int rowBlock=(i*lambdas.rows()+k)*vertices.rows()+l;
          rowBlock*=numInputs;
          for (int m=0;m<numInputs;m++) {
            int row=(rowBlock+m)*final.rows()+j;
            faces.row(row)=combinedVectors.row(lambdaBlock*vertices.rows()+l)-finalVectors.row(finalBlock);
          }
        }
      }
    }
  }
  if (inputType>=eVariableInputs) {
  }
  MatrixS supports=MatrixS::Zero(faces.rows(),1);
  int ineqSize=final.rows()*combinedVectors.rows()*numInputs;
  faces.block(ineqSize,0,2*maxValues,finalVectors.cols())=MatrixS::Zero(2*maxValues,finalVectors.cols());
  supports.block(ineqSize,0,2*maxValues,1)=MatrixS::Ones(2*maxValues,1);
  for (int i=0;i<finalVectors.cols();i++) {
    faces.block(ineqSize+i*finalVectors.rows(),i,finalVectors.rows(),1)=MatrixS::Ones(finalVectors.rows(),1);
    faces.block(ineqSize+maxValues+i*finalVectors.rows(),i,finalVectors.rows(),1)=-MatrixS::Ones(finalVectors.rows(),1);
  }
  //std::vector<MatrixS> &nullSpace;
  //faces=getNullSpaceFaces(faces,nullSpace);
  AbstractPolyhedra<scalar> result(faces.cols());
  result.load(faces,supports);
  result.logTableau();
  result.FindFeasOrBasis(finalVectors.rows());
  ms_logger.logData(result.m_basisInverse);
  return result;
}

/// Synthetises an input/state polyhedra given a set of conditions
template<class scalar>
bool Synthesiser<scalar>::loadSynthesisedResult(synthesisType_t type, AbstractPolyhedra<scalar> &result,MatrixS& templates,refScalar tightness,int time)
{
    boost::timer timer;
    result.toInner(true);
    if (ms_trace_dynamics[eTraceDynamics]) {
      result.logTableau("Transformed Synth inputs");
    }
    result.retemplate(templates,-tightness);
    m_reachTime=time+timer.elapsed()*1000;;
    result.setCalculationTime(time);
    if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Synthesis Time: ",true);
    switch(type)
    {
    case eInitSynth:
      m_initialState.load(result,ms_emptyMatrix,ms_emptyMatrix,eEigenSpace);
      break;
    case eInputSynth:
      m_transformedInputs.load(result,ms_emptyMatrix,ms_emptyMatrix,eEigenSpace);
      result.transform(m_pseudoEigenVectors,m_invPseudoEigenVectors);
      this->m_inputs.copy(result);
      this->m_inputs.transform(ms_emptyMatrix,this->m_sensitivity);
      break;
    case eSensitivitySynth:
      break;
    default:
      break;
    }
  return true;
}

/// Corrects the support set by the input offset
template <class scalar>
void Synthesiser<scalar>::demergeAccelInSupports(MatrixS &supports,MatrixS &inSupports,int numTemplates)
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
typename JordanMatrix<scalar>::MatrixS& Synthesiser<scalar>::getRefinedAccelInSupports()
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
AbstractPolyhedra<scalar>& Synthesiser<scalar>::getRefinedAbstractReachTube(space_t space,bool guarded)
{
  boost::timer timer;
  AbstractPolyhedra<scalar>& init=m_initialState.getPolyhedra(eEigenSpace);
  AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(m_inputType);

  MatrixS& templates=getTemplates(eEigenSpace);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Abstract Vertices: ",true);
  MatrixS supports;
  if (!dynamics.maximiseAll(m_abstractVertices,supports)) processError(dynamics.getName());

  if (m_inputType>eNoInputs) getRefinedAccelInSupports();
  if (ms_trace_dynamics[eTraceAbstractVertices]) {
    traceSupports(templates,supports,dynamics,m_abstractVertices);
  }
  if (m_inputType>eNoInputs) {
    mergeAccelInSupports(supports,templates.cols());
    if (ms_trace_dynamics[eTraceAbstractVertices]) {
      ms_logger.logData(m_abstractVertices,supports,"Combined",true);
    }
  }
  mergeAbstractSupports(templates,supports);
  MatrixS faces=templates.transpose();
  m_pAbstractReachTube->mergeLoad(init,faces,supports,eEigenSpace);
  AbstractPolyhedra<scalar>& result=m_pAbstractReachTube->getPolyhedra(space);
  if (guarded) getGuardedReachTube(result,space);
  if (ms_trace_dynamics[eTraceAbstraction]) result.logTableau();
  m_reachTime=timer.elapsed()*1000;
  result.setCalculationTime(m_reachTime);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(m_reachTime,"Abstract Reach Time: ",true);
  return result;
}


/// Synthetises an input/state polyhedra given a set of conditions
template<class scalar>
bool Synthesiser<scalar>::synthesiseAll(synthesisType_t type,powerS iteration,int precision,int directions,inputType_t inputType,space_t space,refScalar tightness)
{
    /// sup<v.xy>=sup(sum_i(v_ix_iy_i))=sup<vx.y>
    /// (lr1 v1x1 + li1 v1x2) + (lr2 v2x2 + li2 v2x1)

    m_reachTime=-1;
    boost::timer timer;
    this->setInputType(inputType);
    if (iteration<0) iteration=-iteration;
    if (type==eDynamicSynth) {
      AbstractPolyhedra<scalar> &end=getGuardPoly().getPolyhedra();
      std::set<std::string> inequalities;
      for (int i=0;i<m_dimension;i++) {
        std::stringstream buffer;
        buffer << "(lr[" << i << "]*lr[" << i << "]+li[" << i << "]*li[" << i << "])<1";
        inequalities.insert(buffer.str());
        for (int j=i+1;j<m_dimension;j++) {
          std::stringstream buffer;
          buffer << "(w[" << i << "][0]*w[" << j << "][0]";
          for (int k=1;k<m_dimension;k++) {
            buffer << "+w[" << i << "][" << k <<"]*w[" << j << "][" << k << "]";
          }
          buffer << ")==0";
          inequalities.insert(buffer.str());
        }
      }
      for (int i=1;i<m_dimension;i++) {
        std::stringstream buffer;
        buffer << "(li[" << i-1 << "]+li[" << i << "])==0";
        inequalities.insert(buffer.str());
        buffer.str(std::string());
        buffer << "(lr[" << i-1 << "]==lr[" << i << "]) || ((li[" << i-1 << "]==0) && (li[" << i << "]==0))";
        inequalities.insert(buffer.str());
      }
      MatrixS directions=end.getDirections();
      MatrixS safeVertices=end.getVertices();
      MatrixS initVertices=m_initialState.getPolyhedra().getVertices();
      MatrixS inputVertices=m_transformedInputs.getPolyhedra().getVertices();
      MatrixS liveVertices=m_transformedInputs.getPolyhedra().getVertices();
      for (int i=0;i<directions.cols();i++) {
        std::vector<std::string> rv(m_dimension);
        MatrixS row=directions.col(i).transpose();
        for (int k=0;k<m_dimension;k++) {
          rv[k]=ms_logger.MakeWRow(row,k);
        }
        for (int input=0;input<inputVertices.rows();input++) {
          for (int init=0;init<initVertices.rows();init++) {
            std::string centre;
            MatrixS mid=initVertices.row(init)-inputVertices.row(input);
            for (int j=0;j<m_dimension;j++) mid.coeffRef(0,j)*=directions.coeff(j,i);
            std::vector<std::string> rvr(m_dimension);
            std::vector<std::string> rvi(m_dimension);
            for (int k=0;k<m_dimension;k++) {
              rvr[k]=ms_logger.MakeWRow(mid,k);
            }
            mid=initVertices.row(init)-inputVertices.row(input);
            if (i+1<directions.cols()) {
              for (int j=0;j<m_dimension;j++) mid.coeffRef(0,j)*=directions.coeff(j,i+1);
            }
            else mid=MatrixS::Zero(1,m_dimension);

            for (int k=0;k<m_dimension;k++) {
              rvi[k]=ms_logger.MakeWRow(mid,k);
            }
            std::stringstream buffer;
            buffer << "("<< ms_logger.MakeLSTerm("lr",0,rvr[0]);;
            if (rvi[0]!="(0)") buffer << "+" << ms_logger.MakeLSTerm("li",0,rvi[0]);
            for (int k=1;k<m_dimension;k++) {
              if (rvr[k]!="(0)") buffer << "+" << ms_logger.MakeLSTerm("lr",k,rvr[k]);
              if (rvi[k]!="(0)") buffer << "+" << ms_logger.MakeLSTerm("li",k,rvi[k]);
            }
            buffer << ")";
            centre=buffer.str();
            std::string inequality;
            for (int safe=0;safe<safeVertices.rows();safe++) {
              MatrixS max=safeVertices.row(safe)-inputVertices.row(input);
              std::stringstream buffer;
              buffer << "(" << centre << "<(" << ms_logger.MakeSTerm(max.coeff(0,0),rv[0]);
              for (int k=1;k<m_dimension;k++) {
                buffer << "+" << ms_logger.MakeSTerm(max.coeff(0,k),rv[k]);
              }
              buffer << "))";
              if (safe!=0) inequality+="\n  || ";
              inequality+=buffer.str();
            }
            inequalities.insert(inequality);
            for (int live=0;live<liveVertices.rows();live++) {
              MatrixS min=liveVertices.row(live)-inputVertices.row(input);
              std::stringstream buffer;
              buffer << ">(" << ms_logger.MakeSTerm(min.coeff(0,0),rv[0]);
              for (int k=1;k<m_dimension;k++) {
                buffer << "+" << ms_logger.MakeSTerm(min.coeff(0,k),rv[k]);
              }
              buffer << ")";
              inequalities.insert(centre+buffer.str());
            }
          }
        }
      }
      std::stringstream buffer;
      buffer << "extern float lr[" << m_dimension << "];\n";
      buffer << "extern float li[" << m_dimension << "];\n";
      buffer << "extern float w[" << m_dimension << "][" << m_dimension << "];\n";
      buffer << "void main()\n{";
      std::string result=buffer.str();
      result+="if (";
      std::set<std::string>::iterator it=inequalities.begin();
      if (it!=inequalities.end()) {
        result+="("+*it+")\n";
        it++;
      }
      for (;it!=inequalities.end();it++) result+=" && ("+*it+")\n";
      result+=") {\n    assert(0);\n  }\n}\n";
      ms_logger.logData(result);
      return true;
    }
    else if (type==eEigenSynth) {
      m_closedLoop.getAbstractDynamics(iteration,precision,inputType);
      AbstractPolyhedra<scalar> &end=getGuardPoly().getPolyhedra();
      AbstractPolyhedra<scalar> eigenVectors=synthesiseEigenStructure(inputType,precision,directions,end,m_closedLoop.getAbstractDynamics(inputType));
      eigenVectors.logTableau("EigenStructure:");//templog
    }
    else {
      AbstractPolyhedra<scalar> &end=getGuardPoly().getPolyhedra(eEigenSpace);
      AbstractPolyhedra<scalar>& dynamics=getAbstractDynamics(iteration,precision,inputType);
      MatrixS& templates=getTemplates(eEigenSpace,directions);
      AbstractPolyhedra<scalar> &co_space=(type==eInitSynth) ? m_transformedInputs.getPolyhedra(eEigenSpace) : this->getInitialState(eEigenSpace);
      m_reachTime=timer.elapsed()*1000;
      if (tightness==0) tightness=1e-6;
      if (type==eInitSynth) {
        AbstractPolyhedra<scalar> result=synthesiseInitialState(inputType,co_space,end,dynamics);
        return loadSynthesisedResult(type,result,templates,tightness,timer.elapsed()*1000);
      }
      AbstractPolyhedra<scalar> result=synthesiseInputs(inputType,precision,co_space,end,dynamics,templates,tightness);
      return loadSynthesisedResult(type,result,templates,tightness,m_reachTime);
    }
    return false;
  }

template <class scalar>
int Synthesiser<scalar>::loadPoles(const std::string &data,size_t pos)
{
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  MatrixS poles(m_dimension,m_dimension);
  int result=ms_logger.StringToMat(poles,data,pos);
  m_closedLoop.loadJordan(poles);
  return result;
}

/// Calculates the closed loop dynamics given a plant and a controller
template <class scalar>
bool Synthesiser<scalar>::makeClosedLoop(CegarSystem<scalar> &source,CegarSystem<scalar> &closedLoop,bool useObserver,bool makeReference,bool makeNoise)
{
  if (source.m_feedback.rows()!=m_feedback.rows()) source.m_feedback=m_feedback;
  if (source.m_observer.rows()!=m_observer.rows()) source.m_observer=m_observer;
  MatrixS feedbackDynamics=source.m_sensitivity.block(0,0,m_dimension,m_fdimension)*source.m_feedback;
  if (m_ioFeedback && (source.m_outputSensitivity.cols()>0)) feedbackDynamics*=source.m_outputSensitivity;
  if (ms_trace_dynamics[eTraceDynamics]) ms_logger.logData(feedbackDynamics,"BK");
  MatrixS dynamics=source.m_dynamics-feedbackDynamics;
  if (ms_trace_dynamics[eTraceDynamics]) ms_logger.logData(dynamics,"A-BK");
  int fdimension= (makeReference || (m_reference.getDimension()>0)) ? 0 : m_fdimension;
  MatrixS sensitivity=source.m_sensitivity.block(0,fdimension,m_dimension,m_idimension-fdimension);
  closedLoop.setInputType(eParametricInputs);
  AbstractPolyhedra<scalar> inputs=generateFeedbackInput(fdimension,makeNoise,sensitivity,source.m_sampleTime,source.m_delayTime);
  AbstractPolyhedra<scalar> init, guard,safe;
  init.copy(source.m_initialState.getPolyhedra());
  guard.copy(m_guard.getPolyhedra());
  safe.copy(source.m_safeReachTube.getPolyhedra());
  if (useObserver) {
    if (source.m_outputSensitivity.cols()<=0) source.m_outputSensitivity=MatrixS::Identity(m_dimension,m_dimension);
    source.makeObserver(dynamics,sensitivity,makeNoise);
    init.duplicateSpace(true);
    guard.duplicateSpace(false);
    safe.duplicateSpace(false);
  }
  if (ms_trace_dynamics[eTraceDynamics]) ms_logger.logData(dynamics,"Loading Closed Loop");
  closedLoop.setParams(m_paramValues);
  closedLoop.changeDimensions(dynamics.rows(),sensitivity.cols(),0,0);
  bool result=closedLoop.load(dynamics,sensitivity,guard,init,inputs,safe);
  if (result) {
    closedLoop.m_outputSensitivity=source.m_outputSensitivity;
    if (useObserver) {
      closedLoop.m_outputSensitivity.conservativeResize(m_outputSensitivity.rows(),2*m_dimension);
      closedLoop.m_outputSensitivity.block(0,m_dimension,m_outputSensitivity.rows(),m_dimension)=MatrixS::Zero(m_outputSensitivity.rows(),m_dimension);
      if (source.m_observer.cols()>0) {
        std::vector<int> observerRows(closedLoop.m_dimension,-1);
        scalar coef=func::ms_0;
        refScalar error=func::ms_1;
        if (source.m_T.rows()==0) source.makeReachabilityMatrices(useObserver);
        MatrixS coefficients=source.getDynamicPolynomialCoefficients();
        MatrixS canonicalL=(source.m_W*source.m_observer).transpose();
        canonicalL+=coefficients.block(0,1,1,m_dimension);
        if (!closedLoop.m_hasMultiplicities && closedLoop.getObserverRows(coef,closedLoop.m_dimension,abs(canonicalL.coeff(0,0)),error,observerRows,m_dimension))
        {
           int j,pos=0;
           for (int i=0;(i<closedLoop.m_dimension) && (pos<m_dimension);i++) {
             for (j=m_dimension;j<closedLoop.m_dimension;j++) {
               if (i==observerRows[j]) break;
             }
             if (j==closedLoop.m_dimension) observerRows[pos++]=i;
           }
           if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData(observerRows,"new eigenorder ");
           closedLoop.swapEigenvalues(observerRows);
        }
      }
    }
  }
  if (result && (ms_trace_dynamics[eTraceDynamics])) {
    ms_logger.logData(closedLoop.getDescription());
  }
  return result;
}

template <class scalar>
void Synthesiser<scalar>::processFiles(stringList &files,displayType_t displayType,space_t space,bool interval,optionList_t &options)
{
  boost::timer timer;
  for (stringList::iterator i=files.begin();i!=files.end();i++) {
    int pos=loadFromFile(*i);
    if (pos<0) {
      ms_logger.logData("Error loading file ",false);
      ms_logger.logData(*i);
      continue;
    }
    if ((options.size()>0) && (processOptions(options,displayType,space,interval,false)<0)) continue;
    process(displayType,space,interval);
    while (pos<m_source.length()) {
      pos=m_source.find('|',pos);
      if (pos<0) break;
      pos=load(m_source,pos+1);
      if (pos<0) break;
      process(displayType,space,interval,true);
    }
    if (ms_logger.ms_useConsole) ms_logger.logData(timer.elapsed()*1000,"Total time: ",true);
  }
}

// Processes a problem stated by the input options
template <class scalar>
int Synthesiser<scalar>::processOptions(optionList_t &options,displayType_t displayType,space_t space,bool interval,bool run)
{
  if (options.size()<=0) return 0;
  boost::timer timer;
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
    if (m_paramValues.coeff(eNumInputs,2)+m_paramValues.coeff(eNumVarInputs,1)>0) m_inputType=eVariableOnlyInputs;
  }
  else if (run && (m_dimension==0)) processError("no parameters");
  if ((options[eRandStr].size()>0) && (options[eParamStr].size()>0) && (m_synthType<eCEGISSynth)) {
    ParamMatrix params;
    if (ms_logger.StringToDim(params,options[eParamStr])<0) return -1;
    for (int i=0;i<10;i++) {
      std::stringstream buffer;
      buffer << options[eRandStr] << i;
      setName(buffer.str());
      makeConvergentSystem(params,true);
    }
    return 0;
  }
  if ((options[eSpaceXStr].size()>0) && (loadFromSpaceXFiles(options[eSpaceXStr])<0))   return -1;
  if ((options[eARMAXStr].size()>0) && (loadARMAXModel(options[eARMAXStr])<0))          return -1;
  if ((options[eGuardStr].size()>0) && (loadGuard(options[eGuardStr])<0))               return -1;
  if ((options[eDynamicsStr].size()>0) && (loadDynamics(options[eDynamicsStr])<0))      return -1;
  if ((options[eInitStr].size()>0) && (loadInitialState(options[eInitStr])<0))          return -1;
  if ((options[iSenseStr].size()>0) && (loadSensitivities(options[iSenseStr])<0))       return -1;
  if ((options[oSenseStr].size()>0) && (loadOutputSensitivities(options[oSenseStr])<0)) return -1;
  if ((options[ioSenseStr].size()>0) && (loadIOSensitivities(options[oSenseStr])<0))    return -1;
  if ((options[eInputStr].size()>0) && (loadInputs(options[eInputStr])<0))              return -1;
  if ((options[eOInitStr].size()>0) && (loadOutputInitialState(options[eOInitStr])<0))  return -1;
  if ((options[sGuardStr].size()>0) && (loadSafeReachTube(options[sGuardStr])<0))       return -1;
  if ((options[oGuardStr].size()>0) && (loadOutputGuard(options[oGuardStr])<0))         return -1;
  if ((options[eTemplateStr].size()>0) && (loadTemplates(options[eTemplateStr])<0))     return -1;
  if ((options[eReferenceStr].size()>0) && (loadReference(options[eReferenceStr])<0))   return -1;
  if (options[eIncOrderStr].size()>0) setIncrementalOrder(options[eIncOrderStr]);
  if ((options[eObserveStr].size()>0) && (loadObserver(options[eObserveStr])<0))        return -1;
  if (options[eFactorStr].size()>0) func::toScalar(options[eFactorStr].data(),m_factor);
  if (options[eSampleStr].size()>0) {
    m_sampled.copy(*this);
    m_sampled.sample(options[eSampleStr]);
  }
  else m_sampled.m_dimension=0;
  if (options[eSpeedStr].size()>0)
  {
    setSpeed(options[eSpeedStr]);
    if (options[eSampleStr].size()>0) {
      m_sampled.m_eigenValueCap=m_eigenValueCap;//exp(log(0.1)*m_sampled.m_sampleTime/m_eigenValueCap);
    }
  }
  if ((options[eControlStr].size()>0) && (loadController(options[eControlStr],0,m_synthType<eCEGISSynth)<0))      return -1;
  if (run) {
    if ((m_synthType<eCEGISSynth) && (options[eSampleStr].size()>0)) {
      m_sampled.process(displayType,space,interval);
    }
    else {
      if (options[eRandStr].size()>0) {
        size_t countSize=0;
        int count=func::toInt(func::toCentre(ms_logger.getNumber(options[eRandStr],countSize)));
        if (count==0) count=10000;
        MatToStr<scalar> logger(12,defaultLeftBracket,defaultRightBracket,", ","; ");
        for (int i=-1;(i<=1) && (count>0);i+=2) {
          for (int j=-1;(j<=1) && (count>0);j+=2) {
            for (int k=-1;(k<=1) && (count>0);k+=2) {
              MatrixS dynamics=m_dynamics;
              for (int row=0;(row<dynamics.rows()) && (count>0);row++) {
                for (int col=0;(col<dynamics.cols()) && (count>0);col++) {
                  dynamics.coeffRef(row,col)=m_dynamics.coeff(row,col)*(func::ms_1+0.1*refScalar(i));
                  MatrixS isense=m_sensitivity;
                  for (int inrow=0;(inrow<isense.rows()) && (count>0);inrow++) {
                    for (int incol=0;(incol<isense.cols()) && (count>0);incol++) {
                      isense.coeffRef(inrow,incol)=m_sensitivity.coeff(inrow,incol)*(func::ms_1+0.1*refScalar(j));
                      MatrixS osense=m_outputSensitivity;
                      for (int outrow=0;(outrow<osense.rows()) && (count>0);outrow++) {
                        for (int outcol=0;(outcol<osense.cols()) && (count>0);outcol++) {
                          osense.coeffRef(outrow,outcol)=m_outputSensitivity.coeff(outrow,outcol)*(func::ms_1+0.1*refScalar(k));
                          std::ofstream file;
                          std::string filename="benchmark"+ms_logger.MakeNumber(i+1)+"-"+ms_logger.MakeNumber(j+1)+"-"+ms_logger.MakeNumber(k+1)
                          +"-"+ms_logger.MakeNumber(row)+"-"+ms_logger.MakeNumber(col)
                          +"-"+ms_logger.MakeNumber(inrow)+"-"+ms_logger.MakeNumber(incol)
                          +"-"+ms_logger.MakeNumber(outrow)+"-"+ms_logger.MakeNumber(outcol)
                          +".ss";
                          file.open(filename.data());
                          std::string maxIn=ms_logger.MakeNumber(m_inputs.m_supports.coeff(0,0));
                          std::string maxOut=ms_logger.MakeNumber(m_outputGuard.m_supports.coeff(0,0));
                          if (file.is_open()) {
                            std::stringstream buffer;
                            buffer << "implementation <" << m_paramValues.coeff(eNumBits,1)-m_paramValues.coeff(eNumBits,2) << "," << m_paramValues.coeff(eNumBits,2) <<">\n"
                                   << "states = " << m_dimension << ";\n"
                                   << "inputs = " << m_idimension << ";\n"
                                   << "outputs = " << m_odimension << ";\n"
                                   << "sampling = " << options[eSampleStr] << ";\n"
                                   << "A = " << logger.MatToString(dynamics)
                                   << "B = " << logger.MatToString(isense)
                                   << "C = " << logger.MatToString(osense)
                                   << "D = [0]\n"
                                   << "inputs = [-" << maxIn << "," << maxIn << "]\n"
                                   << "outputs = [-" << maxOut << "," << maxOut << "]\n";
                            std::string data=buffer.str();
                            file.write(data.data(),data.size());
                            file.close();
                            count--;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      process(displayType,space,interval);
    }
    if (ms_logger.ms_useConsole) ms_logger.logData(timer.elapsed()*1000,"Total time: ",true);
  }
  return 0;
}

template <class scalar>
bool Synthesiser<scalar>::process(const displayType_t displayType,const space_t space,const bool interval,const bool append)
{
  try {
    if (m_synthType==eClosedReachTubeSynth) {
      makeClosedSystem(m_closedLoop);
      m_closedLoop.setName(m_name+"-sq");
      ms_logger.logData(m_closedLoop.getDescription(displayType,space,interval));
      return m_closedLoop.process(displayType,space,interval,append);
    }
    boost::timer timer;
    func::ms_isImprecise=false;
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
    int minTightness=m_paramValues.coeff(eTightness,0);
    int maxTightness=m_paramValues.coeff(eTightness,1);
    int stepTightness=m_paramValues.coeff(eTightness,2);
    if (maxTightness<=0) maxTightness=minTightness;
    if (stepTightness==0) stepTightness=1;
    int width=((maxIter-iter)/stepIter)*((maxPrecision-minPrecision+1)/stepPrecision);
    if (m_synthType!=eReachTubeSynth) {
      m_dynamicParams.resize(eNumFinalParameters,0);
      save(displayType,space,interval);
    }
    if ((m_templates.cols()>0) || !m_safeReachTube.isEmpty()) {
      directions=-1;
      maxDirections=-1;
    }
    for (;directions<=maxDirections;directions+=stepDirections) {
      MatrixS faces;
      if (!m_safeReachTube.isEmpty()) faces=m_safeReachTube.getPolyhedra().getFaceDirections();
      else if ((directions<=0) && m_templates.cols()>0) faces=m_templates.transpose();
      else faces=makeLogahedralTemplates(directions,eEigenSpace).transpose();//TODO: the space in makelogahedral looks counterintuitive
      MatrixS supports(faces.rows(),width);
      m_dynamicParams.resize(eNumFinalParameters,width);
      int col=0;
      for (iter=m_paramValues.coeff(eNumSteps,0);iter<maxIter;iter+=stepIter) {
        for (int tightness=minTightness;tightness<=maxTightness;tightness+=stepTightness) {
          for (int precision=(minPrecision>0) ? minPrecision : 1;precision<=maxPrecision;precision+=stepPrecision) {
            powerS iteration=iter;
            switch(m_synthType) {
            case eReachTubeSynth: {
                if (iter==0) iteration=this->calculateIterations(m_initialState.getPolyhedra(eEigenSpace),m_inputType);
                refScalar longIter=iteration;
                if (!m_safeReachTube.isEmpty() && ms_incremental) getRefinedAbstractReachTube(iteration,precision,directions,m_inputType,space);
                else getAbstractReachTube(iteration,precision,directions,m_inputType,space);
                m_dynamicParams.coeffRef(eFinalIterations,col)=longIter;
                m_dynamicParams.coeffRef(eFinalPrecision,col)=precision;
                m_dynamicParams.coeffRef(eFinalLoadTime,col)=scalar(m_loadTime);
                m_dynamicParams.coeffRef(eFinalReachTime,col)=scalar(m_reachTime);
                supports.col(col++)=m_pAbstractReachTube->getPolyhedra(space).getSupports();
                if (!m_safeReachTube.isEmpty() && !ms_incremental) {
                  AbstractPolyhedra<scalar> bounds;
                  synthesiseDynamicBounds(bounds,m_inputType,m_safeReachTube.getPolyhedra(eEigenSpace));
                  for(int i=0;(i<5) && refineAbstractDynamics(bounds);i++) {
                    getRefinedAbstractReachTube(space);
                    m_dynamicParams.conservativeResize(m_dynamicParams.rows(),m_dynamicParams.cols()+1);
                    supports.conservativeResize(supports.rows(),supports.cols()+1);
                    m_dynamicParams.coeffRef(eFinalIterations,col)=longIter;
                    m_dynamicParams.coeffRef(eFinalPrecision,col)=precision;
                    m_dynamicParams.coeffRef(eFinalLoadTime,col)=scalar(m_loadTime);
                    m_dynamicParams.coeffRef(eFinalReachTime,col)=scalar(m_reachTime);
                    supports.col(col++)=m_pAbstractReachTube->getPolyhedra(space).getSupports();
                  }
                }
              }
              break;
            case eIterReachTubeSynth: {
                AbstractPolyhedra<scalar>& tube=this->getIterativeReachTube(iter,m_inputType,space,directions);
                m_pAbstractReachTube->load(tube);
                save(displayType,space,interval,true);
              }
              break;
            case eCEGISSynth:
            case eObserverSynth:
              makeCEGISFiles(m_synthType==eObserverSynth);
              break;
            default: {
                if (iteration==0) iteration=func::ms_infPower;
                refScalar longIter=iteration;
                refScalar tight=tightness;
                tight/=100;
                synthesiseAll(m_synthType,iteration,precision,directions,m_inputType,space,tight);
                m_dynamicParams.resize(eNumFinalParameters,1);
                m_dynamicParams.coeffRef(eFinalIterations,0)=longIter;
                m_dynamicParams.coeffRef(eFinalPrecision,0)=precision;
                m_dynamicParams.coeffRef(eFinalLoadTime,0)=scalar(m_loadTime);
                m_dynamicParams.coeffRef(eFinalReachTime,0)=scalar(m_reachTime);
                save(displayType,space,interval,true);
              }
            }
          }
        }
      }
      if (m_synthType==eReachTubeSynth) {
        for (int row=0;row<supports.rows();row++) {
          for (int col=0;col<supports.cols();col++) {
            if (10*func::toUpper(supports.coeff(row,col))>func::ms_infPower) supports.coeffRef(row,col)=func::ms_infinity;
          }
        }
        m_pAbstractReachTube->load(faces,supports,space);
        save(displayType,space,interval,(directions>m_paramValues.coeff(eLogDirections,0)) || append);
        if (ms_logger.ms_useConsole) {
          ms_logger.logData(m_pAbstractReachTube->getPolyhedra(space).getDescription(displayType,interval,true));
          if (m_odimension>0) {
            m_outputs.logTableau("",true);
          }
        }
      }
    }
    if (minPrecision==0) {
      powerS iteration=iter;
      if (iter==0) iteration=this->calculateMaxIterations();
      AbstractPolyhedra<scalar>& tube=this->getIterativeReachTube(iteration,m_inputType,space,maxDirections);
      m_pAbstractReachTube->load(tube);
      if (ms_logger.ms_useConsole) {
        ms_logger.logData(m_pAbstractReachTube->getPolyhedra(space).getDescription(displayType,interval,true));
      }
      save(displayType,space,interval,true);
    }
  }
  catch(std::string &error) {
    ms_logger.logData("Error processing "+this->m_name);
    ms_logger.logData(error);
  }
}

/// Loads a controller candidate for the system
template <class scalar>
int Synthesiser<scalar>::loadController(const std::string &data,size_t pos,bool close)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  //m_ioFeedback=(ms_canonical<eCNF) && (m_odimension>0) && (m_synthType!=eObserverSynth);//TODO:need better user flag
  m_feedback.resize(m_idimension,m_ioFeedback ? m_odimension : m_dimension);
  size_t result=ms_logger.StringToMat(m_feedback,data,pos);
  if ((result>0) && close) makeClosedLoop(m_observer.rows()>0,!m_reference.isEmpty());
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Controller time:",true);
  return result;
}

/// Loads an observer candidate for the system
template <class scalar>
int Synthesiser<scalar>::loadObserver(const std::string &data,size_t pos)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  m_observer.resize(m_dimension,(m_odimension>0) ? m_odimension : m_dimension);
  size_t result=ms_logger.StringToMat(m_observer,data,pos);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Observer time:",true);
  return result;
}

/// Loads a reference input set for the system
template <class scalar>
int Synthesiser<scalar>::loadReference(const std::string &data,size_t pos,bool vertices)
{
  boost::timer timer;
  int result=m_reference.loadData(data,vertices,pos);
  if (ms_trace_dynamics[eTraceTime]) ms_logger.logData(timer.elapsed()*1000,"Reference time:",true);
  return result;
}

///Creates a c header file for CEGIS
template <class scalar>
std::string Synthesiser<scalar>::makeCEGISHeader(bool observer,bool intervals,bool scaling)
{
  std::stringstream result;
  if (observer && func::isZero(m_observer.norm())) {
    m_observer=MatrixS::Zero(m_dimension,m_fdimension);
  }
  bool useObserver=!func::isZero(m_observer.norm());
  result << "#define _DIMENSION " << m_dimension << "\n";
  result << "#define _CL_DIMENSION " << (useObserver ? 2*m_dimension : m_dimension) << "\n";
  if (observer)  result << "#define _USE_OBSERVER\n";
  if (intervals) result << "#define _USE_INTERVALS\n";
  if (scaling) result << "#define USE_SCALING\n";
  int totalbits=m_paramValues.coeff(eNumBits,1);
  int fracbits=m_paramValues.coeff(eNumBits,2);
  if (totalbits<=0) {
    totalbits=m_paramValues.coeff(eNumBits,0);
    if (totalbits<=0) totalbits=func::getDefaultPrec();
    fracbits=totalbits;
  }
  else if (fracbits==0) fracbits=totalbits>>1;
  result << "#define _FRAC_BITS " << fracbits << "\n";
  result << "#define _EXP_BITS " << totalbits << "\n";
  result << "typedef control_floatt vectort[_DIMENSION];\n"
         << "typedef control_floatt matrixt[_DIMENSION][_DIMENSION];\n";
  result << "typedef control_floatt wide_vectort[_CL_DIMENSION];\n"
         << "typedef control_floatt wide_matrixt[_CL_DIMENSION][_CL_DIMENSION];\n";
  result << "struct coefft\n"
         << "{\n"
         << "  vectort coeffs;\n";
  if (intervals) result << "  vectort uncertainty;\n";
  result << "};\n";
  result << "struct transformt\n"
         << "{\n"
         << "  control_floatt coeffs[_DIMENSION][_DIMENSION];\n";
  if (intervals) result << "  control_floatt uncertainty[_DIMENSION][_DIMENSION];\n";
  if (scaling) result   << "  control_floatt scale;\n";
  result << "};\n";
  return result.str();
}

///Adds a transformt element to the stream
template <class scalar>
void Synthesiser<scalar>::maketransformt(std::stringstream &stream, std::string name,const MatrixS &matrix, const scalar &scale, bool intervals)
{
  if (func::isPositive(scale-func::ms_1)) {
    MatrixS scaledMatrix=matrix/scale;
    stream << "struct transformt " << ms_logger.MatToC(name,scaledMatrix,intervals,scale);
  }
  else {
    stream << "struct transformt " << ms_logger.MatToC(name,matrix,intervals,scale);
  }
}

///Adds a implt element to the stream
template <class scalar>
void Synthesiser<scalar>::makeimplt(std::stringstream &stream, std::string name,int int_bits,int frac_bits,int spec_int_bits)
{
  if (frac_bits>31) frac_bits=31;
  if (int_bits<=0) int_bits=1;
  int scale=1;
  if (int_bits>spec_int_bits) {
    int scale_bits=int_bits-spec_int_bits;
    if (scale_bits>(spec_int_bits-1)) scale_bits=spec_int_bits-1;
    scale=1<<scale_bits;
    int_bits-=scale_bits;
    frac_bits-=scale_bits;
  }
  int bits=int_bits+frac_bits;
  if (bits>63) frac_bits=63-int_bits;
  long long fxp_one = 1l << frac_bits;
  long double lsb=1.0;
  lsb/=fxp_one;
  long double max;
  if (ms_bvType==eFixedBV) {
    max=1<<(int_bits-1);
    max-=lsb;
  }
  else {
    max=2;
    max-=lsb;
    max*=pow(2.0,int_bits-1);
  }
  long double min=-max;
  Implementation implementation;
  implementation.intbits=int_bits;
  implementation.fracbits=frac_bits;
  implementation.scale=scale;
  implementation.max=max;
  implementation.fxp_one=fxp_one;
  m_implementation[name]=implementation;
  stream << "struct implt " << name
         << "={ .int_bits=" << int_bits
         << ", .frac_bits=" << frac_bits
         << ", .fxp_one=" << fxp_one
         << ", .max=" << ms_logger.MakeNumber(max,false,15)
         << ", .min=" << ms_logger.MakeNumber(min,false,15)
         << ", .scale=" << scale
         << "};\n";
}

///Adds a set of vertices, vectors and supports that describe a closed safety spec
template <class scalar>
void Synthesiser<scalar>::makeVertexSupportCombo(std::stringstream &stream, std::string name, MatrixS vertices, MatrixS inputs, AbstractPolyhedra<scalar> &bounds, bool normalize)
{
  bounds.normalise();
  MatrixS vectors=bounds.getFaceDirections();
  MatrixS support=bounds.getSupports().transpose();
  if (normalize) {
    refScalar scale=findMaxValue(bounds.boundingHyperBox());
    if (scale > func::ms_1) {
      vertices/=scale;
      support/=scale;
    }
  }
  //stream << "#define _NUM_VERTICES " << vertices.rows() << "\n";
  //stream << "#define _NUM_VECTORS " << vectors.rows() << "\n";
  stream << "control_floatt " << name << "vertices[_NUM_VERTICES][_CL_DIMENSION]";
  stream << ms_logger.MatToC("",vertices);
  stream << "control_floatt " << name << "vectors[_NUM_VECTORS][_CL_DIMENSION]";
  stream << ms_logger.MatToC("",vectors);
  stream << "control_floatt " << name << "supports[_NUM_VECTORS]";
  stream << ms_logger.MatToC("",support);
  stream << "control_floatt " << name << "input_values[_NUM_INPUT_VERTICES][_IN_DIMENSION]";
  stream << ms_logger.MatToC("",inputs);
}

/// Retrieves the index of the eigenvalue with the largest angle
template <class scalar>
int Synthesiser<scalar>::dominantRotation(MatrixC eigenvalues,std::vector<int> &conjugatePairs)
{
  int result=-1;
  scalar maxAngle=func::ms_0;
  for (int row=0;row<m_dimension;row++) {
    if (conjugatePairs[row]<0) continue;
    const complexS &coef=eigenvalues.coeff(row,row);
    scalar angle=func::invtan(coef.imag(),coef.real());
    if (func::isNegative(func::ms_pi-angle)) continue;
    if (func::isPositive(angle-maxAngle)) {
      maxAngle=angle;
      result=row;
    }
  }
  return result;
}

/// Retrieves the index of the eigenvalue with the largest magnitude
template <class scalar>
int Synthesiser<scalar>::dominantEigenvalue(MatrixC &eigenvalues,std::vector<int> &conjugatePairs,int count)
{
  std::multimap<refScalar,int> sortedEigenNorms;
  for (int row=0;row<m_dimension;row++) {
    refScalar mag=func::toUpper(func::norm2(eigenvalues.coeff(row,row)));
    sortedEigenNorms.insert(std::pair<refScalar,int>(mag,row));
  }
  typename std::multimap<refScalar,int>::reverse_iterator it=sortedEigenNorms.rbegin();
  for (int i=0;(i<count) && (it!=sortedEigenNorms.rend());i++) {
    it++;
  }
  return it->second;
}

/// Refines the synthesised control to obtain a minimal phase on all eigenvalues within the spec
template <class scalar>
bool Synthesiser<scalar>::refinePhase(MatrixC &eigenvalues,AbstractPolyhedra<scalar> &bounds,std::vector<int> &conjugatePairs)
{
  int row=dominantRotation(eigenvalues,conjugatePairs);
  if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData(eigenvalues,"original eigenvalues");
  if (row<0) return false;
  int row2=conjugatePairs[row];
  complexS &coef=eigenvalues.coeffRef(row,row);
  complexS orig=coef;
  if (func::isNegative(coef.real()))
  {
    coef=complexS(-orig.real(),orig.imag());
    eigenvalues.coeffRef(row2,row2)=complexS(coef.real(),-coef.imag());
    MatrixS polynomial=getDynamicPolynomialCoefficients(eigenvalues).block(0,1,1,m_dimension);
    if (bounds.isInside(polynomial)) return true;
    coef=orig;
  }
  else {
    refScalar factor=m_factor;
    while(factor<.999) {
      coef=complexS(orig.real(),orig.imag()*factor);
      eigenvalues.coeffRef(row2,row2)=complexS(coef.real(),-coef.imag());
      MatrixS polynomial=getDynamicPolynomialCoefficients(eigenvalues).block(0,1,1,m_dimension);
      if (bounds.isInside(polynomial)) {
        ms_logger.logData(factor,"phase factor",true);
        if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData(eigenvalues,"phase refined eigenvalues");
        return true;
      }
      factor=(func::ms_1+factor)*refScalar(0.5);
      coef=orig;
    }
  }
  conjugatePairs[row]=-1;
  conjugatePairs[row2]=-1;
  return true;
}

/// Refines the synthesised control to obtain a minimal magnitude on all eigenvalues within the spec
template <class scalar>
bool Synthesiser<scalar>::refineMagnitude(MatrixC &eigenvalues,AbstractPolyhedra<scalar> &bounds,std::vector<int> &conjugatePairs,int pass)
{
  int row=dominantEigenvalue(eigenvalues,conjugatePairs,pass);
  if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData(eigenvalues,"original eigenvalues");
  if (row<0) return false;
  complexS &coef=eigenvalues.coeffRef(row,row);
  complexS &coef2=(conjugatePairs[row]>=0) ? eigenvalues.coeffRef(conjugatePairs[row],conjugatePairs[row]) : coef;
  complexS orig=coef;

  refScalar factor=m_factor;
  while(factor<.999) {
    coef=complexS(orig.real()*factor,orig.imag()*factor);
    if (conjugatePairs[row]>=0) coef2=complexS(coef.real(),-coef.imag());
    MatrixS polynomial=getDynamicPolynomialCoefficients(eigenvalues).block(0,1,1,m_dimension);
    if (bounds.isInside(polynomial)) {
      ms_logger.logData(factor,"mag factor",true);
      if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData(eigenvalues,"mag refined eigenvalues");
      return true;
    }
    factor=(func::ms_1+factor)*refScalar(0.5);
    coef=orig;
    if (conjugatePairs[row]>=0) coef2=complexS(coef.real(),-coef.imag());
  }
  return false;
}

/// Refines the synthesised control to obtain a minimal phase on all eigenvalues within the spec
template <class scalar>
bool Synthesiser<scalar>::refineSampling(CegarSystem<scalar> &source,CegarSystem<scalar> &closedLoop,bool observer)
{
  if (closedLoop.isSampled()) {
    MatrixS feedbackTarget=closedLoop.getDynamicPolynomialCoefficients(closedLoop.m_eigenValues.block(0,0,m_dimension,m_dimension)).block(0,1,1,m_dimension);
    MatrixS observerTarget=observer ? closedLoop.getDynamicPolynomialCoefficients(closedLoop.m_eigenValues.block(m_dimension,m_dimension,m_dimension,m_dimension)).block(0,1,1,m_dimension) : ms_emptyMatrix;
    if (!source.resample(closedLoop.m_sampleTime,feedbackTarget,observerTarget)) return false;
    closedLoop.m_sampleTime=func::ms_1;
    makeClosedLoop(observer,false,true);
    int fracbits;
    if (ms_trace_dynamics[eTraceDynamics]) {
      MatrixS controllable=source.m_T*source.m_dynamics*source.m_invT;
      ms_logger.logData(controllable,"Controllable");
    }
    int totalbits=source.getTotalBits(observer,fracbits);
    int observerbits=totalbits+m_paramValues.coeff(eTightness,0)-fracbits-getBits(m_initialOutputs);
    source.makeControlBounds(observer,(observer && (m_paramValues.coeff(eTightness,0)>=0)) ? observerbits : 0);
    return true;
  }
  return false;
}

/// Refines the synthesised control to obtain a better set of eigenvalues within the spec
template <class scalar>
bool Synthesiser<scalar>::refineEigenvalues(CegarSystem<scalar> &source,CegarSystem<scalar> &closedLoop,bool observer,RefineType_t type,int pass,int count)
{
  refineSampling(source,closedLoop,observer);
  std::vector<int> conjugatePairs=closedLoop.m_conjugatePair;
  if (!observer) {
    if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData("refining controller");
    MatrixC eigenvalues=closedLoop.m_eigenValues.block(0,0,m_dimension,m_dimension);
    AbstractPolyhedra<scalar> bounds=source.m_controllerBounds.getPolyhedra(eEigenSpace);
    bounds.translate(source.m_polynomialCoefficients);
    bool refined=false;
    for (int i=0;i<count;i++) {
      if (type==eRefinePhase)       refined=refinePhase(eigenvalues,bounds,conjugatePairs);
      if (type==eRefineMagnitude)   refined=refineMagnitude(eigenvalues,bounds,conjugatePairs,pass);
      if (!refined) break;
    }
    MatrixS canonical=getDynamicPolynomialCoefficients(eigenvalues).block(0,1,1,m_dimension)-source.getDynamicPolynomialCoefficients().block(0,1,1,m_dimension);
    source.m_feedback=canonical*source.m_T;
  }
  if (observer) {
    if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData("refining observer");
    conjugatePairs.erase(conjugatePairs.begin(),conjugatePairs.begin()+m_dimension);
    for (int i=0;i<m_dimension;i++) {
      if (conjugatePairs[i]>=m_dimension) conjugatePairs[i]-=m_dimension;
    }
    if (ms_trace_dynamics[eTraceEigen]) ms_logger.logData(closedLoop.m_eigenValues,"original closed eigenvalues");

    MatrixC Leigenvalues=closedLoop.m_eigenValues.block(m_dimension,m_dimension,m_dimension,m_dimension);
    AbstractPolyhedra<scalar> Lbounds=source.m_observerBounds.getPolyhedra(eEigenSpace);
    Lbounds.translate(source.m_polynomialCoefficients);
    bool refined=false;
    for (int i=0;i<count;i++) {
      if (type==eRefinePhase)       refined=refinePhase(Leigenvalues,Lbounds,conjugatePairs);
      if (type==eRefineMagnitude)   refined=refineMagnitude(Leigenvalues,Lbounds,conjugatePairs,pass);
      if (!refined) break;
    }
    MatrixS canonical=getDynamicPolynomialCoefficients(Leigenvalues).block(0,1,1,m_dimension)-source.getDynamicPolynomialCoefficients().block(0,1,1,m_dimension);
    canonical.transposeInPlace();
    source.m_observer=source.m_invW*canonical;
  }
  return true;
}

///Creates a c header file for CEGIS
template <class scalar>
std::string Synthesiser<scalar>::makeCEGISDescription(bool observer,bool intervals,bool scaling)
{
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  std::stringstream result;
  source.makeReachabilityMatrices(observer);
  MatrixS TinvW=observer ? source.m_T*source.m_invW : source.m_T;
  MatrixS controllable=source.m_T*source.m_dynamics*source.m_invT;
  if (ms_trace_dynamics[eTraceDynamics]) ms_logger.logData(controllable,"Controllable");
  MatrixS coefficients=-controllable.row(0);
  int fracbits=m_paramValues.coeff(eNumBits,2);
  int totalbits=source.getTotalBits(observer,fracbits);
  int multbits=0;
  if (!m_outputGuard.isEmpty()) {
    source.m_safeReachTube.bitConstrain(totalbits-fracbits);
    source.m_initialState.bitConstrain(totalbits-fracbits-1);
  }
  bool useObserver=!func::isZero(source.m_observer.norm());
  bool haveFeedback=!func::isZero(source.m_feedback.norm());
  int observerbits=totalbits+m_paramValues.coeff(eTightness,0)-fracbits-getBits(m_initialOutputs);
  if (ms_canonical>=eCNF) {
    if (source.m_T.rows()==0) source.makeReachabilityMatrices(useObserver);
    source.m_feedback=-m_feedback*source.m_T;
    if (useObserver) source.m_observer=-source.m_invW*m_observer;
  }
  source.makeControlBounds(observer,(observer && (m_paramValues.coeff(eTightness,0)>=0)) ? observerbits : 0);
  if (haveFeedback) {
    fitToSpec(source.m_feedback,totalbits,fracbits);
    if (useObserver) fitToSpec(source.m_observer,totalbits,fracbits);
  }
  scalar speedFactor=func::ms_1;
  scalar scaleT=func::ms_0;
  scalar scaleInvT=func::ms_0;
  if (scaling) {
    scaleT=findScale(source.m_T,totalbits-fracbits);
    scaleInvT=findScale(source.m_invT,totalbits-fracbits);
  }
  refScalar maxT=findMaxValue(source.m_T,0,func::toLower(scaleT));
  maxT=findMaxValue(source.m_invT,maxT,func::toLower(scaleInvT));
  scalar scaleW=func::ms_0;
  scalar scaleInvW=func::ms_0;
  scalar scaleTinvW=func::ms_0;
  if (observer) {
    if (scaling) {
      scaleW=findScale(source.m_W,totalbits-fracbits);
      scaleInvW=findScale(source.m_invW,totalbits-fracbits);
      scaleTinvW=findScale(TinvW,totalbits-fracbits);
    }
    maxT=findMaxValue(source.m_W,maxT,func::toLower(scaleW));
    maxT=findMaxValue(source.m_invW,maxT,func::toLower(scaleInvW));
  }
  multbits=getBits(maxT);
  AbstractPolyhedra<scalar> KW(source.m_controllerBounds.getPolyhedra());
  KW.transform(source.m_invW.transpose(),source.m_W.transpose());
  AbstractPolyhedra<scalar> KTW(source.m_controllerBounds.getPolyhedra(eEigenSpace));
  KTW.transform(TinvW.transpose(),ms_emptyMatrix);
  KW.normalise();
  if (!func::isZero(getSpeed())) speedFactor/=getSpeed();
   if (haveFeedback && makeClosedLoop(useObserver,false,true)) {
    if ((ms_canonical==eCNFR) && refineEigenvalues(source,m_closedLoop,useObserver,eRefinePhase,0,2*m_dimension)) {
      fitToSpec(source.m_feedback,totalbits,fracbits);
      fitToSpec(source.m_observer,totalbits,fracbits);
      makeClosedLoop(useObserver,false,true);
    }
    if (m_closedLoop.isDivergent(false,getSpeed())) {
      refScalar max=func::toUpper(m_closedLoop.largestEigenNorm());
      MatrixS nudge=m_closedLoop.capEigenValues(getSpeed(),useObserver,false);
      MatrixS controller=coefficients-nudge.block(0,0,1,m_dimension);
      bool keepNudge=source.m_controllerBounds.getPolyhedra(eEigenSpace).isInside(controller);
      if (keepNudge) source.m_feedback=controller*source.m_T;
      if (useObserver) {
        MatrixS observer=coefficients-nudge.block(0,m_dimension,1,m_dimension);
        keepNudge&=source.m_observerBounds.getPolyhedra(eEigenSpace).isInside(observer);
        if (keepNudge) source.m_observer=source.m_invW*observer.transpose();
      }
      if(keepNudge) makeClosedLoop(useObserver,false,true);
      if (func::isPositive(max-source.getSpeed())) max=func::toUpper(source.getSpeed());
      if (max>1.05) {
        ms_logger.logData(m_closedLoop.m_dynamics,"loop dynamics");
        ms_logger.logData(max,"divergent loop",true);
        ms_logger.logData(coefficients,"coefficients");
        MatrixS newControllable=source.m_T*m_closedLoop.m_dynamics*source.m_invT;
        ms_logger.logData(newControllable,"cl coefficients");
        max=1.0;//TODO: this should never be needed.
      }
      speedFactor/=max;
    }
  }
  AbstractPolyhedra<scalar>& K=source.m_controllerBounds.getPolyhedra();
  AbstractPolyhedra<scalar>& KC=source.m_controllerBounds.getPolyhedra(eEigenSpace);
  AbstractPolyhedra<scalar>& L=source.m_observerBounds.getPolyhedra();
  AbstractPolyhedra<scalar>& LO=source.m_observerBounds.getPolyhedra(eEigenSpace);

  int Kbits=getBits(K);
  if (Kbits>(totalbits-fracbits)) Kbits=totalbits-fracbits;
  int Lbits=getBits(L);
  refScalar max=m_sampled.findMaxValue(observer,false);
  max=findMaxValue(coefficients,max);
  int Dbits=getBits(max);
  int Sbits=getBits(m_sampled.findMaxValue(false,true));
  makeimplt(result, "impl",totalbits-fracbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implK",Kbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implL",Lbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implKT",getBits(KC),fracbits,totalbits-fracbits);
  makeimplt(result, "implKW",getBits(KW),fracbits,totalbits-fracbits);
  makeimplt(result, "implKTW",getBits(KTW),fracbits,totalbits-fracbits);
  makeimplt(result, "implLW",getBits(LO),fracbits,totalbits-fracbits);
  makeimplt(result, "implD",Dbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implS",Sbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implTW",multbits,fracbits,totalbits-fracbits);
  int cbmcbits=1;
  for (std::map<std::string, Implementation>::iterator it=m_implementation.begin();it!=m_implementation.end();it++) {
    if (it->second.intbits>cbmcbits) cbmcbits=it->second.intbits;
  }
  int cbmcfracbits=totalbits-cbmcbits;
  if (ms_bvType==eFixedBV) {
    if (ms_canonical<eCNF) cbmcbits*=2;
    else cbmcbits+=4;
  }
  int align=(cbmcbits+cbmcfracbits)&7;
  if (align!=0) cbmcfracbits+=8-align;
  makeimplt(result, "implcbmc",cbmcbits,cbmcfracbits,64);
  result << "struct coefft ";
  result << ms_logger.MatToC("plant",coefficients,intervals,func::ms_0);
  maketransformt(result,"transform",source.m_invT,scaleInvT,intervals);
  maketransformt(result,"pretransform",source.m_T,scaleT,intervals);  
  if (observer) {
    scalar factor=func::ms_1-source.m_observerSensitivityError*scalar(1<<Kbits)-source.m_controllerGershgorinRadius;
    result << "control_floatt speed_factor=" << ms_logger.MakeNumber(speedFactor/factor) << ";\n";
    factor=func::ms_1-source.m_observerOutputSensitivityError*scalar(1<<Lbits)-source.m_observerGershgorinRadius;
    result << "control_floatt observer_speed_factor=" << ms_logger.MakeNumber(speedFactor/factor) << ";\n";
    if (ms_trace_dynamics[eTraceDynamics]) {
      MatrixS observer=source.m_W*source.m_dynamics*source.m_invW;
      ms_logger.logData(observer,"OCF");
      MatrixS osense=source.m_outputSensitivity*source.m_invW;
      ms_logger.logData(osense,"OC");
    }
    maketransformt(result,"observer_transform",source.m_invW,scaleInvW,intervals);
    maketransformt(result,"observer_pretransform",source.m_W,scaleW,intervals);
    maketransformt(result,"cross_transform",TinvW,scaleTinvW,intervals);
    source.makeObserver();
    result << "struct transformt " << ms_logger.MatToC("observer_dynamics",source.m_observerDynamics,intervals,scaling ? func::ms_1 : func::ms_0);
    result << "struct transformt " << ms_logger.MatToC("observer_sensitivity",source.m_observerSensitivity,intervals,scaling ? func::ms_1 : func::ms_0);
    result << "struct transformt " << ms_logger.MatToC("observer_output",source.m_observerOutputSensitivity,intervals,scaling ? func::ms_1 : func::ms_0);
    //result << "control_floatt observer_control_error=" << ms_logger.MakeNumber(source.m_observerOutputSensitivityError*scalar(1<<Lbits)+source.m_observerGershgorinRadius) << ";\n";
    //result << "control_floatt observer_input_error=" << ms_logger.MakeNumber(source.m_observerSensitivityError*scalar(1<<Kbits)+source.m_controllerGershgorinRadius) << ";\n";
    //result << "control_floatt observer_dynamics_error=" << ms_logger.MakeNumber(source.m_observerDynamicsError) << ";\n";
    //result << "control_floatt observer_sensitivity_error=" << ms_logger.MakeNumber(source.m_observerSensitivityError) << ";\n";
    //result << "control_floatt observer_output_sensitivity_error=" << ms_logger.MakeNumber(source.m_observerOutputSensitivityError) << ";\n";
  }
  else result << "control_floatt speed_factor=" << ms_logger.MakeNumber(speedFactor) << ";\n";
  result << "matrixt dynamics" << ms_logger.MatToC("",source.m_dynamics,intervals,scaling ? func::ms_1 : func::ms_0);
  result << "vectort sensitivity" << ms_logger.MatToC("",source.m_sensitivity.transpose(),intervals,scaling ? func::ms_1 : func::ms_0);
  result << "#ifdef __CPROVER\n";
  result << "  #ifdef USE_XTRANSFORM\n";
  result << "    extern vectort controller_cbmc;\n";
  if (observer) result << "    extern vectort observer_cbmc;\n";
  result << "  #else\n";
  result << "    extern vectort controller;\n";
  if (observer) result << "    extern vectort observer;\n";
  result << "    vectort controller_cbmc;\n";
  if (observer) result << "    vectort observer_cbmc;\n";
  result << "  #endif\n";
  result << "#else\n";
  result << "  #ifdef USE_XTRANSFORM\n";
  result << "    vectort controller_cbmc" << ms_logger.MatToC("",m_feedback,intervals,scaling ? func::ms_1 : func::ms_0);
  if (observer) result << "    vectort observer_cbmc" << ms_logger.MatToC("",m_observer.transpose(),intervals,scaling ? func::ms_1 : func::ms_0);
  result << "  #else\n";
  result << "    vectort controller" << ms_logger.MatToC("",source.m_feedback,intervals,scaling ? func::ms_1 : func::ms_0);
  if (observer) result << "    vectort observer" << ms_logger.MatToC("",source.m_observer.transpose(),intervals,scaling ? func::ms_1 : func::ms_0);
  result << "    vectort controller_cbmc;\n";
  if (observer) result << "    vectort observer_cbmc;\n";
  result << "  #endif\n";
  result << "wide_matrixt sampled_dynamics" << ms_logger.MatToC("",m_closedLoop.m_dynamics,intervals,scaling ? func::ms_1 : func::ms_0);
  result << "wide_matrixt eigenvalues" << ms_logger.MatToC("",m_closedLoop.m_pseudoEigenValues,intervals,scaling ? func::ms_1 : func::ms_0);
  result << "#endif\n";
  result << "#ifdef USE_XTRANSFORM\n";
  result << "void boundcbmcController()\n{\n";
  result << ms_logger.IneToC("verify_assume","(control_floatt)","controller_cbmc",KC.getFaceDirections(),KC.getSupports(),false,false) << ";\n";
  result << ms_logger.IneToC("verify_assume","(control_floatt)","observer_cbmc",LO.getFaceDirections(),LO.getSupports(),false,false) << ";\n";
  result << "}\n";
  result << "  #else\n";
  result << "void boundController()\n{\n";
  MatrixS Kdirections=K.getFaceDirections()*-MatrixS::Identity(m_dimension,m_dimension);
  result << ms_logger.IneToC("verify_assume","(control_floatt)","controller",Kdirections,K.getSupports()) << ";\n";
  MatrixS Ldirections=-L.getFaceDirections();
  result << ms_logger.IneToC("verify_assume","(control_floatt)","observer",Ldirections,L.getSupports()) << ";\n";
  result << "}\n";
  result << "#endif\n";
  if (m_feedback.rows()>0) {
    makeClosedLoop(useObserver,false,true);
    MatrixS vectors=m_closedLoop.m_safeReachTube.getPolyhedra().getFaceDirections();
    MatrixS vertices=m_closedLoop.m_initialState.getPolyhedra().getVertices();
    const MatrixS inputVals=m_closedLoop.m_inputs.getVertices();
    const MatrixS inputVertices=m_closedLoop.getInputVertices(eNormalSpace,true);
    result << "#define _IN_DIMENSION " << inputVals.cols() << "\n";
    result << "#define _NUM_VERTICES " << vertices.rows() << "\n";
    result << "#define _NUM_INPUT_VERTICES " << inputVertices.rows() << "\n";
    result << "#define _NUM_VECTORS " << vectors.rows() << "\n";
    if (vertices.rows()>0) {
      MatrixS T=source.m_T;
      MatrixS invT=source.m_invT;
      if (useObserver) {
        int dimension=T.rows();
        T.conservativeResize(dimension+source.m_W.rows(),dimension+source.m_W.cols());
        T.block(dimension,dimension,source.m_W.rows(),source.m_W.cols())=source.m_W;
        T.block(0,dimension,dimension,source.m_W.cols())=MatrixS::Zero(dimension,source.m_W.cols());
        T.block(dimension,0,source.m_W.rows(),dimension)=MatrixS::Zero(source.m_W.rows(),dimension);
        invT.conservativeResize(dimension+source.m_invW.rows(),dimension+source.m_invW.cols());
        invT.block(dimension,dimension,source.m_invW.rows(),source.m_invW.cols())=source.m_invW;
        invT.block(0,dimension,dimension,source.m_invW.cols())=MatrixS::Zero(dimension,source.m_invW.cols());
        invT.block(dimension,0,source.m_invW.rows(),dimension)=MatrixS::Zero(source.m_invW.rows(),dimension);
      }
      /*MatrixS transformedDynamics=T*m_closedLoop.m_dynamics*invT;
      ms_logger.logData(transformedDynamics,"reachable");*/
      MatrixS transformedVertices=vertices*T.transpose();
      AbstractPolyhedra<scalar> transformedSafe(m_closedLoop.m_safeReachTube.getPolyhedra());
      transformedSafe.transform(ms_emptyMatrix,invT);
      makeVertexSupportCombo(result,"",vertices,inputVals,m_closedLoop.m_safeReachTube.getPolyhedra());
      makeVertexSupportCombo(result,"transformed_",transformedVertices,inputVals,transformedSafe);
      result << "control_floatt input_vertices[_NUM_INPUT_VERTICES][_CL_DIMENSION]";
      result << ms_logger.MatToC("",inputVertices);
      result << "control_floatt accel_vertices[_NUM_INPUT_VERTICES][_CL_DIMENSION];\n";
      result << "control_floatt reach_vertices[_NUM_INPUT_VERTICES][_NUM_VERTICES][_CL_DIMENSION];\n";
      result << "control_floatt accelsupports[_NUM_INPUT_VERTICES][_NUM_VECTORS];\n\n";
    }
    else {
      result << "control_floatt vertices[1][1]={{1}};\n";
    }
  }
  return result.str();
}

///Creates a list of violating state-input pairs with their lowest corresponding iteration
template <class scalar>
void Synthesiser<scalar>::getIterationPairs(std::vector<iteration_pair>& result, powerList &iterations,AbstractPolyhedra<scalar> &safe,const MatrixS &vertices,const MatrixS &inVertices)
{
  powerS counterPoints[vertices.rows()+1][inVertices.rows()+1];
  for (int i=0;i<vertices.rows();i++) {
    for (int j=0;j<inVertices.rows();j++) {
      counterPoints[i][j]=0;
    }
  }
  int size=0;
  for (typename powerList::iterator it=iterations.begin();it!=iterations.end();) {
    MatrixS dynamics=m_closedLoop.getPseudoDynamics(it->first).transpose();
    int check=size;
    for (int i=0;i<vertices.rows();i++) {
      for (int j=0;j<inVertices.rows();j++) {
        MatrixS point=(vertices.row(i)-inVertices.row(j))*dynamics+inVertices.row(j);
        if (!safe.isInside(point)) {
          if (counterPoints[i][j]<1) size++;
          if ((counterPoints[i][j]<1) || (counterPoints[i][j]>it->first)) counterPoints[i][j]=it->first;
        }
      }
    }
    if (check==size) {
      typename powerList::iterator it2=it;
      it++;
      iterations.erase(it2);
    }
    else it++;
  }
  result.resize(size);
  int pos=0;
  for (int i=0;i<vertices.rows();i++) {
    for (int j=0;j<inVertices.rows();j++) {
      if (counterPoints[i][j]>0) result[pos++]=iteration_pair(i,j,counterPoints[i][j]);
    }
  }
}

///Explicitly checks the reachability for a bounded time horizon
template <class scalar>
typename Synthesiser<scalar>::powerS Synthesiser<scalar>::checkExplicitReachability(powerS steps,bool useObserver)
{
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  MatrixS T=source.m_T;
  if (useObserver) {
    T.conservativeResize(m_closedLoop.m_dimension,m_closedLoop.m_dimension);
    T.block(0,m_dimension,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
    T.block(m_dimension,0,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
    T.block(m_dimension,m_dimension,m_dimension,m_dimension)=source.m_W;
  }
  return m_closedLoop.checkExplicitReachability(steps,T);
}

///Creates a list of iterations to check with CEGIS
template <class scalar>
std::string Synthesiser<scalar>::makeCEGISIterations(CegarSystem<scalar> &closedLoop,int &existing,int max,RefineType_t stage,int pass,refScalar largestError)
{
  std::stringstream result;
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  if (func::isZero(m_feedback.norm())) return "#define NO_FEEDBACK\n";
  bool useObserver=!func::isZero(m_observer.norm());
  makeClosedLoop(useObserver,false,true);
  if (ms_fullAnswers) {
    ms_logger.logData("Closed  Loop");
    ms_logger.logData(closedLoop.getDescription());
    closedLoop.getAbstractReachTube(func::ms_infPower,2,0,m_inputType);
    ms_logger.logData(closedLoop.getDescription());
  }
  if (closedLoop.isDivergent()) {
    ms_logger.logData(closedLoop.m_eigenValues,"eigenvalues");
    return "#define DIVERGENT\n";
  }
  AbstractPolyhedra<scalar>& dynamics=closedLoop.getRefinedDynamics(func::ms_infPower);
  AbstractPolyhedra<scalar> bounds;
  closedLoop.synthesiseDynamicBounds(bounds,m_inputType,closedLoop.m_safeReachTube.getPolyhedra(eEigenSpace));
  if (ms_fullAnswers) {
    ms_logger.logData("Refined Closed  Loop");
    closedLoop.getAbstractReachTube(0,m_inputType,eNormalSpace,false);
    ms_logger.logData(closedLoop.getDescription());
  }
  else if (ms_trace_dynamics[eTraceOutput]) {
    closedLoop.getAbstractReachTube(0,m_inputType,eNormalSpace,false);
    closedLoop.m_outputs.logTableau("output",true);
  }
#if 1
  std::map<int,iteration_vector >pairs;
  MatrixS inputVertices=closedLoop.getInputVertices(eEigenSpace,true);
  MatrixS iterationSupports;
  bool fail=closedLoop.findIterations(bounds,pairs,iterationSupports,true,m_safeReachTube.getPolyhedra().getSupports().rows());
  if (fail) {
    MatrixS vertices=closedLoop.m_initialState.getPolyhedra().getVertices();
    result << "#define POINTS_PER_ITER\n";
    result << "#define _NUM_ITERATIONS " << pairs.size() << "\n";
    int max_iters=0;
    result << "int iterations[_NUM_ITERATIONS]={";
    typename std::map<int,iteration_vector>::iterator it=pairs.begin();
    for (it=pairs.begin();it!=pairs.end();it++) {
      if (it->second[0].iteration>max) it->second[0].iteration=max;
      if (it->second[0].iteration>max_iters) max_iters=it->second[0].iteration;
    }
    if (max_iters<=existing) {
      max_iters=existing+1;
      for (it=pairs.begin();it!=pairs.end();it++) {
        it->second[0].iteration=max_iters;
      }
    }
    it=pairs.begin();
    if (it!=pairs.end()) {
      result << it->second[0].iteration;
      it++;
    }
    for (;it!=pairs.end();it++) {
      result << "," << it->second[0].iteration;
    }
    existing=max_iters;
    result << "};\n";

    powerS failedIter=checkExplicitReachability(max_iters,useObserver);
    result << "#define _MAX_ITERATIONS " << max_iters << "\n";
    ms_logger.logData(max_iters,"max iters",true);
    result << "int iter_vertices[_NUM_ITERATIONS][2]={";
    bool first=true;
    for (int i=0;i<vertices.rows();i++) {
      for (int j=0;j<inputVertices.rows();j++) {
        int k=i*inputVertices.rows()+j;
        if (pairs.find(k)!=pairs.end()) {
          if (!first) result << ",";
          result << "{" << i << "," << j << "}";
          first=false;
        }
      }
    }
    result << "};\n";
    if ((ms_canonical>eCNFR) && (m_refineCount-->0)) {
      refScalar error=0;
      if (!closedLoop.m_outputs.isEmpty()) {
         MatrixS supports=closedLoop.m_outputs.getSupports();
         if (supports.rows()==m_outputGuard.getSupports().rows()) {
           supports-=m_outputGuard.getSupports();
           for (int i=0;i<supports.rows();i++) {
             if (func::toUpper(supports.coeff(i,0))>error) error=func::toUpper(supports.coeff(i,0));
           }
         }
      }
      if (error==0) {
        for (int i=0;i<iterationSupports.rows();i++) {
          if (func::toUpper(iterationSupports.coeff(i,0))>error) error=func::toUpper(iterationSupports.coeff(i,0));
        }
      }
      if (useObserver && (error>=largestError) && (stage<eRefineController)) {
        if (++pass>=2) {
          pass=0;
          stage=(RefineType_t)(stage+1);//stage=eRefineController;
        }
        source.m_feedback=m_feedback;
        source.m_observer=m_observer;
        largestError=func::ms_infinity;
      }
      if (error<largestError) {
        int fracbits=0;
        int totalbits=source.getTotalBits(useObserver,fracbits);
        ms_logger.logData(error,"refining...",true);
        m_feedback=source.m_feedback;
        m_observer=source.m_observer;
        if (refineEigenvalues(source,closedLoop,useObserver && (stage<eRefineController),(ms_canonical==eCNFP) ? eRefinePhase : eRefineMagnitude,pass,1)) {
          if (ms_trace_dynamics[eTraceRefinements]) ms_logger.logData(result.str());
          fitToSpec(source.m_feedback,totalbits,fracbits);
          fitToSpec(source.m_observer,totalbits,fracbits);
          makeClosedLoop(source,closedLoop,useObserver,false,true);
          if (!closedLoop.isDivergent()) {
            std::string newresult=makeCEGISIterations(closedLoop,existing,max_iters,stage,pass,error);
            if (newresult.empty()) ms_logger.logData("OPTIMIZATION SUCCESS");
            return newresult;
          }
          else ms_logger.logData("divergent");
        }
        else if (func::isPositive(source.m_samplingCap) && func::isPositive(source.m_sampleTime-source.m_samplingCap)) {
          scalar scale=source.m_samplingCap/source.m_sampleTime;
          if (func::isPositive(scale-scalar(0.5))) scale=0.5;
          if (closedLoop.resample(scale)) {
            refineSampling(source,closedLoop,useObserver);
            m_feedback=source.m_feedback;
            m_observer=source.m_observer;
            if (refineEigenvalues(source,closedLoop,useObserver && (stage<eRefineController),(ms_canonical==eCNFP) ? eRefinePhase : eRefineMagnitude,pass,1)) {
              ms_logger.logData(result.str());
              fitToSpec(source.m_feedback,totalbits,fracbits);
              fitToSpec(source.m_observer,totalbits,fracbits);
              makeClosedLoop(source,closedLoop,useObserver,false,true);
              if (!closedLoop.isDivergent()) {
                std::string newresult=makeCEGISIterations(closedLoop,existing,max_iters,stage,pass,error);
                return newresult;
              }
              else ms_logger.logData("divergent");
            }
          }
        }
      }
    }
  }
#else
  powerList counterexamples;
  std::vector<iteration_pair> pairs;
  bool fail=closedLoop.findCounterExampleIterations(counterexamples,bounds);
  if (fail && counterexamples.empty()) counterexamples[1]=std::pair<int,powerS>(-1,0);
  if (!counterexamples.empty()) {
    AbstractPolyhedra<scalar> &safe=closedLoop.m_safeReachTube.getPolyhedra();
    MatrixS vertices=closedLoop.m_initialState.getPolyhedra().getVertices();
    MatrixS inputVertices=closedLoop.getInputVertices(eEigenSpace,true);
    getIterationPairs(pairs,counterexamples,safe,vertices,inputVertices);
    powerS counterPoints[vertices.rows()+1][inputVertices.rows()+1];
    result << "#define POINTS_PER_ITER\n";
    result << "#define _NUM_ITERATIONS " << counterexamples.size() << "\n";
    int max_iters=0;
    result << "int iterations[_NUM_ITERATIONS]={";
    for (typename powerList::iterator it=counterexamples.begin();it!=counterexamples.end();it++) {
      if (it!=counterexamples.begin()) result << ",";
      result << it->first;
      if (it->first>max_iters) max_iters=it->first;
    }
    if (max_iters<existing) {
      counterexamples[existing]=std::pair<int,powerS>(-1,0);
      result << "," << existing;
      max_iters=existing;
    }
    existing=max_iters;
    result << "};\n";

    powerS failedIter=checkExplicitReachability(/*max_iters*/20,useObserver);
    result << "#define _MAX_ITERATIONS " << max_iters << "\n";
    ms_logger.logData(max_iters,"max iters",true);
    result << "int iter_vertices[_NUM_ITERATIONS][2]={";
    for (typename powerList::iterator it=counterexamples.begin();it!=counterexamples.end();it++) {
      if (it!=counterexamples.begin()) result << ",";
      MatrixS dynamics=closedLoop.getPseudoDynamics(it->first).transpose();
      if (ms_trace_dynamics[eTraceDynamics]) {
        ms_logger.logData(dynamics,"dynamics");
        ms_logger.logData(vertices,"vertices");
        ms_logger.logData(inputVertices,"inputVertices");
      }
      bool found=false;
      for (int i=0;i<vertices.rows();i++) {
        for (int j=0;j<inputVertices.rows();j++) {
          MatrixS point=(vertices.row(i)-inputVertices.row(j))*dynamics+inputVertices.row(j);
          //ms_logger.logData(point,"point");
          if (!safe.isInside(point)) {
            if (counterPoints[i][j]<it->first) counterPoints[i][j]=it->first;
            result << "{" << i << "," << j << "}";
            i=vertices.rows();
            found=true;
            break;
          }
        }
      }
      if (!found) result << "{0,0}";
    }
    result << "};\n";
  }
  else if (fail) {
    return "#define FAILED\n";
  }
#endif
  return result.str();
}

///Creates a c header file for CEGIS
template <class scalar>
bool Synthesiser<scalar>::makeCEGISFiles(bool observer)
{
  std::ofstream headerFile;
  headerFile.open("types.h");
  if (!headerFile.is_open()) return false;
  ms_logger.setPrecision(12);
  bool scaling=true;
  std::string data=makeCEGISHeader(observer,ms_logger.ms_traceIntervals,scaling);
  headerFile.write(data.data(),data.size());
  headerFile.close();
  data=makeCEGISDescription(observer,ms_logger.ms_traceIntervals,scaling);
  MatToStr<scalar> logger(12,defaultLeftBracket,defaultRightBracket,", ","; ");
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  std::string final_observer;
  std::string final_controller="controller="+logger.MatToString(source.m_feedback);
  if (observer) final_observer="observer="+logger.MatToString(source.m_observer);
  Implementation &implementation=m_implementation["implcbmc"];
  int intbits=implementation.intbits;
  int fracbits=implementation.fracbits;
  if (ms_bvType==eFixedBV) {
    while(fracbits>16) fracbits-=8;
  }
  else if (ms_bvType==eMixedBV) {
    if (intbits<=6) intbits=(1<<intbits);
    while(fracbits>16) fracbits-=8;
  }
  std::ifstream result_file;
  result_file.open("output.txt");
  std::string final_iters="synth_iterations=";
  std::string impl_header="implementation <";
  int iterations=0;
  if (result_file.is_open()) {
    std::string previous;
    bool sameK=false;
    bool sameL=!observer;
    while(std::getline(result_file,previous)) {
      if (previous.empty()) continue;
      if ((final_controller.compare(0,previous.length(),previous)==0) && !func::isZero(source.m_feedback.norm())) sameK=true;
      if (!final_observer.empty() && (final_observer.compare(0,previous.length(),previous)==0)) sameL=true;
      if (previous.compare(0,final_iters.length(),final_iters)==0) {
        size_t pos=final_iters.length();
        iterations=func::toInt(func::toCentre(ms_logger.getNumber(previous,pos)));
      }
      else if (previous.compare(0,impl_header.length(),impl_header)==0) {
        size_t pos=impl_header.length();
        int final_intbits=func::toInt(func::toCentre(ms_logger.getNumber(previous,pos)));
        pos++;
        int final_fracbits=func::toInt(func::toCentre(ms_logger.getNumber(previous,pos)));
        if (final_intbits>intbits) intbits=final_intbits;
        if (final_fracbits>fracbits) fracbits=final_fracbits;
      }
    }
    if (sameK && sameL && ((intbits+fracbits)<=56)) {
      ms_logger.logData("No synthesis update");
      if ((ms_bvType>=eFixedBV) || (intbits<10)) intbits+=4;
      else fracbits+=4;
      fracbits+=4;
    }
  }
  int align=(intbits+fracbits)&7;
  if (align!=0) {
    ms_logger.logData(fracbits,"realigning ");
    ms_logger.logData(intbits,", given ",true);
    fracbits+=8-align;
  }
  int olditerations=iterations;
  m_refineCount=5;
  std::string iters=makeCEGISIterations(iterations,1000,(ms_canonical<=eCNFR) ? eRefineNone : ((ms_canonical==eCNFP) ? eRefinePhase : eRefineMagnitude));
  ms_logger.logData(iters);
  if ((iterations>0) && (iterations<=olditerations)&& ((intbits+fracbits)<=56)) {
    ms_logger.logData(iterations,"iteration check failed ");
    ms_logger.logData(olditerations," <= ",true);
    if ((ms_bvType>=eFixedBV) || (intbits<10)) intbits+=4;
    else fracbits+=4;
    fracbits+=4;
  }
  std::string final_impl="implementation <"+logger.MakeNumber(intbits)+","+logger.MakeNumber(fracbits)+">";
  std::string result=iters.empty() ? "SUCCESS\n" : "FAIL\n";
  result+=final_impl;
  result+="\nsampling = "+ms_logger.MakeNumber(source.m_sampleTime);
  if (!func::isZero(source.m_delayTime)) {
    result+=":"+ms_logger.MakeNumber(source.m_delayTime);
    if (func::isPositive(source.m_sampleTime-source.m_samplingCap) && func::isPositive(source.m_samplingCap)) result+=":"+ms_logger.MakeNumber(source.m_samplingCap);
  }
  result+=";\n";
  result+=final_controller;
  result+=final_observer;
  if (iterations>0) result+=final_iters+ms_logger.MakeNumber(iterations)+";\n";
  std::ofstream sucess_file;
  sucess_file.open("output.txt");
  if (!sucess_file.is_open()) return false;
  sucess_file.write(result.data(),result.size());
  data+=iters;
  sucess_file.close();
  std::ofstream file;
  file.open("system.h");
  if (!file.is_open()) return false;
  file.write(data.data(),data.size());
  file.close();
  return true;
}


#ifdef USE_LDOUBLE
  #ifdef USE_SINGLES
    template class Synthesiser<long double>;
  #endif
  #ifdef USE_INTERVALS
    template class Synthesiser<ldinterval>;
  #endif
#endif
#ifdef USE_MPREAL
  #ifdef USE_SINGLES
    template class Synthesiser<mpfr::mpreal>;
  #endif
  #ifdef USE_INTERVALS
    template class Synthesiser<mpinterval>;
  #endif
#endif

}
