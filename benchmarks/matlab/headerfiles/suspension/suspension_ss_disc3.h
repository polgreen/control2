#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.764526e-01),  interval(-1.739824e-01),  interval(-6.215555e-02),  interval(-2.558090e-02)},
{ interval(1.980814e-01),  interval(9.758136e-01),  interval(-8.657244e-03),  interval(-3.572299e-03)},
{ interval(6.915374e-03),  interval(6.346275e-02),  interval(9.998075e-01),  interval(-7.951762e-05)},
{ interval(7.696640e-05),  interval(1.019597e-03),  interval(3.199842e-02),  interval(9.999993e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.190044e-03), interval(8.644217e-04), interval(1.924160e-05), interval(1.578795e-07)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.552073e+00,  1.578795e-07,  1.924160e-05,  8.644217e-04,  6.190044e-03},
{ 4.702000e+00,  1.570568e-06,  4.855536e-05,  -1.001009e-03,  -1.857082e-02},
{ -2.746737e+00,  1.416656e-06,  -5.293103e-05,  -5.912467e-04,  1.857149e-02},
{ 5.968238e-01,  1.158396e-07,  -1.486592e-05,  7.278342e-04,  -6.190719e-03}};

#endif /*BENCHMARK_H_*/