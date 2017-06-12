#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 1.500000e+00 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 4 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(-6.845458e-09),  interval(-4.553329e-09),  interval(6.245010e-78),  interval(0)},
{ interval(7.450581e-09),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(7.450581e-09),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1.490116e-08),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(67108864)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ 6.845458e-09,  0,  0,  0,  67108864},
{ 3.392495e-17,  0,  0,  5.000000e-01,  0},
{ -3.466677e-94,  0,  3.725290e-09,  0,  0},
{ 0,  5.551115e-17,  0,  0,  0}};

#endif /*BENCHMARK_H_*/