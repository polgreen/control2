#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.145079e-83),  interval(3.836575e-83),  interval(1.494548e-83)},
{ interval(-3.343247e-83),  interval(-2.601126e-83),  interval(1.296412e-83)},
{ interval(-1.450013e-83),  interval(-4.163833e-83),  interval(-5.366806e-83)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.276888e-19), interval(1.112320e-18), interval(1.747627e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ 4.822853e-83,  1.747627e-02,  1.112320e-18,  1.276888e-19},
{ 9.291736e-166,  -9.506263e-86,  2.265645e-85,  2.611912e-85},
{ -3.790750e-263,  8.119243e-168,  -1.585790e-167,  1.548623e-167}};

#endif /*BENCHMARK_H_*/