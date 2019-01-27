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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999475e-01),  interval(-1.011974e-05),  interval(-1.996748e-06)},
{ interval(1.249967e-05),  interval(1.000000e+00),  interval(-1.247978e-11)},
{ interval(1.953091e-11),  interval(3.125000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.124918e-06), interval(1.953091e-11), interval(2.034479e-17)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999948e+00,  2.034479e-17,  1.953091e-11,  3.124918e-06},
{ 2.999895e+00,  8.137807e-17,  -3.417879e-16,  -6.249836e-06},
{ -9.999475e-01,  2.034425e-17,  -1.953057e-11,  3.124918e-06}};

#endif /*BENCHMARK_H_*/