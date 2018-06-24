#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.750  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.999769e-01),  interval(8.711493e-01),  interval(-3.422525e-01)},
{ interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999769e-01,  1,  0,  0},
{ -8.711493e-01,  0,  1,  0},
{ 1.711262e-01,  0,  0,  5.000000e-01}};

#endif /*BENCHMARK_H_*/