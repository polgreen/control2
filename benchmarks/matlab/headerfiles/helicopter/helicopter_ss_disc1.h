#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.588945e-01),  interval(6.689355e-04),  interval(-3.878030e-02)},
{ interval(4.896503e-02),  interval(1.000025e+00),  interval(-9.762895e-04)},
{ interval(1.232689e-03),  interval(5.000049e-02),  interval(9.999837e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.566881e+00), interval(3.944604e-02), interval(6.597273e-04)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.958903e+00,  6.597273e-04,  3.944604e-02,  1.566881e+00},
{ 2.917870e+00,  2.611445e-03,  -5.482598e-04,  -3.133775e+00},
{ -9.588698e-01,  6.460186e-04,  -3.889778e-02,  1.566894e+00}};

#endif /*BENCHMARK_H_*/