#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.794147e-01),  interval(0)},
{ interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.794147e-01,  2.500000e-01,  0},
{ 0,  0,  2.500000e-01}};

#endif /*BENCHMARK_H_*/