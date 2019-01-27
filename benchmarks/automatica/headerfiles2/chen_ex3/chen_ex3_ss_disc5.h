#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.985005e-01),  interval(-7.746157e-04),  interval(-4.919022e-04),  interval(-4.184809e-04),  interval(-2.244552e-04),  interval(-1.428651e-04),  interval(-7.025978e-05)},
{ interval(1.598800e-03),  interval(9.999994e-01),  interval(-3.935978e-07),  interval(-3.348565e-07),  interval(-1.796053e-07),  interval(-1.143197e-07),  interval(-5.622188e-08)},
{ interval(6.396801e-07),  interval(7.999998e-04),  interval(1.000000e+00),  interval(-8.930463e-11),  interval(-4.790022e-11),  interval(-3.048894e-11),  interval(-1.499438e-11)},
{ interval(8.530134e-11),  interval(1.600000e-07),  interval(4.000000e-04),  interval(1.000000e+00),  interval(-4.790351e-15),  interval(-3.049115e-15),  interval(-1.499550e-15)},
{ interval(8.530774e-15),  interval(2.133333e-11),  interval(8.000000e-08),  interval(4.000000e-04),  interval(1),  interval(-2.439410e-19),  interval(-1.199700e-19)},
{ interval(3.412480e-19),  interval(1.066667e-15),  interval(5.333333e-12),  interval(4.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-3.999100e-24)},
{ interval(5.687609e-24),  interval(2.133333e-20),  interval(1.333333e-16),  interval(1.333333e-12),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.998500e-04), interval(1.599200e-07), interval(4.265067e-11), interval(4.265387e-15), interval(3.412480e-19), interval(1.137522e-23), interval(1.706240e-28)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.998500e+00,  1.706240e-28,  1.137522e-23,  3.412480e-19,  4.265387e-15,  4.265067e-11,  1.599200e-07,  1.998500e-04},
{ 2.099100e+01,  1.944875e-26,  6.368808e-22,  8.187734e-18,  3.410902e-14,  -6.396739e-14,  -6.397600e-07,  -1.199100e-03},
{ -3.497750e+01,  1.935977e-25,  2.785623e-21,  5.111897e-18,  -8.102827e-14,  -3.836321e-10,  7.999998e-07,  2.997751e-03},
{ 3.497001e+01,  3.922390e-25,  -7.333165e-25,  -2.728619e-17,  3.837121e-17,  6.821548e-10,  -7.994002e-10,  -3.997001e-03},
{ -2.097751e+01,  1.935252e-25,  -2.785308e-21,  5.120424e-18,  8.098350e-14,  -3.837920e-10,  -7.988007e-07,  2.997751e-03},
{ 6.991006e+00,  1.943408e-26,  -6.364749e-22,  8.183982e-18,  -3.410646e-14,  6.393665e-14,  6.392804e-07,  -1.199100e-03},
{ -9.985011e-01,  1.704535e-28,  -1.136328e-23,  3.409069e-19,  -4.261550e-15,  4.261869e-11,  -1.598401e-07,  1.998500e-04}};

#endif /*BENCHMARK_H_*/