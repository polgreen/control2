#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.040134e+00),  interval(-3.040134e+00),  interval(1.010033e+00),  interval(-5.000000e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250000e-02), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.040134e+00,  6.250000e-02,  0,  0,  0},
{ 6.080267e+00,  0,  1.250000e-01,  0,  0},
{ -4.040134e+00,  0,  0,  2.500000e-01,  0},
{ 1,  0,  0,  0,  1.250000e-01}};

#endif /*BENCHMARK_H_*/