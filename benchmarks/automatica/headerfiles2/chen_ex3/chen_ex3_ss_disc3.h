#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.850505e-01),  interval(-7.711617e-03),  interval(-4.893383e-03),  interval(-4.160636e-03),  interval(-2.230709e-03),  interval(-1.419339e-03),  interval(-6.978634e-04)},
{ interval(1.588027e-02),  interval(9.999382e-01),  interval(-3.922298e-05),  interval(-3.335666e-05),  interval(-1.788665e-05),  interval(-1.138228e-05),  interval(-5.596922e-06)},
{ interval(6.368054e-05),  interval(7.999835e-03),  interval(9.999999e-01),  interval(-8.904657e-08),  interval(-4.775243e-08),  interval(-3.038952e-08),  interval(-1.494383e-08)},
{ interval(8.501376e-08),  interval(1.599983e-05),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-4.778525e-11),  interval(-3.041160e-11),  interval(-1.495505e-11)},
{ interval(8.507762e-11),  interval(2.133320e-08),  interval(8.000000e-06),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-2.434105e-14),  interval(-1.197003e-14)},
{ interval(3.404808e-14),  interval(1.066662e-11),  interval(5.333333e-09),  interval(4.000000e-06),  interval(2.000000e-03),  interval(1),  interval(-3.991436e-18)},
{ interval(5.676709e-18),  interval(2.133327e-15),  interval(1.333333e-12),  interval(1.333333e-09),  interval(1.000000e-06),  interval(1.000000e-03),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.985034e-03), interval(1.592013e-05), interval(4.250688e-08), interval(4.253881e-11), interval(3.404808e-14), interval(1.135342e-17), interval(1.622351e-21)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.984989e+00,  1.622351e-21,  1.135342e-17,  3.404808e-14,  4.253881e-11,  4.250688e-08,  1.592013e-05,  1.985034e-03},
{ 2.091006e+01,  1.943173e-19,  6.344054e-16,  8.149423e-13,  3.389079e-10,  -6.367447e-10,  -6.375994e-05,  -1.191020e-02},
{ -3.477545e+01,  1.924985e-18,  2.768304e-15,  5.039321e-13,  -8.068298e-10,  -3.803326e-07,  7.999768e-05,  2.977551e-02},
{ 3.470101e+01,  3.897608e-18,  -7.308015e-18,  -2.710249e-12,  3.811295e-12,  6.775601e-07,  -7.940187e-07,  -3.970067e-02},
{ -2.077606e+01,  1.917780e-18,  -2.765134e-15,  5.124016e-13,  8.023833e-10,  -3.819206e-07,  -7.880665e-05,  2.977551e-02},
{ 6.910549e+00,  1.928654e-19,  -6.303884e-16,  8.112157e-13,  -3.386539e-10,  6.336914e-10,  6.328353e-05,  -1.191020e-02},
{ -9.851119e-01,  1.604202e-21,  -1.123242e-17,  3.370930e-14,  -4.215768e-11,  4.218927e-08,  -1.584073e-05,  1.985034e-03}};

#endif /*BENCHMARK_H_*/