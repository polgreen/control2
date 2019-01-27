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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.994751e-01),  interval(-1.011738e-04),  interval(-1.996276e-05)},
{ interval(1.249672e-04),  interval(1.000000e+00),  interval(-1.247782e-09)},
{ interval(1.952783e-09),  interval(3.125000e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.124180e-05), interval(1.952783e-09), interval(2.034238e-14)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999475e+00,  2.034238e-14,  1.952783e-09,  3.124180e-05},
{ 2.998950e+00,  8.135885e-14,  -3.417072e-13,  -6.248360e-05},
{ -9.994751e-01,  2.033704e-14,  -1.952442e-09,  3.124180e-05}};

#endif /*BENCHMARK_H_*/