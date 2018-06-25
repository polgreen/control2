#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.090034e+00),  interval(5.160138e-01)},
{ interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.090034e+00,  2,  0},
{ -2.580069e-01,  0,  1}};

#endif /*BENCHMARK_H_*/