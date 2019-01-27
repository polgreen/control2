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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.997000e-01),  interval(-1.374813e-04),  interval(-7.498875e-05)},
{ interval(1.999700e-04),  interval(1.000000e+00),  interval(-7.499250e-09)},
{ interval(4.999500e-09),  interval(5.000000e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499625e-05), interval(2.499750e-09), interval(4.166354e-14)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999700e+00,  4.166354e-14,  2.499750e-09,  2.499625e-05},
{ 2.999400e+00,  1.666417e-13,  -2.499625e-13,  -4.999250e-05},
{ -9.997000e-01,  4.165729e-14,  -2.499500e-09,  2.499625e-05}};

#endif /*BENCHMARK_H_*/