#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-01 
// No controller needed, safe and stable, completeness k with no controller =  1 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.048374e-01),  interval(2.100611e-01),  interval(2.066266e-02),  interval(6.504802e-02),  interval(3.755344e-01)},
{ interval(0),  interval(7.788008e-01),  interval(9.033475e-02),  interval(3.156122e-01),  interval(2.396729e+00)},
{ interval(0),  interval(0),  interval(7.927521e-04),  interval(6.308523e-03),  interval(5.637409e-01)},
{ interval(0),  interval(0),  interval(0),  interval(3.726653e-06),  interval(3.367110e-02)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(6.737947e-03)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.985159e+00), interval(2.332613e+01), interval(5.222808e+01), interval(8.898953e+00), interval(2.979786e+00)};
const __plant_typet __char_poly_const[6][6] = 
 {{ -1,  0,  0,  0,  0,  0},
{ 1.691173e+00,  -1.985159e+00,  -2.332613e+01,  -5.222808e+01,  -8.898953e+00,  -2.979786e+00},
{ -7.173787e-01,  -6.115953e+00,  6.613733e+00,  8.654934e+01,  1.494930e+01,  5.019255e+00},
{ 5.318461e-03,  -9.231013e-01,  1.298350e+01,  -3.447484e+01,  -6.214860e+00,  -2.103816e+00},
{ -3.783917e-06,  -4.032023e-03,  1.175831e-01,  -9.747704e-01,  -2.353222e-02,  1.672477e-03},
{ 1.402752e-11,  -2.214606e-07,  1.129200e-05,  -1.759881e-04,  2.255354e-05,  -6.203523e-09}};

#endif /*BENCHMARK_H_*/