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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999979e-01),  interval(8.399744e-08),  interval(-1.979998e-06)},
{ interval(2.499997e-06),  interval(1.000000e+00),  interval(-2.474998e-12)},
{ interval(3.124998e-12),  interval(2.500000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.999992e-05), interval(9.999993e-11), interval(8.333329e-17)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999998e+00,  8.333329e-17,  9.999993e-11,  7.999992e-05},
{ 2.999996e+00,  3.333330e-16,  -6.999993e-17,  -1.599998e-04},
{ -9.999979e-01,  8.333320e-17,  -9.999986e-11,  7.999992e-05}};

#endif /*BENCHMARK_H_*/