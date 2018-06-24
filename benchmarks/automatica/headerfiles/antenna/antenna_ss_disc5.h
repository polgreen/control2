#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.966709e+00),  interval(-9.336645e-01),  interval(-1.311890e-01),  interval(-3.175732e-02),  interval(1.366500e-02),  interval(-2.826445e-04)},
{ interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2.500000e-01),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(3.125000e-02),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(7.812500e-03),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(4.882812e-04),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.562500e-02), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -1.966709e+00,  1.562500e-02,  0,  0,  0,  0,  0},
{ 9.336645e-01,  0,  1.562500e-02,  0,  0,  0,  0},
{ 3.279724e-02,  0,  0,  3.906250e-03,  0,  0,  0},
{ 2.481040e-04,  0,  0,  0,  1.220703e-04,  0,  0},
{ -8.340454e-07,  0,  0,  0,  0,  9.536743e-07,  0},
{ 8.423464e-12,  0,  0,  0,  0,  0,  4.656613e-10}};

#endif /*BENCHMARK_H_*/