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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999973e-01),  interval(-3.335215e-08),  interval(0)},
{ interval(4.999993e-06),  interval(1.000000e+00),  interval(0)},
{ interval(2.499998e-11),  interval(1.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499997e-06), interval(6.249994e-12), interval(2.083332e-17)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999997e+00,  2.083332e-17,  6.249994e-12,  2.499997e-06},
{ 2.999995e+00,  8.333322e-17,  -5.645826e-18,  -4.999993e-06},
{ -9.999973e-01,  2.083329e-17,  -6.249989e-12,  2.499997e-06}};

#endif /*BENCHMARK_H_*/