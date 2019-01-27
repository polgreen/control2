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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999958e-01),  interval(1.679897e-07),  interval(-3.959992e-06)},
{ interval(4.999990e-06),  interval(1.000000e+00),  interval(-9.899986e-12)},
{ interval(1.249998e-11),  interval(5.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599997e-04), interval(3.999994e-10), interval(6.666660e-16)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999996e+00,  6.666660e-16,  3.999994e-10,  1.599997e-04},
{ 2.999992e+00,  2.666661e-15,  -5.599988e-16,  -3.199993e-04},
{ -9.999958e-01,  6.666646e-16,  -3.999989e-10,  1.599997e-04}};

#endif /*BENCHMARK_H_*/