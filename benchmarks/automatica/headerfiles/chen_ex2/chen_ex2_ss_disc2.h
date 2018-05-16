#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.126804e+00),  interval(-3.606969e+00),  interval(1.733431e+00),  interval(-9.950734e-01),  interval(6.933617e-01),  interval(-2.838589e-01),  interval(1.236495e-01),  interval(-8.706355e-02)},
{ interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(6.250000e-02),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(8), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -4.126804e+00,  8,  0,  0,  0,  0,  0,  0,  0},
{ 7.213938e+00,  0,  16,  0,  0,  0,  0,  0,  0},
{ -6.933724e+00,  0,  0,  32,  0,  0,  0,  0,  0},
{ 3.980294e+00,  0,  0,  0,  32,  0,  0,  0,  0},
{ -1.386723e+00,  0,  0,  0,  0,  16,  0,  0,  0},
{ 2.838589e-01,  0,  0,  0,  0,  0,  8,  0,  0},
{ -3.091238e-02,  0,  0,  0,  0,  0,  0,  2,  0},
{ 1.360368e-03,  0,  0,  0,  0,  0,  0,  0,  1.250000e-01}};

#endif /*BENCHMARK_H_*/