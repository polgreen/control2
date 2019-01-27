#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.609901e-03),  interval(7.040995e-03),  interval(1.061706e-02),  interval(2.533976e-03)},
{ interval(-1.962142e-02),  interval(-3.594974e-02),  interval(-3.991537e-02),  interval(3.603460e-02)},
{ interval(-6.975695e-02),  interval(-1.455455e-01),  interval(-2.779816e-01),  interval(-2.536838e-01)},
{ interval(2.455447e-01),  interval(4.863343e-01),  interval(7.791803e-01),  interval(3.339818e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-6.131693e-04), interval(-8.719619e-03), interval(6.138618e-02), interval(1.611625e-01)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -2.366039e-02,  1.611625e-01,  6.138618e-02,  -8.719619e-03,  -6.131693e-04},
{ 7.980600e-02,  9.345185e-02,  -5.808908e-02,  3.888981e-03,  1.011022e-03},
{ -5.879326e-07,  9.506822e-04,  -3.297091e-03,  4.830624e-03,  -3.978328e-04},
{ 4.028305e-23,  2.002441e-10,  -2.332010e-09,  1.357910e-08,  -1.976751e-08}};

#endif /*BENCHMARK_H_*/