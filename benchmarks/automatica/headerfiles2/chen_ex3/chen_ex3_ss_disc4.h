#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.925126e-01),  interval(-3.865397e-03),  interval(-2.453809e-03),  interval(-2.087028e-03),  interval(-1.119197e-03),  interval(-7.122538e-04),  interval(-3.502456e-04)},
{ interval(7.970034e-03),  interval(9.999845e-01),  interval(-9.824736e-06),  interval(-8.357070e-06),  interval(-4.481918e-06),  interval(-2.852467e-06),  interval(-1.402737e-06)},
{ interval(1.596003e-05),  interval(3.999979e-03),  interval(1.000000e+00),  interval(-1.114873e-08),  interval(-5.979312e-09),  interval(-3.805590e-09),  interval(-1.871487e-09)},
{ interval(1.064668e-08),  interval(3.999990e-06),  interval(2.000000e-03),  interval(1.000000e+00),  interval(-2.990683e-12),  interval(-1.903486e-12),  interval(-9.360945e-13)},
{ interval(5.325338e-12),  interval(2.666663e-09),  interval(2.000000e-06),  interval(2.000000e-03),  interval(1.000000e+00),  interval(-7.615786e-16),  interval(-3.745315e-16)},
{ interval(1.065334e-15),  interval(6.666660e-13),  interval(6.666667e-10),  interval(1.000000e-06),  interval(1.000000e-03),  interval(1),  interval(-6.242973e-20)},
{ interval(8.878894e-20),  interval(6.666662e-17),  interval(8.333333e-14),  interval(1.666667e-10),  interval(2.500000e-07),  interval(5.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.962542e-04), interval(3.990008e-06), interval(5.323340e-09), interval(2.662669e-12), interval(1.065334e-15), interval(1.775779e-19), interval(1.331668e-23)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.992497e+00,  1.331668e-23,  1.775779e-19,  1.065334e-15,  2.662669e-12,  5.323340e-09,  3.990008e-06,  9.962542e-04},
{ 2.095501e+01,  1.517169e-21,  9.934108e-18,  2.553340e-14,  2.125744e-11,  -3.989817e-11,  -1.597000e-05,  -5.977525e-03},
{ -3.488761e+01,  1.509080e-20,  4.340478e-17,  1.587364e-14,  -5.054672e-11,  -4.777039e-08,  1.999985e-05,  1.494381e-02},
{ 3.485025e+01,  3.055186e-20,  -5.711870e-20,  -8.501382e-14,  1.195507e-13,  8.501375e-08,  -9.962558e-08,  -1.992508e-02},
{ -2.088777e+01,  1.506257e-20,  -4.338021e-17,  1.600647e-14,  5.040724e-11,  -4.787002e-08,  -1.985042e-05,  1.494381e-02},
{ 6.955137e+00,  1.511457e-21,  -9.902493e-18,  2.547496e-14,  -2.124947e-11,  3.980240e-11,  1.591022e-05,  -5.977525e-03},
{ -9.925281e-01,  1.325026e-23,  -1.766480e-19,  1.060021e-15,  -2.650714e-12,  5.303415e-09,  -3.980046e-06,  9.962542e-04}};

#endif /*BENCHMARK_H_*/