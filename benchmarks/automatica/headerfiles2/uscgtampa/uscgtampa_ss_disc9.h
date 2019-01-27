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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999997e-01),  interval(-3.335220e-09),  interval(0)},
{ interval(4.999999e-07),  interval(1.000000e+00),  interval(0)},
{ interval(2.500000e-13),  interval(1.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-07), interval(6.249999e-14), interval(2.083333e-20)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -3.000000e+00,  2.083333e-20,  6.249999e-14,  2.500000e-07},
{ 2.999999e+00,  8.333332e-20,  -5.645833e-21,  -4.999999e-07},
{ -9.999997e-01,  2.083333e-20,  -6.249999e-14,  2.500000e-07}};

#endif /*BENCHMARK_H_*/