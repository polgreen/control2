#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.048279e-01),  interval(-9.896858e-03)},
{ interval(9.516210e-05),  interval(9.999995e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.516210e-05), interval(4.837402e-09)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.904827e+00,  4.837402e-09,  9.516210e-05},
{ 9.048284e-01,  4.678809e-09,  -9.516210e-05}};

#endif /*BENCHMARK_H_*/