#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.744536e-01),  interval(-1.096689e-02),  interval(-3.937834e-03),  interval(-1.631849e-03)},
{ interval(1.263595e-02),  interval(9.999295e-01),  interval(-2.530801e-05),  interval(-1.048888e-05)},
{ interval(2.030472e-05),  interval(3.199925e-03),  interval(1.000000e+00),  interval(-1.121221e-08)},
{ interval(1.085248e-08),  interval(2.559970e-06),  interval(1.600000e-03),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.948734e-04), interval(2.538090e-06), interval(2.713121e-09), interval(1.086648e-12)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.974383e+00,  1.086648e-12,  2.713121e-09,  2.538090e-06,  3.948734e-04},
{ 5.923290e+00,  1.189167e-11,  8.069629e-09,  -2.559829e-06,  -1.184620e-03},
{ -3.923430e+00,  1.183046e-11,  -8.104412e-09,  -2.494611e-06,  1.184620e-03},
{ 9.745235e-01,  1.069952e-12,  -2.678337e-09,  2.516350e-06,  -3.948734e-04}};

#endif /*BENCHMARK_H_*/