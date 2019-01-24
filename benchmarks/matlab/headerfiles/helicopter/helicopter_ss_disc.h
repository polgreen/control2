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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.096392e-01),  interval(-1.552869e-02),  interval(-1.785605e-01)},
{ interval(2.254552e-01),  interval(9.990216e-01),  interval(-2.310399e-02)},
{ interval(2.917170e-02),  interval(2.499594e-01),  interval(9.980414e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.214566e+00), interval(9.334945e-01), interval(7.913591e-02)};
const __plant_typet __char_poly_const[4][4] = 
 {{ 1,  0,  0,  0},
{ -2.806702e+00,  7.913591e-02,  9.334945e-01,  7.214566e+00},
{ 2.628450e+00,  3.006669e-01,  -6.272694e-02,  -1.443657e+01},
{ -8.105842e-01,  7.126433e-02,  -8.707676e-01,  7.222003e+00}};

#endif /*BENCHMARK_H_*/