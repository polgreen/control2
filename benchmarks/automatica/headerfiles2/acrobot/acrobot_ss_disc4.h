#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000002e+00),  interval(-1.567501e-06),  interval(5.000003e-04),  interval(-2.612501e-10)},
{ interval(-1.811252e-06),  interval(1.000004e+00),  interval(-3.018752e-10),  interval(5.000006e-04)},
{ interval(6.245007e-03),  interval(-6.270011e-03),  interval(1.000002e+00),  interval(-1.567501e-06)},
{ interval(-7.245013e-03),  interval(1.468002e-02),  interval(-1.811252e-06),  interval(1.000004e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-3.725003e-07), interval(7.475006e-07), interval(-1.490002e-03), interval(2.990005e-03)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000010e+00,  2.990005e-03,  -1.490002e-03,  7.475006e-07,  -3.725003e-07},
{ 6.000021e+00,  -8.970018e-03,  4.470009e-03,  -7.475016e-07,  3.725007e-07},
{ -4.000010e+00,  8.970018e-03,  -4.470009e-03,  -7.475016e-07,  3.725007e-07},
{ 1.000000e+00,  -2.990005e-03,  1.490002e-03,  7.475006e-07,  -3.725003e-07}};

#endif /*BENCHMARK_H_*/