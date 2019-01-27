#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.792273e-01),  interval(5.854670e-04),  interval(-1.959361e-02)},
{ interval(2.473940e-02),  interval(1.000008e+00),  interval(-2.457769e-04)},
{ interval(3.103244e-04),  interval(2.500007e-02),  interval(9.999979e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.916609e-01), interval(9.930381e-03), interval(8.289774e-05)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.979234e+00,  8.289774e-05,  9.930381e-03,  7.916609e-01},
{ 2.958465e+00,  3.298578e-04,  -6.926560e-05,  -1.583323e+00},
{ -9.792190e-01,  8.203189e-05,  -9.861116e-03,  7.916617e-01}};

#endif /*BENCHMARK_H_*/