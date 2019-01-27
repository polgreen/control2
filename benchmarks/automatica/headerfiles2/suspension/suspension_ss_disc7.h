#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.948491e-01),  interval(-2.215105e-03),  interval(-7.955235e-04),  interval(-3.297551e-04)},
{ interval(2.553402e-03),  interval(9.999972e-01),  interval(-1.019124e-06),  interval(-4.224498e-07)},
{ interval(8.177920e-07),  interval(6.399994e-04),  interval(1.000000e+00),  interval(-9.016138e-11)},
{ interval(8.726867e-11),  interval(1.024000e-07),  interval(3.200000e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.979383e-05), interval(1.022240e-07), interval(2.181717e-11), interval(1.745824e-15)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.994846e+00,  1.745824e-15,  2.181717e-11,  1.022240e-07,  7.979383e-05},
{ 5.984545e+00,  1.918425e-14,  6.533899e-11,  -1.023997e-07,  -2.393815e-04},
{ -3.984550e+00,  1.916446e-14,  -6.539522e-11,  -1.018726e-07,  2.393815e-04},
{ 9.948520e-01,  1.740426e-15,  -2.176094e-11,  1.020483e-07,  -7.979383e-05}};

#endif /*BENCHMARK_H_*/