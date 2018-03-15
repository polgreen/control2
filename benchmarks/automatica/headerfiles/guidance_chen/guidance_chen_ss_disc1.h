#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.276921e+00),  interval(-2.422193e+00),  interval(1.060653e+00),  interval(-5.295059e-01),  interval(4.434504e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250000e-02), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -3.276921e+00,  6.250000e-02,  0,  0,  0,  0},
{ 4.844386e+00,  0,  1.250000e-01,  0,  0,  0},
{ -4.242613e+00,  0,  0,  2.500000e-01,  0,  0},
{ 2.118024e+00,  0,  0,  0,  2.500000e-01,  0},
{ -4.434504e-01,  0,  0,  0,  0,  6.250000e-02}};

#endif /*BENCHMARK_H_*/