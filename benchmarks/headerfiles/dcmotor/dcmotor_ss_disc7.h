#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-02 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.990059e-01),  interval(-5.805383e-03)},
{ interval(7.812500e-03),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.990059e-01,  0,  1.250000e-01},
{ 4.535455e-05,  9.765625e-04,  0}};

#endif /*BENCHMARK_H_*/