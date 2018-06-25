#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.676440e-166),  interval(0),  interval(0)},
{ interval(5.125333e-144),  interval(0),  interval(0)},
{ interval(0),  interval(2.562666e-144),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.250000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -4.676440e-166,  1.250000e-01,  0,  0},
{ 0,  0,  6.406666e-145,  0},
{ 0,  0,  0,  1.641815e-288}};

#endif /*BENCHMARK_H_*/