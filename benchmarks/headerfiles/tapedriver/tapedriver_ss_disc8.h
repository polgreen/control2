#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-02 
// No controller needed, safe and stable, suggested completeness k 3 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-4.464097e-02),  interval(-1.594953e-02),  interval(7.445040e-04)},
{ interval(3.125000e-02),  interval(0),  interval(0)},
{ interval(0),  interval(9.765625e-04),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ -4.464097e-02,  0,  0,  -2.500000e-01},
{ -4.984227e-04,  0,  -7.812500e-03,  0},
{ 2.272046e-08,  -7.629395e-06,  0,  0}};

#endif /*BENCHMARK_H_*/