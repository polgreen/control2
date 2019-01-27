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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999850e-01),  interval(-7.749962e-06),  interval(-4.921846e-06),  interval(-4.187473e-06),  interval(-2.246078e-06),  interval(-1.429677e-06),  interval(-7.031197e-07)},
{ interval(1.599988e-05),  interval(1.000000e+00),  interval(-3.937485e-11),  interval(-3.349986e-11),  interval(-1.796867e-11),  interval(-1.143744e-11),  interval(-5.624972e-12)},
{ interval(6.399968e-11),  interval(8.000000e-06),  interval(1.000000e+00),  interval(-8.933305e-17),  interval(-4.791650e-17),  interval(-3.049989e-17),  interval(-1.499994e-17)},
{ interval(8.533301e-17),  interval(1.600000e-11),  interval(4.000000e-06),  interval(1),  interval(-4.791654e-23),  interval(-3.049991e-23),  interval(-1.499996e-23)},
{ interval(8.533308e-23),  interval(2.133333e-17),  interval(8.000000e-12),  interval(4.000000e-06),  interval(1),  interval(-2.439994e-29),  interval(-1.199997e-29)},
{ interval(3.413325e-29),  interval(1.066667e-23),  interval(5.333333e-18),  interval(4.000000e-12),  interval(2.000000e-06),  interval(1),  interval(-3.999991e-36)},
{ interval(5.688876e-36),  interval(2.133333e-30),  interval(1.333333e-24),  interval(1.333333e-18),  interval(1.000000e-12),  interval(1.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.999985e-06), interval(1.599992e-11), interval(4.266651e-17), interval(4.266654e-23), interval(3.413325e-29), interval(1.137775e-35), interval(1.706662e-42)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.999985e+00,  1.706662e-42,  1.137775e-35,  3.413325e-29,  4.266654e-23,  4.266651e-17,  1.599992e-11,  1.999985e-06},
{ 2.099991e+01,  1.945593e-40,  6.371528e-34,  8.191957e-28,  3.413309e-22,  -6.399967e-22,  -6.399976e-11,  -1.199991e-05},
{ -3.499978e+01,  1.937056e-39,  2.787536e-33,  5.119919e-28,  -8.106628e-22,  -3.839963e-16,  8.000000e-11,  2.999978e-05},
{ 3.499970e+01,  3.925304e-39,  -7.338612e-39,  -2.730646e-27,  3.839971e-27,  6.826615e-16,  -7.999940e-16,  -3.999970e-05},
{ -2.099978e+01,  1.937049e-39,  -2.787533e-33,  5.120004e-28,  8.106583e-22,  -3.839979e-16,  -7.999880e-11,  2.999978e-05},
{ 6.999910e+00,  1.945578e-40,  -6.371487e-34,  8.191920e-28,  -3.413306e-22,  6.399937e-22,  6.399928e-11,  -1.199991e-05},
{ -9.999850e-01,  1.706645e-42,  -1.137763e-35,  3.413291e-29,  -4.266615e-23,  4.266619e-17,  -1.599984e-11,  1.999985e-06}};

#endif /*BENCHMARK_H_*/