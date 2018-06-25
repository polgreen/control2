#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.075  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.156732e+01),  interval(2.753027e-01),  interval(-1.154742e-01)},
{ interval(4.823889e+02),  interval(1.156732e+01),  interval(-4.960676e+00)},
{ interval(0),  interval(0),  interval(5.668802e-02)}};
const __plant_typet _controller_B[NSTATES] = {interval(-4.522692e-03), interval(-2.220657e-01), interval(4.740261e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.319134e+01,  4.740261e-02,  -2.220657e-01,  -4.522692e-03},
{ 2.311457e+00,  -1.096643e+00,  1.644495e-01,  -1.403726e-02},
{ -5.668802e-02,  4.740261e-02,  5.761624e-02,  -9.202228e-04}};

#endif /*BENCHMARK_H_*/