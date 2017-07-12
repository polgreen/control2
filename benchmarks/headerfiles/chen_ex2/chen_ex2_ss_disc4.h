#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
// stable. safety not checked, completeness k with no controller = 127
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.586401e+00),  interval(-4.730041e+00),  interval(3.869615e+00),  interval(-1.971908e+00),  interval(1.281717e+00),  interval(-5.187920e-01),  interval(2.390780e-01),  interval(-1.920499e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(4), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -6.586401e+00,  0,  0,  0,  0,  0,  0,  0,  4},
{ 1.892016e+01,  0,  0,  0,  0,  0,  0,  16,  0},
{ -3.095692e+01,  0,  0,  0,  0,  0,  32,  0,  0},
{ 3.155053e+01,  0,  0,  0,  0,  64,  0,  0,  0},
{ -2.050747e+01,  0,  0,  0,  64,  0,  0,  0,  0},
{ 8.300672e+00,  0,  0,  64,  0,  0,  0,  0,  0},
{ -1.912624e+00,  0,  32,  0,  0,  0,  0,  0,  0},
{ 1.920499e-01,  4,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/