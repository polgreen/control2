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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.912262e-01),  interval(-4.864292e-03),  interval(-2.278768e-03)},
{ interval(5.097517e-03),  interval(9.999875e-01),  interval(-5.842213e-06)},
{ interval(6.534405e-06),  interval(2.559989e-03),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.982435e-05), interval(1.021001e-07), interval(8.718932e-11)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.991214e+00,  8.718932e-11,  1.021001e-07,  3.982435e-05},
{ 2.982452e+00,  3.479909e-10,  -2.990547e-10,  -7.964870e-05},
{ -9.912386e-01,  8.680653e-11,  -1.018010e-07,  3.982435e-05}};

#endif /*BENCHMARK_H_*/