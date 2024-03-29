#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.075843e-33),  interval(-1.260487e-33),  interval(1.051845e-48)},
{ interval(7.703720e-34),  interval(0),  interval(0)},
{ interval(0),  interval(7.703720e-34),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -1.075843e-33,  1.250000e-01,  0,  0},
{ 9.710436e-67,  0,  9.629650e-35,  0},
{ -6.242418e-115,  0,  0,  7.418412e-68}};

#endif /*BENCHMARK_H_*/