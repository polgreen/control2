#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 2.500000e-02 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.950125e-01),  interval(1.239113e-02),  interval(2.213941e-04),  interval(1.400081e-04),  interval(6.548272e-05)},
{ interval(0),  interval(9.875778e-01),  interval(3.341716e-02),  interval(3.100698e-02),  interval(1.971776e-02)},
{ interval(0),  interval(0),  interval(6.997725e-01),  interval(1.315321e+00),  interval(1.336378e+00)},
{ interval(0),  interval(0),  interval(0),  interval(5.352614e-01),  interval(1.217697e+00)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(7.788008e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.023331e-05), interval(3.933056e-03), interval(3.709370e-01), interval(5.295568e-01), interval(6.635977e-01)};
const __plant_typet __char_poly_const[6][6] = 
 {{ -1,  0,  0,  0,  0,  0},
{ 3.996425e+00,  -1.023331e-05,  -3.933056e-03,  -3.709370e-01,  -5.295568e-01,  -6.635977e-01},
{ -6.311668e+00,  -2.177403e-04,  -3.006631e-02,  -3.605040e-01,  1.024822e+00,  2.135208e+00},
{ 4.920155e+00,  -4.503101e-04,  7.314159e-03,  1.607912e+00,  -1.938034e-01,  -2.525506e+00},
{ -1.891562e+00,  -1.436127e-04,  2.449983e-02,  -6.797041e-01,  -5.735352e-01,  1.298137e+00},
{ 2.866481e-01,  -4.449311e-06,  1.854841e-03,  -1.968706e-01,  2.720561e-01,  -2.442460e-01}};

#endif /*BENCHMARK_H_*/