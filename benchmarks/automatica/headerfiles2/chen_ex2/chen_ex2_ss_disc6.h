#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.983508e-01),  interval(-1.364734e-03),  interval(-5.888298e-04),  interval(-2.895727e-04),  interval(-1.675310e-04),  interval(-1.143243e-04),  interval(-8.806281e-05),  interval(-2.927271e-05)},
{ interval(7.993402e-04),  interval(9.999995e-01),  interval(-2.355890e-07),  interval(-1.158587e-07),  interval(-6.703008e-08),  interval(-4.574202e-08),  interval(-3.523472e-08),  interval(-1.171231e-08)},
{ interval(3.198240e-07),  interval(7.999999e-04),  interval(1.000000e+00),  interval(-3.089960e-11),  interval(-1.787704e-11),  interval(-1.219951e-11),  interval(-9.397204e-12),  interval(-3.123711e-12)},
{ interval(4.264907e-11),  interval(1.600000e-07),  interval(4.000000e-04),  interval(1.000000e+00),  interval(-1.787846e-15),  interval(-1.220049e-15),  interval(-9.397971e-16),  interval(-3.123969e-16)},
{ interval(2.132629e-15),  interval(1.066667e-11),  interval(4.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-4.880460e-20),  interval(-3.759393e-20),  interval(-1.249656e-20)},
{ interval(4.265494e-20),  interval(2.666667e-16),  interval(1.333333e-12),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1),  interval(-6.265826e-25),  interval(-2.082818e-25)},
{ interval(3.554676e-25),  interval(2.666667e-21),  interval(1.666667e-17),  interval(1.666667e-13),  interval(2.500000e-09),  interval(5.000000e-05),  interval(1),  interval(-1.562070e-30)},
{ interval(2.665934e-30),  interval(2.222222e-26),  interval(1.666667e-22),  interval(2.083333e-18),  interval(4.166667e-14),  interval(1.250000e-09),  interval(5.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.993402e-04), interval(3.198240e-07), interval(8.529814e-11), interval(8.530518e-15), interval(3.412395e-19), interval(5.687481e-24), interval(4.265494e-29), interval(3.554187e-34)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.998350e+00,  3.554187e-34,  4.265494e-29,  5.687481e-24,  3.412395e-19,  8.530518e-15,  8.529814e-11,  3.198240e-07,  7.993402e-04},
{ 2.798845e+01,  6.219952e-32,  4.819351e-27,  3.127392e-22,  7.846069e-18,  5.968266e-14,  -8.543885e-11,  -1.599296e-06,  -5.595382e-03},
{ -5.596536e+01,  1.090600e-30,  4.353469e-26,  1.074288e-21,  -3.076220e-18,  -2.302620e-13,  -7.670500e-10,  2.879472e-06,  1.678614e-02},
{ 6.994228e+01,  3.963313e-30,  4.965571e-26,  -1.393118e-21,  -3.239524e-17,  1.621333e-13,  2.131398e-09,  -1.601758e-06,  -2.797691e-02},
{ -5.594228e+01,  3.962590e-30,  -4.967564e-26,  -1.392138e-21,  3.240461e-17,  1.618660e-13,  -2.131750e-09,  -1.595603e-06,  2.797691e-02},
{ 2.796537e+01,  1.090000e-30,  -4.351879e-26,  1.074338e-21,  3.062715e-18,  -2.301579e-13,  7.676831e-10,  2.875779e-06,  -1.678614e-02},
{ -7.988458e+00,  6.214231e-32,  -4.815365e-27,  3.125226e-22,  -7.842317e-18,  5.968548e-14,  8.508714e-11,  -1.598065e-06,  5.595382e-03},
{ 9.983514e-01,  3.551061e-34,  -4.260804e-29,  5.680916e-24,  -3.408643e-19,  8.522077e-15,  -8.522780e-11,  3.196482e-07,  -7.993402e-04}};

#endif /*BENCHMARK_H_*/