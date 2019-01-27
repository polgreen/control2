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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.982410e-01),  interval(-9.758206e-04),  interval(-4.573610e-04)},
{ interval(1.023099e-03),  interval(9.999995e-01),  interval(-2.342375e-07)},
{ interval(2.619903e-07),  interval(5.119999e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.992963e-06), interval(4.093598e-09), interval(6.987432e-13)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.998241e+00,  6.987432e-13,  4.093598e-09,  7.992963e-06},
{ 2.996482e+00,  2.793743e-12,  -2.400873e-12,  -1.598593e-05},
{ -9.982415e-01,  6.981285e-13,  -4.091197e-09,  7.992963e-06}};

#endif /*BENCHMARK_H_*/