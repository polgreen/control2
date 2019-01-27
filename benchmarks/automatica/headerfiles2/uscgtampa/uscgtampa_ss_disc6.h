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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999865e-01),  interval(-1.667599e-07),  interval(0)},
{ interval(2.499983e-05),  interval(1.000000e+00),  interval(0)},
{ interval(6.249972e-10),  interval(5.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.249992e-05), interval(1.562493e-10), interval(2.604158e-15)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999986e+00,  2.604158e-15,  1.562493e-10,  1.249992e-05},
{ 2.999973e+00,  1.041660e-14,  -7.057244e-16,  -2.499983e-05},
{ -9.999865e-01,  2.604140e-15,  -1.562486e-10,  1.249992e-05}};

#endif /*BENCHMARK_H_*/