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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.146545e+08),  interval(1.468377e+07),  interval(-6.243557e+06)},
{ interval(2.572909e+10),  interval(6.146545e+08),  interval(-2.613518e+08)},
{ interval(0),  interval(0),  interval(4.897136e-09)}};
const __plant_typet _controller_B[NSTATES] = {interval(-2.868371e+05), interval(-1.200684e+07), interval(5.025126e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -1.229309e+09,  5.025126e-02,  -1.200684e+07,  -2.868371e+05},
{ 3.076133e+01,  -6.177432e+07,  1.200684e+07,  -9.143302e+05},
{ -1.211612e-07,  1.243278e+00,  2.076613e+00,  -3.698018e-02}};

#endif /*BENCHMARK_H_*/