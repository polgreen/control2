#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000016e+00),  interval(-1.211104e-05),  interval(5.303303e-06),  interval(-2.647550e-06),  interval(2.217270e-06)},
{ interval(1.000008e-05),  interval(1.000000e+00),  interval(2.651646e-11),  interval(-1.323772e-11),  interval(1.108632e-11)},
{ interval(5.000027e-11),  interval(1.000000e-05),  interval(1),  interval(-4.412566e-17),  interval(3.695435e-17)},
{ interval(8.333367e-17),  interval(2.500000e-11),  interval(5.000000e-06),  interval(1),  interval(4.619290e-23)},
{ interval(2.604175e-23),  interval(1.041667e-17),  interval(3.125000e-12),  interval(1.250000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.125026e-07), interval(1.562509e-12), interval(5.208355e-18), interval(6.510438e-24), interval(1.627609e-30)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.000016e+00,  1.627609e-30,  6.510438e-24,  5.208355e-18,  1.562509e-12,  3.125026e-07},
{ 1.000007e+01,  4.231794e-29,  6.510461e-23,  1.041679e-17,  -3.125009e-12,  -1.250010e-06},
{ -1.000010e+01,  1.074228e-28,  2.346772e-28,  -3.125026e-17,  -2.560115e-17,  1.875015e-06},
{ 5.000066e+00,  4.231817e-29,  -6.510479e-23,  1.041671e-17,  3.125043e-12,  -1.250010e-06},
{ -1.000016e+00,  1.627626e-30,  -6.510502e-24,  5.208397e-18,  -1.562517e-12,  3.125026e-07}};

#endif /*BENCHMARK_H_*/