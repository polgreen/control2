#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1000000
#define INPUT_LOWERBOUND (__plant_precisiont)-1000000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.974220e-01),  interval(-1.108919e-03),  interval(-3.982620e-04),  interval(-1.650904e-04)},
{ interval(1.278349e-03),  interval(9.999993e-01),  interval(-2.549945e-07),  interval(-1.057033e-07)},
{ interval(2.046239e-07),  interval(3.199999e-04),  interval(1.000000e+00),  interval(-1.127744e-11)},
{ interval(1.091562e-11),  interval(2.560000e-08),  interval(1.600000e-04),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(3.994842e-05), interval(2.557799e-08), interval(2.728906e-12), interval(1.091703e-16)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -3.997421e+00,  1.091703e-16,  2.728906e-12,  2.557799e-08,  3.994842e-05},
{ 5.992265e+00,  1.200254e-15,  8.179677e-12,  -2.559998e-08,  -1.198453e-04},
{ -3.992267e+00,  1.199635e-15,  -8.183196e-12,  -2.553400e-08,  1.198453e-04},
{ 9.974227e-01,  1.090014e-16,  -2.725387e-12,  2.555600e-08,  -3.994842e-05}};

#endif /*BENCHMARK_H_*/