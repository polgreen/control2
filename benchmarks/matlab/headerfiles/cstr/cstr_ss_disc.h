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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.677953e-01),  interval(-4.455178e-02),  interval(-8.776488e-03)},
{ interval(5.494095e-02),  interval(9.985473e-01),  interval(-2.863273e-04)},
{ interval(4.481034e-04),  interval(1.561727e-02),  interval(9.999985e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.373524e-02), interval(4.481034e-04), interval(2.384262e-06)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.766341e+00,  2.384262e-06,  4.481034e-04,  1.373524e-02},
{ 2.535476e+00,  8.941536e-06,  -3.752793e-05,  -2.747049e-02},
{ -7.691264e-01,  2.091059e-06,  -4.105754e-04,  1.373525e-02}};

#endif /*BENCHMARK_H_*/