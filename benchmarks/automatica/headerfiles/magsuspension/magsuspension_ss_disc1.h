#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.414987e+13),  interval(-8.068959e+05)},
{ interval(524288),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(8388608), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -5.414987e+13,  8388608,  0},
{ 4.230458e+11,  0,  4398046511104}};

#endif /*BENCHMARK_H_*/