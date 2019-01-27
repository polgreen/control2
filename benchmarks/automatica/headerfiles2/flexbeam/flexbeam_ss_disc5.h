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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.998981e-01),  interval(-2.893634e-03),  interval(-7.687624e-05),  interval(-1.184608e-03),  interval(-1.583904e-06),  interval(0)},
{ interval(1.599919e-03),  interval(9.999977e-01),  interval(-6.137567e-08),  interval(-9.477026e-07),  interval(-1.267145e-09),  interval(0)},
{ interval(6.399785e-07),  interval(7.999994e-04),  interval(1.000000e+00),  interval(-2.527228e-10),  interval(-3.379082e-13),  interval(0)},
{ interval(1.706624e-10),  interval(3.199999e-07),  interval(8.000000e-04),  interval(1.000000e+00),  interval(-6.758198e-17),  interval(0)},
{ interval(2.133291e-15),  interval(5.333332e-12),  interval(2.000000e-08),  interval(5.000000e-05),  interval(1),  interval(0)},
{ interval(1.066649e-20),  interval(3.333333e-17),  interval(1.666667e-13),  interval(6.250000e-10),  interval(2.500000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599919e-03), interval(1.279957e-06), interval(3.413248e-10), interval(6.826530e-14), interval(6.826553e-19), interval(2.844402e-24)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999896e+00,  2.844402e-24,  6.826553e-19,  6.826530e-14,  3.413248e-10,  1.279957e-06,  1.599919e-03},
{ 1.499948e+01,  1.621287e-22,  1.706608e-17,  6.143725e-13,  3.412904e-10,  -3.839914e-06,  -7.999595e-03},
{ -1.999898e+01,  8.589852e-22,  2.730500e-17,  -6.826528e-13,  -2.730512e-09,  2.560084e-06,  1.599919e-02},
{ 1.499899e+01,  8.589730e-22,  -2.730559e-17,  -6.826120e-13,  2.730546e-09,  2.559659e-06,  -1.599919e-02},
{ -5.999497e+00,  1.621217e-22,  -1.706554e-17,  6.143657e-13,  -3.413414e-10,  -3.839701e-06,  7.999595e-03},
{ 9.999004e-01,  2.844203e-24,  -6.826099e-19,  6.826122e-14,  -3.413078e-10,  1.279915e-06,  -1.599919e-03}};

#endif /*BENCHMARK_H_*/