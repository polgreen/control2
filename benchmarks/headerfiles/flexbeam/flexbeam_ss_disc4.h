#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
// stable but not safe with no controller 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.909829e+00),  interval(-2.667239e+00),  interval(1.679025e+00),  interval(-1.306034e+00),  interval(5.908275e-01),  interval(-4.757098e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250000e-02), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -4.909829e+00,  6.250000e-02,  0,  0,  0,  0,  0},
{ 1.066895e+01,  0,  2.500000e-01,  0,  0,  0,  0},
{ -1.343220e+01,  0,  0,  5.000000e-01,  0,  0,  0},
{ 1.044827e+01,  0,  0,  0,  5.000000e-01,  0,  0},
{ -4.726620e+00,  0,  0,  0,  0,  5.000000e-01,  0},
{ 9.514197e-01,  0,  0,  0,  0,  0,  1.250000e-01}};

#endif /*BENCHMARK_H_*/