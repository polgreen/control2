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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.951654e-01),  interval(5.361383e-03)},
{ interval(6.234862e-03),  interval(1.000017e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.987890e-02), interval(1.559975e-04)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.995182e+00,  1.559975e-04,  4.987890e-02},
{ 9.951487e-01,  1.557448e-04,  -4.987890e-02}};

#endif /*BENCHMARK_H_*/