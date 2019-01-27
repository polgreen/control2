#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.665331e-01),  interval(-9.821415e-02),  interval(-3.518448e-02),  interval(-1.453507e-02)},
{ interval(1.125498e-01),  interval(9.934500e-01),  interval(-2.348568e-03),  interval(-9.713834e-04)},
{ interval(1.880436e-03),  interval(3.192869e-02),  interval(9.999744e-01),  interval(-1.058531e-05)},
{ interval(1.024570e-05),  interval(2.557113e-04),  interval(1.599990e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.517183e-03), interval(2.350545e-04), interval(2.561424e-06), interval(1.037748e-08)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.759957e+00,  1.037748e-08,  2.561424e-06,  2.350545e-04,  3.517183e-03},
{ 5.292603e+00,  1.084832e-07,  7.049332e-06,  -2.544276e-04,  -1.055160e-02},
{ -3.305189e+00,  1.030272e-07,  -7.359388e-06,  -1.963083e-04,  1.055164e-02},
{ 7.725437e-01,  8.888910e-09,  -2.251368e-06,  2.156814e-04,  -3.517231e-03}};

#endif /*BENCHMARK_H_*/