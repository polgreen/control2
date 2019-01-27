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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999986e-01),  interval(-1.667609e-08),  interval(0)},
{ interval(2.499998e-06),  interval(1.000000e+00),  interval(0)},
{ interval(6.249997e-12),  interval(5.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.249999e-06), interval(1.562499e-12), interval(2.604166e-18)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999999e+00,  2.604166e-18,  1.562499e-12,  1.249999e-06},
{ 2.999997e+00,  1.041666e-17,  -7.057287e-19,  -2.499998e-06},
{ -9.999986e-01,  2.604164e-18,  -1.562499e-12,  1.249999e-06}};

#endif /*BENCHMARK_H_*/