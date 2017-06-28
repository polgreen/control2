#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-02 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.944128e+00),  interval(-3.691705e+00),  interval(2.453207e+00),  interval(-9.198413e-01),  interval(3.690364e-01),  interval(-2.475224e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.562500e-02), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.944128e+00,  0,  0,  0,  0,  0,  1.562500e-02},
{ 1.476682e+01,  0,  0,  0,  0,  6.250000e-02,  0},
{ -1.962566e+01,  0,  0,  0,  1.250000e-01,  0,  0},
{ 1.471746e+01,  0,  0,  2.500000e-01,  0,  0,  0},
{ -5.904583e+00,  0,  2.500000e-01,  0,  0,  0,  0},
{ 9.900894e-01,  6.250000e-02,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/