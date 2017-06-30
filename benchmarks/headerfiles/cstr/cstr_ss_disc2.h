#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 2.000000e-01 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.899844e+00),  interval(-1.400085e+00),  interval(4.501623e-01)},
{ interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.953125e-03), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.899844e+00,  0,  0,  -1.953125e-03},
{ -2.800169e+00,  0,  -3.906250e-03,  0},
{ 9.003245e-01,  -3.906250e-03,  0,  0}};

#endif /*BENCHMARK_H_*/