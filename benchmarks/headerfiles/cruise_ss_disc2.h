#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.500000e+00 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.277435e-01),  interval(9.277435e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.125000e-02)};
const __plant_typet __char_poly_const[2][2] = 
 {{ -1,  0},
{ 9.277435e-01,  -3.125000e-02}};

#endif /*BENCHMARK_H_*/