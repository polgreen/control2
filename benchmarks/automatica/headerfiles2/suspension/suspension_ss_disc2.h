#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(4.680495e-03),  interval(1.004249e-02),  interval(1.969995e-02),  interval(1.045700e-02)},
{ interval(-8.097199e-02),  interval(-1.585708e-01),  interval(-2.407741e-01),  interval(-4.420440e-02)},
{ interval(8.557232e-02),  interval(1.522833e-01),  interval(1.383347e-01),  interval(-2.682790e-01)},
{ interval(2.596716e-01),  interval(5.342323e-01),  interval(9.771099e-01),  interval(7.855061e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-2.530375e-03), interval(1.069654e-02), interval(6.491789e-02), interval(5.190303e-02)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -7.699505e-01,  5.190303e-02,  6.491789e-02,  1.069654e-02,  -2.530375e-03},
{ 2.845817e-01,  6.929667e-02,  -5.351528e-02,  -2.765197e-02,  3.865469e-03},
{ -7.667699e-04,  3.144479e-03,  -1.139957e-02,  1.693772e-02,  -1.309314e-03},
{ 6.198792e-12,  2.611273e-07,  -3.041250e-06,  1.770935e-05,  -2.578022e-05}};

#endif /*BENCHMARK_H_*/