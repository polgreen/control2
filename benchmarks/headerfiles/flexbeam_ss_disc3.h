#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 1.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 6 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(2.768515e+00),  interval(-1.411764e+00),  interval(4.976521e-01),  interval(-6.224860e-01),  interval(6.148870e-01),  interval(-4.525997e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.768515e+00,  0,  0,  0,  0,  0,  1.250000e-01},
{ 2.823527e+00,  0,  0,  0,  0,  2.500000e-01,  0},
{ -1.990608e+00,  0,  0,  0,  5.000000e-01,  0,  0},
{ 2.489944e+00,  0,  0,  5.000000e-01,  0,  0,  0},
{ -2.459548e+00,  0,  5.000000e-01,  0,  0,  0,  0},
{ 9.051994e-01,  2.500000e-01,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/