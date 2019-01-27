#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.116149e+00),  interval(9.538659e-02),  interval(-3.768663e-02)},
{ interval(1.671376e+02),  interval(4.116149e+00),  interval(-1.807659e+00)},
{ interval(0),  interval(0),  interval(1.475687e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.151013e-03), interval(-7.247430e-02), interval(4.283574e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -8.379866e+00,  4.283574e-02,  -7.247430e-02,  -1.151013e-03},
{ 2.214829e+00,  -3.526366e-01,  3.920009e-02,  -3.619818e-03},
{ -1.475687e-01,  4.283574e-02,  3.327420e-02,  -4.201576e-04}};

#endif /*BENCHMARK_H_*/