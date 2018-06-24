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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-1.590522e-01),  interval(-1.019035e-01),  interval(8.849018e-11),  interval(-6.047672e-42)},
{ interval(6.250000e-02),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(6.250000e-02),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(6.250000e-02),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(16), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ 1.590522e-01,  16,  0,  0,  0},
{ 6.368970e-03,  0,  1,  0,  0},
{ -3.456648e-13,  0,  0,  6.250000e-02,  0},
{ 1.476482e-45,  0,  0,  0,  3.906250e-03}};

#endif /*BENCHMARK_H_*/