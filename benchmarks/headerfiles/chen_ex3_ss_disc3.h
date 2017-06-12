#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 1.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 7 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(5.433322e+00),  interval(-3.203438e+00),  interval(2.125692e+00),  interval(-8.573825e-01),  interval(4.205040e-01),  interval(-2.322895e-01),  interval(1.115651e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0},
{ 5.433322e+00,  0,  0,  0,  0,  0,  0,  -1.250000e-01},
{ -1.281375e+01,  0,  0,  0,  0,  0,  -5.000000e-01,  0},
{ 1.700554e+01,  0,  0,  0,  0,  -1,  0,  0},
{ -1.371812e+01,  0,  0,  0,  -2,  0,  0,  0},
{ 6.728064e+00,  0,  0,  -2,  0,  0,  0,  0},
{ -1.858316e+00,  0,  -1,  0,  0,  0,  0,  0},
{ 2.231302e-01,  -2.500000e-01,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/