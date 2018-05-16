#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.250  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)100
#define INPUT_LOWERBOUND (__plant_precisiont)-100
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.361328e+00),  interval(-2.279994e-02),  interval(-6.770571e-01)},
{ interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -1.361328e+00,  1.250000e-01,  0,  0},
{ 2.279994e-02,  0,  1.250000e-01,  0},
{ 3.385285e-01,  0,  0,  6.250000e-02}};

#endif /*BENCHMARK_H_*/