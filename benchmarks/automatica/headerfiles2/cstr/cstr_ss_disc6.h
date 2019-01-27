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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999738e-01),  interval(-5.059934e-06),  interval(-9.983869e-07)},
{ interval(6.249918e-06),  interval(1.000000e+00),  interval(-3.119973e-12)},
{ interval(4.882770e-12),  interval(1.562500e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.562479e-06), interval(4.882770e-12), interval(2.543115e-18)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999974e+00,  2.543115e-18,  4.882770e-12,  1.562479e-06},
{ 2.999948e+00,  1.017239e-17,  -4.272405e-17,  -3.124959e-06},
{ -9.999738e-01,  2.543081e-18,  -4.882727e-12,  1.562479e-06}};

#endif /*BENCHMARK_H_*/