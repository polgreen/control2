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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000003e+00),  interval(-2.422196e-06),  interval(1.060655e-06),  interval(-5.295067e-07),  interval(4.434512e-07)},
{ interval(2.000003e-06),  interval(1.000000e+00),  interval(1.060654e-12),  interval(-5.295065e-13),  interval(4.434509e-13)},
{ interval(2.000002e-12),  interval(2.000000e-06),  interval(1),  interval(-3.530042e-19),  interval(2.956339e-19)},
{ interval(6.666672e-19),  interval(1.000000e-12),  interval(1.000000e-06),  interval(1),  interval(7.390845e-26)},
{ interval(4.166669e-26),  interval(8.333333e-20),  interval(1.250000e-13),  interval(2.500000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.250010e-08), interval(6.250007e-14), interval(4.166670e-20), interval(1.041667e-26), interval(5.208336e-34)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -5.000003e+00,  5.208336e-34,  1.041667e-26,  4.166670e-20,  6.250007e-14,  6.250010e-08},
{ 1.000001e+01,  1.354168e-32,  1.041668e-25,  8.333354e-20,  -1.250001e-13,  -2.500004e-07},
{ -1.000002e+01,  3.437506e-32,  7.509619e-32,  -2.500004e-19,  -2.048079e-19,  3.750006e-07},
{ 5.000013e+00,  1.354170e-32,  -1.041669e-25,  8.333340e-20,  1.250003e-13,  -2.500004e-07},
{ -1.000003e+00,  5.208348e-34,  -1.041669e-26,  4.166677e-20,  -6.250014e-14,  6.250010e-08}};

#endif /*BENCHMARK_H_*/