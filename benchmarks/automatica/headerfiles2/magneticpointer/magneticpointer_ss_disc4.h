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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.998645e-01),  interval(-1.667497e-06),  interval(0)},
{ interval(2.499831e-04),  interval(1.000000e+00),  interval(0)},
{ interval(6.249718e-08),  interval(5.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.249915e-04), interval(1.562429e-08), interval(2.604078e-12)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999865e+00,  2.604078e-12,  1.562429e-08,  1.249915e-04},
{ 2.999729e+00,  1.041596e-11,  -7.056814e-13,  -2.499831e-04},
{ -9.998645e-01,  2.603902e-12,  -1.562359e-08,  1.249915e-04}};

#endif /*BENCHMARK_H_*/