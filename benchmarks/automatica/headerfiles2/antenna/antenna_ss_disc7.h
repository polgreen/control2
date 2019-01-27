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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.997450e-01),  interval(-1.453018e-04),  interval(-9.827044e-05),  interval(-4.311950e-05),  interval(0),  interval(0)},
{ interval(3.199592e-04),  interval(1.000000e+00),  interval(-1.572385e-08),  interval(-6.899414e-09),  interval(0),  interval(0)},
{ interval(2.559782e-08),  interval(1.600000e-04),  interval(1.000000e+00),  interval(-3.679765e-13),  interval(0),  interval(0)},
{ interval(6.826231e-13),  interval(6.400000e-09),  interval(8.000000e-05),  interval(1),  interval(0),  interval(0)},
{ interval(2.133225e-19),  interval(2.666667e-15),  interval(5.000000e-11),  interval(1.250000e-06),  interval(1),  interval(0)},
{ interval(2.666553e-26),  interval(4.166667e-22),  interval(1.041667e-17),  interval(3.906250e-13),  interval(6.250000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499681e-06), interval(3.999660e-10), interval(2.133197e-14), interval(4.266449e-19), interval(1.066621e-25), interval(1.111069e-32)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999745e+00,  1.111069e-32,  1.066621e-25,  4.266449e-19,  2.133197e-14,  3.999660e-10,  2.499681e-06},
{ 1.499872e+01,  6.332873e-31,  2.666435e-24,  3.839565e-18,  2.132653e-14,  -1.199932e-09,  -1.249841e-05},
{ -1.999745e+01,  3.355189e-30,  4.266005e-24,  -4.266449e-18,  -1.706422e-13,  8.000680e-10,  2.499681e-05},
{ 1.499745e+01,  3.355067e-30,  -4.266241e-24,  -4.265796e-18,  1.706476e-13,  7.997280e-10,  -2.499681e-05},
{ -5.998725e+00,  6.332179e-31,  -2.666218e-24,  3.839456e-18,  -2.133469e-14,  -1.199762e-09,  1.249841e-05},
{ 9.997450e-01,  1.110870e-32,  -1.066440e-25,  4.265796e-19,  -2.132925e-14,  3.999320e-10,  -2.499681e-06}};

#endif /*BENCHMARK_H_*/