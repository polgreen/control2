#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.983490e+00),  interval(-3.732253e+00),  interval(2.485140e+00),  interval(-1.863025e+00),  interval(7.454540e-01),  interval(-4.975162e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.812500e-03), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.983490e+00,  0,  0,  0,  0,  0,  7.812500e-03},
{ 1.492901e+01,  0,  0,  0,  0,  3.125000e-02,  0},
{ -1.988112e+01,  0,  0,  0,  6.250000e-02,  0,  0},
{ 1.490420e+01,  0,  0,  6.250000e-02,  0,  0,  0},
{ -5.963632e+00,  0,  6.250000e-02,  0,  0,  0,  0},
{ 9.950324e-01,  1.562500e-02,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/