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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.910075e-01),  interval(-8.231237e-03),  interval(-4.581111e-03),  interval(-4.006404e-03),  interval(-2.472566e-03),  interval(-2.278249e-03),  interval(-1.423857e-03),  interval(-1.198164e-03),  interval(-8.263449e-04)},
{ interval(7.964020e-03),  interval(9.999671e-01),  interval(-1.834130e-05),  interval(-1.604312e-05),  interval(-9.902103e-06),  interval(-9.124808e-06),  interval(-5.703202e-06),  interval(-4.799594e-06),  interval(-3.310356e-06)},
{ interval(3.190404e-05),  interval(7.999912e-03),  interval(1.000000e+00),  interval(-4.280499e-08),  interval(-2.642139e-08),  interval(-2.434857e-08),  interval(-1.521890e-08),  interval(-1.280817e-08),  interval(-8.834251e-09)},
{ interval(4.257070e-08),  interval(1.599991e-05),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-2.643087e-11),  interval(-2.435802e-11),  interval(-1.522512e-11),  interval(-1.281372e-11),  interval(-8.838234e-12)},
{ interval(4.258989e-11),  interval(2.133326e-08),  interval(8.000000e-06),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-1.949146e-14),  interval(-1.218341e-14),  interval(-1.025394e-14),  interval(-7.072711e-15)},
{ interval(1.704107e-14),  interval(1.066664e-11),  interval(5.333333e-09),  interval(4.000000e-06),  interval(2.000000e-03),  interval(1),  interval(-4.061928e-18),  interval(-3.418685e-18),  interval(-2.358076e-18)},
{ interval(5.681576e-18),  interval(4.266660e-15),  interval(2.666667e-12),  interval(2.666667e-09),  interval(2.000000e-06),  interval(2.000000e-03),  interval(1),  interval(-9.769183e-22),  interval(-6.738444e-22)},
{ interval(8.117843e-22),  interval(7.111103e-19),  interval(5.333333e-16),  interval(6.666667e-13),  interval(6.666667e-10),  interval(1.000000e-06),  interval(1.000000e-03),  interval(1),  interval(-8.424109e-26)},
{ interval(5.074287e-26),  interval(5.079360e-23),  interval(4.444444e-20),  interval(6.666667e-17),  interval(8.333333e-14),  interval(1.666667e-10),  interval(2.500000e-07),  interval(5.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.955025e-04), interval(3.988005e-06), interval(1.064267e-08), interval(1.064747e-11), interval(8.520536e-15), interval(2.840788e-18), interval(8.117843e-22), interval(1.014857e-25), interval(5.638660e-30)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.990975e+00,  5.638660e-30,  1.014857e-25,  8.117843e-22,  2.840788e-18,  8.520536e-15,  1.064747e-11,  1.064267e-08,  3.988005e-06,  9.955025e-04},
{ 3.592786e+01,  2.828059e-27,  2.494041e-23,  9.568091e-20,  1.531943e-16,  1.871194e-13,  6.367399e-11,  -2.138110e-08,  -2.393998e-05,  -7.964020e-03},
{ -8.374775e+01,  8.222129e-26,  4.097651e-22,  7.708631e-19,  3.790853e-16,  -2.730133e-13,  -3.613809e-10,  -8.461467e-08,  5.591569e-05,  2.787407e-02},
{ 1.254960e+02,  4.961790e-25,  1.145547e-21,  1.226422e-19,  -1.230216e-15,  -7.290124e-13,  4.897234e-10,  3.607014e-07,  -5.608294e-05,  -5.574814e-02},
{ -1.253705e+02,  8.775355e-25,  -1.579564e-24,  -1.982164e-18,  2.675923e-18,  1.614046e-12,  -1.815804e-12,  -5.309355e-07,  4.181123e-07,  6.968518e-02},
{ 8.349688e+01,  4.952867e-25,  -1.145270e-21,  1.265414e-19,  1.227668e-15,  -7.321216e-13,  -4.872004e-10,  3.613703e-07,  5.541396e-05,  -5.574814e-02},
{ -3.574867e+01,  8.192582e-26,  -4.085875e-22,  7.695633e-19,  -3.797989e-16,  -2.706687e-13,  3.606928e-10,  -8.528365e-08,  -5.558120e-05,  2.787407e-02},
{ 8.928257e+00,  2.812829e-27,  -2.481622e-23,  9.525495e-20,  -1.526263e-16,  1.866607e-13,  -6.375044e-11,  -2.109439e-08,  2.384441e-05,  -7.964020e-03},
{ -9.910404e-01,  5.598208e-30,  -1.007778e-25,  8.063232e-22,  -2.822584e-18,  8.469566e-15,  -1.059013e-11,  1.059489e-08,  -3.976059e-06,  9.955025e-04}};

#endif /*BENCHMARK_H_*/