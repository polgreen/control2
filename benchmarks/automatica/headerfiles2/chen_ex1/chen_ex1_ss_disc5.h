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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.994001e-01),  interval(-2.749250e-04),  interval(-1.499550e-04)},
{ interval(3.998800e-04),  interval(9.999999e-01),  interval(-2.999400e-08)},
{ interval(1.999600e-08),  interval(1.000000e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.998500e-05), interval(9.998000e-09), interval(3.332833e-13)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999400e+00,  3.332833e-13,  9.998000e-09,  4.998500e-05},
{ 2.998800e+00,  1.332933e-12,  -1.999400e-12,  -9.997000e-05},
{ -9.994002e-01,  3.331834e-13,  -9.996001e-09,  4.998500e-05}};

#endif /*BENCHMARK_H_*/