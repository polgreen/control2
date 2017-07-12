#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.005  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000156e+00),  interval(-1.567637e-04),  interval(5.000260e-03),  interval(-2.612637e-07)},
{ interval(-1.811408e-04),  interval(1.000367e+00),  interval(-3.018908e-07),  interval(5.000612e-03)},
{ interval(6.245704e-02),  interval(-6.271093e-02),  interval(1.000156e+00),  interval(-1.567637e-04)},
{ interval(-7.246263e-02),  interval(1.468217e-01),  interval(-1.811408e-04),  interval(1.000367e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-3.725292e-05), interval(7.475570e-05), interval(-1.490234e-02), interval(2.990456e-02)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.001046e+00,  2.990456e-02,  -1.490234e-02,  7.475570e-05,  -3.725292e-05},
{ 6.002093e+00,  -8.971761e-02,  4.470858e-02,  -7.476554e-05,  3.725683e-05},
{ -4.001046e+00,  8.971761e-02,  -4.470858e-02,  -7.476554e-05,  3.725683e-05},
{ 1,  -2.990456e-02,  1.490234e-02,  7.475570e-05,  -3.725292e-05}};

#endif /*BENCHMARK_H_*/