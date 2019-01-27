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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999950e-01),  interval(-1.446872e-04),  interval(-3.821488e-06),  interval(-5.923325e-05),  interval(-7.919902e-08),  interval(0)},
{ interval(7.999980e-05),  interval(1.000000e+00),  interval(-1.528438e-10),  interval(-2.369332e-09),  interval(-3.167963e-12),  interval(0)},
{ interval(1.599997e-09),  interval(4.000000e-05),  interval(1.000000e+00),  interval(-3.159111e-14),  interval(-4.223953e-17),  interval(0)},
{ interval(2.133331e-14),  interval(8.000000e-10),  interval(4.000000e-05),  interval(1),  interval(-4.223954e-22),  interval(0)},
{ interval(1.333332e-20),  interval(6.666667e-16),  interval(5.000000e-11),  interval(2.500000e-06),  interval(1),  interval(0)},
{ interval(3.333331e-27),  interval(2.083333e-22),  interval(2.083333e-17),  interval(1.562500e-12),  interval(1.250000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.999980e-05), interval(3.199995e-09), interval(4.266661e-14), interval(4.266662e-19), interval(2.133332e-25), interval(4.444441e-32)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.999995e+00,  4.444441e-32,  2.133332e-25,  4.266662e-19,  4.266661e-14,  3.199995e-09,  7.999980e-05},
{ 1.499998e+01,  2.533330e-30,  5.333324e-24,  3.839991e-18,  4.266640e-14,  -9.599989e-09,  -3.999990e-04},
{ -1.999995e+01,  1.342219e-29,  8.533307e-24,  -4.266662e-18,  -3.413324e-13,  6.400011e-09,  7.999980e-04},
{ 1.499995e+01,  1.342218e-29,  -8.533317e-24,  -4.266650e-18,  3.413326e-13,  6.399957e-09,  -7.999980e-04},
{ -5.999975e+00,  2.533324e-30,  -5.333316e-24,  3.839989e-18,  -4.266672e-14,  -9.599963e-09,  3.999990e-04},
{ 9.999950e-01,  4.444426e-32,  -2.133324e-25,  4.266650e-19,  -4.266651e-14,  3.199989e-09,  -7.999980e-05}};

#endif /*BENCHMARK_H_*/