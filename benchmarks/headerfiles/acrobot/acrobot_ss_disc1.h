#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.743724e+00),  interval(-3.438393e+00),  interval(8.690112e-01),  interval(-4.326137e-01)},
{ interval(-3.973071e+00),  interval(8.369377e+00),  interval(-4.998862e-01),  interval(1.451004e+00)},
{ interval(1.712252e+01),  interval(-2.359894e+01),  interval(3.743724e+00),  interval(-3.438393e+00)},
{ interval(-2.726863e+01),  interval(4.887006e+01),  interval(-3.973071e+00),  interval(8.369377e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-7.710746e-01), interval(1.523697e+00), interval(-5.176683e+00), interval(1.016667e+01)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -2.422620e+01,  -7.710746e-01,  1.523697e+00,  -5.176683e+00,  1.016667e+01},
{ 7.268661e+01,  1.657612e+00,  -3.757837e+00,  2.191392e+01,  -4.515438e+01},
{ -2.422620e+01,  1.657612e+00,  -3.757837e+00,  -2.191392e+01,  4.515438e+01},
{ 1.000000e+00,  -7.710746e-01,  1.523697e+00,  5.176683e+00,  -1.016667e+01}};

#endif /*BENCHMARK_H_*/