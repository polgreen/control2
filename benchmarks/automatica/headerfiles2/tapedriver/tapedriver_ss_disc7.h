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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.825045e-01),  interval(-9.691678e-03),  interval(-4.537513e-03)},
{ interval(1.015025e-02),  interval(9.999503e-01),  interval(-2.330041e-05)},
{ interval(2.606107e-05),  interval(5.119915e-03),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.929879e-05), interval(4.072042e-07), interval(6.959822e-10)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.982455e+00,  6.959822e-10,  4.072042e-07,  7.929879e-05},
{ 2.965009e+00,  2.771709e-09,  -2.381936e-09,  -1.585976e-04},
{ -9.825540e-01,  6.898844e-10,  -4.048222e-07,  7.929879e-05}};

#endif /*BENCHMARK_H_*/