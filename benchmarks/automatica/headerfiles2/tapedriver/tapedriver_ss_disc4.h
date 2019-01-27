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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.420388e-01),  interval(-3.329555e-01),  interval(-1.458255e-01)},
{ interval(3.262062e-01),  interval(9.027057e-01),  interval(-4.372209e-02)},
{ interval(4.890232e-02),  interval(2.471540e-01),  interval(9.959795e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.548486e-03), interval(7.640988e-04), interval(7.026405e-05)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.240724e+00,  7.026405e-05,  7.640988e-04,  2.548486e-03},
{ 1.675050e+00,  2.260161e-04,  -1.941184e-04,  -5.103429e-03},
{ -4.147829e-01,  4.525651e-05,  -5.699804e-04,  2.554944e-03}};

#endif /*BENCHMARK_H_*/