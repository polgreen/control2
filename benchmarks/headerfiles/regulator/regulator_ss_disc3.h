#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.801987e-01),  interval(4.828208e-02),  interval(2.553160e-03),  interval(4.657690e-03),  interval(8.447735e-03)},
{ interval(0),  interval(9.512294e-01),  interval(8.260568e-02),  interval(2.066413e-01),  interval(5.330778e-01)},
{ interval(0),  interval(0),  interval(2.397880e-01),  interval(1.260889e+00),  interval(6.521160e+00)},
{ interval(0),  interval(0),  interval(0),  interval(8.208500e-02),  interval(1.428972e+00)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(3.678794e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.922048e-03), interval(5.092329e-01), interval(1.015434e+01), interval(3.974318e+00), interval(1.896362e+00)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -2.621181e+00,  1.896362e+00,  3.974318e+00,  1.015434e+01,  5.092329e-01,  5.922048e-03},
{ 2.402695e+00,  -4.273074e+00,  -7.381326e+00,  -6.803831e+00,  1.820579e+00,  7.532562e-02},
{ -9.170795e-01,  2.984402e+00,  2.837073e+00,  -1.440611e+01,  -1.409883e+00,  8.811530e-02},
{ 1.427429e-01,  -6.412143e-01,  8.527426e-01,  1.027224e+01,  -8.209814e-01,  1.451195e-02},
{ -6.751436e-03,  3.480261e-02,  -2.789743e-01,  8.063730e-01,  -2.531232e-02,  2.129032e-04}};

#endif /*BENCHMARK_H_*/