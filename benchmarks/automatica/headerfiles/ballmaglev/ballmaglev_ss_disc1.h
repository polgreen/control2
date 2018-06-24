#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.288536e+01),  interval(7.852508e-01),  interval(-3.331115e-01)},
{ interval(1.375926e+03),  interval(3.288536e+01),  interval(-1.400620e+01)},
{ interval(0),  interval(0),  interval(2.177652e-02)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.441616e-02), interval(-6.405991e-01), interval(4.915696e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -6.579250e+01,  4.915696e-02,  -6.405991e-01,  -1.441616e-02},
{ 2.432257e+00,  -3.233089e+00,  5.562075e-01,  -4.501104e-02},
{ -2.177652e-02,  4.915696e-02,  8.439162e-02,  -1.526751e-03}};

#endif /*BENCHMARK_H_*/