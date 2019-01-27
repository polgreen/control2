#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.701006e-01),  interval(-2.981902e-01),  interval(-1.805478e-01),  interval(-1.482008e-01),  interval(-7.752286e-02),  interval(-4.825396e-02),  interval(-2.339844e-02)},
{ interval(5.324444e-01),  interval(8.692672e-01),  interval(-8.057497e-02),  interval(-6.703505e-02),  interval(-3.540049e-02),  interval(-2.222289e-02),  interval(-1.083422e-02)},
{ interval(1.232693e-01),  interval(3.817872e-01),  interval(9.886844e-01),  interval(-9.470908e-03),  interval(-5.022553e-03),  interval(-3.164748e-03),  interval(-1.546541e-03)},
{ interval(8.798098e-03),  interval(3.906554e-02),  interval(1.994167e-01),  interval(9.995101e-01),  interval(-2.603986e-04),  interval(-1.644286e-04),  interval(-8.046036e-05)},
{ interval(4.577300e-04),  interval(2.628646e-03),  interval(1.997620e-02),  interval(1.999800e-01),  interval(9.999893e-01),  interval(-6.744934e-06),  interval(-3.303390e-06)},
{ interval(9.396310e-06),  interval(6.602529e-05),  interval(6.662643e-04),  interval(9.999661e-03),  interval(9.999982e-02),  interval(9.999999e-01),  interval(-5.608089e-08)},
{ interval(7.975949e-08),  interval(6.620439e-07),  interval(8.330429e-06),  interval(1.666642e-04),  interval(2.499999e-03),  interval(5.000000e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.655555e-02), interval(3.081733e-02), interval(4.399049e-03), interval(2.288650e-04), interval(9.396310e-06), interval(1.595190e-07), interval(1.155183e-09)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.227552e+00,  1.155183e-09,  1.595190e-07,  9.396310e-06,  2.288650e-04,  4.399049e-03,  3.081733e-02,  6.655555e-02},
{ 1.667454e+01,  1.259284e-07,  7.985337e-06,  1.959972e-04,  1.470184e-03,  -3.078333e-03,  -1.300610e-01,  -3.998642e-01},
{ -2.488419e+01,  1.135834e-06,  3.055072e-05,  6.027387e-05,  -3.927190e-03,  -2.865292e-02,  1.880438e-01,  1.000898e+00},
{ 2.235434e+01,  2.096420e-06,  -3.931992e-06,  -5.788403e-04,  8.177572e-04,  5.741409e-02,  -6.791203e-02,  -1.336072e+00},
{ -1.208881e+01,  9.415939e-07,  -2.885778e-05,  1.515877e-04,  2.975055e-03,  -3.552713e-02,  -8.617689e-02,  1.003133e+00},
{ 3.644038e+00,  8.654482e-08,  -5.812451e-06,  1.558860e-04,  -1.418731e-03,  2.421062e-03,  8.931553e-02,  -4.016570e-01},
{ -4.723666e-01,  6.581974e-10,  -9.335821e-08,  5.699214e-06,  -1.459402e-04,  3.024189e-03,  -2.402678e-02,  6.700579e-02}};

#endif /*BENCHMARK_H_*/