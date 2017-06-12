#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 4 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(1.015701e+00),  interval(-1.581209e-02),  interval(5.026109e-02),  interval(-2.626197e-04)},
{ interval(-1.827091e-02),  interval(1.036973e+00),  interval(-3.034577e-04),  interval(5.061439e-02)},
{ interval(6.315664e-01),  interval(-6.379846e-01),  interval(1.015701e+00),  interval(-1.581209e-02)},
{ interval(-7.371927e-01),  interval(1.489844e+00),  interval(-1.827091e-02),  interval(1.036973e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-3.754311e-03)interval(7.532142e-03)interval(-1.513485e-01)interval(3.035784e-01)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.105347e+00,  -3.754311e-03,  7.532142e-03,  -1.513485e-01,  3.035784e-01},
{ 6.211860e+00,  3.793727e-03,  -7.631472e-03,  4.556366e-01,  -9.147373e-01},
{ -4.105347e+00,  3.793727e-03,  -7.631472e-03,  -4.556366e-01,  9.147373e-01},
{ 1,  -3.754311e-03,  7.532142e-03,  1.513485e-01,  -3.035784e-01}};

#endif /*BENCHMARK_H_*/