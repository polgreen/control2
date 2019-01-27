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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999990e-01),  interval(2.499996e-06),  interval(9.999750e-12),  interval(1.428429e-15),  interval(1.339152e-19)},
{ interval(0),  interval(9.999975e-01),  interval(7.999704e-06),  interval(1.714086e-09),  interval(2.142617e-13)},
{ interval(0),  interval(0),  interval(9.999286e-01),  interval(4.285079e-04),  interval(8.034653e-08)},
{ interval(0),  interval(0),  interval(0),  interval(9.998750e-01),  interval(3.749672e-04)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.999500e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.017489e-24), interval(8.034913e-18), interval(4.017409e-12), interval(2.812336e-08), interval(1.499963e-04)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.999750e+00,  1.499963e-04,  2.812336e-08,  4.017409e-12,  8.034913e-18,  4.017489e-24},
{ 9.999000e+00,  -5.999550e-04,  -5.624625e-08,  8.033842e-12,  8.034473e-17,  1.044504e-22},
{ -9.998501e+00,  8.998876e-04,  2.814961e-12,  -2.410293e-11,  -4.311049e-21,  2.651322e-22},
{ 4.999001e+00,  -5.998951e-04,  5.623969e-08,  8.034775e-12,  -8.034144e-17,  1.044417e-22},
{ -9.997501e-01,  1.499663e-04,  -2.811961e-08,  4.016900e-12,  -8.033705e-18,  4.016820e-24}};

#endif /*BENCHMARK_H_*/