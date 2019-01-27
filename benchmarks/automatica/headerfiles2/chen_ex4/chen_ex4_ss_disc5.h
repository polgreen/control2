#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.991001e-01),  interval(-8.248125e-04),  interval(-4.592487e-04),  interval(-4.018219e-04),  interval(-2.480557e-04),  interval(-2.286223e-04),  interval(-1.429104e-04),  interval(-1.202848e-04),  interval(-8.297046e-05)},
{ interval(7.996400e-04),  interval(9.999997e-01),  interval(-1.837163e-07),  interval(-1.607462e-07),  interval(-9.923413e-08),  interval(-9.146074e-08),  interval(-5.717195e-08),  interval(-4.812088e-08),  interval(-3.319316e-08)},
{ interval(3.199040e-07),  interval(7.999999e-04),  interval(1.000000e+00),  interval(-4.286800e-11),  interval(-2.646401e-11),  interval(-2.439111e-11),  interval(-1.524689e-11),  interval(-1.283316e-11),  interval(-8.852175e-12)},
{ interval(4.265707e-11),  interval(1.600000e-07),  interval(4.000000e-04),  interval(1.000000e+00),  interval(-2.646496e-15),  interval(-2.439205e-15),  interval(-1.524751e-15),  interval(-1.283372e-15),  interval(-8.852573e-16)},
{ interval(4.265899e-15),  interval(2.133333e-11),  interval(8.000000e-08),  interval(4.000000e-04),  interval(1),  interval(-1.951415e-19),  interval(-1.219834e-19),  interval(-1.026727e-19),  interval(-7.082271e-20)},
{ interval(1.706411e-19),  interval(1.066667e-15),  interval(5.333333e-12),  interval(4.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-4.066169e-24),  interval(-3.422472e-24),  interval(-2.360792e-24)},
{ interval(5.688121e-24),  interval(4.266667e-20),  interval(2.666667e-16),  interval(2.666667e-12),  interval(2.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-1.026727e-28),  interval(-7.082271e-29)},
{ interval(8.532053e-29),  interval(7.111111e-25),  interval(5.333333e-21),  interval(6.666667e-17),  interval(6.666667e-13),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1),  interval(-1.180308e-33)},
{ interval(7.109618e-34),  interval(5.333333e-30),  interval(4.444444e-26),  interval(6.666667e-22),  interval(8.333333e-18),  interval(1.666667e-13),  interval(2.500000e-09),  interval(5.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.995500e-05), interval(3.998800e-08), interval(1.066427e-11), interval(1.066475e-15), interval(8.532053e-20), interval(2.844060e-24), interval(8.532053e-29), interval(1.421924e-33), interval(1.658833e-38)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.999100e+00,  1.658833e-38,  1.421924e-33,  8.532053e-29,  2.844060e-24,  8.532053e-20,  1.066475e-15,  1.066427e-11,  3.998800e-08,  9.995500e-05},
{ 3.599280e+01,  2.806004e-36,  2.474174e-31,  9.555183e-27,  1.535596e-22,  1.876719e-18,  6.396736e-15,  -2.133813e-11,  -2.399400e-07,  -7.996400e-04},
{ -8.397480e+01,  8.236241e-35,  4.114652e-30,  7.745430e-26,  3.809477e-22,  -2.730615e-18,  -3.625380e-14,  -8.526135e-11,  5.599160e-07,  2.798740e-03},
{ 1.259496e+02,  4.980914e-34,  1.149505e-29,  1.226292e-26,  -1.234060e-21,  -7.333804e-18,  4.905726e-14,  3.624699e-10,  -5.600839e-07,  -5.597480e-03},
{ -1.259370e+02,  8.806466e-34,  -1.579662e-33,  -1.987372e-25,  2.673996e-25,  1.620604e-17,  -1.823179e-17,  -5.330934e-10,  4.198110e-10,  6.996850e-03},
{ 8.394961e+01,  4.980019e-34,  -1.149478e-29,  1.230202e-26,  1.233807e-21,  -7.336925e-18,  -4.903192e-14,  3.625371e-10,  5.594122e-07,  -5.597480e-03},
{ -3.597481e+01,  8.233264e-35,  -4.113466e-30,  7.744131e-26,  -3.810204e-22,  -2.728261e-18,  3.624689e-14,  -8.532852e-11,  -5.595801e-07,  2.798740e-03},
{ 8.992803e+00,  2.804507e-36,  -2.472932e-31,  9.550884e-27,  -1.535022e-22,  1.876258e-18,  -6.397504e-15,  -2.130934e-11,  2.398440e-07,  -7.996400e-04},
{ -9.991004e-01,  1.658193e-38,  -1.421241e-33,  8.526936e-29,  -2.842269e-24,  8.526936e-20,  -1.065899e-15,  1.065947e-11,  -3.997601e-08,  9.995500e-05}};

#endif /*BENCHMARK_H_*/