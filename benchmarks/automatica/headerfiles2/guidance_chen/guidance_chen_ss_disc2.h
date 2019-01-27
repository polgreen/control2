#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.171376e+00),  interval(-1.285568e-01),  interval(5.681319e-02),  interval(-2.856400e-02),  interval(2.404431e-02)},
{ interval(1.084419e-01),  interval(9.936978e-01),  interval(2.776829e-03),  interval(-1.392898e-03),  interval(1.170553e-03)},
{ interval(5.279297e-03),  interval(9.979200e-02),  interval(1.000092e+00),  interval(-4.584648e-05),  interval(3.849543e-05)},
{ interval(8.680886e-05),  interval(2.497416e-03),  interval(5.000114e-02),  interval(9.999994e-01),  interval(4.772935e-07)},
{ interval(2.690794e-07),  interval(1.041023e-05),  interval(3.125028e-04),  interval(1.250000e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.388810e-03), interval(1.649780e-04), interval(5.425554e-06), interval(6.726985e-08), interval(1.672626e-10)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.165164e+00,  1.672626e-10,  6.726985e-08,  5.425554e-06,  1.649780e-04,  3.388810e-03},
{ 1.067296e+01,  4.469016e-09,  6.972912e-07,  1.175619e-05,  -3.206963e-04,  -1.355509e-02},
{ -1.102845e+01,  1.165827e-08,  2.546855e-08,  -3.390031e-05,  -2.777938e-05,  2.033242e-02},
{ 5.698687e+00,  4.719879e-09,  -7.158107e-07,  1.082983e-05,  3.577354e-04,  -1.355479e-02},
{ -1.178033e+00,  1.865680e-10,  -7.421894e-08,  5.888737e-06,  -1.742378e-04,  3.388660e-03}};

#endif /*BENCHMARK_H_*/