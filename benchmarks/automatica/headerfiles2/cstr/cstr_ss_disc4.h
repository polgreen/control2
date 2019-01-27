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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.997375e-01),  interval(-5.059344e-05),  interval(-9.982690e-06)},
{ interval(6.249180e-05),  interval(1.000000e+00),  interval(-3.119727e-10)},
{ interval(4.882385e-10),  interval(1.562500e-05),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.562295e-05), interval(4.882385e-10), interval(2.542965e-15)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.999738e+00,  2.542965e-15,  4.882385e-10,  1.562295e-05},
{ 2.999475e+00,  1.017119e-14,  -4.271900e-14,  -3.124590e-05},
{ -9.997375e-01,  2.542631e-15,  -4.881958e-10,  1.562295e-05}};

#endif /*BENCHMARK_H_*/