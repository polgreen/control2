#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999250e-01),  interval(-3.874904e-05),  interval(-2.460866e-05),  interval(-2.093683e-05),  interval(-1.123008e-05),  interval(-7.148178e-06),  interval(-3.515493e-06)},
{ interval(7.999700e-05),  interval(1.000000e+00),  interval(-9.843560e-10),  interval(-8.374821e-10),  interval(-4.492085e-10),  interval(-2.859306e-10),  interval(-1.406215e-10)},
{ interval(1.599960e-09),  interval(4.000000e-05),  interval(1.000000e+00),  interval(-1.116649e-14),  interval(-5.989481e-15),  interval(-3.812431e-15),  interval(-1.874965e-15)},
{ interval(1.066647e-14),  interval(4.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-2.994751e-20),  interval(-1.906222e-20),  interval(-9.374859e-21)},
{ interval(5.333253e-20),  interval(2.666667e-15),  interval(2.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-7.624908e-26),  interval(-3.749953e-26)},
{ interval(1.066653e-25),  interval(6.666667e-21),  interval(6.666667e-16),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1),  interval(-6.249930e-32)},
{ interval(8.888789e-32),  interval(6.666667e-27),  interval(8.333333e-22),  interval(1.666667e-16),  interval(2.500000e-11),  interval(5.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.999625e-06), interval(3.999900e-10), interval(5.333233e-15), interval(2.666627e-20), interval(1.066653e-25), interval(1.777758e-31), interval(1.333317e-37)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.999925e+00,  1.333317e-37,  1.777758e-31,  1.066653e-25,  2.666627e-20,  5.333233e-15,  3.999900e-10,  9.999625e-06},
{ 2.099955e+01,  1.519972e-35,  9.955341e-30,  2.559933e-24,  2.133257e-19,  -3.999898e-19,  -1.599970e-09,  -5.999775e-05},
{ -3.499888e+01,  1.513291e-34,  4.355405e-29,  1.599873e-24,  -5.066547e-19,  -4.799770e-14,  2.000000e-09,  1.499944e-04},
{ 3.499850e+01,  3.066552e-34,  -5.733118e-34,  -8.533013e-24,  1.199955e-23,  8.533013e-14,  -9.999625e-14,  -1.999925e-04},
{ -2.099888e+01,  1.513262e-34,  -4.355380e-29,  1.600007e-24,  5.066407e-19,  -4.799870e-14,  -1.999850e-09,  1.499944e-04},
{ 6.999550e+00,  1.519914e-35,  -9.955024e-30,  2.559875e-24,  -2.133249e-19,  3.999802e-19,  1.599910e-09,  -5.999775e-05},
{ -9.999250e-01,  1.333250e-37,  -1.777664e-31,  1.066600e-25,  -2.666507e-20,  5.333033e-15,  -3.999800e-10,  9.999625e-06}};

#endif /*BENCHMARK_H_*/