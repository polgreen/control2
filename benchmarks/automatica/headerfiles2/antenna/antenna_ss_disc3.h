#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.745930e-01),  interval(-1.442448e-02),  interval(-9.720224e-03),  interval(-4.257649e-03),  interval(0),  interval(0)},
{ interval(3.159299e-02),  interval(9.997686e-01),  interval(-1.560986e-04),  interval(-6.841457e-05),  interval(0),  interval(0)},
{ interval(2.538280e-04),  interval(1.599876e-02),  interval(9.999992e-01),  interval(-3.656574e-07),  interval(0),  interval(0)},
{ interval(6.783210e-07),  interval(6.399753e-05),  interval(7.999998e-03),  interval(1.000000e+00),  interval(0),  interval(0)},
{ interval(2.122467e-11),  interval(2.666605e-09),  interval(5.000000e-07),  interval(1.250000e-04),  interval(1),  interval(0)},
{ interval(2.655345e-16),  interval(4.166602e-14),  interval(1.041667e-11),  interval(3.906250e-09),  interval(6.250000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.468202e-04), interval(3.966062e-06), interval(2.119753e-08), interval(4.244933e-11), interval(1.062138e-15), interval(1.107067e-20)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.974361e+00,  1.107067e-20,  1.062138e-15,  4.244933e-11,  2.119753e-08,  3.966062e-06,  2.468202e-04},
{ 1.487227e+01,  6.287287e-19,  2.643607e-14,  3.796634e-10,  2.065778e-08,  -1.193175e-05,  -1.234101e-03},
{ -1.974547e+01,  3.319029e-18,  4.200863e-14,  -4.244760e-10,  -1.682296e-07,  8.066397e-06,  2.468203e-03},
{ 1.474639e+01,  3.306961e-18,  -4.224138e-14,  -4.180308e-10,  1.687667e-07,  7.730714e-06,  -2.468203e-03},
{ -5.873655e+00,  6.218950e-19,  -2.622123e-14,  3.785893e-10,  -2.146344e-08,  -1.176391e-05,  1.234102e-03},
{ 9.748224e-01,  1.087085e-20,  -1.044234e-15,  4.180480e-11,  -2.092898e-08,  3.932494e-06,  -2.468203e-04}};

#endif /*BENCHMARK_H_*/