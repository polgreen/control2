#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000000e+00),  interval(5.000000e-05),  interval(0),  interval(0)},
{ interval(5.000000e-05),  interval(1.000000e+00),  interval(0),  interval(0)},
{ interval(1.250000e-09),  interval(5.000000e-05),  interval(1),  interval(0)},
{ interval(2.083333e-14),  interval(1.250000e-09),  interval(5.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.000000e-05), interval(1.250000e-09), interval(2.083333e-14), interval(2.604167e-19)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000000e+00,  2.604167e-19,  2.083333e-14,  1.250000e-09,  5.000000e-05},
{ 6.000000e+00,  2.864583e-18,  6.250000e-14,  -1.250000e-09,  -1.500000e-04},
{ -4.000000e+00,  2.864583e-18,  -6.250000e-14,  -1.250000e-09,  1.500000e-04},
{ 1.000000e+00,  2.604167e-19,  -2.083333e-14,  1.250000e-09,  -5.000000e-05}};

#endif /*BENCHMARK_H_*/