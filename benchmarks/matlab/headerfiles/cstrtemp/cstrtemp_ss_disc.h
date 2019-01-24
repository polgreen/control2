#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.763909e-01),  interval(2.655164e-02)},
{ interval(3.087745e-02),  interval(1.000417e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.470196e-01), interval(3.875051e-03)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.976807e+00,  3.875051e-03,  2.470196e-01},
{ 9.759777e-01,  3.843771e-03,  -2.470196e-01}};

#endif /*BENCHMARK_H_*/