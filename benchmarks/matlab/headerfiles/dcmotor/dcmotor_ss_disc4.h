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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.064910e-01),  interval(-4.091970e-02)},
{ interval(3.934586e-04),  interval(9.999889e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.934586e-04), interval(1.065288e-07)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.606480e+00,  1.065288e-07,  3.934586e-04},
{ 6.065003e-01,  9.020093e-08,  -3.934586e-04}};

#endif /*BENCHMARK_H_*/