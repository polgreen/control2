#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.017618e+00),  interval(-1.930139e+00),  interval(1.709861e+00),  interval(-1.519539e+00),  interval(1.541584e+00),  interval(-8.193860e-01)},
{ interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.000000e-01), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.017618e+00,  5.000000e-01,  0,  0,  0,  0,  0},
{ 1.930139e+00,  0,  5.000000e-01,  0,  0,  0,  0},
{ -1.709861e+00,  0,  0,  5.000000e-01,  0,  0,  0},
{ 1.519539e+00,  0,  0,  0,  5.000000e-01,  0,  0},
{ -1.541584e+00,  0,  0,  0,  0,  5.000000e-01,  0},
{ 8.193860e-01,  0,  0,  0,  0,  0,  5.000000e-01}};

#endif /*BENCHMARK_H_*/