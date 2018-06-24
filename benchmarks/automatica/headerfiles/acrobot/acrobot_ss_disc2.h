#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.200  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.273392e+00),  interval(-2.875794e-01),  interval(2.175845e-01),  interval(-1.817039e-02)},
{ interval(-3.322987e-01),  interval(1.660272e+00),  interval(-2.099593e-02),  interval(2.420291e-01)},
{ interval(2.980920e+00),  interval(-3.261992e+00),  interval(1.273392e+00),  interval(-2.875794e-01)},
{ interval(-3.769240e+00),  interval(7.369262e+00),  interval(-3.322987e-01),  interval(1.660272e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(-6.745890e-02), interval(1.349181e-01), interval(-7.570608e-01), interval(1.509902e+00)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -5.867328e+00,  1.509902e+00,  -7.570608e-01,  1.349181e-01,  -6.745890e-02},
{ 1.007446e+01,  -4.852155e+00,  2.402481e+00,  -1.638562e-01,  7.894195e-02},
{ -5.867328e+00,  4.852155e+00,  -2.402481e+00,  -1.638562e-01,  7.894195e-02},
{ 1.000000e+00,  -1.509902e+00,  7.570608e-01,  1.349181e-01,  -6.745890e-02}};

#endif /*BENCHMARK_H_*/