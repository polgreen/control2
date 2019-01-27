#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.145773e-01),  interval(-4.700632e-02),  interval(-2.190085e-02)},
{ interval(4.899138e-02),  interval(9.987812e-01),  interval(-5.690034e-04)},
{ interval(6.364196e-04),  interval(2.558953e-02),  interval(9.999951e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.827451e-04), interval(9.944056e-06), interval(8.548166e-08)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.913354e+00,  8.548166e-08,  9.944056e-06,  3.827451e-04},
{ 2.829143e+00,  3.344932e-07,  -2.874534e-07,  -7.654912e-04},
{ -9.157609e-01,  8.180202e-08,  -9.656602e-06,  3.827461e-04}};

#endif /*BENCHMARK_H_*/