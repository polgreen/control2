#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.699505e-01),  interval(-5.691634e-01),  interval(4.907328e-02),  interval(-1.269513e-08)},
{ interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(3.125000e-02),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(3.125000e-02),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(16), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -7.699505e-01,  0,  0,  0,  16},
{ 2.845817e-01,  0,  0,  8,  0},
{ -7.667699e-04,  0,  2.500000e-01,  0,  0},
{ 6.198792e-12,  7.812500e-03,  0,  0,  0}};

#endif /*BENCHMARK_H_*/