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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999790e-01),  interval(8.397437e-07),  interval(-1.979979e-05)},
{ interval(2.499974e-05),  interval(1.000000e+00),  interval(-2.474983e-10)},
{ interval(3.124978e-10),  interval(2.500000e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.999916e-04), interval(9.999930e-09), interval(8.333290e-14)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999979e+00,  8.333290e-14,  9.999930e-09,  7.999916e-04},
{ 2.999958e+00,  3.333298e-13,  -6.999927e-14,  -1.599983e-03},
{ -9.999790e-01,  8.333202e-14,  -9.999860e-09,  7.999916e-04}};

#endif /*BENCHMARK_H_*/