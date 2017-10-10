#ifndef FWL_LTI_CONTROL_H
#define FWL_LTI_CONTROL_H

#include "FWL_LTI_transform.h"
vectort plant_base;
vectort plant_radius;
vectort point;
vectort radius;

void makeControllablePlant()
{
  cnttype j;
  for (j=0;j<_DIMENSION;j++)
  {
    plant_base[j]=-plant_cbmc[j];
    if (plant_base[j]<0) plant_radius[j]=-plant_base[j];
    else plant_radius[j]=plant_base[j];
  }  
}

void checkControlIteration(vectort init,control_floatt input,cnttype iter)
{
  cnttype i,j;
  for (j=0;j<_DIMENSION;j++)
  {
    point[j]=init[j];
    radius[j]=0;
  }
  for (j=0;j<_DIMENSION;j++)
  {
    point[j]=init[j];
    radius[j]=0;
  }
  //transformPoint(point,transform);
  for (i=0;i<iter;i++)
  {
    control_floatt next=findSupport(plant_base,point);
    control_floatt next_radius=findSupport(plant_radius,radius);
    for (j=1;j<_DIMENSION;j++) 
    {
      point[j]=point[j-1];
      radius[j]=radius[j-1];
    }
    point[0]=next;
    radius[0]=next_radius+input;
    for (j=0;j<_NUM_VECTORS;j++)
    {
      control_floatt value=findSupport(point,transformed_vectors[j]);
      value+=findSupportRadius(radius,transformed_vectors[j]);
#ifndef __CPROVER
      printf("%f<%f\n",value,supports[j]);
#endif      
      verify_assume(value<supports[j]);
    }
  }
}

void checkControlIterations()
{
  cnttype i,j;
  makeControllablePlant();
  for(i=0;i<_NUM_ITERATIONS;i++)
  {
    checkControlIteration(transformed_vertices[iter_vertices[i][0]],input_values[0][0],iterations[i]);
  }
#ifndef __CPROVER
  printf("control iters checked\n");
#endif
}
#endif