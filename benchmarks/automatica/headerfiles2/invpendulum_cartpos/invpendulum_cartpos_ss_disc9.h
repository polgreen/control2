#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(1.000000e-06),  interval(0),  interval(0)},
{ interval(1.000000e-06),  interval(1.000000e+00),  interval(0),  interval(0)},
{ interval(5.000000e-13),  interval(1.000000e-06),  interval(1),  interval(0)},
{ interval(1.666667e-19),  interval(5.000000e-13),  interval(1.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.000000e-06), interval(5.000000e-13), interval(1.666667e-19), interval(4.166667e-26)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000000e+00,  4.166667e-26,  1.666667e-19,  5.000000e-13,  1.000000e-06},
{ 6.000000e+00,  4.583333e-25,  5.000000e-19,  -5.000000e-13,  -3.000000e-06},
{ -4.000000e+00,  4.583333e-25,  -5.000000e-19,  -5.000000e-13,  3.000000e-06},
{ 1,  4.166667e-26,  -1.666667e-19,  5.000000e-13,  -1.000000e-06}};

#endif /*BENCHMARK_H_*/