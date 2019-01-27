#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.719622e-01),  interval(-3.642676e-01),  interval(-1.975362e-01),  interval(-1.681102e-01),  interval(-1.020195e-01),  interval(-9.252857e-02),  interval(-5.719685e-02),  interval(-4.749838e-02),  interval(-3.245873e-02)},
{ interval(3.128257e-01),  interval(9.238912e-01),  interval(-4.166603e-02),  interval(-3.581159e-02),  interval(-2.186710e-02),  interval(-1.994793e-02),  interval(-1.238092e-02),  interval(-1.033173e-02),  interval(-7.084333e-03)},
{ interval(6.827630e-02),  interval(3.896366e-01),  interval(9.943011e-01),  interval(-4.920998e-03),  interval(-3.013495e-03),  interval(-2.756439e-03),  interval(-1.714029e-03),  interval(-1.433565e-03),  interval(-9.845174e-04)},
{ interval(4.744216e-03),  interval(3.947539e-02),  interval(1.997108e-01),  interval(9.997496e-01),  interval(-1.536171e-04),  interval(-1.407340e-04),  interval(-8.760757e-05),  interval(-7.336850e-05),  interval(-5.043250e-05)},
{ interval(2.430253e-04),  interval(2.645511e-03),  interval(1.998832e-02),  interval(1.999899e-01),  interval(9.999938e-01),  interval(-5.707209e-06),  interval(-3.555297e-06),  interval(-2.980004e-06),  interval(-2.049634e-06)},
{ interval(4.938413e-06),  interval(6.631205e-05),  interval(6.664706e-04),  interval(9.999830e-03),  interval(9.999990e-02),  interval(9.999999e-01),  interval(-5.986345e-08),  interval(-5.020724e-08),  interval(-3.454688e-08)},
{ interval(8.323767e-08),  interval(1.328246e-06),  interval(1.666385e-05),  interval(3.333309e-04),  interval(4.999998e-03),  interval(1.000000e-01),  interval(1.000000e+00),  interval(-7.230511e-10),  interval(-4.976773e-10)},
{ interval(5.995548e-10),  interval(1.107921e-08),  interval(1.666490e-07),  interval(4.166651e-06),  interval(8.333332e-05),  interval(2.500000e-03),  interval(5.000000e-02),  interval(1.000000e+00),  interval(-3.130702e-12)},
{ interval(1.885788e-12),  interval(3.959369e-11),  interval(6.943952e-10),  interval(2.083329e-08),  interval(5.208333e-07),  interval(2.083333e-05),  interval(6.250000e-04),  interval(2.500000e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.910322e-02), interval(8.534538e-03), interval(1.186054e-03), interval(6.075633e-05), interval(2.469207e-06), interval(4.161883e-08), interval(5.995548e-10), interval(3.771576e-12), interval(1.053082e-14)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.489898e+00,  1.053082e-14,  3.771576e-12,  5.995548e-10,  4.161883e-08,  2.469207e-06,  6.075633e-05,  1.186054e-03,  8.534538e-03,  3.910322e-02},
{ 3.210181e+01,  5.044239e-12,  8.803489e-10,  6.662432e-08,  2.092273e-06,  4.944504e-05,  3.042117e-04,  -2.895297e-03,  -5.239152e-02,  -3.129704e-01},
{ -7.095448e+01,  1.400356e-10,  1.370069e-08,  4.998402e-07,  4.465481e-06,  -8.298423e-05,  -1.876681e-03,  -6.588084e-03,  1.277735e-01,  1.095877e+00},
{ 1.010301e+02,  8.074690e-10,  3.582873e-08,  1.452035e-08,  -1.605842e-05,  -1.608349e-04,  2.740140e-03,  3.391073e-02,  -1.443530e-01,  -2.192667e+00},
{ -9.610277e+01,  1.365791e-09,  -2.458697e-09,  -1.230714e-06,  1.663673e-06,  3.996880e-04,  -4.508410e-04,  -5.242078e-02,  4.144842e-02,  2.741919e+00},
{ 6.107109e+01,  7.379644e-10,  -3.540158e-08,  1.359468e-07,  1.447676e-05,  -1.995707e-04,  -2.114185e-03,  3.725385e-02,  7.803572e-02,  -2.194362e+00},
{ -2.500092e+01,  1.169660e-10,  -1.186471e-08,  4.594520e-07,  -4.913431e-06,  -5.378737e-05,  1.706789e-03,  -9.931204e-03,  -9.461520e-02,  1.097574e+00},
{ 5.982730e+00,  3.850638e-12,  -6.858959e-10,  5.330330e-08,  -1.737783e-06,  4.374565e-05,  -3.238070e-04,  -1.462527e-03,  4.291790e-02,  -3.136995e-01},
{ -6.376282e-01,  7.347097e-15,  -2.657784e-12,  4.278147e-10,  -3.017861e-08,  1.829278e-06,  -4.638314e-05,  9.472576e-04,  -7.350364e-03,  3.922517e-02}};

#endif /*BENCHMARK_H_*/