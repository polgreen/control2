#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.998646e+00),  interval(-1.498646e+00),  interval(9.986459e-01)},
{ interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(5.000000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.882812e-04), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.998646e+00,  0,  0,  -4.882812e-04},
{ -2.997292e+00,  0,  -9.765625e-04,  0},
{ 9.986459e-01,  -4.882812e-04,  0,  0}};

#endif /*BENCHMARK_H_*/