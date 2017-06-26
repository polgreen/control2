#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-01 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.063874e+00),  interval(-6.491412e-02),  interval(1.021100e-01),  interval(-2.134125e-03)},
{ interval(-7.500843e-02),  interval(1.151202e+00),  interval(-2.465987e-03),  interval(1.049811e-01)},
{ interval(1.306278e+00),  interval(-1.343118e+00),  interval(1.063874e+00),  interval(-6.491412e-02)},
{ interval(-1.551976e+00),  interval(3.113168e+00),  interval(-7.500843e-02),  interval(1.151202e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.537333e-02), interval(3.082272e-02), interval(-3.170500e-01), interval(6.351355e-01)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.430152e+00,  -1.537333e-02,  3.082272e-02,  -3.170500e-01,  6.351355e-01},
{ 6.879459e+00,  1.602064e-02,  -3.245398e-02,  9.645688e-01,  -1.938980e+00},
{ -4.430152e+00,  1.602064e-02,  -3.245398e-02,  -9.645688e-01,  1.938980e+00},
{ 1.000000e+00,  -1.537333e-02,  3.082272e-02,  3.170500e-01,  -6.351355e-01}};

#endif /*BENCHMARK_H_*/