#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(6.718249e-02),  interval(1.165955e-01),  interval(6.467191e-02),  interval(2.225161e-02),  interval(8.092287e-03),  interval(3.221996e-03),  interval(1.113713e-03),  interval(2.012553e-05)},
{ interval(-5.495610e-04),  interval(6.604902e-02),  interval(1.156574e-01),  interval(1.285342e-01),  interval(8.821015e-02),  interval(6.381688e-02),  interval(5.029436e-02),  interval(1.685071e-02)},
{ interval(-4.601366e-01),  interval(-9.495814e-01),  interval(-7.194186e-01),  interval(-4.465329e-01),  interval(-1.525893e-01),  interval(-6.580032e-02),  interval(-3.187444e-02),  interval(-6.370886e-03)},
{ interval(8.698383e-02),  interval(-5.066417e-02),  interval(-3.263066e-01),  interval(-5.912788e-01),  interval(-7.670285e-01),  interval(-4.645172e-01),  interval(-3.273549e-01),  interval(-1.016695e-01)},
{ interval(6.940639e-01),  interval(1.453253e+00),  interval(1.172123e+00),  interval(8.593031e-01),  interval(4.144021e-01),  interval(-3.703647e-01),  interval(-2.698215e-01),  interval(-8.599637e-02)},
{ interval(2.935343e-01),  interval(6.921724e-01),  interval(6.827288e-01),  interval(7.254491e-01),  interval(8.549753e-01),  interval(9.065521e-01),  interval(-6.902620e-02),  interval(-2.223156e-02)},
{ interval(3.794187e-02),  interval(9.660099e-02),  interval(1.080287e-01),  interval(1.412349e-01),  interval(2.363391e-01),  interval(4.911023e-01),  interval(9.933756e-01),  interval(-2.146251e-03)},
{ interval(3.662934e-03),  interval(9.926169e-03),  interval(1.229031e-02),  interval(1.889962e-02),  interval(4.061624e-02),  interval(1.243109e-01),  interval(4.994843e-01),  interval(9.998323e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-5.495610e-04), interval(-4.601366e-01), interval(1.739677e-01), interval(2.776255e+00), interval(2.348274e+00), interval(6.070698e-01), interval(5.860695e-02), interval(4.580201e-03)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -2.136696e+00,  4.580201e-03,  5.860695e-02,  6.070698e-01,  2.348274e+00,  2.776255e+00,  1.739677e-01,  -4.601366e-01,  -5.495610e-04},
{ 1.862419e+00,  2.449486e-01,  1.152533e+00,  3.070935e+00,  -2.364983e+00,  -9.709896e+00,  -1.699535e+00,  1.578653e+00,  4.153868e-02},
{ -8.173632e-01,  9.262251e-01,  8.018291e-01,  -5.291885e+00,  -6.088789e+00,  1.137532e+01,  4.484799e+00,  -2.147884e+00,  -1.480970e-01},
{ 1.824322e-01,  6.659303e-01,  -1.413276e+00,  -7.913269e-01,  9.028704e+00,  -3.590883e+00,  -5.094531e+00,  1.396264e+00,  2.178148e-01},
{ -1.999166e-02,  1.132642e-01,  -5.638072e-01,  2.142643e+00,  -2.089712e+00,  -1.922474e+00,  2.589385e+00,  -3.565484e-01,  -1.630921e-01},
{ 9.694284e-04,  4.372301e-03,  -3.553422e-02,  2.585530e-01,  -8.123619e-01,  1.020784e+00,  -3.991344e-01,  -3.592810e-02,  6.153181e-02},
{ -1.580858e-05,  2.882406e-05,  -3.518727e-04,  4.006382e-03,  -2.109187e-02,  5.072607e-02,  -5.464721e-02,  2.531798e-02,  -8.934710e-03},
{ 6.825603e-08,  1.248438e-08,  -2.528254e-07,  4.736665e-06,  -4.099958e-05,  1.640057e-04,  -3.038803e-04,  2.620395e-04,  -2.118508e-04}};

#endif /*BENCHMARK_H_*/