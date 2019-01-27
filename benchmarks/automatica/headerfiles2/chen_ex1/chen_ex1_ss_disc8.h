#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999700e-01),  interval(-1.374981e-05),  interval(-7.499888e-06)},
{ interval(1.999970e-05),  interval(1.000000e+00),  interval(-7.499925e-11)},
{ interval(4.999950e-11),  interval(5.000000e-06),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499963e-06), interval(2.499975e-11), interval(4.166635e-17)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999970e+00,  4.166635e-17,  2.499975e-11,  2.499963e-06},
{ 2.999940e+00,  1.666642e-16,  -2.499963e-16,  -4.999925e-06},
{ -9.999700e-01,  4.166573e-17,  -2.499950e-11,  2.499963e-06}};

#endif /*BENCHMARK_H_*/