#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000164e+00),  interval(-1.211169e-04),  interval(5.303635e-05),  interval(-2.647733e-05),  interval(2.217434e-05)},
{ interval(1.000082e-04),  interval(1.000000e+00),  interval(2.651756e-09),  interval(-1.323832e-09),  interval(1.108687e-09)},
{ interval(5.000273e-09),  interval(1.000000e-04),  interval(1.000000e+00),  interval(-4.412718e-14),  interval(3.695572e-14)},
{ interval(8.333675e-14),  interval(2.500000e-09),  interval(5.000000e-05),  interval(1),  interval(4.619427e-19)},
{ interval(2.604252e-19),  interval(1.041667e-14),  interval(3.125000e-10),  interval(1.250000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.125256e-06), interval(1.562585e-10), interval(5.208547e-15), interval(6.510630e-20), interval(1.627649e-25)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.000164e+00,  1.627649e-25,  6.510630e-20,  5.208547e-15,  1.562585e-10,  3.125256e-06},
{ 1.000066e+01,  4.232002e-24,  6.510865e-19,  1.041795e-14,  -3.125085e-10,  -1.250102e-05},
{ -1.000098e+01,  1.074307e-23,  2.346945e-23,  -3.125256e-14,  -2.560304e-14,  1.875154e-05},
{ 5.000655e+00,  4.232233e-24,  -6.511035e-19,  1.041709e-14,  3.125427e-10,  -1.250102e-05},
{ -1.000164e+00,  1.627826e-25,  -6.511270e-20,  5.208973e-15,  -1.562671e-10,  3.125256e-06}};

#endif /*BENCHMARK_H_*/