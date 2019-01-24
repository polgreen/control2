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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.519668e-17),  interval(-3.550333e-17),  interval(9.514085e-33)},
{ interval(2.775558e-17),  interval(0),  interval(0)},
{ interval(0),  interval(2.775558e-17),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -5.519668e-17,  2.500000e-01,  0,  0},
{ 9.854155e-34,  0,  6.938894e-18,  0},
{ -7.329384e-66,  0,  0,  1.925930e-34}};

#endif /*BENCHMARK_H_*/