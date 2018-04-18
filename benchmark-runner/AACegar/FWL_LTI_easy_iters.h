#ifndef FWL_LTI_CONTROL_H
#define FWL_LTI_CONTROL_H

#include "FWL_LTI_transform.h"
vectort even_point,odd_point;

void make_closed_loop_dynamics()
{
  cnttype i,j;
  for (i=0;i<_DIMENSION;i++)
  {
    for (j=0;j<_DIMENSION;j++)
    {
      dynamics[i][j]-=sensitivity[i]*controller[j];
#ifndef __CPROVER
      printf("dynamics[%d][%d]==%f\n",i,j,dynamics[i][j]);
#endif
    }
  }
}

void checkEasyIteration(vectort src, vectort dest)
{
  cnttype i,j;
  for (i=0;i<_DIMENSION;i++)
  {
    dest[i]=dynamics[i][0]*src[0];
#ifndef __CPROVER
  printf("point src %d=%f\n",1,src[1]);
#endif
    for (j=1;j<_DIMENSION;j++)
    {
      dest[i]+=dynamics[i][j]*src[j];
#ifndef __CPROVER
  printf("point element %d=%f\n",i,dest[i]);
#endif
    }
#ifndef __CPROVER
  printf("point element %d=%f\n",i,dest[i]);
#endif
    verify_assume(dest[i]<1);
    verify_assume(dest[i]>-1);
  }
}

void checkEasyIterations(vectort init,control_floatt input,cnttype iter)
{
  cnttype i;
  checkEasyIteration(init, odd_point);
  iter>>=1;
  for (i=0;i<iter;i++)
  {
#ifndef __CPROVER
  printf("checking iter %d\n",2*i);
#endif
    checkEasyIteration(odd_point, even_point);
    checkEasyIteration(even_point, odd_point);
  }
}

void checkControlIterations()
{
  cnttype i;
#ifndef __CPROVER
  printf("checking iterations [%d]\n",_MIN_ITERATIONS);
#endif

  make_closed_loop_dynamics();
  for(i=0;i<_NUM_ITERATIONS;i++)
  {
    checkEasyIterations(vertices[iter_vertices[i][0]],input_values[0][0],_MIN_ITERATIONS/*iterations[i]*/);
  }
#ifndef __CPROVER
  printf("control iters checked\n");
#endif
}
#endif