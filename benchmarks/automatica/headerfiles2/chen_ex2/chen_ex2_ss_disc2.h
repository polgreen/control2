#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.412802e-02),  interval(-6.909876e-01),  interval(-2.703188e-01),  interval(-1.258029e-01),  interval(-7.042991e-02),  interval(-4.707328e-02),  interval(-3.570723e-02),  interval(-1.173141e-02)},
{ interval(3.203457e-01),  interval(6.465850e-01),  interval(-1.441474e-01),  interval(-6.872215e-02),  interval(-3.903870e-02),  interval(-2.633616e-02),  interval(-2.011567e-02),  interval(-6.643839e-03)},
{ interval(1.814211e-01),  interval(6.945267e-01),  interval(9.562765e-01),  interval(-2.103536e-02),  interval(-1.201404e-02),  interval(-8.132465e-03),  interval(-6.227203e-03),  interval(-2.060651e-03)},
{ interval(2.813476e-02),  interval(1.487385e-01),  interval(3.952903e-01),  interval(9.977231e-01),  interval(-1.304173e-03),  interval(-8.844092e-04),  interval(-6.781125e-04),  interval(-2.246216e-04)},
{ interval(1.533417e-03),  interval(1.019636e-02),  interval(3.980221e-02),  interval(1.999041e-01),  interval(9.999450e-01),  interval(-3.736524e-05),  interval(-2.867334e-05),  interval(-9.503914e-06)},
{ interval(3.244003e-05),  interval(2.585846e-04),  interval(1.329921e-03),  interval(9.998342e-03),  interval(9.999905e-02),  interval(9.999994e-01),  interval(-4.969889e-07),  interval(-1.648011e-07)},
{ interval(2.812605e-07),  interval(2.607601e-06),  interval(1.664166e-05),  interval(1.666545e-04),  interval(2.499993e-03),  interval(5.000000e-02),  interval(1.000000e+00),  interval(-1.212404e-09)},
{ interval(2.069170e-09),  interval(2.184644e-08),  interval(1.665072e-07),  interval(2.083256e-06),  interval(4.166662e-05),  interval(1.250000e-03),  interval(5.000000e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.203457e-01), interval(1.814211e-01), interval(5.626951e-02), interval(6.133666e-03), interval(2.595202e-04), interval(4.500168e-06), interval(3.310672e-08), interval(2.117002e-10)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -6.586401e+00,  2.117002e-10,  3.310672e-08,  4.500168e-06,  2.595202e-04,  6.133666e-03,  5.626951e-02,  1.814211e-01,  3.203457e-01},
{ 1.892016e+01,  4.368476e-08,  3.210655e-06,  1.942773e-04,  4.357056e-03,  2.396051e-02,  -1.328173e-01,  -9.835294e-01,  -2.255812e+00},
{ -3.095692e+01,  6.342599e-07,  2.302722e-05,  4.505473e-04,  -4.717163e-03,  -1.223067e-01,  -1.552789e-01,  2.091265e+00,  6.805043e+00},
{ 3.155053e+01,  1.924819e-06,  1.713694e-05,  -8.283242e-04,  -1.162266e-02,  1.292278e-01,  7.992235e-01,  -2.053131e+00,  -1.140042e+01},
{ -2.050747e+01,  1.602511e-06,  -2.601473e-05,  -3.943661e-04,  1.579397e-02,  1.226733e-02,  -9.571923e-01,  6.207196e-01,  1.145539e+01},
{ 8.300672e+00,  3.659973e-07,  -1.597149e-05,  4.745130e-04,  -1.280112e-03,  -7.731628e-02,  4.396244e-01,  4.870712e-01,  -6.904122e+00},
{ -1.912624e+00,  1.746961e-08,  -1.412094e-06,  9.746768e-05,  -2.704224e-03,  2.575427e-02,  -2.515421e-02,  -4.488756e-01,  2.311022e+00},
{ 1.920499e-01,  5.866590e-11,  -9.604752e-09,  1.384817e-06,  -8.639050e-05,  2.279438e-03,  -2.467470e-02,  1.050587e-01,  -3.314380e-01}};

#endif /*BENCHMARK_H_*/