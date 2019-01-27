#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.997900e-01),  interval(8.374370e-06),  interval(-1.979792e-04)},
{ interval(2.499738e-04),  interval(1.000000e+00),  interval(-2.474827e-08)},
{ interval(3.124781e-08),  interval(2.500000e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.999160e-03), interval(9.999300e-07), interval(8.332896e-11)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999790e+00,  8.332896e-11,  9.999300e-07,  7.999160e-03},
{ 2.999580e+00,  3.332983e-10,  -6.999265e-11,  -1.599832e-02},
{ -9.997900e-01,  8.332021e-11,  -9.998600e-07,  7.999160e-03}};

#endif /*BENCHMARK_H_*/