#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
// No controller needed, safe and stable, completeness k with no controller =  1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.006218e+00),  interval(-1.077533e-01)},
{ interval(6.250000e-02),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250000e-02), interval(0)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -1.006218e+00,  0,  6.250000e-02},
{ 6.734579e-03,  3.906250e-03,  0}};

#endif /*BENCHMARK_H_*/