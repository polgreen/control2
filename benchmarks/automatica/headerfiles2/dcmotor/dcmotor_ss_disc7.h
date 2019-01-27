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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.900488e-01),  interval(-1.034817e-03)},
{ interval(9.950161e-06),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.950161e-06), interval(4.983373e-11)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.990049e+00,  4.983373e-11,  9.950161e-06},
{ 9.900488e-01,  4.966788e-11,  -9.950161e-06}};

#endif /*BENCHMARK_H_*/