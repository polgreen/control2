#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.001639e+00),  interval(-1.211824e-03),  interval(5.306950e-04),  interval(-2.649560e-04),  interval(2.219069e-04)},
{ interval(1.000819e-03),  interval(9.999994e-01),  interval(2.652861e-07),  interval(-1.324442e-07),  interval(1.109232e-07)},
{ interval(5.002731e-07),  interval(9.999998e-04),  interval(1.000000e+00),  interval(-4.414241e-11),  interval(3.696934e-11)},
{ interval(8.336747e-11),  interval(2.500000e-07),  interval(5.000000e-04),  interval(1.000000e+00),  interval(4.620789e-15)},
{ interval(2.605020e-15),  interval(1.041667e-11),  interval(3.125000e-08),  interval(1.250000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.127561e-05), interval(1.563354e-08), interval(5.210467e-12), interval(6.512550e-16), interval(1.628049e-20)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.001639e+00,  1.628049e-20,  6.512550e-16,  5.210467e-12,  1.563354e-08,  3.127561e-05},
{ 1.000656e+01,  4.234083e-19,  6.514898e-15,  1.042947e-11,  -3.125853e-08,  -1.251024e-04},
{ -1.000984e+01,  1.075099e-18,  2.348676e-18,  -3.127561e-11,  -2.562192e-11,  1.876537e-04},
{ 5.006558e+00,  4.236396e-19,  -6.516606e-15,  1.042093e-11,  3.129269e-08,  -1.251024e-04},
{ -1.001640e+00,  1.629828e-20,  -6.518956e-16,  5.214737e-12,  -1.564208e-08,  3.127561e-05}};

#endif /*BENCHMARK_H_*/