#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-4.539109e-02),  interval(-4.444947e-01),  interval(-2.524337e-01),  interval(-1.972677e-01),  interval(-9.959569e-02),  interval(-6.005976e-02),  interval(-2.853614e-02)},
{ interval(6.493558e-01),  interval(5.633800e-01),  interval(-2.599260e-01),  interval(-2.107226e-01),  interval(-1.092764e-01),  interval(-6.750852e-02),  interval(-3.258029e-02)},
{ interval(3.706913e-01),  interval(6.722010e-01),  interval(9.224872e-01),  interval(-6.372805e-02),  interval(-3.337773e-02),  interval(-2.080207e-02),  interval(-1.009548e-02)},
{ interval(5.743204e-02),  interval(1.465154e-01),  interval(3.917378e-01),  interval(9.931555e-01),  interval(-3.603885e-03),  interval(-2.256594e-03),  interval(-1.098393e-03)},
{ interval(6.248635e-03),  interval(2.021611e-02),  interval(7.931104e-02),  interval(3.994265e-01),  interval(9.996970e-01),  interval(-1.902604e-04),  interval(-9.278070e-05)},
{ interval(2.639095e-04),  interval(1.028495e-03),  interval(5.309689e-03),  interval(3.998025e-02),  interval(1.999895e-01),  interval(9.999934e-01),  interval(-3.212673e-06)},
{ interval(4.569134e-06),  interval(2.077791e-05),  interval(1.329882e-04),  interval(1.333044e-03),  interval(9.999847e-03),  interval(9.999990e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(8.116948e-02), interval(9.267282e-02), interval(2.871602e-02), interval(3.124317e-03), interval(2.639095e-04), interval(9.138269e-06), interval(1.342775e-07)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -5.433322e+00,  1.342775e-07,  9.138269e-06,  2.639095e-04,  3.124317e-03,  2.871602e-02,  9.267282e-02,  8.116948e-02},
{ 1.281375e+01,  1.323775e-05,  4.063852e-04,  4.736037e-03,  1.561541e-02,  -3.735776e-02,  -4.067552e-01,  -4.937889e-01},
{ -1.700554e+01,  1.080967e-04,  1.347925e-03,  8.200733e-05,  -4.706488e-02,  -1.241284e-01,  6.435584e-01,  1.249153e+00},
{ 1.371812e+01,  1.812578e-04,  -3.402742e-04,  -1.223417e-02,  1.752994e-02,  2.957801e-01,  -3.601598e-01,  -1.682563e+00},
{ -6.728064e+00,  7.426476e-05,  -1.204734e-03,  4.055723e-03,  2.678063e-02,  -1.997316e-01,  -1.034131e-01,  1.273066e+00},
{ 1.858316e+00,  6.250527e-06,  -2.153096e-04,  2.999400e-03,  -1.471450e-02,  2.312925e-02,  1.908112e-01,  -5.131304e-01},
{ -2.231302e-01,  4.359029e-08,  -3.129907e-06,  9.709559e-05,  -1.270910e-03,  1.359242e-02,  -5.671428e-02,  8.609364e-02}};

#endif /*BENCHMARK_H_*/