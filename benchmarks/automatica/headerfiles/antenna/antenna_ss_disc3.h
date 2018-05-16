#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.894408e+00),  interval(-1.718491e+00),  interval(1.292322e+00),  interval(-7.570273e-01),  interval(5.500668e-01),  interval(-3.123267e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.765625e-04), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.894408e+00,  9.765625e-04,  0,  0,  0,  0,  0},
{ 3.436982e+00,  0,  1.953125e-03,  0,  0,  0,  0},
{ -2.584643e+00,  0,  0,  1.953125e-03,  0,  0,  0},
{ 1.514055e+00,  0,  0,  0,  1.953125e-03,  0,  0},
{ -5.500668e-01,  0,  0,  0,  0,  9.765625e-04,  0},
{ 7.808167e-02,  0,  0,  0,  0,  0,  2.441406e-04}};

#endif /*BENCHMARK_H_*/