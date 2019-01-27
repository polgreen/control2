#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.987731e-01),  interval(-2.892404e-02),  interval(-8.109924e-04),  interval(-1.183987e-02),  interval(-1.583074e-05),  interval(0)},
{ interval(1.599080e-02),  interval(9.997686e-01),  interval(-6.362896e-06),  interval(-9.473835e-05),  interval(-1.266718e-07),  interval(0)},
{ interval(6.397629e-05),  interval(7.999383e-03),  interval(1.000000e+00),  interval(-2.526604e-07),  interval(-3.378247e-10),  interval(0)},
{ interval(1.706202e-07),  interval(3.199877e-05),  interval(8.000000e-03),  interval(1.000000e+00),  interval(-6.756883e-13),  interval(0)},
{ interval(2.132876e-11),  interval(5.333210e-09),  interval(2.000000e-06),  interval(5.000000e-04),  interval(1.000000e+00),  interval(0)},
{ interval(1.066478e-15),  interval(3.333282e-13),  interval(1.666667e-10),  interval(6.250000e-08),  interval(2.500000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599080e-02), interval(1.279526e-04), interval(3.412405e-07), interval(6.825202e-10), interval(6.825458e-14), interval(2.844016e-18)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.998542e+00,  2.844016e-18,  6.825458e-14,  6.825202e-10,  3.412405e-07,  1.279526e-04,  1.599080e-02},
{ 1.499317e+01,  1.620827e-16,  1.706029e-12,  6.140997e-09,  3.408691e-07,  -3.839002e-04,  -7.995400e-02},
{ -1.998727e+01,  8.586207e-16,  2.728879e-12,  -6.825012e-09,  -2.728979e-06,  2.560750e-04,  1.599080e-01},
{ 1.498819e+01,  8.584986e-16,  -2.729468e-12,  -6.820935e-09,  2.729319e-06,  2.556503e-04,  -1.599080e-01},
{ -5.994560e+00,  1.620135e-16,  -1.705486e-12,  6.140317e-09,  -3.413787e-07,  -3.836878e-04,  7.995400e-02},
{ 9.990045e-01,  2.841994e-18,  -6.820928e-14,  6.821124e-10,  -3.410706e-07,  1.279101e-04,  -1.599080e-02}};

#endif /*BENCHMARK_H_*/