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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999757e-01),  interval(2.687167e-05)},
{ interval(3.124962e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499970e-04), interval(3.906218e-09)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.999976e+00,  3.906218e-09,  2.499970e-04},
{ 9.999757e-01,  3.906187e-09,  -2.499970e-04}};

#endif /*BENCHMARK_H_*/