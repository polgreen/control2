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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000328e+00),  interval(-2.422484e-04),  interval(1.060801e-04),  interval(-5.295871e-05),  interval(4.435231e-05)},
{ interval(2.000328e-04),  interval(1.000000e+00),  interval(1.060752e-08),  interval(-5.295601e-09),  interval(4.434989e-09)},
{ interval(2.000218e-08),  interval(2.000000e-04),  interval(1.000000e+00),  interval(-3.530310e-13),  interval(2.956578e-13)},
{ interval(6.667213e-13),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1),  interval(7.391325e-18)},
{ interval(4.166940e-18),  interval(8.333333e-14),  interval(1.250000e-09),  interval(2.500000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.251024e-06), interval(6.250683e-10), interval(4.167008e-14), interval(1.041735e-18), interval(5.208618e-24)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.000328e+00,  5.208618e-24,  1.041735e-18,  4.167008e-14,  6.250683e-10,  6.251024e-06},
{ 1.000131e+01,  1.354315e-22,  1.041810e-17,  8.335382e-14,  -1.250068e-09,  -2.500410e-05},
{ -1.000197e+01,  3.438063e-22,  7.510840e-22,  -2.500410e-13,  -2.048411e-13,  3.750614e-05},
{ 5.001311e+00,  1.354463e-22,  -1.041865e-17,  8.334016e-14,  1.250341e-09,  -2.500410e-05},
{ -1.000328e+00,  5.209756e-24,  -1.041940e-18,  4.167691e-14,  -6.251366e-10,  6.251024e-06}};

#endif /*BENCHMARK_H_*/