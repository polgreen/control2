#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.994840e-01),  interval(-2.220025e-04),  interval(-7.973255e-05),  interval(-3.305218e-05)},
{ interval(2.559339e-04),  interval(1.000000e+00),  interval(-1.020662e-08),  interval(-4.231043e-09)},
{ interval(8.190591e-09),  interval(6.400000e-05),  interval(1.000000e+00),  interval(-9.026613e-14)},
{ interval(8.737006e-14),  interval(1.024000e-09),  interval(3.200000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.997936e-06), interval(1.023824e-09), interval(2.184251e-14), interval(1.747446e-19)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.999484e+00,  1.747446e-19,  2.184251e-14,  1.023824e-09,  7.997936e-06},
{ 5.998452e+00,  1.921992e-18,  6.551627e-14,  -1.024000e-09,  -2.399381e-05},
{ -3.998452e+00,  1.921794e-18,  -6.552191e-14,  -1.023472e-09,  2.399381e-05},
{ 9.994840e-01,  1.746905e-19,  -2.183688e-14,  1.023648e-09,  -7.997936e-06}};

#endif /*BENCHMARK_H_*/