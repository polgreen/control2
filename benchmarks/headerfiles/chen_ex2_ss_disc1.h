#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 5.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 8 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(2.136696e+00),  interval(-9.312093e-01),  interval(4.086816e-01),  interval(-1.824322e-01),  interval(7.996664e-02),  interval(-3.102171e-02),  interval(1.618798e-02),  interval(-8.946455e-03)},
{ interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(3.125000e-02),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(7.812500e-03),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(8)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -2.136696e+00,  0,  0,  0,  0,  0,  0,  0,  8},
{ 1.862419e+00,  0,  0,  0,  0,  0,  0,  16,  0},
{ -8.173632e-01,  0,  0,  0,  0,  0,  16,  0,  0},
{ 1.824322e-01,  0,  0,  0,  0,  8,  0,  0,  0},
{ -1.999166e-02,  0,  0,  0,  2,  0,  0,  0,  0},
{ 9.694284e-04,  0,  0,  2.500000e-01,  0,  0,  0,  0,  0},
{ -1.580858e-05,  0,  7.812500e-03,  0,  0,  0,  0,  0,  0},
{ 6.825603e-08,  6.103516e-05,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/