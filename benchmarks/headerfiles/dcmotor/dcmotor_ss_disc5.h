#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
// No controller needed, safe and stable, completeness k with no controller =  3 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.896539e-01),  interval(1.474699e-08)},
{ interval(7.450581e-09),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(128), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.896539e-01,  0,  128},
{ -1.098736e-16,  9.536743e-07,  0}};

#endif /*BENCHMARK_H_*/