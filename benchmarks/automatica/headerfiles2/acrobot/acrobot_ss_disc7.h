#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(-6.270000e-10),  interval(1.000000e-05),  interval(-2.090000e-15)},
{ interval(-7.245000e-10),  interval(1.000000e+00),  interval(-2.415000e-15),  interval(1.000000e-05)},
{ interval(1.249000e-04),  interval(-1.254000e-04),  interval(1.000000e+00),  interval(-6.270000e-10)},
{ interval(-1.449000e-04),  interval(2.936000e-04),  interval(-7.245000e-10),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.490000e-10), interval(2.990000e-10), interval(-2.980000e-05), interval(5.980000e-05)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000000e+00,  5.980000e-05,  -2.980000e-05,  2.990000e-10,  -1.490000e-10},
{ 6.000000e+00,  -1.794000e-04,  8.940000e-05,  -2.990000e-10,  1.490000e-10},
{ -4.000000e+00,  1.794000e-04,  -8.940000e-05,  -2.990000e-10,  1.490000e-10},
{ 1.000000e+00,  -5.980000e-05,  2.980000e-05,  2.990000e-10,  -1.490000e-10}};

#endif /*BENCHMARK_H_*/