#ifndef BENCHMARK_H_ 
 #define BENCHMARK_H_ 

// time discretisation 1.000000e-03 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
 #endif
#define NSTATES 4 
 #include "control_types.h"
#define NINPUTS 1 
 #define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {,
{ interval(1.000006e+00),  interval(-6.270022e-06),  interval(1.000002e-03),  interval(-2.090004e-09)},
{ interval(-7.245025e-06),  interval(1.000015e+00),  interval(-2.415005e-09),  interval(1.000005e-03)},
{ interval(1.249006e-02),  interval(-1.254009e-02),  interval(1.000006e+00),  interval(-6.270022e-06)},
{ interval(-1.449010e-02),  interval(2.936017e-02),  interval(-7.245025e-06),  interval(1.000015e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.490005e-06)interval(2.990009e-06)interval(-2.980019e-03)interval(5.980036e-03)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.000042e+00,  -1.490005e-06,  2.990009e-06,  -2.980019e-03,  5.980036e-03},
{ 6.000084e+00,  1.490011e-06,  -2.990025e-06,  8.940069e-03,  -1.794014e-02},
{ -4.000042e+00,  1.490011e-06,  -2.990025e-06,  -8.940069e-03,  1.794014e-02},
{ 1.000000e+00,  -1.490005e-06,  2.990009e-06,  2.980019e-03,  -5.980036e-03}};

#endif /*BENCHMARK_H_*/