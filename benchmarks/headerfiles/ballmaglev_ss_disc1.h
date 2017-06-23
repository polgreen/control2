#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1.000000e-03 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 3 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.001000e+00),  interval(1.000000e-03),  interval(-1.686000e-05)},
{ interval(1.867000e+00),  interval(1.001000e+00),  interval(-3.349000e-02)},
{ interval(0),  interval(0),  interval(9.585000e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.200000e-08), interval(3.587000e-05), interval(2.083000e-03)};
const __plant_typet __char_poly_const[4][4] = 
 {{ -1,  0,  0,  0},
{ 2.960500e+00,  1.200000e-08,  -3.587000e-05,  -2.083000e-03},
{ -2.919051e+00,  -2.426462e-08,  1.400693e-04,  4.170166e-03},
{ 9.586284e-01,  8.050007e-08,  -1.042011e-04,  -2.083279e-03}};

#endif /*BENCHMARK_H_*/