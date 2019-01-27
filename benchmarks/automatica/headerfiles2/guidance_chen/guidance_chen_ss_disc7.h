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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000033e+00),  interval(-2.422222e-05),  interval(1.060668e-05),  interval(-5.295140e-06),  interval(4.434577e-06)},
{ interval(2.000033e-05),  interval(1.000000e+00),  interval(1.060663e-10),  interval(-5.295113e-11),  interval(4.434553e-11)},
{ interval(2.000022e-10),  interval(2.000000e-05),  interval(1.000000e+00),  interval(-3.530066e-16),  interval(2.956360e-16)},
{ interval(6.666721e-16),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1),  interval(7.390889e-22)},
{ interval(4.166694e-22),  interval(8.333333e-17),  interval(1.250000e-11),  interval(2.500000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250102e-07), interval(6.250068e-12), interval(4.166701e-17), interval(1.041673e-22), interval(5.208362e-29)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.000033e+00,  5.208362e-29,  1.041673e-22,  4.166701e-17,  6.250068e-12,  6.250102e-07},
{ 1.000013e+01,  1.354181e-27,  1.041681e-21,  8.333538e-17,  -1.250007e-11,  -2.500041e-06},
{ -1.000020e+01,  3.437556e-27,  7.509733e-27,  -2.500041e-16,  -2.048109e-16,  3.750061e-06},
{ 5.000131e+00,  1.354196e-27,  -1.041686e-21,  8.333402e-17,  1.250034e-11,  -2.500041e-06},
{ -1.000033e+00,  5.208476e-29,  -1.041694e-22,  4.166769e-17,  -6.250137e-12,  6.250102e-07}};

#endif /*BENCHMARK_H_*/