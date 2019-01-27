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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-2.562480e-17),  interval(-4.180707e-17),  interval(-3.277902e-17)},
{ interval(7.332542e-17),  interval(1.004033e-16),  interval(5.624299e-17)},
{ interval(-6.290672e-17),  interval(-7.145822e-17),  interval(-1.958178e-17)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.432426e-19), interval(-3.576156e-18), interval(1.747627e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -5.519668e-17,  1.747627e-02,  -3.576156e-18,  -1.432426e-19},
{ 9.854155e-34,  -1.306848e-18,  9.829175e-19,  -5.728548e-19},
{ 4.623921e-65,  8.610692e-36,  -1.681776e-35,  1.642359e-35}};

#endif /*BENCHMARK_H_*/