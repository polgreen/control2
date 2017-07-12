#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-01 
// No controller needed, safe and stable, completeness k with no controller =  1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.872889e+00),  interval(-1.373084e+00),  interval(8.732792e-01)},
{ interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250000e-02), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.872889e+00,  0,  0,  -6.250000e-02},
{ -2.746168e+00,  0,  -1.250000e-01,  0},
{ 8.732792e-01,  -6.250000e-02,  0,  0}};

#endif /*BENCHMARK_H_*/