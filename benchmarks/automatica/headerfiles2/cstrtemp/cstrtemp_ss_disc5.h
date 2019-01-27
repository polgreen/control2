#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999951e-01),  interval(5.374387e-06)},
{ interval(6.249985e-06),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.999988e-05), interval(1.562497e-10)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.999995e+00,  1.562497e-10,  4.999988e-05},
{ 9.999951e-01,  1.562495e-10,  -4.999988e-05}};

#endif /*BENCHMARK_H_*/