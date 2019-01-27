#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.358477e+00),  interval(-2.727365e-01),  interval(1.215903e-01),  interval(-6.154614e-02),  interval(5.206091e-02)},
{ interval(2.347993e-01),  interval(9.737679e-01),  interval(1.162806e-02),  interval(-5.860046e-03),  interval(4.941247e-03)},
{ interval(2.228545e-02),  interval(1.982854e-01),  interval(1.000758e+00),  interval(-3.810138e-04),  interval(3.207432e-04)},
{ interval(7.232900e-04),  interval(9.957644e-03),  interval(1.000187e-01),  interval(9.999906e-01),  interval(7.890019e-06)},
{ interval(4.448084e-06),  interval(8.312324e-05),  interval(1.250093e-03),  interval(2.499995e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.337477e-03), interval(6.964204e-04), interval(4.520562e-05), interval(1.112021e-06), interval(5.500218e-09)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.332994e+00,  5.500218e-09,  1.112021e-06,  4.520562e-05,  6.964204e-04,  7.337477e-03},
{ 1.138198e+01,  1.510057e-07,  1.194485e-05,  1.057672e-04,  -1.312500e-03,  -2.934743e-02},
{ -1.215250e+01,  4.048093e-07,  8.843150e-07,  -2.938981e-04,  -2.410210e-04,  4.401731e-02},
{ 6.491271e+00,  1.684342e-07,  -1.258755e-05,  8.967223e-05,  1.633862e-03,  -2.934223e-02},
{ -1.387762e+00,  6.843149e-09,  -1.353631e-06,  5.325309e-05,  -7.767606e-04,  7.334873e-03}};

#endif /*BENCHMARK_H_*/