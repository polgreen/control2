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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.000002e+00),  interval(5.000004e-05),  interval(-4.256136e-08)},
{ interval(8.761068e-02),  interval(1.000002e+00),  interval(-1.701912e-03)},
{ interval(0),  interval(0),  interval(9.980884e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.364363e-12), interval(-8.184877e-08), interval(9.606191e-05)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.998093e+00,  9.606191e-05,  -8.184877e-08,  -1.364363e-12},
{ 2.996181e+00,  -1.921242e-04,  5.218819e-11,  -5.454845e-12},
{ -9.980884e-01,  9.606191e-05,  8.179658e-08,  -1.363059e-12}};

#endif /*BENCHMARK_H_*/