#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.029355e-04),  interval(-1.029351e-01)},
{ interval(9.897607e-04),  interval(9.897568e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.897607e-04), interval(9.849243e-05)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.896539e-01,  9.849243e-05,  9.897607e-04},
{ -2.853564e-20,  9.897647e-07,  -9.897607e-04}};

#endif /*BENCHMARK_H_*/