#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(-1.567500e-10),  interval(5.000000e-06),  interval(-2.612500e-16)},
{ interval(-1.811250e-10),  interval(1.000000e+00),  interval(-3.018750e-16),  interval(5.000000e-06)},
{ interval(6.245000e-05),  interval(-6.270000e-05),  interval(1.000000e+00),  interval(-1.567500e-10)},
{ interval(-7.245000e-05),  interval(1.468000e-04),  interval(-1.811250e-10),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-3.725000e-11), interval(7.475000e-11), interval(-1.490000e-05), interval(2.990000e-05)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000000e+00,  2.990000e-05,  -1.490000e-05,  7.475000e-11,  -3.725000e-11},
{ 6.000000e+00,  -8.970000e-05,  4.470000e-05,  -7.475000e-11,  3.725000e-11},
{ -4.000000e+00,  8.970000e-05,  -4.470000e-05,  -7.475000e-11,  3.725000e-11},
{ 1.000000e+00,  -2.990000e-05,  1.490000e-05,  7.475000e-11,  -3.725000e-11}};

#endif /*BENCHMARK_H_*/