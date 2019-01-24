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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999948e-01),  interval(-1.011997e-06),  interval(-1.996795e-07)},
{ interval(1.249997e-06),  interval(1.000000e+00),  interval(-1.247998e-13)},
{ interval(1.953122e-13),  interval(3.125000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.124992e-07), interval(1.953122e-13), interval(2.034503e-20)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999995e+00,  2.034503e-20,  1.953122e-13,  3.124992e-07},
{ 2.999990e+00,  8.137999e-20,  -3.417960e-19,  -6.249984e-07},
{ -9.999948e-01,  2.034497e-20,  -1.953118e-13,  3.124992e-07}};

#endif /*BENCHMARK_H_*/