#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 1 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = { interval(9.753099e-01)};
 const __plant_typet _controller_B[NSTATES] = {interval(1.543130e-02)};
const __plant_typet __char_poly_const[2][2] = 
 {{ 1,  0},
{ -9.753099e-01,  1.543130e-02}};

#endif /*BENCHMARK_H_*/