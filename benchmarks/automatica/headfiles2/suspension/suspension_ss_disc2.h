#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-6.845458e-09),  interval(-2.276665e-09),  interval(7.806263e-79),  interval(0)},
{ interval(1.490116e-08),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2.980232e-08),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.960464e-08),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(33554432), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ 6.845458e-09,  33554432,  0,  0,  0},
{ 3.392495e-17,  0,  5.000000e-01,  0,  0},
{ -3.466677e-94,  0,  0,  1.490116e-08,  0},
{ 0,  0,  0,  0,  8.881784e-16}};

#endif /*BENCHMARK_H_*/