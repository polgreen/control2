#include <assert.h>
#include <stdbool.h>

#include "FWL_LTI.h"
#include "types.h"
#include "system.h"
#if defined(__CPROVER) && !defined(_FIXEBV)
  typedef __CPROVER_floatbv[_EXP_BITS][_FRAC_BITS] controller_floatt;
#endif

void print_vector(char *name,vectort vector)
{
#ifndef __CPROVER
  cnttype i;
  printf("%s ",name);
  for (i=0;i<_DIMENSION;i++) printf("%f ", vector[i]);
  puts("");
#endif
}

void print_matrix(char *name,matrixt matrix)
{
#ifndef __CPROVER
  cnttype i,j;
  printf("%s ",name);
  for (i=0;i<_DIMENSION;i++) 
  {
    for (j=0;j<_DIMENSION;j++) printf("%f ", matrix[i][j]);
    printf(";");
  }
  puts("");
#endif
}

vectort plant_cbmc,controller_cbmc;
#ifdef _USE_OBSERVER
vectort observer_plant_cbmc,observer_cbmc;
#endif
matrixt transform_cbmc,observer_transform_cbmc;
matrixt loop_cbmc;

#include "FWL_LTI_FWL.h"
#include "FWL_LTI_nondet.h"
#include "FWL_LTI_stability.h"

#ifdef _NUM_ITERATIONS
  #include "FWL_LTI_control_iters.h"
  #ifdef _USE_OBSERVER
    #include "FWL_LTI_observer_iters.h"
  #endif
  #include "FWL_LTI_iters.h"
#endif

int initialization()
{
  #ifndef _CPROVER
    printf("initializing");
  #endif
  get_bounds();
  int result=validation();
  return result;
}

#ifndef __CPROVER 
void print_poly(control_floatt *pol,cnttype n)
{
  cnttype i;
  for (i=0;i<n;i++)
  {
    printf("%fz%d ", pol[i], n-i-1);
  }
  puts("");
}
#endif

// main
int main()
{
  cnttype i;
  int result=initialization();
#ifndef __CPROVER
  if (result!=0) return 10;
#endif
  make_closed_loop();
#ifndef __CPROVER
  print_matrix("dynamics",dynamics);
  print_matrix("loop",loop_cbmc);
#endif

#ifdef _USE_OBSERVER
  control_floatt observerControlError=0;
  for (i=0;i<_DIMENSION;i++) observerControlError+=observer[i]*observer[i];
  observerControlError=observer_output_sensitivity_error*observerControlError;
  observerControlError+=observer_dynamics_error;
  result=check_restricted_stability(observer_plant_cbmc,1.0/(1.0-observerControlError));
  
  if (result>0)
  {
    control_floatt observerInputError=0;
    for (i=0;i<_DIMENSION;i++) observerInputError+=controller[i]*controller[i];
    observerControlError+=observer_sensitivity_error*observerInputError;
    result=check_restricted_stability(plant_cbmc,speed_factor/(1.0-observerControlError));
  }
#else
  result=check_restricted_stability(plant_cbmc,speed_factor);
#endif

#ifndef __CPROVER
  printf("stability=%d\n",result);
#endif 
#ifdef _NUM_ITERATIONS
//  if (result>0) checkIterations(loop_cbmc);
  if (result>0) checkControlIterations();
#endif
#ifdef __CPROVER
  __CPROVER_array_copy(controller_cbmc, controller);
  #ifdef _USE_OBSERVER
    __CPROVER_array_copy(observer_cbmc, observer);
  #endif
  verify_assert(0);
#else
  printf("end\n");
  if (result != 0) return 10;
#endif
  return 0;
}
