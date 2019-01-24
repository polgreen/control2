#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.034722e-04),  interval(-1.034718e-01)},
{ interval(9.949209e-04),  interval(9.949169e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.949209e-04), interval(4.887550e-05)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.948135e-01,  4.887550e-05,  9.949209e-04},
{ -1.795973e-20,  9.949249e-07,  -9.949209e-04}};

#endif /*BENCHMARK_H_*/