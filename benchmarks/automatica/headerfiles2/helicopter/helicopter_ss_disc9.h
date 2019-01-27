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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999996e-01),  interval(1.679990e-08),  interval(-3.959999e-07)},
{ interval(4.999999e-07),  interval(1.000000e+00),  interval(-9.899999e-14)},
{ interval(1.250000e-13),  interval(5.000000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.600000e-05), interval(3.999999e-12), interval(6.666666e-19)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -3.000000e+00,  6.666666e-19,  3.999999e-12,  1.600000e-05},
{ 2.999999e+00,  2.666666e-18,  -5.599999e-19,  -3.199999e-05},
{ -9.999996e-01,  6.666665e-19,  -3.999999e-12,  1.600000e-05}};

#endif /*BENCHMARK_H_*/