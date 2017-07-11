#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-03 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.984989e+00),  interval(-5.227514e+00),  interval(2.173465e+00),  interval(-1.084407e+00),  interval(6.492520e-01),  interval(-4.319093e-01),  interval(2.462780e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.765625e-04), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0},
{ 6.984989e+00,  0,  0,  0,  0,  0,  0,  -9.765625e-04},
{ -2.091006e+01,  0,  0,  0,  0,  0,  -3.906250e-03,  0},
{ 3.477545e+01,  0,  0,  0,  0,  -1.562500e-02,  0,  0},
{ -3.470101e+01,  0,  0,  0,  -3.125000e-02,  0,  0,  0},
{ 2.077606e+01,  0,  0,  -3.125000e-02,  0,  0,  0,  0},
{ -6.910549e+00,  0,  -1.562500e-02,  0,  0,  0,  0,  0},
{ 9.851119e-01,  -3.906250e-03,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/