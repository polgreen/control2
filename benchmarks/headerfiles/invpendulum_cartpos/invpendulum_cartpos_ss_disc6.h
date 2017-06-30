#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-03 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.000025e+00),  interval(-1.500013e+00),  interval(1.000006e+00),  interval(-5.000000e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.441406e-04), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000025e+00,  0,  0,  0,  2.441406e-04},
{ 6.000050e+00,  0,  0,  9.765625e-04,  0},
{ -4.000025e+00,  0,  9.765625e-04,  0,  0},
{ 1,  4.882812e-04,  0,  0,  0}};

#endif /*BENCHMARK_H_*/