#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000125e+00),  interval(1.562565e-02)},
{ interval(1.600067e-02),  interval(1.000125e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.000167e-03), interval(3.200067e-05)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -2.000250e+00,  3.200067e-05,  4.000167e-03},
{ 1,  3.200067e-05,  -4.000167e-03}};

#endif /*BENCHMARK_H_*/