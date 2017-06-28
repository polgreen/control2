#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-03 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.869087e+00),  interval(-3.589310e+00),  interval(2.342185e+00),  interval(-8.599929e-01),  interval(3.369281e-01),  interval(-2.200734e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.768372e-07), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.869087e+00,  0,  0,  0,  0,  0,  4.768372e-07},
{ 1.435724e+01,  0,  0,  0,  0,  1.907349e-06,  0},
{ -1.873748e+01,  0,  0,  0,  3.814697e-06,  0,  0},
{ 1.375989e+01,  0,  0,  7.629395e-06,  0,  0,  0},
{ -5.390850e+00,  0,  7.629395e-06,  0,  0,  0,  0},
{ 8.802934e-01,  1.907349e-06,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/