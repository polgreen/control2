#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.954366e+00),  interval(-4.454575e+00),  interval(2.585434e+00),  interval(-1.929364e+00),  interval(1.919741e+00),  interval(-1.273471e+00),  interval(5.430738e-01),  interval(-2.701995e-01),  interval(2.389994e-01)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.768372e-07), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ 8.954366e+00,  0,  0,  0,  0,  0,  0,  0,  0,  -4.768372e-07},
{ -3.563660e+01,  0,  0,  0,  0,  0,  0,  0,  -3.814697e-06,  0},
{ 8.273389e+01,  0,  0,  0,  0,  0,  0,  -1.525879e-05,  0,  0},
{ -1.234793e+02,  0,  0,  0,  0,  0,  -3.051758e-05,  0,  0,  0},
{ 1.228634e+02,  0,  0,  0,  0,  -3.051758e-05,  0,  0,  0,  0},
{ -8.150214e+01,  0,  0,  0,  -3.051758e-05,  0,  0,  0,  0,  0},
{ 3.475673e+01,  0,  0,  -3.051758e-05,  0,  0,  0,  0,  0,  0},
{ -8.646384e+00,  0,  -1.525879e-05,  0,  0,  0,  0,  0,  0,  0},
{ 9.559975e-01,  -1.907349e-06,  0,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/