#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 2.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.893483e+00),  interval(-1.708843e+00),  interval(8.777455e-01),  interval(-5.696812e-01),  interval(2.338174e-01),  interval(-1.127176e-01),  interval(9.957414e-02)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[8][8] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0},
{ 3.893483e+00,  0,  0,  0,  0,  0,  0,  -2.500000e-01},
{ -6.835373e+00,  0,  0,  0,  0,  0,  -1,  0},
{ 7.021964e+00,  0,  0,  0,  0,  -2,  0,  0},
{ -4.557450e+00,  0,  0,  0,  -2,  0,  0,  0},
{ 1.870539e+00,  0,  0,  -2,  0,  0,  0,  0},
{ -4.508704e-01,  0,  -1,  0,  0,  0,  0,  0},
{ 4.978707e-02,  -1.250000e-01,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/