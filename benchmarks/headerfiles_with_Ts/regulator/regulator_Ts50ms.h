#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
// No controller needed, safe and stable, completeness k with no controller =  1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.900498e-01),  interval(2.456654e-02),  interval(7.892919e-04),  interval(8.896667e-04),  interval(8.268331e-04)},
{ interval(0),  interval(9.753099e-01),  interval(5.638646e-02),  interval(9.117294e-02),  interval(1.172441e-01)},
{ interval(0),  interval(0),  interval(4.896815e-01),  interval(1.624466e+00),  interval(3.577595e+00)},
{ interval(0),  interval(0),  interval(0),  interval(2.865048e-01),  interval(1.600129e+00)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(6.065307e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.688703e-04), interval(4.971753e-02), interval(2.213863e+00), interval(1.621069e+00), interval(1.180408e+00)};
const __plant_typet __char_poly_const[6][6] = 
 {{ -1,  0,  0,  0,  0,  0},
{ 3.348077e+00,  -2.688703e-04,  -4.971753e-02,  -2.213863e+00,  -1.621069e+00,  -1.180408e+00},
{ -4.294219e+00,  -4.752980e-03,  -2.930572e-01,  -5.282980e-01,  3.074214e+00,  3.236143e+00},
{ 2.621239e+00,  -8.065882e-03,  1.305952e-01,  6.806055e+00,  -9.022001e-01,  -3.106110e+00},
{ -7.572993e-01,  -2.071507e-03,  1.950324e-01,  -3.442134e+00,  -9.794538e-01,  1.210180e+00},
{ 8.216712e-02,  -5.085783e-05,  1.106306e-02,  -6.236613e-01,  4.281925e-01,  -1.599107e-01}};

#endif /*BENCHMARK_H_*/