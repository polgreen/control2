#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.641667e-01),  interval(-3.393718e-01),  interval(-1.466975e-01)},
{ interval(3.911932e-01),  interval(4.226232e-01),  interval(-2.817058e-01)},
{ interval(1.878039e-01),  interval(3.795041e-01),  interval(9.390838e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.889916e-02), interval(9.390194e-02), interval(2.030539e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -1.197540e+00,  2.030539e-02,  9.390194e-02,  4.889916e-02},
{ 4.405504e-01,  3.957156e-02,  -5.935735e-02,  -1.014327e-01},
{ -4.978707e-02,  4.530746e-03,  -3.454459e-02,  5.253359e-02}};

#endif /*BENCHMARK_H_*/