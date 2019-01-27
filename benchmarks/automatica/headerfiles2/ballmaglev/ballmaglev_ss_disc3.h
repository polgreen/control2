#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000876e+00),  interval(1.000292e-03),  interval(-1.682262e-05)},
{ interval(1.752724e+00),  interval(1.000876e+00),  interval(-3.343696e-02)},
{ interval(0),  interval(0),  interval(9.624538e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.081740e-08), interval(-3.235119e-05), interval(1.886745e-03)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.964206e+00,  1.886745e-03,  -3.235119e-05,  -1.081740e-08},
{ 2.926594e+00,  -3.776796e-03,  4.101072e-07,  -4.286251e-08},
{ -9.624538e-01,  1.886745e-03,  3.194108e-05,  -1.061237e-08}};

#endif /*BENCHMARK_H_*/