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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.111777e-01),  interval(-2.091381e-01),  interval(-1.107232e-01)},
{ interval(2.952619e-01),  interval(9.540705e-01),  interval(-2.458240e-02)},
{ interval(1.638827e-02),  interval(9.839786e-02),  interval(9.991382e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.690773e-02), interval(8.194133e-03), interval(2.872615e-04)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.464386e+00,  2.872615e-04,  8.194133e-03,  3.690773e-02},
{ 2.017669e+00,  9.902295e-04,  -1.485344e-03,  -7.383402e-02},
{ -5.488116e-01,  2.128085e-04,  -6.708788e-03,  3.692628e-02}};

#endif /*BENCHMARK_H_*/