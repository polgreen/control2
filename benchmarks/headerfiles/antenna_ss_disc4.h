#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 6 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(4.473822e+00),  interval(-2.140084e+00),  interval(1.132605e+00),  interval(-7.019233e-01),  interval(2.400616e-01),  interval(-1.397155e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.220703e-04)interval(0)interval(0)interval(0)interval(0)interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -4.473822e+00,  0,  0,  0,  0,  0,  1.220703e-04},
{ 8.560338e+00,  0,  0,  0,  0,  4.882812e-04,  0},
{ -9.060840e+00,  0,  0,  0,  9.765625e-04,  0,  0},
{ 5.615386e+00,  0,  0,  9.765625e-04,  0,  0,  0},
{ -1.920493e+00,  0,  9.765625e-04,  0,  0,  0,  0},
{ 2.794310e-01,  2.441406e-04,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/