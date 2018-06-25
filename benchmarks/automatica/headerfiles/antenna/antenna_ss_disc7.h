#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.974361e+00),  interval(-3.718068e+00),  interval(2.468184e+00),  interval(-1.843299e+00),  interval(7.342069e-01),  interval(-4.874112e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.490116e-08), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.974361e+00,  1.490116e-08,  0,  0,  0,  0,  0},
{ 1.487227e+01,  0,  5.960464e-08,  0,  0,  0,  0},
{ -1.974547e+01,  0,  0,  1.192093e-07,  0,  0,  0},
{ 1.474639e+01,  0,  0,  0,  1.192093e-07,  0,  0},
{ -5.873655e+00,  0,  0,  0,  0,  1.192093e-07,  0},
{ 9.748224e-01,  0,  0,  0,  0,  0,  2.980232e-08}};

#endif /*BENCHMARK_H_*/