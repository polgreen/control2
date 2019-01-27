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
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.001250e+00),  interval(5.002084e-02),  interval(0),  interval(0)},
{ interval(5.002084e-02),  interval(1.001250e+00),  interval(0),  interval(0)},
{ interval(1.250260e-03),  interval(5.002084e-02),  interval(1),  interval(0)},
{ interval(2.083594e-05),  interval(1.250260e-03),  interval(5.000000e-02),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.002084e-02), interval(1.250260e-03), interval(2.083594e-05), interval(2.604384e-07)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.002501e+00,  2.604384e-07,  2.083594e-05,  1.250260e-03,  5.002084e-02},
{ 6.005001e+00,  2.865213e-06,  6.251823e-05,  -1.250260e-03,  -1.500625e-01},
{ -4.002501e+00,  2.865213e-06,  -6.251823e-05,  -1.250260e-03,  1.500625e-01},
{ 1,  2.604384e-07,  -2.083594e-05,  1.250260e-03,  -5.002084e-02}};

#endif /*BENCHMARK_H_*/