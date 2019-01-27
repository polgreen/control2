#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.494212e-01),  interval(-2.166545e-02),  interval(-7.777404e-03),  interval(-3.221896e-03)},
{ interval(2.494821e-02),  interval(9.997204e-01),  interval(-1.003893e-04),  interval(-4.159699e-05)},
{ interval(8.052481e-05),  interval(6.399401e-03),  interval(9.999998e-01),  interval(-8.912229e-08)},
{ interval(8.626292e-08),  interval(1.023952e-05),  interval(3.200000e-03),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.796314e-04), interval(1.006560e-05), interval(2.156573e-08), interval(1.729708e-11)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.949141e+00,  1.729708e-11,  2.156573e-08,  1.006560e-05,  7.796314e-04},
{ 5.847980e+00,  1.883190e-10,  6.359310e-08,  -1.023729e-05,  -2.338894e-03},
{ -3.848535e+00,  1.863851e-10,  -6.414252e-08,  -9.722218e-06,  2.338894e-03},
{ 9.496960e-01,  1.676963e-11,  -2.101631e-08,  9.893910e-06,  -7.796315e-04}};

#endif /*BENCHMARK_H_*/