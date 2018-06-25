#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.025  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.599398e+00),  interval(2.981953e-02),  interval(-8.773700e-03)},
{ interval(5.225014e+01),  interval(1.599398e+00),  interval(-6.802122e-01)},
{ interval(0),  interval(0),  interval(3.841467e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.447871e-04), interval(-1.687250e-02), interval(3.094740e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -3.582943e+00,  3.094740e-02,  -1.687250e-02,  -1.447871e-04},
{ 2.228807e+00,  -9.899444e-02,  4.851411e-03,  -4.874614e-04},
{ -3.841467e-01,  3.094740e-02,  1.202109e-02,  -8.913319e-05}};

#endif /*BENCHMARK_H_*/