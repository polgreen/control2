#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-5.584676e-01),  interval(1.060472e+00),  interval(1.633580e+00),  interval(1.744956e-01),  interval(-7.023347e-01),  interval(-6.077449e-01)},
{ interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ 5.584676e-01,  2,  0,  0,  0,  0,  0},
{ -1.060472e+00,  0,  2,  0,  0,  0,  0},
{ -1.633580e+00,  0,  0,  2,  0,  0,  0},
{ -1.744956e-01,  0,  0,  0,  2,  0,  0},
{ 7.023347e-01,  0,  0,  0,  0,  2,  0},
{ 6.077449e-01,  0,  0,  0,  0,  0,  2}};

#endif /*BENCHMARK_H_*/