#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999729e-01),  interval(-3.335175e-07),  interval(0)},
{ interval(4.999932e-05),  interval(1.000000e+00),  interval(0)},
{ interval(2.499977e-09),  interval(1.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499966e-05), interval(6.249944e-10), interval(2.083319e-14)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999973e+00,  2.083319e-14,  6.249944e-10,  2.499966e-05},
{ 2.999946e+00,  8.333220e-14,  -5.645757e-15,  -4.999932e-05},
{ -9.999729e-01,  2.083291e-14,  -6.249887e-10,  2.499966e-05}};

#endif /*BENCHMARK_H_*/