#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.998725e-01),  interval(-7.265358e-05),  interval(-4.913792e-05),  interval(-2.156113e-05),  interval(0),  interval(0)},
{ interval(1.599898e-04),  interval(1.000000e+00),  interval(-3.931106e-09),  interval(-1.724927e-09),  interval(0),  interval(0)},
{ interval(6.399728e-09),  interval(8.000000e-05),  interval(1.000000e+00),  interval(-4.599853e-14),  interval(0),  interval(0)},
{ interval(8.533061e-14),  interval(1.600000e-09),  interval(4.000000e-05),  interval(1),  interval(0),  interval(0)},
{ interval(1.333299e-20),  interval(3.333333e-16),  interval(1.250000e-11),  interval(6.250000e-07),  interval(1),  interval(0)},
{ interval(8.333156e-28),  interval(2.604167e-23),  interval(1.302083e-18),  interval(9.765625e-14),  interval(3.125000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.249920e-06), interval(9.999575e-11), interval(2.666582e-15), interval(2.666599e-20), interval(3.333263e-27), interval(1.736078e-34)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999872e+00,  1.736078e-34,  3.333263e-27,  2.666599e-20,  2.666582e-15,  9.999575e-11,  1.249920e-06},
{ 1.499936e+01,  9.895474e-33,  8.332972e-26,  2.399864e-19,  2.666242e-15,  -2.999915e-10,  -6.249602e-06},
{ -1.999873e+01,  5.242769e-32,  1.333230e-25,  -2.666599e-19,  -2.133180e-14,  2.000085e-10,  1.249920e-05},
{ 1.499873e+01,  5.242674e-32,  -1.333267e-25,  -2.666395e-19,  2.133214e-14,  1.999660e-10,  -1.249920e-05},
{ -5.999363e+00,  9.894931e-33,  -8.332632e-26,  2.399830e-19,  -2.666752e-15,  -2.999703e-10,  6.249602e-06},
{ 9.998725e-01,  1.735923e-34,  -3.332979e-27,  2.666395e-20,  -2.666412e-15,  9.999150e-11,  -1.249920e-06}};

#endif /*BENCHMARK_H_*/