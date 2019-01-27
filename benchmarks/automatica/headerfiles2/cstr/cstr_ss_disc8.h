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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999974e-01),  interval(-5.059993e-07),  interval(-9.983987e-08)},
{ interval(6.249992e-07),  interval(1.000000e+00),  interval(-3.119997e-14)},
{ interval(4.882808e-14),  interval(1.562500e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.562498e-07), interval(4.882808e-14), interval(2.543130e-21)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999997e+00,  2.543130e-21,  4.882808e-14,  1.562498e-07},
{ 2.999995e+00,  1.017251e-20,  -4.272455e-20,  -3.124996e-07},
{ -9.999974e-01,  2.543127e-21,  -4.882804e-14,  1.562498e-07}};

#endif /*BENCHMARK_H_*/