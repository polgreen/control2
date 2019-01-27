#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000009e+00),  interval(1.000003e-04),  interval(-1.701371e-07)},
{ interval(1.752218e-01),  interval(1.000009e+00),  interval(-3.400579e-03)},
{ interval(0),  interval(0),  interval(9.961804e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.090970e-11), interval(-3.271868e-07), interval(1.919402e-04)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.996198e+00,  1.919402e-04,  -3.271868e-07,  -1.090970e-11},
{ 2.992378e+00,  -3.838837e-04,  4.171072e-10,  -4.359711e-11},
{ -9.961804e-01,  1.919402e-04,  3.267697e-07,  -1.088884e-11}};

#endif /*BENCHMARK_H_*/