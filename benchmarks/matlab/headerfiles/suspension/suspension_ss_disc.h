#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.377293e-05),  interval(4.660464e-05),  interval(7.174996e-05),  interval(2.199300e-05)},
{ interval(-1.702991e-04),  interval(-3.195749e-04),  interval(-4.044589e-04),  interval(1.495685e-04)},
{ interval(-2.895396e-04),  interval(-6.263289e-04),  interval(-1.324175e-03),  interval(-1.530528e-03)},
{ interval(1.481423e-03),  interval(2.950573e-03),  interval(4.826849e-03),  interval(2.367931e-03)}};
const __plant_typet _controller_B[NSTATES] = {interval(-5.321847e-06), interval(-3.619246e-05), interval(3.703558e-04), interval(2.414061e-01)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -7.479541e-04,  2.414061e-01,  3.703558e-04,  -3.619246e-05,  -5.321847e-06},
{ 3.237226e-06,  3.927452e-04,  -3.702221e-04,  3.599650e-05,  5.337985e-06},
{ -7.089229e-26,  3.859157e-08,  -1.337612e-07,  1.959521e-07,  -1.613850e-08},
{ -6.172801e-47,  1.307296e-28,  -3.000352e-28,  -5.102908e-28,  1.784983e-27}};

#endif /*BENCHMARK_H_*/