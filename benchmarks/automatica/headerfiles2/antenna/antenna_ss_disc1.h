#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-4.306408e-01),  interval(-4.336171e-01),  interval(-1.458050e-01),  interval(-3.904971e-02),  interval(0),  interval(0)},
{ interval(2.897602e-01),  interval(-1.997381e-01),  interval(-6.040732e-01),  interval(-2.272449e-01),  interval(0),  interval(0)},
{ interval(8.431117e-01),  interval(8.167347e-01),  interval(5.659785e-01),  interval(-1.723705e-01),  interval(0),  interval(0)},
{ interval(3.197598e-01),  interval(4.655865e-01),  interval(6.987742e-01),  interval(9.588084e-01),  interval(0),  interval(0)},
{ interval(1.193959e-03),  interval(2.200498e-03),  interval(4.721752e-03),  interval(1.238514e-02),  interval(1),  interval(0)},
{ interval(1.664576e-06),  interval(3.658411e-06),  interval(1.010747e-05),  interval(3.893365e-05),  interval(6.250000e-03),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.263751e-03), interval(1.317362e-02), interval(9.992494e-03), interval(2.387918e-03), interval(6.658304e-06), interval(7.469830e-09)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.894408e+00,  7.469830e-09,  6.658304e-06,  2.387918e-03,  9.992494e-03,  1.317362e-02,  2.263751e-03},
{ 3.436982e+00,  2.733954e-07,  9.583460e-05,  9.217759e-03,  -1.101048e-02,  -4.668400e-02,  -1.478959e-02},
{ -2.584643e+00,  9.502206e-07,  6.050739e-05,  -1.711310e-02,  -2.407426e-02,  5.487308e-02,  3.563789e-02},
{ 1.514055e+00,  6.595500e-07,  -1.190246e-04,  -2.458844e-03,  3.836071e-02,  -1.625143e-02,  -4.081362e-02},
{ -5.500668e-01,  9.156240e-08,  -4.275793e-05,  7.446351e-03,  -1.041919e-02,  -1.124847e-02,  2.255319e-02},
{ 7.808167e-02,  1.208336e-09,  -1.217809e-06,  5.199126e-04,  -2.849270e-03,  6.137202e-03,  -4.851615e-03}};

#endif /*BENCHMARK_H_*/