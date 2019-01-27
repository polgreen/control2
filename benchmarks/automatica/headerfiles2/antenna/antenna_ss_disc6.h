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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.987252e-01),  interval(-7.262959e-04),  interval(-4.911361e-04),  interval(-2.154876e-04),  interval(0),  interval(0)},
{ interval(1.598980e-03),  interval(9.999994e-01),  interval(-3.929809e-07),  interval(-1.724267e-07),  interval(0),  interval(0)},
{ interval(6.397280e-07),  interval(7.999998e-04),  interval(1.000000e+00),  interval(-4.598534e-11),  interval(0),  interval(0)},
{ interval(8.530614e-11),  interval(1.600000e-07),  interval(4.000000e-04),  interval(1.000000e+00),  interval(0),  interval(0)},
{ interval(1.332993e-16),  interval(3.333333e-13),  interval(1.250000e-09),  interval(6.250000e-06),  interval(1),  interval(0)},
{ interval(8.331563e-23),  interval(2.604167e-19),  interval(1.302083e-15),  interval(9.765625e-12),  interval(3.125000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.249203e-05), interval(9.995750e-09), interval(2.665817e-12), interval(2.665987e-16), interval(3.332625e-22), interval(1.735779e-28)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.998725e+00,  1.735779e-28,  3.332625e-22,  2.665987e-16,  2.665817e-12,  9.995750e-09,  1.249203e-05},
{ 1.499362e+01,  9.892237e-27,  8.329721e-21,  2.398640e-15,  2.662418e-12,  -2.999150e-08,  -6.246016e-05},
{ -1.998725e+01,  5.240190e-26,  1.332299e-20,  -2.665986e-15,  -2.131804e-11,  2.000849e-08,  1.249203e-04},
{ 1.498725e+01,  5.239238e-26,  -1.332668e-20,  -2.663948e-15,  2.132143e-11,  1.996602e-08,  -1.249203e-04},
{ -5.993628e+00,  9.886817e-27,  -8.326323e-21,  2.398300e-15,  -2.667515e-12,  -2.997026e-08,  6.246016e-05},
{ 9.987258e-01,  1.734231e-28,  -3.329794e-22,  2.663948e-16,  -2.664118e-12,  9.991503e-09,  -1.249203e-05}};

#endif /*BENCHMARK_H_*/