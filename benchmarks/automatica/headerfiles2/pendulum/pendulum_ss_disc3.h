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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999951e-01),  interval(-2.452496e-03)},
{ interval(3.999993e-03),  interval(9.999951e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.999993e-03), interval(7.999993e-06)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.999990e+00,  7.999993e-06,  3.999993e-03},
{ 1,  7.999993e-06,  -3.999993e-03}};

#endif /*BENCHMARK_H_*/