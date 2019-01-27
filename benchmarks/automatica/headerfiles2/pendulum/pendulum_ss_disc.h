#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.750333e-03),  interval(-7.830142e-01)},
{ interval(1.277087e+00),  interval(4.750333e-03)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.277087e+00), interval(1.623241e+00)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.500665e-03,  1.623241e+00,  1.277087e+00},
{ 1.000000e+00,  1.623241e+00,  -1.277087e+00}};

#endif /*BENCHMARK_H_*/