#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.010  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.907479e+00),  interval(-4.408322e+00),  interval(2.545510e+00),  interval(-1.889978e+00),  interval(1.871173e+00),  interval(-1.235139e+00),  interval(5.241657e-01),  interval(-2.595399e-01),  interval(2.284828e-01)},
{ interval(8),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.814697e-06), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ 8.907479e+00,  0,  0,  0,  0,  0,  0,  0,  0,  -3.814697e-06},
{ -3.526657e+01,  0,  0,  0,  0,  0,  0,  0,  -3.051758e-05,  0},
{ 8.145631e+01,  0,  0,  0,  0,  0,  0,  -1.220703e-04,  0,  0},
{ -1.209586e+02,  0,  0,  0,  0,  0,  -2.441406e-04,  0,  0,  0},
{ 1.197551e+02,  0,  0,  0,  0,  -2.441406e-04,  0,  0,  0,  0},
{ -7.904891e+01,  0,  0,  0,  -2.441406e-04,  0,  0,  0,  0,  0},
{ 3.354660e+01,  0,  0,  -2.441406e-04,  0,  0,  0,  0,  0,  0},
{ -8.305278e+00,  0,  -1.220703e-04,  0,  0,  0,  0,  0,  0,  0},
{ 9.139312e-01,  -1.525879e-05,  0,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/