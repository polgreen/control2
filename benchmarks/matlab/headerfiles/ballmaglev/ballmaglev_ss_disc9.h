#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(1.000000e-06),  interval(-1.703518e-11)},
{ interval(1.752212e-03),  interval(1.000000e+00),  interval(-3.407014e-05)},
{ interval(0),  interval(0),  interval(9.999617e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.092002e-17), interval(-3.275996e-11), interval(1.923040e-06)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999962e+00,  1.923040e-06,  -3.275996e-11,  -1.092002e-17},
{ 2.999923e+00,  -3.846080e-06,  4.178969e-16,  -4.367967e-17},
{ -9.999617e-01,  1.923040e-06,  3.275955e-11,  -1.091981e-17}};

#endif /*BENCHMARK_H_*/