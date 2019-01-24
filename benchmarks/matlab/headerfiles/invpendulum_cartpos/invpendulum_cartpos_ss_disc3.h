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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000001e+00),  interval(1.000000e-03),  interval(0),  interval(0)},
{ interval(1.000000e-03),  interval(1.000001e+00),  interval(0),  interval(0)},
{ interval(5.000000e-07),  interval(1.000000e-03),  interval(1),  interval(0)},
{ interval(1.666667e-10),  interval(5.000000e-07),  interval(1.000000e-03),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.000000e-03), interval(5.000000e-07), interval(1.666667e-10), interval(4.166667e-14)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000001e+00,  4.166667e-14,  1.666667e-10,  5.000000e-07,  1.000000e-03},
{ 6.000002e+00,  4.583334e-13,  5.000001e-10,  -5.000000e-07,  -3.000001e-03},
{ -4.000001e+00,  4.583334e-13,  -5.000001e-10,  -5.000000e-07,  3.000001e-03},
{ 1.000000e+00,  4.166667e-14,  -1.666667e-10,  5.000000e-07,  -1.000000e-03}};

#endif /*BENCHMARK_H_*/