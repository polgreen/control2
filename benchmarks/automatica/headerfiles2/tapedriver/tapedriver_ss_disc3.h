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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.247192e-03),  interval(-4.504859e-01),  interval(-1.805597e-01)},
{ interval(4.039052e-01),  interval(6.954593e-01),  interval(-1.305837e-01)},
{ interval(1.460554e-01),  interval(4.529853e-01),  interval(9.740378e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.155510e-03), interval(2.282115e-03), interval(4.537225e-04)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -1.670744e+00,  4.537225e-04,  2.282115e-03,  3.155510e-03},
{ 9.469636e-01,  1.178532e-03,  -1.010434e-03,  -6.378099e-03},
{ -1.720449e-01,  1.883262e-04,  -1.271681e-03,  3.222589e-03}};

#endif /*BENCHMARK_H_*/