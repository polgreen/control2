#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.990975e+00),  interval(-4.490983e+00),  interval(2.617117e+00),  interval(-1.960874e+00),  interval(1.958914e+00),  interval(-1.304639e+00),  interval(5.585730e-01),  interval(-2.790080e-01),  interval(2.477601e-01)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.450581e-09), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.990975e+00,  7.450581e-09,  0,  0,  0,  0,  0,  0,  0,  0},
{ 3.592786e+01,  0,  5.960464e-08,  0,  0,  0,  0,  0,  0,  0},
{ -8.374775e+01,  0,  0,  2.384186e-07,  0,  0,  0,  0,  0,  0},
{ 1.254960e+02,  0,  0,  0,  4.768372e-07,  0,  0,  0,  0,  0},
{ -1.253705e+02,  0,  0,  0,  0,  4.768372e-07,  0,  0,  0,  0},
{ 8.349688e+01,  0,  0,  0,  0,  0,  4.768372e-07,  0,  0,  0},
{ -3.574867e+01,  0,  0,  0,  0,  0,  0,  4.768372e-07,  0,  0},
{ 8.928257e+00,  0,  0,  0,  0,  0,  0,  0,  2.384186e-07,  0},
{ -9.910404e-01,  0,  0,  0,  0,  0,  0,  0,  0,  2.980232e-08}};

#endif /*BENCHMARK_H_*/