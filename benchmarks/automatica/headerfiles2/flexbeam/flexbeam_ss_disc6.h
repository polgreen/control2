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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999496e-01),  interval(-1.446846e-03),  interval(-3.832063e-05),  interval(-5.923191e-04),  interval(-7.919723e-07),  interval(0)},
{ interval(7.999799e-04),  interval(9.999994e-01),  interval(-1.531259e-08),  interval(-2.369296e-07),  interval(-3.167916e-10),  interval(0)},
{ interval(1.599973e-07),  interval(3.999999e-04),  interval(1.000000e+00),  interval(-3.159075e-11),  interval(-4.223906e-14),  interval(0)},
{ interval(2.133307e-11),  interval(7.999999e-08),  interval(4.000000e-04),  interval(1.000000e+00),  interval(-4.223916e-18),  interval(0)},
{ interval(1.333320e-16),  interval(6.666666e-13),  interval(5.000000e-09),  interval(2.500000e-05),  interval(1),  interval(0)},
{ interval(3.333306e-22),  interval(2.083333e-18),  interval(2.083333e-14),  interval(1.562500e-10),  interval(1.250000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.999799e-04), interval(3.199947e-07), interval(4.266613e-11), interval(4.266624e-15), interval(2.133316e-20), interval(4.444411e-26)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999949e+00,  4.444411e-26,  2.133316e-20,  4.266624e-15,  4.266613e-11,  3.199947e-07,  7.999799e-04},
{ 1.499975e+01,  2.533297e-24,  5.333243e-19,  3.839915e-14,  4.266400e-11,  -9.599893e-07,  -3.999900e-03},
{ -1.999950e+01,  1.342193e-23,  8.533074e-19,  -4.266624e-14,  -3.413237e-10,  6.400106e-07,  7.999799e-03},
{ 1.499950e+01,  1.342184e-23,  -8.533166e-19,  -4.266496e-14,  3.413258e-10,  6.399574e-07,  -7.999799e-03},
{ -5.999750e+00,  2.533243e-24,  -5.333158e-19,  3.839893e-14,  -4.266719e-11,  -9.599627e-07,  3.999900e-03},
{ 9.999502e-01,  4.444256e-26,  -2.133245e-20,  4.266497e-15,  -4.266507e-11,  3.199893e-07,  -7.999799e-04}};

#endif /*BENCHMARK_H_*/