#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.519668e-17),  interval(-3.550333e-17),  interval(9.514085e-33)},
{ interval(2.775558e-17),  interval(0),  interval(0)},
{ interval(0),  interval(2.775558e-17),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 5.519668e-17,  0,  0,  -2.500000e-01},
{ -9.854155e-34,  0,  -6.938894e-18,  0},
{ 7.329384e-66,  -1.925930e-34,  0,  0}};

#endif /*BENCHMARK_H_*/