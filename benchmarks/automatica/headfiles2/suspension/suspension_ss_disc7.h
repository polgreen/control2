#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.010  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.072734e+00),  interval(-1.360203e+00),  interval(5.395038e-01),  interval(-9.174479e-02)},
{ interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -2.072734e+00,  1,  0,  0,  0},
{ 1.360203e+00,  0,  1,  0,  0},
{ -2.697519e-01,  0,  0,  5.000000e-01,  0},
{ 5.734049e-03,  0,  0,  0,  6.250000e-02}};

#endif /*BENCHMARK_H_*/