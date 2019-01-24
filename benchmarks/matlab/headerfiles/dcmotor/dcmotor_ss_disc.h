#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 2 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-9.874124e-05),  interval(-9.874085e-02)},
{ interval(9.494312e-04),  interval(9.494274e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.494312e-04), interval(4.862749e-04)};
const __plant_typet __char_poly_const[3][3] = 
 {{ 1,  0,  0},
{ -9.493287e-01,  4.862749e-04,  9.494312e-04},
{ 2.826151e-21,  9.494350e-07,  -9.494312e-04}};

#endif /*BENCHMARK_H_*/