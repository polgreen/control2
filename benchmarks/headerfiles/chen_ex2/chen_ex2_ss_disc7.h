#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.967107e+00),  interval(-6.942546e+00),  interval(3.456991e+00),  interval(-2.151727e+00),  interval(1.714294e+00),  interval(-8.536168e-01),  interval(4.857713e-01),  interval(-2.418846e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.000000e-01), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.967107e+00,  0,  0,  0,  0,  0,  0,  0,  5.000000e-01},
{ 2.777018e+01,  0,  0,  0,  0,  0,  0,  2,  0},
{ -5.531185e+01,  0,  0,  0,  0,  0,  8,  0,  0},
{ 6.885525e+01,  0,  0,  0,  0,  16,  0,  0,  0},
{ -5.485741e+01,  0,  0,  0,  16,  0,  0,  0,  0},
{ 2.731574e+01,  0,  0,  16,  0,  0,  0,  0,  0},
{ -7.772342e+00,  0,  8,  0,  0,  0,  0,  0,  0},
{ 9.675386e-01,  2,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/