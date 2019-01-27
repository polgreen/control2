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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.679330e+06),  interval(3.635957e+06)},
{ interval(3.723220e+06),  interval(3.679330e+06)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.308049e+05), interval(9.419081e+05)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -7.358659e+06,  9.419081e+05,  9.308049e+05},
{ 1.001401e+00,  9.419081e+05,  -9.308049e+05}};

#endif /*BENCHMARK_H_*/