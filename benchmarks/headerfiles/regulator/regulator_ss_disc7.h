#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-03 
// No controller needed, safe and stable, suggested completeness k 1 
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.990005e-01),  interval(2.495629e-03),  interval(9.754735e-06),  interval(1.359229e-06),  interval(1.274157e-07)},
{ interval(0),  interval(9.975031e-01),  interval(7.711320e-03),  interval(1.604739e-03),  interval(2.013870e-04)},
{ interval(0),  interval(0),  interval(9.310894e-01),  interval(3.885132e-01),  interval(7.402640e-02)},
{ interval(0),  interval(0),  interval(0),  interval(8.824969e-01),  interval(3.436626e-01)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.512294e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.854344e-09), interval(7.646486e-06), interval(3.778397e-03), interval(2.654005e-02), interval(1.463117e-01)};
const __plant_typet __char_poly_const[6][6] = 
 {{ -1,  0,  0,  0,  0,  0},
{ 4.761319e+00,  -3.854344e-09,  -7.646486e-06,  -3.778397e-03,  -2.654005e-02,  -1.463117e-01},
{ -9.063291e+00,  -9.615521e-08,  -7.241159e-05,  -6.669961e-03,  5.266226e-02,  5.574608e-01},
{ 8.621501e+00,  -2.341589e-07,  3.807260e-06,  2.127176e-02,  -2.487445e-03,  -7.957926e-01},
{ -4.098408e+00,  -8.847024e-08,  6.950130e-05,  -7.494700e-03,  -4.686427e-02,  5.044454e-01},
{ 7.788787e-01,  -3.262852e-09,  6.579159e-06,  -3.328760e-03,  2.322949e-02,  -1.198019e-01}};

#endif /*BENCHMARK_H_*/