#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.730886e-01),  interval(-1.559456e-03),  interval(0)},
{ interval(2.337860e-01),  interval(9.998007e-01),  interval(0)},
{ interval(5.976812e-02),  interval(4.999664e-01),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.168930e-01), interval(1.494203e-02), interval(2.518236e-03)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.872889e+00,  2.518236e-03,  1.494203e-02,  1.168930e-01},
{ 2.746168e+00,  9.740611e-03,  -6.597887e-04,  -2.337860e-01},
{ -8.732792e-01,  2.353288e-03,  -1.428224e-02,  1.168930e-01}};

#endif /*BENCHMARK_H_*/