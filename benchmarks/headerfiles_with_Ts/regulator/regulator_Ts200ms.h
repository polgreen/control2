#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
// No controller needed, safe and stable, completeness k with no controller =  1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.607894e-01),  interval(9.325337e-02),  interval(7.103195e-03),  interval(1.814411e-02),  interval(6.043159e-02)},
{ interval(0),  interval(9.048374e-01),  interval(9.838480e-02),  interval(3.176820e-01),  interval(1.537157e+00)},
{ interval(0),  interval(0),  interval(5.749829e-02),  interval(4.058460e-01),  interval(5.764471e+00)},
{ interval(0),  interval(0),  interval(0),  interval(6.737947e-03),  interval(6.429867e-01)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1.353353e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.677042e-02), interval(3.664603e+00), interval(2.996688e+01), interval(7.010398e+00), interval(2.593994e+00)};
const __plant_typet __char_poly_const[6][6] = 
 {{ -1,  0,  0,  0,  0,  0},
{ 2.065198e+00,  -9.677042e-02,  -3.664603e+00,  -2.996688e+01,  -7.010398e+00,  -2.593994e+00},
{ -1.250765e+00,  -7.316797e-01,  -4.910477e+00,  4.236637e+01,  1.276272e+01,  5.006054e+00},
{ 1.904931e-01,  -4.469172e-01,  6.891044e+00,  -1.008586e+00,  -5.463541e+00,  -2.566982e+00},
{ -7.992330e-03,  -2.976817e-02,  1.152604e+00,  -1.136416e+01,  -3.519158e-01,  1.467347e-01},
{ 4.558189e-05,  -1.298043e-04,  9.326853e-03,  -1.899006e-01,  3.594785e-02,  -8.736758e-04}};

#endif /*BENCHMARK_H_*/