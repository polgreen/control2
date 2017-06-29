#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.082149e+00),  interval(-1.184319e+00),  interval(2.463276e-01),  interval(-1.757780e-01),  interval(6.275873e-02),  interval(-1.188790e-02)},
{ interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2.500000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1.562500e-02),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.082149e+00,  0,  0,  0,  0,  0,  7.812500e-03},
{ 1.184319e+00,  0,  0,  0,  0,  7.812500e-03,  0},
{ -1.231638e-01,  0,  0,  0,  3.906250e-03,  0,  0},
{ 2.197224e-02,  0,  0,  9.765625e-04,  0,  0,  0},
{ -9.806051e-04,  0,  1.220703e-04,  0,  0,  0,  0},
{ 2.902320e-06,  1.907349e-06,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/