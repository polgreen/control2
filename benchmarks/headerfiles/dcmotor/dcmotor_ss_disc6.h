#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.948135e-01),  interval(-1.482388e-08)},
{ interval(7.450581e-09),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(128), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.948135e-01,  128,  0},
{ 1.104465e-16,  0,  9.536743e-07}};

#endif /*BENCHMARK_H_*/