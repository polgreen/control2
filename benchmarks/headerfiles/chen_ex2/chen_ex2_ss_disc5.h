#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.010  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.680469e+00),  interval(-6.451100e+00),  interval(3.095862e+00),  interval(-1.856858e+00),  interval(1.425361e+00),  interval(-6.837370e-01),  interval(3.747859e-01),  interval(-1.797309e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.680469e+00,  2,  0,  0,  0,  0,  0,  0,  0},
{ 2.580440e+01,  0,  8,  0,  0,  0,  0,  0,  0},
{ -4.953379e+01,  0,  0,  32,  0,  0,  0,  0,  0},
{ 5.941947e+01,  0,  0,  0,  64,  0,  0,  0,  0},
{ -4.561154e+01,  0,  0,  0,  0,  64,  0,  0,  0},
{ 2.187958e+01,  0,  0,  0,  0,  0,  64,  0,  0},
{ -5.996574e+00,  0,  0,  0,  0,  0,  0,  32,  0},
{ 7.189237e-01,  0,  0,  0,  0,  0,  0,  0,  8}};

#endif /*BENCHMARK_H_*/