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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.341348e-01),  interval(-9.050037e-02),  interval(-4.190402e-02)},
{ interval(9.373770e-02),  interval(9.952465e-01),  interval(-2.210263e-03)},
{ interval(2.472138e-03),  interval(5.111784e-02),  interval(9.999617e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.323258e-04), interval(3.862715e-05), interval(6.690131e-07)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.829343e+00,  6.690131e-07,  3.862715e-05,  7.323258e-04},
{ 2.668181e+00,  2.561067e-06,  -2.200865e-06,  -1.464666e-03},
{ -8.386180e-01,  6.126565e-07,  -3.642629e-05,  7.323405e-04}};

#endif /*BENCHMARK_H_*/