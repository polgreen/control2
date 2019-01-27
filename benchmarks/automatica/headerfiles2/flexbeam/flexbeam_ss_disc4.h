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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.994443e-01),  interval(-1.446565e-02),  interval(-3.937734e-04),  interval(-5.921752e-03),  interval(-7.917797e-06),  interval(0)},
{ interval(7.997854e-03),  interval(9.999421e-01),  interval(-1.559444e-06),  interval(-2.368920e-05),  interval(-3.167412e-08),  interval(0)},
{ interval(1.599719e-05),  interval(3.999923e-03),  interval(1.000000e+00),  interval(-3.158703e-08),  interval(-4.223408e-11),  interval(0)},
{ interval(2.133055e-08),  interval(7.999923e-06),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-4.223521e-14),  interval(0)},
{ interval(1.333195e-12),  interval(6.666628e-10),  interval(5.000000e-07),  interval(2.500000e-04),  interval(1),  interval(0)},
{ interval(3.333047e-17),  interval(2.083325e-14),  interval(2.083333e-11),  interval(1.562500e-08),  interval(1.250000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.997854e-03), interval(3.199438e-05), interval(4.266111e-08), interval(4.266225e-11), interval(2.133150e-15), interval(4.444100e-20)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999386e+00,  4.444100e-20,  2.133150e-15,  4.266225e-11,  4.266111e-08,  3.199438e-05,  7.997854e-03},
{ 1.499705e+01,  2.532956e-18,  5.332384e-14,  3.839106e-10,  4.263888e-08,  -9.598845e-05,  -3.998927e-02},
{ -1.999433e+01,  1.341922e-17,  8.530644e-14,  -4.266196e-10,  -3.412328e-07,  6.401000e-05,  7.997854e-02},
{ 1.499456e+01,  1.341827e-17,  -8.531564e-14,  -4.264921e-10,  3.412540e-07,  6.395690e-05,  -7.997854e-02},
{ -5.997395e+00,  2.532414e-18,  -5.331534e-14,  3.838893e-10,  -4.267074e-08,  -9.596190e-05,  3.998927e-02},
{ 9.995021e-01,  4.442551e-20,  -2.132442e-15,  4.264951e-11,  -4.265049e-08,  3.198907e-05,  -7.997854e-03}};

#endif /*BENCHMARK_H_*/