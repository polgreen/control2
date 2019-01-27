#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.005004e+00),  interval(1.001668e-01),  interval(0),  interval(0)},
{ interval(1.001668e-01),  interval(1.005004e+00),  interval(0),  interval(0)},
{ interval(5.004168e-03),  interval(1.001668e-01),  interval(1),  interval(0)},
{ interval(1.667500e-04),  interval(5.004168e-03),  interval(1.000000e-01),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.001668e-01), interval(5.004168e-03), interval(1.667500e-04), interval(4.168056e-06)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.010008e+00,  4.168056e-06,  1.667500e-04,  5.004168e-03,  1.001668e-01},
{ 6.020017e+00,  4.587362e-05,  5.005836e-04,  -5.004168e-03,  -3.005003e-01},
{ -4.010008e+00,  4.587362e-05,  -5.005836e-04,  -5.004168e-03,  3.005003e-01},
{ 1.000000e+00,  4.168056e-06,  -1.667500e-04,  5.004168e-03,  -1.001668e-01}};

#endif /*BENCHMARK_H_*/