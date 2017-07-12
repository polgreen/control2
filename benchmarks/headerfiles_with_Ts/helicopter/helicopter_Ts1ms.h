#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.999580e+00),  interval(-1.499580e+00),  interval(9.995801e-01)},
{ interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.999580e+00,  0,  0,  -1.250000e-01},
{ -2.999160e+00,  0,  -2.500000e-01,  0},
{ 9.995801e-01,  -1.250000e-01,  0,  0}};

#endif /*BENCHMARK_H_*/