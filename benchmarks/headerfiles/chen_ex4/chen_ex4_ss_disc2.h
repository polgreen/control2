#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 2.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.424040e+00),  interval(-2.373906e+00),  interval(2.118453e+00),  interval(-1.257444e+00),  interval(1.029509e+00),  interval(-5.813156e-01),  interval(2.183278e-01),  interval(-9.900929e-02),  interval(8.264944e-02)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ 6.424040e+00,  0,  0,  0,  0,  0,  0,  0,  0,  -7.812500e-03},
{ -1.899125e+01,  0,  0,  0,  0,  0,  0,  0,  -6.250000e-02,  0},
{ 3.389525e+01,  0,  0,  0,  0,  0,  0,  -1.250000e-01,  0,  0},
{ -4.023821e+01,  0,  0,  0,  0,  0,  -2.500000e-01,  0,  0,  0},
{ 3.294430e+01,  0,  0,  0,  0,  -2.500000e-01,  0,  0,  0,  0},
{ -1.860210e+01,  0,  0,  0,  -2.500000e-01,  0,  0,  0,  0,  0},
{ 6.986491e+00,  0,  0,  -2.500000e-01,  0,  0,  0,  0,  0,  0},
{ -1.584149e+00,  0,  -1.250000e-01,  0,  0,  0,  0,  0,  0,  0},
{ 1.652989e-01,  -1.562500e-02,  0,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/