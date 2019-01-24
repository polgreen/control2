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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999940e-01),  interval(-2.749993e-06),  interval(-1.499996e-06)},
{ interval(3.999988e-06),  interval(1.000000e+00),  interval(-2.999994e-12)},
{ interval(1.999996e-12),  interval(1.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.999985e-07), interval(9.999980e-13), interval(3.333328e-19)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999994e+00,  3.333328e-19,  9.999980e-13,  4.999985e-07},
{ 2.999988e+00,  1.333329e-18,  -1.999994e-18,  -9.999970e-07},
{ -9.999940e-01,  3.333318e-19,  -9.999960e-13,  4.999985e-07}};

#endif /*BENCHMARK_H_*/