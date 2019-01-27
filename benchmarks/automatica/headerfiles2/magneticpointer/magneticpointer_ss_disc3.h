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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.997290e-01),  interval(-3.334768e-06),  interval(0)},
{ interval(4.999323e-04),  interval(1.000000e+00),  interval(0)},
{ interval(2.499774e-07),  interval(1.000000e-03),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499661e-04), interval(6.249435e-08), interval(2.083192e-11)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999729e+00,  2.083192e-11,  6.249435e-08,  2.499661e-04},
{ 2.999458e+00,  8.332204e-11,  -5.645068e-12,  -4.999323e-04},
{ -9.997290e-01,  2.082910e-11,  -6.248871e-08,  2.499661e-04}};

#endif /*BENCHMARK_H_*/