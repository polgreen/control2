#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.732557e-01),  interval(-3.290424e-04),  interval(0)},
{ interval(4.932844e-02),  interval(9.999917e-01),  interval(0)},
{ interval(2.477565e-03),  interval(9.999972e-02),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.466422e-02), interval(6.193914e-04), interval(2.069293e-05)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.973247e+00,  2.069293e-05,  6.193914e-04,  2.466422e-02},
{ 2.946511e+00,  8.221391e-05,  -5.569946e-06,  -4.932844e-02},
{ -9.732639e-01,  2.041443e-05,  -6.138214e-04,  2.466422e-02}};

#endif /*BENCHMARK_H_*/