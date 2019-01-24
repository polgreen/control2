#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.000001e+00),  interval(-3.000001e+00),  interval(1.000000e+00),  interval(-5.000000e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.051758e-05), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000001e+00,  3.051758e-05,  0,  0,  0},
{ 6.000002e+00,  0,  6.103516e-05,  0,  0},
{ -4.000001e+00,  0,  0,  1.220703e-04,  0},
{ 1,  0,  0,  0,  6.103516e-05}};

#endif /*BENCHMARK_H_*/