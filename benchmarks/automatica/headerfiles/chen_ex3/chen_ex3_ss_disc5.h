#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.010  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.848902e+00),  interval(-5.026456e+00),  interval(2.049685e+00),  interval(-1.003115e+00),  interval(5.891859e-01),  interval(-3.845642e-01),  interval(2.151770e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.562500e-02), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.848902e+00,  1.562500e-02,  0,  0,  0,  0,  0,  0},
{ 2.010582e+01,  0,  6.250000e-02,  0,  0,  0,  0,  0},
{ -3.279496e+01,  0,  0,  2.500000e-01,  0,  0,  0,  0},
{ 3.209967e+01,  0,  0,  0,  5.000000e-01,  0,  0,  0},
{ -1.885395e+01,  0,  0,  0,  0,  5.000000e-01,  0,  0},
{ 6.153027e+00,  0,  0,  0,  0,  0,  2.500000e-01,  0},
{ -8.607080e-01,  0,  0,  0,  0,  0,  0,  6.250000e-02}};

#endif /*BENCHMARK_H_*/