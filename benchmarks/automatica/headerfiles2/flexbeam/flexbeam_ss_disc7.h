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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999900e-01),  interval(-2.893739e-04),  interval(-7.645326e-06),  interval(-1.184662e-04),  interval(-1.583976e-07),  interval(0)},
{ interval(1.599992e-04),  interval(1.000000e+00),  interval(-6.115007e-10),  interval(-9.477312e-09),  interval(-1.267183e-11),  interval(0)},
{ interval(6.399979e-09),  interval(8.000000e-05),  interval(1.000000e+00),  interval(-2.527285e-13),  interval(-3.379158e-16),  interval(0)},
{ interval(1.706662e-13),  interval(3.200000e-09),  interval(8.000000e-05),  interval(1),  interval(-6.758320e-21),  interval(0)},
{ interval(2.133329e-19),  interval(5.333333e-15),  interval(2.000000e-10),  interval(5.000000e-06),  interval(1),  interval(0)},
{ interval(1.066665e-25),  interval(3.333333e-21),  interval(1.666667e-16),  interval(6.250000e-12),  interval(2.500000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599992e-04), interval(1.279996e-08), interval(3.413325e-13), interval(6.826653e-18), interval(6.826655e-24), interval(2.844440e-30)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999990e+00,  2.844440e-30,  6.826655e-24,  6.826653e-18,  3.413325e-13,  1.279996e-08,  1.599992e-04},
{ 1.499995e+01,  1.621329e-28,  1.706661e-22,  6.143973e-17,  3.413291e-13,  -3.839991e-08,  -7.999960e-04},
{ -1.999990e+01,  8.590185e-28,  2.730650e-22,  -6.826653e-17,  -2.730651e-12,  2.560008e-08,  1.599992e-03},
{ 1.499990e+01,  8.590173e-28,  -2.730656e-22,  -6.826612e-17,  2.730655e-12,  2.559966e-08,  -1.599992e-03},
{ -5.999950e+00,  1.621322e-28,  -1.706655e-22,  6.143966e-17,  -3.413342e-13,  -3.839970e-08,  7.999960e-04},
{ 9.999900e-01,  2.844420e-30,  -6.826610e-24,  6.826612e-18,  -3.413308e-13,  1.279991e-08,  -1.599992e-04}};

#endif /*BENCHMARK_H_*/