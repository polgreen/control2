#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999900e-01),  interval(2.499956e-05),  interval(9.997504e-10),  interval(1.427786e-12),  interval(1.338550e-15)},
{ interval(0),  interval(9.999750e-01),  interval(7.997045e-05),  interval(1.713064e-07),  interval(2.141417e-10)},
{ interval(0),  interval(0),  interval(9.992863e-01),  interval(4.281294e-03),  interval(8.028716e-06)},
{ interval(0),  interval(0),  interval(0),  interval(9.987508e-01),  interval(3.746720e-03)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.995001e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.015983e-19), interval(8.031314e-14), interval(4.015182e-09), interval(2.810860e-06), interval(1.499625e-03)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.997502e+00,  1.499625e-03,  2.810860e-06,  4.015182e-09,  8.031314e-14,  4.015983e-19},
{ 9.990011e+00,  -5.995504e-03,  -5.621254e-06,  8.020615e-09,  8.026925e-13,  1.043721e-17},
{ -9.985019e+00,  8.988763e-03,  2.811797e-09,  -2.407584e-08,  -4.306204e-16,  2.648342e-17},
{ 4.990015e+00,  -5.989515e-03,  5.614700e-06,  8.029940e-09,  -8.023633e-13,  1.042852e-17},
{ -9.975041e-01,  1.496630e-03,  -2.807117e-06,  4.010098e-09,  -8.019248e-14,  4.009298e-19}};

#endif /*BENCHMARK_H_*/