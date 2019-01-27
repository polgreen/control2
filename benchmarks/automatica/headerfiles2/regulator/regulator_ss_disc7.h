#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999980e-01),  interval(4.999983e-06),  interval(3.999800e-11),  interval(1.142686e-14),  interval(2.142536e-18)},
{ interval(0),  interval(9.999950e-01),  interval(1.599882e-05),  interval(6.855891e-09),  interval(1.713987e-12)},
{ interval(0),  interval(0),  interval(9.998572e-01),  interval(8.569317e-04),  interval(3.213597e-07)},
{ interval(0),  interval(0),  interval(0),  interval(9.997500e-01),  interval(7.498688e-04)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.999000e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.285543e-22), interval(1.285522e-16), interval(3.213729e-11), interval(1.124869e-07), interval(2.999850e-04)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.999500e+00,  2.999850e-04,  1.124869e-07,  3.213729e-11,  1.285522e-16,  1.285543e-22},
{ 9.998001e+00,  -1.199820e-03,  -2.249700e-07,  6.425897e-11,  1.285381e-15,  3.342133e-21},
{ -9.997002e+00,  1.799550e-03,  2.251687e-11,  -1.927993e-10,  -1.379363e-19,  8.483170e-21},
{ 4.998001e+00,  -1.199580e-03,  2.249175e-07,  6.427391e-11,  -1.285276e-15,  3.341576e-21},
{ -9.995003e-01,  2.998651e-04,  -1.124569e-07,  3.212915e-11,  -1.285136e-16,  1.285115e-22}};

#endif /*BENCHMARK_H_*/