#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
// No controller needed, safe and stable, completeness k with no controller =  5 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.366039e-02),  interval(-3.192240e-01),  interval(1.204086e-03),  interval(-4.029156e-17)},
{ interval(2.500000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1.953125e-03),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1.953125e-03),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(256), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -2.366039e-02,  0,  0,  0,  256},
{ 7.980600e-02,  0,  0,  64,  0},
{ -5.879326e-07,  0,  1.250000e-01,  0,  0},
{ 3.842502e-23,  2.441406e-04,  0,  0,  0}};

#endif /*BENCHMARK_H_*/