#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 5.000000e-03 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 8 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(7.837652e+00),  interval(-3.359270e+00),  interval(1.645435e+00),  interval(-1.007421e+00),  interval(7.894712e-01),  interval(-3.866572e-01),  interval(2.164176e-01),  interval(-2.119734e-01)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.837652e+00,  0,  0,  0,  0,  0,  0,  0,  1},
{ 2.687416e+01,  0,  0,  0,  0,  0,  0,  8,  0},
{ -5.265391e+01,  0,  0,  0,  0,  0,  32,  0,  0},
{ 6.447496e+01,  0,  0,  0,  0,  64,  0,  0,  0},
{ -5.052615e+01,  0,  0,  0,  64,  0,  0,  0,  0},
{ 2.474606e+01,  0,  0,  64,  0,  0,  0,  0,  0},
{ -6.925362e+00,  0,  32,  0,  0,  0,  0,  0,  0},
{ 8.478937e-01,  4,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/