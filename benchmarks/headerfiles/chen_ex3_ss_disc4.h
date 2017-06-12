#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 7 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(6.227552e+00),  interval(-2.084317e+00),  interval(1.555262e+00),  interval(-6.985732e-01),  interval(3.777753e-01),  interval(-2.277524e-01),  interval(1.180916e-01)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250000e-02)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0},
{ 6.227552e+00,  0,  0,  0,  0,  0,  0,  -6.250000e-02},
{ -1.667454e+01,  0,  0,  0,  0,  0,  -5.000000e-01,  0},
{ 2.488419e+01,  0,  0,  0,  0,  -1,  0,  0},
{ -2.235434e+01,  0,  0,  0,  -2,  0,  0,  0},
{ 1.208881e+01,  0,  0,  -2,  0,  0,  0,  0},
{ -3.644038e+00,  0,  -1,  0,  0,  0,  0,  0},
{ 4.723666e-01,  -2.500000e-01,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/