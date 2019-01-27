#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.975756e-01),  interval(2.683939e-03)},
{ interval(3.121208e-03),  interval(1.000004e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.496967e-02), interval(3.903089e-05)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.997580e+00,  3.903089e-05,  2.496967e-02},
{ 9.975714e-01,  3.899926e-05,  -2.496967e-02}};

#endif /*BENCHMARK_H_*/