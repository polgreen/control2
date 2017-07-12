#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
// No controller needed, safe and stable, completeness k with no controller =  3 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.086183e-08),  interval(-4.213273e-09),  interval(1.082726e-22)},
{ interval(7.450581e-09),  interval(0),  interval(0)},
{ interval(0),  interval(7.450581e-09),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ -1.086183e-08,  0,  0,  -2.500000e-01},
{ -3.139133e-17,  0,  -1.862645e-09,  0},
{ 6.010334e-39,  -1.387779e-17,  0,  0}};

#endif /*BENCHMARK_H_*/