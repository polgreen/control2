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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999995e-01),  interval(-1.012000e-07),  interval(-1.996799e-08)},
{ interval(1.250000e-07),  interval(1.000000e+00),  interval(-1.248000e-15)},
{ interval(1.953125e-15),  interval(3.125000e-08),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.124999e-08), interval(1.953125e-15), interval(2.034505e-23)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999999e+00,  2.034505e-23,  1.953125e-15,  3.124999e-08},
{ 2.999999e+00,  8.138019e-23,  -3.417968e-22,  -6.249998e-08},
{ -9.999995e-01,  2.034504e-23,  -1.953124e-15,  3.124999e-08}};

#endif /*BENCHMARK_H_*/