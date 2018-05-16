#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(7.874743e+00),  interval(-6.948441e+00),  interval(3.606627e+00),  interval(-2.427159e+00),  interval(1.098092e+00),  interval(-6.679637e-01),  interval(5.268053e-01),  interval(-2.444051e-01),  interval(2.032848e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.953125e-03), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.874743e+00,  1.953125e-03,  0,  0,  0,  0,  0,  0,  0,  0},
{ 2.779377e+01,  0,  7.812500e-03,  0,  0,  0,  0,  0,  0,  0},
{ -5.770603e+01,  0,  0,  3.125000e-02,  0,  0,  0,  0,  0,  0},
{ 7.766907e+01,  0,  0,  0,  6.250000e-02,  0,  0,  0,  0,  0},
{ -7.027788e+01,  0,  0,  0,  0,  1.250000e-01,  0,  0,  0,  0},
{ 4.274968e+01,  0,  0,  0,  0,  0,  1.250000e-01,  0,  0,  0},
{ -1.685777e+01,  0,  0,  0,  0,  0,  0,  6.250000e-02,  0,  0},
{ 3.910481e+00,  0,  0,  0,  0,  0,  0,  0,  3.125000e-02,  0},
{ -4.065697e-01,  0,  0,  0,  0,  0,  0,  0,  0,  3.906250e-03}};

#endif /*BENCHMARK_H_*/