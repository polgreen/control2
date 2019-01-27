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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.970031e-01),  interval(-1.373126e-03),  interval(-7.488758e-04)},
{ interval(1.997002e-03),  interval(9.999986e-01),  interval(-7.492504e-07)},
{ interval(4.995003e-07),  interval(4.999998e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.496253e-04), interval(2.497501e-07), interval(4.163543e-11)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.997002e+00,  4.163543e-11,  2.497501e-07,  2.496253e-04},
{ 2.994006e+00,  1.664169e-10,  -2.496253e-10,  -4.992505e-04},
{ -9.970045e-01,  4.157302e-11,  -2.495005e-07,  2.496253e-04}};

#endif /*BENCHMARK_H_*/