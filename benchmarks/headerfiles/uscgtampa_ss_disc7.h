#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-02 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.997294e+00),  interval(-1.497294e+00),  interval(4.986468e-01)},
{ interval(2),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.765625e-04), interval(0), interval(0)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.997294e+00,  0,  0,  -9.765625e-04},
{ -2.994587e+00,  0,  -1.953125e-03,  0},
{ 9.972937e-01,  -1.953125e-03,  0,  0}};

#endif /*BENCHMARK_H_*/