#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.740760e-01),  interval(-4.994912e-03),  interval(-9.854047e-04)},
{ interval(6.168649e-03),  interval(9.999843e-01),  interval(-3.092870e-06)},
{ interval(4.840354e-06),  interval(1.562492e-03),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.542162e-03), interval(4.840354e-06), interval(2.526525e-09)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.974060e+00,  2.526525e-09,  4.840354e-06,  1.542162e-03},
{ 2.948152e+00,  1.004011e-08,  -4.216817e-08,  -3.084325e-03},
{ -9.740915e-01,  2.493582e-09,  -4.798186e-06,  1.542162e-03}};

#endif /*BENCHMARK_H_*/