#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10
#define INPUT_LOWERBOUND (__plant_precisiont)-10
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.255252e+00),  interval(-1)},
{ interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.000000e-01), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -2.255252e+00,  0,  5.000000e-01},
{ 1,  5.000000e-01,  0}};

#endif /*BENCHMARK_H_*/