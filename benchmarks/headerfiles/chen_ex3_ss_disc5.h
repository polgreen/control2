#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-02 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.848902e+00),  interval(-2.513228e+00),  interval(2.049685e+00),  interval(-1.003115e+00),  interval(5.891859e-01),  interval(-3.845642e-01),  interval(2.151770e-01)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0},
{ 6.848902e+00,  0,  0,  0,  0,  0,  0,  -7.812500e-03},
{ -2.010582e+01,  0,  0,  0,  0,  0,  -6.250000e-02,  0},
{ 3.279496e+01,  0,  0,  0,  0,  -1.250000e-01,  0,  0},
{ -3.209967e+01,  0,  0,  0,  -2.500000e-01,  0,  0,  0},
{ 1.885395e+01,  0,  0,  -2.500000e-01,  0,  0,  0,  0},
{ -6.153027e+00,  0,  -1.250000e-01,  0,  0,  0,  0,  0},
{ 8.607080e-01,  -3.125000e-02,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/