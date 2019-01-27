#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.988787e-01),  interval(-6.287706e-01),  interval(-3.298914e-01),  interval(-2.715510e-01),  interval(-1.613264e-01),  interval(-1.434554e-01),  interval(-8.744285e-02),  interval(-7.141778e-02),  interval(-4.824013e-02)},
{ interval(4.649214e-01),  interval(7.219152e-01),  interval(-1.493204e-01),  interval(-1.258496e-01),  interval(-7.591060e-02),  interval(-6.846701e-02),  interval(-4.215857e-02),  interval(-3.485053e-02),  interval(-2.374054e-02)},
{ interval(2.288029e-01),  interval(7.223247e-01),  interval(9.578682e-01),  interval(-3.587497e-02),  interval(-2.177911e-02),  interval(-1.976142e-02),  interval(-1.221939e-02),  interval(-1.015184e-02),  interval(-6.939647e-03)},
{ interval(3.344093e-02),  interval(1.520225e-01),  interval(3.956483e-01),  interval(9.962730e-01),  interval(-2.270755e-03),  interval(-2.067295e-03),  interval(-1.281298e-03),  interval(-1.067469e-03),  interval(-7.311188e-04)},
{ interval(3.523133e-03),  interval(2.068399e-02),  interval(7.964449e-02),  interval(3.996944e-01),  interval(9.998134e-01),  interval(-1.702786e-04),  interval(-1.056962e-04),  interval(-8.821476e-05),  interval(-6.049407e-05)},
{ interval(1.457551e-04),  interval(1.044758e-03),  interval(5.321308e-03),  interval(3.998964e-02),  interval(1.999937e-01),  interval(9.999942e-01),  interval(-3.599664e-06),  interval(-3.008064e-06),  interval(-2.064597e-06)},
{ interval(4.974463e-06),  interval(4.203505e-05),  interval(2.663193e-04),  interval(2.666367e-03),  interval(1.999982e-02),  interval(1.999998e-01),  interval(9.999999e-01),  interval(-8.740071e-08),  interval(-6.002630e-08)},
{ interval(7.231403e-08),  interval(7.031612e-07),  interval(5.328955e-06),  interval(6.666288e-05),  interval(6.666643e-04),  interval(9.999998e-03),  interval(1.000000e-01),  interval(1.000000e+00),  interval(-7.604684e-10)},
{ interval(4.580704e-10),  interval(5.034956e-09),  interval(4.441996e-08),  interval(6.666455e-07),  interval(8.333320e-06),  interval(1.666667e-04),  interval(2.500000e-03),  interval(5.000000e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.811517e-02), interval(2.860037e-02), interval(8.360233e-03), interval(8.807831e-04), interval(7.287756e-05), interval(2.487232e-06), interval(7.231403e-08), interval(9.161408e-10), interval(5.144176e-12)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.874743e+00,  5.144176e-12,  9.161408e-10,  7.231403e-08,  2.487232e-06,  7.287756e-05,  8.807831e-04,  8.360233e-03,  2.860037e-02,  5.811517e-02},
{ 2.779377e+01,  2.342232e-09,  2.019704e-07,  7.524136e-06,  1.155366e-04,  1.313179e-03,  3.540427e-03,  -2.390425e-02,  -1.789194e-01,  -4.670765e-01},
{ -5.770603e+01,  6.177688e-08,  2.959707e-06,  5.213422e-05,  2.066652e-04,  -2.496637e-03,  -2.427265e-02,  -2.679911e-02,  4.516093e-01,  1.641542e+00},
{ 7.766907e+01,  3.390940e-07,  7.197860e-06,  -5.345695e-06,  -8.383511e-04,  -3.413274e-03,  3.794297e-02,  1.946128e-01,  -5.539725e-01,  -3.295286e+00},
{ -7.027788e+01,  5.474937e-07,  -9.859276e-07,  -1.223436e-04,  1.660496e-04,  9.845171e-03,  -1.119489e-02,  -3.196445e-01,  2.558755e-01,  4.132877e+00},
{ 4.274968e+01,  2.832146e-07,  -7.031619e-06,  1.902323e-05,  6.813330e-04,  -5.357620e-03,  -2.243597e-02,  2.369082e-01,  1.445948e-01,  -3.316270e+00},
{ -1.685777e+01,  4.309589e-08,  -2.219850e-06,  4.408179e-05,  -2.526744e-04,  -1.033207e-03,  2.012640e-02,  -6.909592e-02,  -2.469554e-01,  1.662656e+00},
{ 3.910481e+00,  1.364843e-09,  -1.226020e-07,  4.816773e-06,  -7.973827e-05,  1.029506e-03,  -4.073523e-03,  -5.776062e-03,  1.204637e-01,  -4.762190e-01},
{ -4.065697e-01,  2.503915e-12,  -4.549420e-10,  3.681997e-08,  -1.307853e-06,  4.000393e-05,  -5.135415e-04,  5.338637e-03,  -2.129638e-02,  5.966108e-02}};

#endif /*BENCHMARK_H_*/