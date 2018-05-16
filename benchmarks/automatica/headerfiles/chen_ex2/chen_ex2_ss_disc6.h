#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.837652e+00),  interval(-6.718540e+00),  interval(3.290869e+00),  interval(-2.014842e+00),  interval(1.578942e+00),  interval(-7.733144e-01),  interval(4.328351e-01),  interval(-2.119734e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.837652e+00,  1,  0,  0,  0,  0,  0,  0,  0},
{ 2.687416e+01,  0,  4,  0,  0,  0,  0,  0,  0},
{ -5.265391e+01,  0,  0,  16,  0,  0,  0,  0,  0},
{ 6.447496e+01,  0,  0,  0,  32,  0,  0,  0,  0},
{ -5.052615e+01,  0,  0,  0,  0,  32,  0,  0,  0},
{ 2.474606e+01,  0,  0,  0,  0,  0,  32,  0,  0},
{ -6.925362e+00,  0,  0,  0,  0,  0,  0,  16,  0},
{ 8.478937e-01,  0,  0,  0,  0,  0,  0,  0,  4}};

#endif /*BENCHMARK_H_*/