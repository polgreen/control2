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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.992501e-01),  interval(-3.874039e-04),  interval(-2.460224e-04),  interval(-2.093077e-04),  interval(-1.122662e-04),  interval(-7.145845e-05),  interval(-3.514307e-05)},
{ interval(7.997000e-04),  interval(9.999998e-01),  interval(-9.841848e-08),  interval(-8.373206e-08),  interval(-4.491160e-08),  interval(-2.858684e-08),  interval(-1.405898e-08)},
{ interval(1.599600e-07),  interval(4.000000e-04),  interval(1.000000e+00),  interval(-1.116487e-11),  interval(-5.988556e-12),  interval(-3.811809e-12),  interval(-1.874648e-12)},
{ interval(1.066467e-11),  interval(4.000000e-08),  interval(2.000000e-04),  interval(1.000000e+00),  interval(-2.994381e-16),  interval(-1.905973e-16),  interval(-9.373594e-17)},
{ interval(5.332533e-16),  interval(2.666667e-12),  interval(2.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-7.624078e-21),  interval(-3.749531e-21)},
{ interval(1.066533e-20),  interval(6.666667e-17),  interval(6.666667e-13),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1),  interval(-6.249297e-26)},
{ interval(8.887889e-26),  interval(6.666667e-22),  interval(8.333333e-18),  interval(1.666667e-13),  interval(2.500000e-09),  interval(5.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.996250e-05), interval(3.999000e-08), interval(5.332333e-12), interval(2.666267e-16), interval(1.066533e-20), interval(1.777578e-25), interval(1.333167e-30)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.999250e+00,  1.333167e-30,  1.777578e-25,  1.066533e-20,  2.666267e-16,  5.332333e-12,  3.999000e-08,  9.996250e-05},
{ 2.099550e+01,  1.519717e-28,  9.953409e-24,  2.559333e-19,  2.132573e-15,  -3.998981e-15,  -1.599700e-07,  -5.997750e-04},
{ -3.498875e+01,  1.512908e-27,  4.354046e-23,  1.598734e-19,  -5.065467e-15,  -4.797700e-11,  2.000000e-07,  1.499438e-03},
{ 3.498500e+01,  3.065517e-27,  -5.731184e-27,  -8.530134e-19,  1.199550e-18,  8.530134e-11,  -9.996251e-11,  -1.999250e-03},
{ -2.098875e+01,  1.512624e-27,  -4.353799e-23,  1.600066e-19,  5.064067e-15,  -4.798700e-11,  -1.998500e-07,  1.499438e-03},
{ 6.995501e+00,  1.519144e-28,  -9.950237e-24,  2.558747e-19,  -2.132493e-15,  3.998020e-15,  1.599100e-07,  -5.997750e-04},
{ -9.992503e-01,  1.332500e-30,  -1.776645e-25,  1.066000e-20,  -2.665067e-16,  5.330334e-12,  -3.998000e-08,  9.996250e-05}};

#endif /*BENCHMARK_H_*/