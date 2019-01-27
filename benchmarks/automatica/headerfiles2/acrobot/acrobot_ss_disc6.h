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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(-1.567500e-08),  interval(5.000000e-05),  interval(-2.612500e-13)},
{ interval(-1.811250e-08),  interval(1.000000e+00),  interval(-3.018750e-13),  interval(5.000000e-05)},
{ interval(6.245000e-04),  interval(-6.270000e-04),  interval(1.000000e+00),  interval(-1.567500e-08)},
{ interval(-7.245000e-04),  interval(1.468000e-03),  interval(-1.811250e-08),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-3.725000e-09), interval(7.475000e-09), interval(-1.490000e-04), interval(2.990000e-04)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000000e+00,  2.990000e-04,  -1.490000e-04,  7.475000e-09,  -3.725000e-09},
{ 6.000000e+00,  -8.970000e-04,  4.470000e-04,  -7.475000e-09,  3.725000e-09},
{ -4.000000e+00,  8.970000e-04,  -4.470000e-04,  -7.475000e-09,  3.725000e-09},
{ 1.000000e+00,  -2.990000e-04,  1.490000e-04,  7.475000e-09,  -3.725000e-09}};

#endif /*BENCHMARK_H_*/