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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999580e-01),  interval(1.678975e-06),  interval(-3.959917e-05)},
{ interval(4.999895e-05),  interval(1.000000e+00),  interval(-9.899861e-10)},
{ interval(1.249983e-09),  interval(5.000000e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599966e-03), interval(3.999944e-08), interval(6.666597e-13)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999958e+00,  6.666597e-13,  3.999944e-08,  1.599966e-03},
{ 2.999916e+00,  2.666611e-12,  -5.599882e-13,  -3.199933e-03},
{ -9.999580e-01,  6.666457e-13,  -3.999888e-08,  1.599966e-03}};

#endif /*BENCHMARK_H_*/