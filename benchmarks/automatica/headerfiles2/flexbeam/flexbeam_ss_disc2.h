#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.390321e-01),  interval(-1.174511e+00),  interval(-1.361431e-01),  interval(-4.720219e-01),  interval(-6.311146e-04),  interval(0)},
{ interval(6.374958e-01),  interval(4.787162e-01),  interval(-4.308086e-02),  interval(-2.114003e-01),  interval(-2.826538e-04),  interval(0)},
{ interval(1.427559e-01),  interval(3.276345e-01),  interval(9.950909e-01),  interval(-2.944656e-02),  interval(-3.937179e-05),  interval(0)},
{ interval(1.988494e-02),  interval(7.261577e-02),  interval(3.995620e-01),  interval(9.969901e-01),  interval(-4.024410e-06),  interval(0)},
{ interval(1.270344e-04),  interval(6.293122e-04),  interval(4.997993e-03),  interval(2.498476e-02),  interval(1.000000e+00),  interval(0)},
{ interval(3.216373e-07),  interval(2.004934e-06),  interval(2.082943e-05),  interval(1.562180e-04),  interval(1.250000e-02),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.374958e-01), interval(2.855117e-01), interval(3.976988e-02), interval(4.065100e-03), interval(2.058479e-05), interval(4.323151e-08)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -4.909829e+00,  4.323151e-08,  2.058479e-05,  4.065100e-03,  3.976988e-02,  2.855117e-01,  6.374958e-01},
{ 1.066895e+01,  2.329182e-06,  4.805120e-04,  3.339367e-02,  2.874137e-02,  -8.613065e-01,  -3.192785e+00},
{ -1.343220e+01,  1.185839e-05,  7.304879e-04,  -3.788527e-02,  -2.860624e-01,  5.901057e-01,  6.391618e+00},
{ 1.044827e+01,  1.177083e-05,  -7.389876e-04,  -3.672627e-02,  2.880403e-01,  5.424047e-01,  -6.393104e+00},
{ -4.726620e+00,  2.278812e-06,  -4.726876e-04,  3.320819e-02,  -3.170819e-02,  -8.374591e-01,  3.195014e+00},
{ 9.514197e-01,  4.171594e-08,  -1.990948e-05,  3.944587e-03,  -3.878094e-02,  2.807435e-01,  -6.382391e-01}};

#endif /*BENCHMARK_H_*/