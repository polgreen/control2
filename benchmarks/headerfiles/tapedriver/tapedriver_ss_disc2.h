#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.500000e+00 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.225890e-248),  interval(0),  interval(0)},
{ interval(1.025067e-143),  interval(0),  interval(0)},
{ interval(0),  interval(5.125333e-144),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.225890e-248,  0,  0,  -1.250000e-01},
{ 0,  0,  -1.281333e-144,  0},
{ 0,  -6.567259e-288,  0,  0}};

#endif /*BENCHMARK_H_*/