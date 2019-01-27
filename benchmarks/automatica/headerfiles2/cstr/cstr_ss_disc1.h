#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.487932e-01),  interval(-9.861797e-03),  interval(-1.945248e-03)},
{ interval(1.217729e-02),  interval(9.999378e-01),  interval(-1.226431e-05)},
{ interval(1.919369e-05),  interval(3.124935e-03),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.044321e-03), interval(1.919369e-05), interval(2.008068e-08)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.948731e+00,  2.008068e-08,  1.919369e-05,  3.044321e-03},
{ 2.897585e+00,  7.927896e-08,  -3.329622e-07,  -6.088643e-03},
{ -9.488543e-01,  1.956042e-08,  -1.886073e-05,  3.044321e-03}};

#endif /*BENCHMARK_H_*/