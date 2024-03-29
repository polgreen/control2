#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000005e+00),  interval(3.125005e-03)},
{ interval(3.200005e-03),  interval(1.000005e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(8.000013e-04), interval(1.280001e-06)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -2.000010e+00,  1.280001e-06,  8.000013e-04},
{ 1,  1.280001e-06,  -8.000013e-04}};

#endif /*BENCHMARK_H_*/