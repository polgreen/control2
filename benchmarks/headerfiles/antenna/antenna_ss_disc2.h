#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 2.000000e-01 
// stable. safety not checked, completeness k 206366755
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.503634e+00),  interval(1.210708e-01),  interval(-6.991028e-01),  interval(2.872256e-02),  interval(2.645347e-01),  interval(-1.950959e-01)},
{ interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(1.250000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.906250e-03), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -1.503634e+00,  0,  0,  0,  0,  0,  3.906250e-03},
{ -1.210708e-01,  0,  0,  0,  0,  3.906250e-03,  0},
{ 6.991028e-01,  0,  0,  0,  3.906250e-03,  0,  0},
{ -1.436128e-02,  0,  0,  1.953125e-03,  0,  0,  0},
{ -6.613367e-02,  0,  9.765625e-04,  0,  0,  0,  0},
{ 6.096747e-03,  1.220703e-04,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/