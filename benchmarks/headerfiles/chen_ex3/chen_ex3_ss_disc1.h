#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-01 
// No controller needed, safe and stable, suggested completeness k 7 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.294464e-01),  interval(-2.761755e-01),  interval(1.439034e-01),  interval(-7.846111e-02),  interval(6.814942e-02),  interval(-2.617412e-02),  interval(7.079480e-02)},
{ interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0},
{ 7.294464e-01,  0,  0,  0,  0,  0,  0,  -1},
{ -2.761755e-01,  0,  0,  0,  0,  0,  -1,  0},
{ 1.439034e-01,  0,  0,  0,  0,  -1,  0,  0},
{ -3.923056e-02,  0,  0,  0,  -5.000000e-01,  0,  0,  0},
{ 1.703735e-02,  0,  0,  -2.500000e-01,  0,  0,  0,  0},
{ -1.635882e-03,  0,  -6.250000e-02,  0,  0,  0,  0,  0},
{ 5.530844e-04,  -7.812500e-03,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/