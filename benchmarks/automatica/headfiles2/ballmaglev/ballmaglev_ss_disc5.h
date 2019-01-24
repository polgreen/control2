#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.021983e+00),  interval(5.036584e-03),  interval(-4.014716e-04)},
{ interval(8.825166e+00),  interval(1.021983e+00),  interval(-1.562364e-01)},
{ interval(0),  interval(0),  interval(8.258467e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.305040e-06), interval(-7.720608e-04), interval(8.751424e-03)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.869812e+00,  8.751424e-03,  -7.720608e-04,  -1.305040e-06},
{ 2.688002e+00,  -1.788761e-02,  4.782819e-05,  -4.990507e-06},
{ -8.258467e-01,  8.751424e-03,  7.242326e-04,  -1.185904e-06}};

#endif /*BENCHMARK_H_*/