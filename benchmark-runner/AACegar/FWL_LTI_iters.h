#if (_DIMENSION==2)
  #include "2Inverse.h"
#else
  #include "3Inverse.h"
#endif

#include "FWL_LTI_transform.h"

void simulate_observable(vectort point,vectort input,matrixt transform)
{

}

void powerMatrix(matrixt result,matrixt transform,int pow)
{
  cnttype i,j;
  matrixt temp;
  for (i=0;i<_DIMENSION;i++)
  {
    for (j=0;j<_DIMENSION;j++) temp[i][j]=transform[i][j];
  }
  if (pow&1)
  {
    for (i=0;i<_DIMENSION;i++)
    {
      for (j=0;j<_DIMENSION;j++) result[i][j]=transform[i][j];
    }
  }
  else
  {
    for (i=0;i<_DIMENSION;i++)
    {
      for (j=0;j<_DIMENSION;j++) result[i][j]=0;
      result[i][i]=1;  
    }      
  }
  while (pow >>= 1) {
    multiply(temp,temp);
    if (pow&1) multiply(result,transform);
  }
}

void accelerateInputs()
{
  cnttype i,j;
  matrixt mat_inv,matrix;
  for (i=0;i<_DIMENSION;i++)
  {
    for (j=0;j<_DIMENSION;j++) matrix[i][j]=-loop_cbmc[i][j];
    matrix[i][i]+=_one;
  }
#ifndef __CPROVER
  print_matrix("I-A",matrix);
#endif  
  inverse(mat_inv,matrix);
#ifndef __CPROVER
  print_matrix("inverse",mat_inv);
#endif  
  for (i=0;i<_NUM_INPUT_VERTICES;i++)
  {
    for (j=0;j<_DIMENSION;j++) accel_vertices[i][j]=input_vertices[i][j];
    for (j=0;j<_NUM_VECTORS;j++) accelsupports[i][j]=findSupport(accel_vertices[i],vectors[j]);
    transformPoint(accel_vertices[i],mat_inv);
  }
  
}
./axelerator -u -p -ii -mpi 256 -synth CEGIS -params "p=2,q=1,f=1,m=256:16:8" -dynamics "[0.90122,1.3429e-08;7.4506e-09,0]" -init "[cube<.5]" -isense "[128;0]" -inputs "[1>-1;1<1]" -sguard "[cube<1]" -control "[0]"
#ifdef _NUM_ITERATIONS

void checkIteration(vectort point,matrixt transform,int input_index)
{
  // Warning: point is being transformed here!
  cnttype i;
  transformPoint(point,transform);
#ifndef __CPROVER
    print_vector("point",point);
#endif

  for (i=0;i<_NUM_VECTORS;i++)
  {
    control_floatt value=findSupport(point,vectors[i])+accelsupports[input_index][i];
#ifndef __CPROVER
    printf("%f<%f\n",value,supports[i]);
#endif      
    verify_assume(value<supports[i]);
  }
}

void checkIterations(matrixt transform)
{
  matrixt matrix,temp;
  cnttype i,j,k;
#if (_NUM_INPUT_VERTICES>1)
  #ifndef __CPROVER
    printf("accel inputs\n");
  #endif  
  accelerateInputs();
  #ifndef __CPROVER
    for (i=0;i<_NUM_INPUT_VERTICES;i++) print_vector("input",accel_vertices[i]);
  #endif
  for (k=0;k<_NUM_INPUT_VERTICES;k++)
  {
    for (i=0;i<_NUM_VERTICES;i++)
    {
      #ifndef __CPROVER
        print_vector("init",vertices[i]);
      #endif
      #ifdef POINTS_PER_ITER
        bool skip=true;
        for (j=0;j<_NUM_ITERATIONS;j++)
        {
           if ((iter_vertices[j][0]==i) && (iter_vertices[j][1]==k)) skip=false;
        }
        if (skip) continue;
      #endif  
      for (j=0;j<_DIMENSION;j++) reach_vertices[k][i][j]=vertices[i][j]-accel_vertices[k][j];
      checkIteration(reach_vertices[k][i],transform,k);
    }
  }
#else
  for (j=0;j<_NUM_VECTORS;j++) accelsupports[0][j]=0;
  #ifndef __CPROVER
    printf("no inputs\n");
  #endif
  for (i=0;i<_NUM_VERTICES;i++)
  {
    #ifdef POINTS_PER_ITER
      bool skip=true;
      for (j=0;j<_NUM_ITERATIONS;j++)
      {
         if (iter_vertices[j][0]==i) skip=false;
      }
      if (skip) continue;
    #endif  
    for (j=0;j<_DIMENSION;j++) reach_vertices[0][i][j]=vertices[i][j];
    checkIteration(reach_vertices[0][i],transform,0);
  }
#endif
  for (i=0;i<_DIMENSION;i++)
  {
    for (j=0;j<_DIMENSION;j++) matrix[i][j]=transform[i][j];
  }
  int lastIteration=1;
  for(i=0;i<_NUM_ITERATIONS;i++)
  {
    powerMatrix(temp,transform,iterations[i]-lastIteration);
    multiply(matrix,temp);
    #ifndef __CPROVER
      printf("iter %d\n",iterations[i]);
      print_matrix("matrix",matrix);
    #endif
    #if (_NUM_INPUT_VERTICES>1)
      for (k=0;k<_NUM_INPUT_VERTICES;k++)
      {
        #ifdef POINTS_PER_ITER
          if (iter_vertices[i][1]!=k) continue;
        #endif
        for (j=0;j<_NUM_VERTICES;j++) 
        {
          #ifdef POINTS_PER_ITER
            if (iter_vertices[i][0]!=k) continue;
          #endif
          checkIteration(reach_vertices[k][j],matrix,k);
        }
      }
    #else
      for (j=0;j<_NUM_VERTICES;j++) checkIteration(reach_vertices[0][j],matrix,0);      
    #endif
    lastIteration=iterations[i];
  }
#ifndef __CPROVER
  printf("iters checked\n");
#endif
}
#endif