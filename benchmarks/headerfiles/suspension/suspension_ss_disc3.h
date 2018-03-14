#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.479541e-04),  interval(-1.657460e-03),  interval(1.841525e-26),  interval(-1.124296e-104)},
{ interval(1.953125e-03),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1.953125e-03),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1.953125e-03),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(256), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -7.479541e-04,  256,  0,  0,  0},
{ 3.237226e-06,  0,  5.000000e-01,  0,  0},
{ -7.024862e-32,  0,  0,  9.765625e-04,  0},
{ 8.376656e-113,  0,  0,  0,  1.907349e-06}};

#endif /*BENCHMARK_H_*/