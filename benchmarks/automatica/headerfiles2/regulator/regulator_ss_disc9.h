#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999998e-01),  interval(4.999998e-07),  interval(3.999980e-13),  interval(1.142789e-17),  interval(2.142729e-22)},
{ interval(0),  interval(9.999995e-01),  interval(1.599988e-06),  interval(6.856709e-11),  interval(1.714179e-15)},
{ interval(0),  interval(0),  interval(9.999857e-01),  interval(8.570832e-05),  interval(3.214072e-09)},
{ interval(0),  interval(0),  interval(0),  interval(9.999750e-01),  interval(7.499869e-05)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.999900e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.285639e-27), interval(1.285637e-20), interval(3.214085e-14), interval(1.124987e-09), interval(2.999985e-05)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.999950e+00,  2.999985e-05,  1.124987e-09,  3.214085e-14,  1.285637e-20,  1.285639e-27},
{ 9.999800e+00,  -1.199982e-04,  -2.249970e-09,  6.428015e-14,  1.285623e-19,  3.342634e-26},
{ -9.999700e+00,  1.799955e-04,  2.252194e-14,  -1.928427e-13,  -1.379674e-24,  8.485078e-26},
{ 4.999800e+00,  -1.199958e-04,  2.249918e-09,  6.428164e-14,  -1.285613e-19,  3.342579e-26},
{ -9.999500e-01,  2.999865e-05,  -1.124957e-09,  3.214004e-14,  -1.285599e-20,  1.285596e-27}};

#endif /*BENCHMARK_H_*/