#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-3.075744e-01),  interval(1.792737e-02),  interval(2.342165e-01),  interval(3.061885e-01),  interval(2.188017e-01),  interval(2.163274e-01),  interval(1.401787e-01),  interval(1.199280e-01),  interval(8.305914e-02)},
{ interval(-8.004947e-01),  interval(-1.208131e+00),  interval(-8.075827e-01),  interval(-4.508851e-01),  interval(-1.920264e-01),  interval(-1.179852e-01),  interval(-5.009971e-02),  interval(-2.302730e-02),  interval(-7.732680e-03)},
{ interval(7.452484e-02),  interval(-7.166542e-01),  interval(-1.131277e+00),  interval(-1.529578e+00),  interval(-8.268815e-01),  interval(-6.756409e-01),  interval(-3.867174e-01),  interval(-2.942504e-01),  interval(-1.890750e-01)},
{ interval(9.111191e-01),  interval(1.062271e+00),  interval(5.812644e-01),  interval(-8.491390e-02),  interval(-6.140105e-01),  interval(-5.233169e-01),  interval(-3.093673e-01),  interval(-2.442543e-01),  interval(-1.611783e-01)},
{ interval(7.766898e-01),  interval(1.329336e+00),  interval(1.332097e+00),  interval(1.473244e+00),  interval(6.955684e-01),  interval(-2.643643e-01),  interval(-1.584465e-01),  interval(-1.270453e-01),  interval(-8.474492e-02)},
{ interval(2.041854e-01),  interval(4.238810e-01),  interval(5.429001e-01),  interval(9.005427e-01),  interval(9.418045e-01),  interval(9.489058e-01),  interval(-3.086710e-02),  interval(-2.497162e-02),  interval(-1.676051e-02)},
{ interval(4.038298e-02),  interval(9.647720e-02),  interval(1.476152e-01),  interval(3.178274e-01),  interval(4.908515e-01),  interval(9.919086e-01),  interval(9.950860e-01),  interval(-3.999169e-03),  interval(-2.695221e-03)},
{ interval(3.246948e-03),  interval(8.700689e-03),  interval(1.540807e-02),  interval(4.063272e-02),  interval(8.271965e-02),  interval(2.494543e-01),  interval(4.996673e-01),  interval(9.997281e-01),  interval(-1.837826e-04)},
{ interval(1.107020e-04),  interval(3.274740e-04),  interval(6.579545e-04),  interval(2.053142e-03),  interval(5.190332e-03),  interval(2.081726e-02),  interval(6.249017e-02),  interval(2.499919e-01),  interval(9.999945e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.000618e-01), interval(9.315605e-03), interval(2.277798e-01), interval(1.941725e-01), interval(1.020927e-01), interval(2.019149e-02), interval(3.246948e-03), interval(2.214039e-04), interval(6.575782e-06)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -1.907386e+00,  6.575782e-06,  2.214039e-04,  3.246948e-03,  2.019149e-02,  1.020927e-01,  1.941725e-01,  2.277798e-01,  9.315605e-03,  -1.000618e-01},
{ 2.200475e+00,  1.743017e-03,  2.605892e-02,  1.593724e-01,  3.587322e-01,  3.945559e-01,  -4.100343e-01,  -1.102664e+00,  -2.425791e-01,  3.617915e-01},
{ -1.899562e+00,  2.614016e-02,  1.937101e-01,  4.132398e-01,  -2.460128e-01,  -1.738859e+00,  -5.928424e-01,  1.938375e+00,  9.726364e-01,  -5.300764e-01},
{ 1.383374e+00,  8.654835e-02,  2.070270e-01,  -5.232042e-01,  -1.104981e+00,  1.159266e+00,  2.375497e+00,  -1.072973e+00,  -1.728972e+00,  2.926717e-01},
{ -8.585977e-01,  9.226871e-02,  -1.680177e-01,  -6.025920e-01,  9.643410e-01,  1.288277e+00,  -2.162960e+00,  -9.306430e-01,  1.591405e+00,  1.898911e-01},
{ 4.201466e-01,  3.485391e-02,  -2.099133e-01,  3.232728e-01,  3.925418e-01,  -1.500781e+00,  2.564357e-01,  1.587552e+00,  -6.836292e-01,  -4.306749e-01},
{ -1.807887e-01,  4.262801e-03,  -4.692924e-02,  2.090012e-01,  -3.226966e-01,  1.170091e-01,  5.257138e-01,  -7.287559e-01,  7.121897e-03,  3.080972e-01},
{ 5.759757e-02,  1.161504e-04,  -2.150534e-03,  1.755163e-02,  -6.129642e-02,  1.732199e-01,  -1.719206e-01,  5.043445e-02,  1.007571e-01,  -1.064472e-01},
{ -1.110900e-02,  1.794603e-07,  -6.685819e-06,  1.114210e-04,  -8.192005e-04,  5.219643e-03,  -1.406134e-02,  3.089466e-02,  -2.605579e-02,  1.480870e-02}};

#endif /*BENCHMARK_H_*/