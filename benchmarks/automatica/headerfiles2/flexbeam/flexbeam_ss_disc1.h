#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-5.848183e-01),  interval(-1.156788e+00),  interval(-3.332521e-01),  interval(-4.255486e-01),  interval(-5.689543e-04),  interval(0)},
{ interval(5.747070e-01),  interval(-5.490428e-01),  interval(-2.347525e-01),  interval(-6.116153e-01),  interval(-8.177508e-04),  interval(0)},
{ interval(4.130095e-01),  interval(3.130633e-01),  interval(9.448901e-01),  interval(-1.953068e-01),  interval(-2.611342e-04),  interval(0)},
{ interval(1.318873e-01),  interval(2.147147e-01),  interval(7.901243e-01),  interval(9.574863e-01),  interval(-5.684298e-05),  interval(0)},
{ interval(1.794304e-03),  interval(4.233173e-03),  interval(1.991000e-02),  interval(4.955414e-02),  interval(9.999994e-01),  interval(0)},
{ interval(9.408822e-06),  interval(2.862169e-05),  interval(1.663201e-04),  interval(6.230862e-04),  interval(2.500000e-02),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.747070e-01), interval(8.260190e-01), interval(2.637746e-01), interval(5.741772e-02), interval(6.021646e-04), interval(2.584673e-06)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.768515e+00,  2.584673e-06,  6.021646e-04,  5.741772e-02,  2.637746e-01,  8.260190e-01,  5.747070e-01},
{ 2.823527e+00,  1.191797e-04,  1.155998e-02,  3.575846e-01,  3.715705e-03,  -2.507117e+00,  -2.995050e+00},
{ -1.990608e+00,  5.389632e-04,  1.506689e-02,  -4.258860e-01,  -1.343427e+00,  1.767940e+00,  6.121049e+00},
{ 2.489944e+00,  5.298810e-04,  -1.551683e-02,  -3.966600e-01,  1.370241e+00,  1.478693e+00,  -6.139923e+00},
{ -2.459548e+00,  1.136944e-04,  -1.114943e-02,  3.535513e-01,  -4.393673e-02,  -2.362833e+00,  3.023365e+00},
{ 9.051994e-01,  2.404971e-06,  -5.627711e-04,  5.399244e-02,  -2.503675e-01,  7.972976e-01,  -5.841476e-01}};

#endif /*BENCHMARK_H_*/