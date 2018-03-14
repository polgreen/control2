#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-4.822853e-83),  interval(-2.820432e-83),  interval(5.799821e-98)},
{ interval(3.294437e-83),  interval(0),  interval(0)},
{ interval(0),  interval(3.294437e-83),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ 4.822853e-83,  2.500000e-01,  0,  0},
{ 9.291736e-166,  0,  8.236092e-84,  0},
{ -6.294728e-263,  0,  0,  2.713329e-166}};

#endif /*BENCHMARK_H_*/