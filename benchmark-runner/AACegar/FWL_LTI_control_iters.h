#ifndef FWL_LTI_CONTROL_H
#define FWL_LTI_CONTROL_H

#include "FWL_LTI_transform.h"

void checkControlIteration(vectort init,control_floatt input,cnttype iter)
{
  cnttype i,j;
  vectort point;
  vectort radius;
  vectort plant_radius;
  for (j=0;j<_DIMENSION;j++)
  {
    point[j]=init[j];
    radius[j]=0;
    if (plant_cbmc[j]<0) plant_radius[j]=-plant_cbmc[j];
    else plant_radius[j]=plant_cbmc[j];
  }
  //transformPoint(point,transform);
  for (i=0;i<iter;i++)
  {
    control_floatt next=findSupport(plant_cbmc,point);
    control_floatt next_radius=findSupport(plant_radius,radius);
    for (j=1;j<_DIMENSION;j++) 
    {
      point[j]=point[j-1];
      radius[j]=radius[j-1];
    }
    point[0]=next;
    radius[0]=next_radius+input;
    for (i=0;i<_NUM_VECTORS;i++)
    {
      control_floatt value=findSupport(point,transformed_vectors[i]);
#ifndef __CPROVER
      printf("%f<%f\n",value,supports[i]);
#endif      
      verify_assume(value<supports[i]);
    }
  }
}

void checkControlIterations()
{
  cnttype i;
  for(i=0;i<_NUM_ITERATIONS;i++)
  {
    checkControlIteration(transformed_vertices[iter_vertices[i][0]],input_values[0][0],iterations[i]);
  }
#ifndef __CPROVER
  printf("control iters checked\n");
#endif
}
#endif