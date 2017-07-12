#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
// No controller needed, safe and stable, completeness k with no controller =  1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 1 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = { interval(9.950125e-01)};
 const __plant_typet __char_poly_const[2][2] = 
 {{ -1,  0},
{ 9.950125e-01,  -7.812500e-03}};

#endif /*BENCHMARK_H_*/