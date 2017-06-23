#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.894408e+00),  interval(-8.592455e-01),  interval(6.461608e-01),  interval(-3.785136e-01),  interval(2.750334e-01),  interval(-1.561633e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.765625e-04), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.894408e+00,  0,  0,  0,  0,  0,  9.765625e-04},
{ 3.436982e+00,  0,  0,  0,  0,  3.906250e-03,  0},
{ -2.584643e+00,  0,  0,  0,  3.906250e-03,  0,  0},
{ 1.514055e+00,  0,  0,  3.906250e-03,  0,  0,  0},
{ -5.500668e-01,  0,  1.953125e-03,  0,  0,  0,  0},
{ 7.808167e-02,  4.882812e-04,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/