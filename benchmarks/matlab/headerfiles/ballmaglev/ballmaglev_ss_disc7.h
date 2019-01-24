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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(1.000000e-05),  interval(-1.703323e-09)},
{ interval(1.752212e-02),  interval(1.000000e+00),  interval(-3.406428e-04)},
{ interval(0),  interval(0),  interval(9.996174e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.091908e-14), interval(-3.275620e-09), interval(1.922709e-05)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999618e+00,  1.922709e-05,  -3.275620e-09,  -1.091908e-14},
{ 2.999235e+00,  -3.845418e-05,  4.178249e-13,  -4.367215e-14},
{ -9.996174e-01,  1.922709e-05,  3.275202e-09,  -1.091699e-14}};

#endif /*BENCHMARK_H_*/