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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999990e-01),  interval(-2.893749e-05),  interval(-7.641095e-07),  interval(-1.184667e-05),  interval(-1.583984e-08),  interval(0)},
{ interval(1.599999e-05),  interval(1.000000e+00),  interval(-6.112751e-12),  interval(-9.477341e-11),  interval(-1.267187e-13),  interval(0)},
{ interval(6.399998e-11),  interval(8.000000e-06),  interval(1),  interval(-2.527291e-16),  interval(-3.379166e-19),  interval(0)},
{ interval(1.706666e-16),  interval(3.200000e-11),  interval(8.000000e-06),  interval(1),  interval(-6.758332e-25),  interval(0)},
{ interval(2.133333e-23),  interval(5.333333e-18),  interval(2.000000e-12),  interval(5.000000e-07),  interval(1),  interval(0)},
{ interval(1.066666e-30),  interval(3.333333e-25),  interval(1.666667e-19),  interval(6.250000e-14),  interval(2.500000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599999e-05), interval(1.280000e-10), interval(3.413332e-16), interval(6.826665e-22), interval(6.826666e-29), interval(2.844444e-36)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999999e+00,  2.844444e-36,  6.826666e-29,  6.826665e-22,  3.413332e-16,  1.280000e-10,  1.599999e-05},
{ 1.500000e+01,  1.621333e-34,  1.706666e-27,  6.143997e-21,  3.413329e-16,  -3.839999e-10,  -7.999996e-05},
{ -1.999999e+01,  8.590219e-34,  2.730665e-27,  -6.826665e-21,  -2.730665e-15,  2.560001e-10,  1.599999e-04},
{ 1.499999e+01,  8.590217e-34,  -2.730666e-27,  -6.826661e-21,  2.730665e-15,  2.559997e-10,  -1.599999e-04},
{ -5.999995e+00,  1.621332e-34,  -1.706666e-27,  6.143997e-21,  -3.413334e-16,  -3.839997e-10,  7.999996e-05},
{ 9.999990e-01,  2.844442e-36,  -6.826661e-29,  6.826661e-22,  -3.413331e-16,  1.279999e-10,  -1.599999e-05}};

#endif /*BENCHMARK_H_*/