#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)100
#define INPUT_LOWERBOUND (__plant_precisiont)-100
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.002501e+00),  interval(-3.002501e+00),  interval(1.000625e+00),  interval(-5.000000e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.002501e+00,  0,  0,  0,  7.812500e-03},
{ 6.005001e+00,  0,  0,  1.562500e-02,  0},
{ -4.002501e+00,  0,  3.125000e-02,  0,  0},
{ 1,  1.562500e-02,  0,  0,  0}};

#endif /*BENCHMARK_H_*/