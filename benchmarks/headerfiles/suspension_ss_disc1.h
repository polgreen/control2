#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 4 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(-5.915017e-06),  interval(-2.747173e-06),  interval(3.391216e-52),  interval(-1.264041e-208)},
{ interval(3.814697e-06),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(3.814697e-06),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(3.814697e-06),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(131072)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ 5.915017e-06,  0,  0,  0,  131072},
{ 1.047963e-11,  0,  0,  5.000000e-01,  0},
{ -4.934869e-63,  0,  1.907349e-06,  0,  0},
{ 7.016837e-225,  7.275958e-12,  0,  0,  0}};

#endif /*BENCHMARK_H_*/