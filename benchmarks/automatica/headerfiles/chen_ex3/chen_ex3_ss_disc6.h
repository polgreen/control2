#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.924719e+00),  interval(-5.137854e+00),  interval(2.117888e+00),  interval(-1.047659e+00),  interval(6.219167e-01),  interval(-4.102195e-01),  interval(2.319359e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.924719e+00,  7.812500e-03,  0,  0,  0,  0,  0,  0},
{ 2.055142e+01,  0,  3.125000e-02,  0,  0,  0,  0,  0},
{ -3.388622e+01,  0,  0,  1.250000e-01,  0,  0,  0,  0},
{ 3.352508e+01,  0,  0,  0,  2.500000e-01,  0,  0,  0},
{ -1.990133e+01,  0,  0,  0,  0,  2.500000e-01,  0,  0},
{ 6.563512e+00,  0,  0,  0,  0,  0,  1.250000e-01,  0},
{ -9.277435e-01,  0,  0,  0,  0,  0,  0,  3.125000e-02}};

#endif /*BENCHMARK_H_*/