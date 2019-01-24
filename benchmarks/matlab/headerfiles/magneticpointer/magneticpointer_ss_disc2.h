#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.865393e-01),  interval(-1.656362e-04),  interval(0)},
{ interval(2.483137e-02),  interval(9.999979e-01),  interval(0)},
{ interval(6.221864e-04),  interval(4.999997e-02),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.241569e-02), interval(1.555466e-04), interval(2.595368e-06)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.986537e+00,  2.595368e-06,  1.555466e-04,  1.241569e-02},
{ 2.973079e+00,  1.034640e-05,  -7.009671e-07,  -2.483137e-02},
{ -9.865414e-01,  2.577844e-06,  -1.548456e-04,  1.241569e-02}};

#endif /*BENCHMARK_H_*/