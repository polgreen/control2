#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.872732e-01),  interval(-7.238947e-03),  interval(-4.887068e-03),  interval(-2.142521e-03),  interval(0),  interval(0)},
{ interval(1.589812e-02),  interval(9.999420e-01),  interval(-3.916850e-05),  interval(-1.717675e-05),  interval(0),  interval(0)},
{ interval(6.372825e-05),  interval(7.999845e-03),  interval(9.999999e-01),  interval(-4.585348e-08),  interval(0),  interval(0)},
{ interval(8.506153e-08),  interval(1.599985e-05),  interval(4.000000e-03),  interval(1.000000e+00),  interval(0),  interval(0)},
{ interval(1.329935e-12),  interval(3.333314e-10),  interval(1.250000e-07),  interval(6.250000e-05),  interval(1),  interval(0)},
{ interval(8.315634e-18),  interval(2.604157e-15),  interval(1.302083e-12),  interval(9.765625e-10),  interval(3.125000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.242041e-04), interval(9.957539e-07), interval(2.658173e-09), interval(2.659871e-12), interval(3.326254e-17), interval(1.732950e-22)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.987215e+00,  1.732950e-22,  3.326254e-17,  2.659871e-12,  2.658173e-09,  9.957539e-07,  1.242041e-04},
{ 1.493619e+01,  9.859822e-21,  8.297255e-16,  2.386424e-11,  2.624306e-09,  -2.991485e-06,  -6.210205e-04},
{ -1.987262e+01,  5.214463e-20,  1.323022e-15,  -2.659844e-11,  -2.118067e-08,  2.008400e-06,  1.242041e-03},
{ 1.487285e+01,  5.204974e-20,  -1.326682e-15,  -2.639573e-11,  2.121446e-08,  1.966170e-06,  -1.242041e-03},
{ -5.936539e+00,  9.806092e-21,  -8.263472e-16,  2.383046e-11,  -2.674982e-09,  -2.970370e-06,  6.210205e-04},
{ 9.873309e-01,  1.717240e-22,  -3.298100e-17,  2.639600e-12,  -2.641281e-09,  9.915309e-07,  -1.242041e-04}};

#endif /*BENCHMARK_H_*/