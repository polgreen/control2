#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999745e-01),  interval(-1.453114e-05),  interval(-9.828017e-06),  interval(-4.312445e-06),  interval(0),  interval(0)},
{ interval(3.199959e-05),  interval(1.000000e+00),  interval(-1.572488e-10),  interval(-6.899941e-11),  interval(0),  interval(0)},
{ interval(2.559978e-10),  interval(1.600000e-05),  interval(1.000000e+00),  interval(-3.679977e-16),  interval(0),  interval(0)},
{ interval(6.826623e-16),  interval(6.400000e-11),  interval(8.000000e-06),  interval(1),  interval(0),  interval(0)},
{ interval(2.133322e-23),  interval(2.666667e-18),  interval(5.000000e-13),  interval(1.250000e-07),  interval(1),  interval(0)},
{ interval(2.666655e-31),  interval(4.166667e-26),  interval(1.041667e-20),  interval(3.906250e-15),  interval(6.250000e-08),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.499968e-07), interval(3.999966e-12), interval(2.133320e-17), interval(4.266645e-23), interval(1.066662e-30), interval(1.111107e-38)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999974e+00,  1.111107e-38,  1.066662e-30,  4.266645e-23,  2.133320e-17,  3.999966e-12,  2.499968e-07},
{ 1.499987e+01,  6.333287e-37,  2.666644e-29,  3.839956e-22,  2.133265e-17,  -1.199993e-11,  -1.249984e-06},
{ -1.999975e+01,  3.355519e-36,  4.266600e-29,  -4.266645e-22,  -1.706642e-16,  8.000068e-12,  2.499968e-06},
{ 1.499975e+01,  3.355507e-36,  -4.266624e-29,  -4.266580e-22,  1.706648e-16,  7.999728e-12,  -2.499968e-06},
{ -5.999873e+00,  6.333218e-37,  -2.666622e-29,  3.839946e-22,  -2.133347e-17,  -1.199976e-11,  1.249984e-06},
{ 9.999745e-01,  1.111087e-38,  -1.066644e-30,  4.266580e-23,  -2.133293e-17,  3.999932e-12,  -2.499968e-07}};

#endif /*BENCHMARK_H_*/