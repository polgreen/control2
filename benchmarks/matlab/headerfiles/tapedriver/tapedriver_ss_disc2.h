#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.490058e-09),  interval(8.317668e-09),  interval(5.773992e-09)},
{ interval(-1.291620e-08),  interval(-1.670966e-08),  interval(-8.000363e-09)},
{ interval(8.948255e-09),  interval(8.921712e-09),  interval(3.577775e-10)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.009078e-10), interval(1.398165e-10), interval(1.747627e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ 1.086183e-08,  1.747627e-02,  1.398165e-10,  -1.009078e-10},
{ 3.139133e-17,  1.960768e-10,  -1.398165e-10,  1.009078e-10},
{ -6.070745e-39,  2.743016e-19,  -5.357453e-19,  5.231888e-19}};

#endif /*BENCHMARK_H_*/