#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.678152e-01),  interval(-6.573667e-02)},
{ interval(6.320834e-04),  interval(9.999617e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.320834e-04), interval(3.678661e-07)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.367777e+00,  3.678661e-07,  6.320834e-04},
{ 3.678427e-01,  2.642226e-07,  -6.320834e-04}};

#endif /*BENCHMARK_H_*/