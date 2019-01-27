#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.294509e-01),  interval(-1.199419e-01),  interval(-6.449724e-02)},
{ interval(1.719926e-01),  interval(9.874399e-01),  interval(-6.787695e-03)},
{ interval(4.525130e-03),  interval(4.978585e-02),  interval(9.998840e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.149908e-02), interval(2.262565e-03), interval(3.866806e-05)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.716775e+00,  3.866806e-05,  2.262565e-03,  2.149908e-02},
{ 2.458240e+00,  1.435410e-04,  -2.153115e-04,  -4.299950e-02},
{ -7.408182e-01,  3.328191e-05,  -2.047253e-03,  2.150043e-02}};

#endif /*BENCHMARK_H_*/