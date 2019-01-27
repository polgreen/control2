#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999514e-01),  interval(5.374269e-05)},
{ interval(6.249848e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.999878e-04), interval(1.562475e-08)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.999951e+00,  1.562475e-08,  4.999878e-04},
{ 9.999514e-01,  1.562449e-08,  -4.999878e-04}};

#endif /*BENCHMARK_H_*/