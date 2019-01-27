#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.995801e-01),  interval(1.669749e-05),  interval(-3.959169e-04)},
{ interval(4.998950e-04),  interval(1.000000e+00),  interval(-9.898614e-08)},
{ interval(1.249825e-07),  interval(5.000000e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599664e-02), interval(3.999440e-06), interval(6.665967e-10)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999580e+00,  6.665967e-10,  3.999440e-06,  1.599664e-02},
{ 2.999160e+00,  2.666107e-09,  -5.598824e-10,  -3.199328e-02},
{ -9.995801e-01,  6.664567e-10,  -3.998880e-06,  1.599664e-02}};

#endif /*BENCHMARK_H_*/