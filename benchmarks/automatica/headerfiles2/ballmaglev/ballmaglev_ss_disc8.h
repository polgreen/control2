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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(5.000000e-06),  interval(-4.258578e-10)},
{ interval(8.761062e-03),  interval(1.000000e+00),  interval(-1.703377e-04)},
{ interval(0),  interval(0),  interval(9.998087e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.364951e-15), interval(-8.189573e-10), interval(9.614465e-06)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999809e+00,  9.614465e-06,  -8.189573e-10,  -1.364951e-15},
{ 2.999617e+00,  -1.922893e-05,  5.223311e-14,  -5.459541e-15},
{ -9.998087e-01,  9.614465e-06,  8.189051e-10,  -1.364820e-15}};

#endif /*BENCHMARK_H_*/