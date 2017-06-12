#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 1.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 8 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(5.540349e+00),  interval(-3.321083e+00),  interval(2.248482e+00),  interval(-9.393281e-01),  interval(4.953709e-01),  interval(-3.216924e-01),  interval(1.174609e-01),  interval(-7.376633e-02)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(4)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -5.540349e+00,  0,  0,  0,  0,  0,  0,  0,  4},
{ 1.328433e+01,  0,  0,  0,  0,  0,  0,  16,  0},
{ -1.798786e+01,  0,  0,  0,  0,  0,  32,  0,  0},
{ 1.502925e+01,  0,  0,  0,  0,  64,  0,  0,  0},
{ -7.925934e+00,  0,  0,  0,  64,  0,  0,  0,  0},
{ 2.573539e+00,  0,  0,  32,  0,  0,  0,  0,  0},
{ -4.698435e-01,  0,  16,  0,  0,  0,  0,  0,  0},
{ 3.688317e-02,  2,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/