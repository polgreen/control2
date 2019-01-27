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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.003280e+00),  interval(-2.425102e-03),  interval(1.062127e-03),  interval(-5.303185e-04),  interval(4.441774e-04)},
{ interval(2.003279e-03),  interval(9.999976e-01),  interval(1.061636e-06),  interval(-5.300476e-07),  interval(4.439350e-07)},
{ interval(2.002186e-06),  interval(1.999998e-03),  interval(1.000000e+00),  interval(-3.532747e-10),  interval(2.958759e-10)},
{ interval(6.672130e-10),  interval(9.999996e-07),  interval(1.000000e-03),  interval(1.000000e+00),  interval(7.395686e-14)},
{ interval(4.169398e-14),  interval(8.333331e-11),  interval(1.250000e-07),  interval(2.500000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.260247e-05), interval(6.256830e-08), interval(4.170081e-11), interval(1.042350e-14), interval(5.211179e-19)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.003277e+00,  5.211179e-19,  1.042350e-14,  4.170081e-11,  6.256830e-08,  6.260247e-05},
{ 1.001311e+01,  1.355647e-17,  1.043101e-13,  8.353833e-11,  -1.250682e-07,  -2.504099e-04},
{ -1.001968e+01,  3.443137e-17,  7.521924e-17,  -2.504099e-10,  -2.051434e-10,  3.756148e-04},
{ 5.013124e+00,  1.357128e-17,  -1.043648e-13,  8.340156e-11,  1.253417e-07,  -2.504099e-04},
{ -1.003282e+00,  5.222576e-19,  -1.044401e-14,  4.176919e-11,  -6.263668e-08,  6.260247e-05}};

#endif /*BENCHMARK_H_*/