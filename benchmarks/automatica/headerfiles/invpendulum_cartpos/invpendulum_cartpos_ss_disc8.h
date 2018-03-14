#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)100
#define INPUT_LOWERBOUND (__plant_precisiont)-100
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.000000e+00),  interval(-3.000000e+00),  interval(1.000000e+00),  interval(-5.000000e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.629395e-06), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000000e+00,  7.629395e-06,  0,  0,  0},
{ 6.000001e+00,  0,  1.525879e-05,  0,  0},
{ -4.000000e+00,  0,  0,  3.051758e-05,  0},
{ 1,  0,  0,  0,  1.525879e-05}};

#endif /*BENCHMARK_H_*/