#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999400e-01),  interval(-2.749925e-05),  interval(-1.499955e-05)},
{ interval(3.999880e-05),  interval(1.000000e+00),  interval(-2.999940e-10)},
{ interval(1.999960e-10),  interval(1.000000e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.999850e-06), interval(9.999800e-11), interval(3.333283e-16)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999940e+00,  3.333283e-16,  9.999800e-11,  4.999850e-06},
{ 2.999880e+00,  1.333293e-15,  -1.999940e-15,  -9.999700e-06},
{ -9.999400e-01,  3.333183e-16,  -9.999600e-11,  4.999850e-06}};

#endif /*BENCHMARK_H_*/