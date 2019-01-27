#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.513497e-01),  interval(-2.412598e-01)},
{ interval(3.934920e-01),  interval(9.513497e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.934920e-01), interval(7.934813e-02)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.902699e+00,  7.934813e-02,  3.934920e-01},
{ 1.000000e+00,  7.934813e-02,  -3.934920e-01}};

#endif /*BENCHMARK_H_*/