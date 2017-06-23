#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.986537e+00),  interval(-1.486539e+00),  interval(4.932707e-01)},
{ interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.986537e+00,  0,  0,  -7.812500e-03},
{ -2.973079e+00,  0,  -1.562500e-02,  0},
{ 9.865414e-01,  -1.562500e-02,  0,  0}};

#endif /*BENCHMARK_H_*/