#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000001e+00),  interval(1.562501e-03)},
{ interval(1.600001e-03),  interval(1.000001e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.000002e-04), interval(3.200001e-07)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -2.000003e+00,  3.200001e-07,  4.000002e-04},
{ 1,  3.200001e-07,  -4.000002e-04}};

#endif /*BENCHMARK_H_*/