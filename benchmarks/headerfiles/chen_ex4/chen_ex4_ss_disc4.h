#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-02 
// No controller needed, safe and stable, completeness k with no controller =  97 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.489898e+00),  interval(-8.025453e+00),  interval(4.434655e+00),  interval(-3.157189e+00),  interval(1.501606e+00),  interval(-9.542358e-01),  interval(7.812786e-01),  interval(-3.739206e-01),  interval(1.594070e-01)},
{ interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(4),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.441406e-04), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ 8.489898e+00,  0,  0,  0,  0,  0,  0,  0,  0,  -2.441406e-04},
{ -3.210181e+01,  0,  0,  0,  0,  0,  0,  0,  -9.765625e-04,  0},
{ 7.095448e+01,  0,  0,  0,  0,  0,  0,  -3.906250e-03,  0,  0},
{ -1.010301e+02,  0,  0,  0,  0,  0,  -7.812500e-03,  0,  0,  0},
{ 9.610277e+01,  0,  0,  0,  0,  -1.562500e-02,  0,  0,  0,  0},
{ -6.107109e+01,  0,  0,  0,  -1.562500e-02,  0,  0,  0,  0,  0},
{ 2.500092e+01,  0,  0,  -7.812500e-03,  0,  0,  0,  0,  0,  0},
{ -5.982730e+00,  0,  -3.906250e-03,  0,  0,  0,  0,  0,  0,  0},
{ 6.376282e-01,  -9.765625e-04,  0,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/