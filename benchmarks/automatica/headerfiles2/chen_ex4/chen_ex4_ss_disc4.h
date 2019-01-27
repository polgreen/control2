#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.955019e-01),  interval(-4.120311e-03),  interval(-2.293716e-03),  interval(-2.006484e-03),  interval(-1.238503e-03),  interval(-1.141339e-03),  interval(-7.133860e-04),  interval(-6.003830e-04),  interval(-4.141055e-04)},
{ interval(3.991003e-03),  interval(9.999918e-01),  interval(-4.589538e-06),  interval(-4.015156e-06),  interval(-2.478486e-06),  interval(-2.284156e-06),  interval(-1.427744e-06),  interval(-1.201634e-06),  interval(-8.288333e-07)},
{ interval(7.988003e-06),  interval(3.999989e-03),  interval(1.000000e+00),  interval(-5.355000e-09),  interval(-3.305634e-09),  interval(-3.046525e-09),  interval(-1.904306e-09),  interval(-1.602757e-09),  interval(-1.105526e-09)},
{ interval(5.327334e-09),  interval(3.999995e-06),  interval(2.000000e-03),  interval(1.000000e+00),  interval(-1.653113e-12),  interval(-1.523558e-12),  interval(-9.523475e-13),  interval(-8.015518e-13),  interval(-5.528874e-13)},
{ interval(2.664267e-12),  interval(2.666664e-09),  interval(2.000000e-06),  interval(2.000000e-03),  interval(1.000000e+00),  interval(-6.095020e-16),  interval(-3.809908e-16),  interval(-3.206670e-16),  interval(-2.211882e-16)},
{ interval(5.329334e-16),  interval(6.666663e-13),  interval(6.666667e-10),  interval(1.000000e-06),  interval(1.000000e-03),  interval(1),  interval(-6.350279e-20),  interval(-5.344836e-20),  interval(-3.686746e-20)},
{ interval(8.882890e-20),  interval(1.333333e-16),  interval(1.666667e-13),  interval(3.333333e-10),  interval(5.000000e-07),  interval(1.000000e-03),  interval(1),  interval(-8.016676e-24),  interval(-5.529705e-24)},
{ interval(6.661668e-24),  interval(1.111111e-20),  interval(1.666667e-17),  interval(4.166667e-14),  interval(8.333333e-11),  interval(2.500000e-07),  interval(5.000000e-04),  interval(1),  interval(-4.606704e-28)},
{ interval(2.774862e-28),  interval(4.166664e-25),  interval(6.944444e-22),  interval(2.083333e-18),  interval(5.208333e-15),  interval(2.083333e-11),  interval(6.250000e-08),  interval(2.500000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.988753e-04), interval(9.985003e-07), interval(1.331834e-09), interval(6.660668e-13), interval(2.664667e-16), interval(4.441445e-20), interval(6.661668e-24), interval(5.549724e-28), interval(3.236575e-32)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.995494e+00,  3.236575e-32,  5.549724e-28,  6.661668e-24,  4.441445e-20,  2.664667e-16,  6.660668e-13,  1.331834e-09,  9.985003e-07,  4.988753e-04},
{ 3.596397e+01,  5.476462e-30,  9.657052e-26,  7.458269e-22,  2.396841e-18,  5.857070e-15,  3.989806e-12,  -2.669659e-09,  -5.992499e-06,  -3.991003e-03},
{ -8.387394e+01,  1.606909e-28,  1.605320e-24,  6.042259e-21,  5.939329e-18,  -8.532517e-15,  -2.262648e-11,  -1.062171e-08,  1.398948e-05,  1.396851e-02},
{ 1.257480e+02,  9.714336e-28,  4.482385e-24,  9.502161e-22,  -1.925542e-17,  -2.285741e-14,  3.063723e-11,  4.521042e-08,  -1.401043e-05,  -2.793702e-02},
{ -1.256851e+02,  1.716918e-27,  -3.079727e-27,  -1.549841e-20,  2.085301e-20,  5.055273e-14,  -5.687184e-14,  -6.651673e-08,  5.238195e-08,  3.492127e-02},
{ 8.374822e+01,  9.705614e-28,  -4.481861e-24,  9.654617e-22,  1.923562e-17,  -2.290610e-14,  -3.055821e-11,  4.525232e-08,  1.392662e-05,  -2.793702e-02},
{ -3.587417e+01,  1.604007e-28,  -1.603008e-24,  6.037191e-21,  -5.944996e-18,  -8.495799e-15,  2.260493e-11,  -1.066361e-08,  -1.394758e-05,  1.396851e-02},
{ 8.964064e+00,  5.461869e-30,  -9.632840e-26,  7.441506e-22,  -2.392371e-18,  5.849886e-15,  -3.992201e-12,  -2.651700e-09,  5.980525e-06,  -3.991003e-03},
{ -9.955101e-01,  3.230339e-32,  -5.536420e-28,  6.641713e-24,  -4.427476e-20,  2.656685e-16,  -6.642708e-13,  1.328840e-09,  -9.970037e-07,  4.988753e-04}};

#endif /*BENCHMARK_H_*/