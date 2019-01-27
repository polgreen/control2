#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 1 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = { interval(9.999500e-01)};
 const __plant_typet _controller_B[NSTATES] = {interval(3.124922e-05)};
const __plant_typet __char_poly_const[2][2] = 
 {{ 1,  0},
{ -9.999500e-01,  3.124922e-05}};

#endif /*BENCHMARK_H_*/