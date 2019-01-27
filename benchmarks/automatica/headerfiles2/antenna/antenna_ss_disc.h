#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.304452e-01),  interval(-1.094174e-01),  interval(-6.132962e-02),  interval(-2.472802e-02),  interval(0),  interval(0)},
{ interval(1.834891e-01),  interval(1.577266e-02),  interval(-5.218938e-02),  interval(-1.989931e-02),  interval(0),  interval(0)},
{ interval(7.382931e-02),  interval(1.505773e-01),  interval(8.282467e-02),  interval(-1.367831e-02),  interval(0),  interval(0)},
{ interval(2.537425e-02),  interval(3.867744e-02),  interval(9.833361e-02),  interval(1.139973e-01),  interval(0),  interval(0)},
{ interval(2.568124e-02),  interval(2.056385e-02),  interval(2.362595e-02),  interval(3.308626e-02),  interval(1),  interval(0)},
{ interval(4.262860e-04),  interval(3.898554e-04),  interval(4.674819e-04),  interval(7.082768e-04),  interval(3.125000e-02),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.433508e-03), interval(1.153583e-03), interval(7.929454e-04), interval(5.136247e-02), interval(1.705144e-03), interval(1.555280e-05)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -2.082149e+00,  1.555280e-05,  1.705144e-03,  5.136247e-02,  7.929454e-04,  1.153583e-03,  1.433508e-03},
{ 1.184319e+00,  7.426565e-05,  -6.655816e-05,  -1.009302e-01,  -2.008369e-03,  -3.184165e-03,  -4.616718e-03},
{ -1.231638e-01,  1.497038e-05,  -1.618018e-03,  4.888597e-02,  1.333000e-03,  2.582126e-03,  5.267338e-03},
{ 2.197224e-02,  9.917703e-07,  9.287451e-06,  -3.885219e-04,  1.217592e-04,  -1.772191e-04,  -2.436790e-03},
{ -9.806051e-04,  2.976127e-07,  -2.944886e-05,  1.027545e-03,  -1.737699e-04,  -4.231960e-04,  3.708957e-04},
{ 2.902320e-06,  1.759314e-09,  -4.062567e-07,  4.272677e-05,  -6.556580e-05,  4.887067e-05,  -1.823419e-05}};

#endif /*BENCHMARK_H_*/