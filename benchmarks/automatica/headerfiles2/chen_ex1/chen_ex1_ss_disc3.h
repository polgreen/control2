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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.940125e-01),  interval(-2.742510e-03),  interval(-1.495506e-03)},
{ interval(3.988017e-03),  interval(9.999945e-01),  interval(-2.994006e-06)},
{ interval(1.996004e-06),  interval(9.999982e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.985021e-04), interval(9.980021e-07), interval(3.328337e-10)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.994007e+00,  3.328337e-10,  9.980021e-07,  4.985021e-04},
{ 2.988025e+00,  1.329340e-09,  -1.994009e-09,  -9.970042e-04},
{ -9.940180e-01,  3.318367e-10,  -9.960081e-07,  4.985021e-04}};

#endif /*BENCHMARK_H_*/