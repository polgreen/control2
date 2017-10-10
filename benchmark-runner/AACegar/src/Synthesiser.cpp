#include "Synthesiser.h"
#include <boost/timer.hpp>
#include <set>
#include <Eigen/QR>
#include <Eigen/Eigenvalues>

namespace abstract{

/// Constructs an empty buffer
template<class scalar>
Synthesiser<scalar>::Synthesiser(int dimension,int idimension) :
  CegarSystem<scalar>(dimension,idimension),
  m_closedLoop(dimension),
  m_synthType(eEigenSynth)
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
    if (ms_trace_dynamics>=eTraceDynamics) {
      result.logTableau("Transformed Synth inputs");
    }
    result.retemplate(templates,-tightness);
    m_reachTime=time+timer.elapsed()*1000;;
    result.setCalculationTime(time);
    if (ms_trace_time) ms_logger.logData(m_reachTime,"Synthesis Time: ",true);
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
    if (ms_trace_dynamics>=eTraceAbstraction) ms_logger.logData(m_accelInSupports,"Input Supports",true);
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
bool Synthesiser<scalar>::makeClosedLoop(bool useObserver,bool makeReference,bool makeNoise)
{
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  if (source.m_feedback.rows()!=m_feedback.rows()) source.m_feedback=m_feedback;
  if (source.m_observer.rows()!=m_observer.rows()) source.m_feedback=m_observer;
  MatrixS feedbackDynamics=source.m_sensitivity.block(0,0,m_dimension,m_fdimension)*m_feedback;
  if ((m_synthType!=eObserverSynth) && (source.m_outputSensitivity.cols()>0)) feedbackDynamics*=source.m_outputSensitivity;
  MatrixS dynamics=source.m_dynamics-feedbackDynamics;
  int fdimension= (makeReference || (m_reference.getDimension()>0)) ? 0 : m_fdimension;
  MatrixS sensitivity=source.m_sensitivity.block(0,fdimension,m_dimension,m_idimension-fdimension);
  m_closedLoop.setInputType(eParametricInputs);
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
  if (ms_trace_dynamics>=eTraceDynamics) {
    ms_logger.logData(dynamics,"Loading Closed Loop");
  }
  m_closedLoop.setParams(m_paramValues);
  m_closedLoop.changeDimensions(dynamics.rows(),sensitivity.cols(),0,0);
  bool result=m_closedLoop.load(dynamics,sensitivity,guard,init,inputs,safe);
  if (result && (ms_trace_dynamics>=eTraceDynamics)) {
    ms_logger.logData(m_closedLoop.getDescription());
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

// Processes a problem stated by the inut options
template <class scalar>
int Synthesiser<scalar>::processOptions(optionList_t &options,displayType_t displayType,space_t space,bool interval,bool run)
{
  if (options.size()<=0) return 0;
  boost::timer timer;
  if (options[eParamStr].size()>0) {
    if (ms_logger.StringToDim(m_paramValues,options[eParamStr])<0) return -1;
    if (m_paramValues.coeff(eNumBits,0)>0) {
      functions<mpfr::mpreal>::setDefaultPrec(m_paramValues.coeff(eNumBits,0));
    }
    traceDynamics((traceDynamics_t)m_paramValues.coeff(eTraceLevel,0));
    traceSimplex((traceTableau_t)(m_paramValues.coeff(eTraceLevel,1)/10),(tracePivots_t)(m_paramValues.coeff(eTraceLevel,1)%10),(traceVertices_t)m_paramValues.coeff(eTraceLevel,2));
    if (m_paramValues.coeff(eNumStates,0)>0) changeDimensions(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0),m_paramValues.coeff(eNumOutputs,0),m_paramValues.coeff(eNumFeedbacks,0));
    m_sensitivity.conservativeResize(m_paramValues.coeff(eNumStates,0),m_paramValues.coeff(eNumInputs,0)+m_paramValues.coeff(eNumVarInputs,0));
    m_inputType=(m_paramValues.coeff(eNumVarInputs,0)>0) ? eVariableInputs : ((m_paramValues.coeff(eNumInputs,0)>0) ? eParametricInputs : eNoInputs);
    if (m_paramValues.coeff(eNumInputs,2)+m_paramValues.coeff(eNumVarInputs,1)>0) m_inputType=eVariableOnlyInputs;
  }
  else if (run && (m_dimension==0)) processError("no parameters");
  if ((options[eRandStr].size()>0) && (options[eParamStr].size()>0)) {
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
  if (options[eSampleStr].size()>0) {
    m_sampled.copy(*this);
    m_sampled.sample(options[eSampleStr]);
  }
  else m_sampled.m_dimension=0;
  if (options[eSpeedStr].size()>0) { setSpeed(options[eSpeedStr]); }
  if ((options[eControlStr].size()>0) && (loadController(options[eControlStr])<0))      return -1;
  if (run) {
    if ((m_synthType<eCEGISSynth) && (options[eSampleStr].size()>0)) {
      m_sampled.process(displayType,space,interval);
    }
    else {
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
        for (tightness=minTightness;tightness<=maxTightness;tightness+=stepTightness) {
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
int Synthesiser<scalar>::loadController(const std::string &data,size_t pos)
{
  boost::timer timer;
  commands_t command;
  pos=ms_logger.getCommand(command,data,pos);
  bool ioFeedback=(m_odimension>0) && (m_synthType!=eObserverSynth);
  m_feedback.resize(m_idimension,ioFeedback ? m_odimension : m_dimension);
  size_t result=ms_logger.StringToMat(m_feedback,data,pos);
  if (result>0) makeClosedLoop();
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Controller time:",true);
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
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Observer time:",true);
  return result;
}

/// Loads a reference input set for the system
template <class scalar>
int Synthesiser<scalar>::loadReference(const std::string &data,size_t pos,bool vertices)
{
  boost::timer timer;
  int result=m_reference.loadData(data,vertices,pos);
  if (ms_trace_time) ms_logger.logData(timer.elapsed()*1000,"Reference time:",true);
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
  if (ms_fixedBVs) {
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

///Creates a c header file for CEGIS
template <class scalar>
std::string Synthesiser<scalar>::makeCEGISDescription(bool observer,bool intervals,bool scaling)
{
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  std::stringstream result;
  source.makeReachabilityMatrices(observer);
  MatrixS TinvW=observer ? source.m_T*source.m_invW : source.m_T;
  MatrixS controllable=source.m_T*source.m_dynamics*source.m_invT;
  if (ms_trace_dynamics>=eTraceDynamics) {
    ms_logger.logData(controllable,"Controllable");
  }
  MatrixS coefficients=-controllable.row(0);
  int totalbits=m_paramValues.coeff(eNumBits,1);
  int fracbits=m_paramValues.coeff(eNumBits,2);
  int multbits=0;
  if (totalbits<=0) {
    totalbits=m_paramValues.coeff(eNumBits,0);
    if (totalbits<=0) totalbits=func::getDefaultPrec();
    fracbits=totalbits;
  }
  else if (fracbits==0) {
    refScalar max=m_sampled.findMaxValue(observer);
    max=findMaxValue(coefficients,max);
    int intbits=getBits(max);
    fracbits=totalbits-intbits;
  }
  if (!m_outputGuard.isEmpty()) {
    source.m_safeReachTube.bitConstrain(totalbits-fracbits);
    source.m_initialState.bitConstrain(totalbits-fracbits-1);
  }
  bool useObserver=!func::isZero(m_observer.norm());
  scalar speedFactor=func::ms_1;
  if (ms_canonical) {
    source.m_feedback=-source.m_feedback*source.m_T;
    if (useObserver) source.m_observer=-source.m_invW*m_observer;
  }
  fitToSpec(source.m_feedback,totalbits,fracbits);
  if (useObserver) fitToSpec(source.m_observer,totalbits,fracbits);
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
  AbstractPolyhedra<scalar> K=source.getControllerInBounds(source.m_safeReachTube.getPolyhedra());
  AbstractPolyhedra<scalar> KS=source.getControllerStabilityBounds(coefficients);
  KS.mirror();
  AbstractPolyhedra<scalar> KSC(KS);
  KSC.transform(source.m_T.transpose(),source.m_invT.transpose());
  AbstractPolyhedra<scalar> KO(KS);
  AbstractPolyhedra<scalar> KC(K);
  KC.transform(source.m_invT.transpose(),source.m_T.transpose());
  KC.intersect(KS);
  K.intersect(KSC);
  AbstractPolyhedra<scalar> KSO(KO);
  KSO.transform(source.m_invW,source.m_W);
  if (m_paramValues.coeff(eTightness,0)>=0) {
    AbstractPolyhedra<scalar> L(m_dimension);
    L.loadData("cube<"+ms_logger.MakeNumber(1<<(totalbits+m_paramValues.coeff(eTightness,0)-fracbits-getBits(m_initialOutputs))));
    KSO.intersect(L);
    L.transform(source.m_W,source.m_invW);
    KO.intersect(L);
  }
  AbstractPolyhedra<scalar> KW(K);
  KW.transform(source.m_invW.transpose(),source.m_W.transpose());
  AbstractPolyhedra<scalar> KTW(KC);
  KTW.transform(TinvW.transpose(),ms_emptyMatrix);
  KSO.normalise();
  KO.normalise();
  KW.normalise();
  K.toOuter(true);
  KC.toOuter(true);
  KSO.toOuter(true);
  KO.toOuter(true);

  if (!func::isZero(source.m_feedback.norm()) && makeClosedLoop(useObserver,false,true) && m_closedLoop.isDivergent(false,getSpeed())) {
    refScalar max=func::toUpper(m_closedLoop.largestEigenNorm());
    MatrixS nudge=m_closedLoop.capEigenValues(getSpeed(),useObserver,false);
    MatrixS controller=coefficients-nudge.block(0,0,1,m_dimension);
    bool keepNudge=KC.isInside(controller);
    if (keepNudge) source.m_feedback=controller*source.m_T;
    if (useObserver) {
      MatrixS observer=coefficients-nudge.block(0,m_dimension,1,m_dimension);
      keepNudge&=KO.isInside(observer);
      if (keepNudge) source.m_observer=source.m_invW*observer;
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
  else if (!func::isZero(getSpeed())) speedFactor/=getSpeed();
  int Kbits=getBits(K);
  if (Kbits>(totalbits-fracbits)) Kbits=totalbits-fracbits;
  int KSObits=getBits(KSO);
  int KCbits=getBits(KC);
  int KObits=getBits(KO);
  int KWbits=getBits(KW);
  int KTWbits=getBits(KTW);
  refScalar max=m_sampled.findMaxValue(observer,false);
  max=findMaxValue(coefficients,max);
  int Dbits=getBits(max);
  int Sbits=getBits(m_sampled.findMaxValue(false,true));
  makeimplt(result, "impl",totalbits-fracbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implK",Kbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implL",KSObits,fracbits,totalbits-fracbits);
  makeimplt(result, "implKT",KCbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implKW",KWbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implKTW",KTWbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implLW",KObits,fracbits,totalbits-fracbits);
  makeimplt(result, "implD",Dbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implS",Sbits,fracbits,totalbits-fracbits);
  makeimplt(result, "implTW",multbits,fracbits,totalbits-fracbits);
  int cbmcbits=1;
  for (std::map<std::string, Implementation>::iterator it=m_implementation.begin();it!=m_implementation.end();it++) {
    if (it->second.intbits>cbmcbits) cbmcbits=it->second.intbits;
  }
  int cbmcfracbits=totalbits-cbmcbits;
  cbmcbits*=2;
  int align=(cbmcbits+cbmcfracbits)&7;
  if (align!=0) cbmcfracbits+=8-align;
  makeimplt(result, "implcbmc",cbmcbits,cbmcfracbits,64);
  result << "struct coefft ";
  result << ms_logger.MatToC("plant",coefficients,intervals,func::ms_0);
  maketransformt(result,"transform",source.m_invT,scaleInvT,intervals);
  maketransformt(result,"pretransform",source.m_T,scaleT,intervals);
  result << "control_floatt speed_factor=" << ms_logger.MakeNumber(speedFactor) << ";\n";
  if (observer) {
    result << "control_floatt observer_speed_factor=" << ms_logger.MakeNumber(scalar(2)*speedFactor) << ";\n";
    if (ms_trace_dynamics>=eTraceDynamics) {
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
    result << "control_floatt observer_dynamics_error=" << ms_logger.MakeNumber(source.m_observerDynamicsError) << ";\n";
    result << "control_floatt observer_sensitivity_error=" << ms_logger.MakeNumber(source.m_observerSensitivityError) << ";\n";
    result << "control_floatt observer_output_sensitivity_error=" << ms_logger.MakeNumber(source.m_observerOutputSensitivityError) << ";\n";
  }

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
  result << ms_logger.IneToC("verify_assume","(control_floatt)","controller_cbmc",KS.getFaceDirections(),KS.getSupports(),false,false) << ";\n";
  result << ms_logger.IneToC("verify_assume","(control_floatt)","observer_cbmc",KO.getFaceDirections(),KO.getSupports(),false,false) << ";\n";
  result << "}\n";
  result << "  #else\n";
  result << "void boundController()\n{\n";
  result << ms_logger.IneToC("verify_assume","(control_floatt)","controller",K.getFaceDirections(),K.getSupports()) << ";\n";
  result << ms_logger.IneToC("verify_assume","(control_floatt)","observer",KSO.getFaceDirections(),KSO.getSupports()) << ";\n";
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

///Creates a list of iterations to check with CEGIS
template <class scalar>
std::string Synthesiser<scalar>::makeCEGISIterations(std::string &existing)
{
  std::stringstream result;
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  if (func::isZero(m_feedback.norm())) return "#define NO_FEEDBACK\n";
  bool useObserver=!func::isZero(m_observer.norm());
  makeClosedLoop(useObserver,false,true);
  if (m_closedLoop.isDivergent()) return "#define DIVERGENT\n";
  AbstractPolyhedra<scalar>& dynamics=m_closedLoop.getRefinedDynamics(4,true);
  AbstractPolyhedra<scalar> bounds;
  m_closedLoop.synthesiseDynamicBounds(bounds,m_inputType,m_closedLoop.m_safeReachTube.getPolyhedra(eEigenSpace));

  powerList counterexamples;
  bool fail=m_closedLoop.findCounterExampleIterations(counterexamples,bounds);
  if (fail && counterexamples.empty()) counterexamples[1]=std::pair<int,powerS>(-1,0);
  if (!counterexamples.empty()) {
    scalar distance=bounds.violatingDistance(dynamics.getVertices());
    ms_logger.logData(distance,"max distance: ",true);
    AbstractPolyhedra<scalar> &safe=m_closedLoop.m_safeReachTube.getPolyhedra();
    MatrixS vertices=m_closedLoop.m_initialState.getPolyhedra().getVertices();
    MatrixS inputVertices=m_closedLoop.getInputVertices(eEigenSpace,true);
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
    result << "};\n";

    MatrixS T=source.getReachableCanonicalTransformMatrix();
    if (useObserver) {
      MatrixS W=source.getObservableCanonicalTransformMatrix().inverse();
      T.conservativeResize(m_closedLoop.m_dimension,m_closedLoop.m_dimension);
      T.block(0,m_dimension,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
      T.block(m_dimension,0,m_dimension,m_dimension)=MatrixS::Zero(m_dimension,m_dimension);
      T.block(m_dimension,m_dimension,m_dimension,m_dimension)=W;
    }
    m_closedLoop.checkExplicitReachability(max_iters,T);
    result << "#define _MAX_ITERATIONS " << max_iters << "\n";
    result << "int iter_vertices[_NUM_ITERATIONS][2]={";
    for (typename powerList::iterator it=counterexamples.begin();it!=counterexamples.end();it++) {
      if (it!=counterexamples.begin()) result << ",";
      MatrixS dynamics=m_closedLoop.getPseudoDynamics(it->first).transpose();
      if (ms_trace_dynamics>eTraceDynamics) {
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
  std::string oldIters;
  std::string iters=makeCEGISIterations(oldIters);
  std::ofstream sucess_file;
  sucess_file.open("output.txt");
  if (!sucess_file.is_open()) return false;
  std::string result=iters.empty() ? "SUCCESS" : "FAIL";
  Implementation &implementation=m_implementation["implcbmc"];
  MatToStr<scalar> logger(12,defaultLeftBracket,defaultRightBracket,", ","; ");
  int fracbits=implementation.fracbits;
  while(fracbits>16) fracbits-=8;
  result+="\nimplementation <"+logger.MakeNumber(implementation.intbits)+","+logger.MakeNumber(fracbits)+">";
  CegarSystem<scalar> &source=(m_sampled.m_dimension==m_dimension) ? m_sampled : *this;
  result+="\nsampling = "+ms_logger.MakeNumber(source.m_sampleTime);
  if (!func::isZero(source.m_delayTime)) result+=":"+ms_logger.MakeNumber(source.m_delayTime);
  result+=";";
  result+="\ncontroller="+logger.MatToString(source.m_feedback);
  if (observer) result+="observer="+logger.MatToString(source.m_observer);
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
