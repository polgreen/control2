#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000219e+00),  interval(5.000365e-04),  interval(-4.231970e-06)},
{ interval(8.761702e-01),  interval(1.000219e+00),  interval(-1.687469e-02)},
{ interval(0),  interval(0),  interval(9.810473e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.358541e-09), interval(-8.138404e-06), interval(9.523975e-04)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.981485e+00,  9.523975e-04,  -8.138404e-06,  -1.358541e-09},
{ 2.962524e+00,  -1.905212e-03,  5.174459e-08,  -5.408386e-09},
{ -9.810473e-01,  9.523975e-04,  8.086659e-06,  -1.345605e-09}};

#endif /*BENCHMARK_H_*/