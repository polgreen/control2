#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.998542e+00),  interval(-3.748293e+00),  interval(2.498409e+00),  interval(-1.873524e+00),  interval(7.493200e-01),  interval(-4.995022e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.953125e-03), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.998542e+00,  1.953125e-03,  0,  0,  0,  0,  0},
{ 1.499317e+01,  0,  7.812500e-03,  0,  0,  0,  0},
{ -1.998727e+01,  0,  0,  1.562500e-02,  0,  0,  0},
{ 1.498819e+01,  0,  0,  0,  1.562500e-02,  0,  0},
{ -5.994560e+00,  0,  0,  0,  0,  1.562500e-02,  0},
{ 9.990045e-01,  0,  0,  0,  0,  0,  3.906250e-03}};

#endif /*BENCHMARK_H_*/