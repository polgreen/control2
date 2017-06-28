#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 4 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(5.435289e+01),  interval(-8.329919e+01),  interval(9.944285e+00),  interval(-1.321742e+01)},
{ interval(-9.625242e+01),  interval(1.664149e+02),  interval(-1.527276e+01),  interval(2.772561e+01)},
{ interval(3.157245e+02),  interval(-5.127647e+02),  interval(5.435289e+01),  interval(-8.329919e+01)},
{ interval(-5.925009e+02),  interval(1.005544e+03),  interval(-9.625242e+01),  interval(1.664149e+02)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.779367e+01), interval(3.467926e+01), interval(-1.086741e+02), interval(2.113120e+02)};
const __plant_typet __char_poly_const[5][5] = 
 {{ 1,  0,  0,  0,  0},
{ -4.415356e+02,  -1.779367e+01,  3.467926e+01,  -1.086741e+02,  2.113120e+02},
{ 4.111525e+03,  1.269610e+02,  -3.097891e+02,  1.074424e+03,  -2.261851e+03},
{ -4.415356e+02,  1.269610e+02,  -3.097891e+02,  -1.074424e+03,  2.261851e+03},
{ 1.000000e+00,  -1.779367e+01,  3.467926e+01,  1.086741e+02,  -2.113120e+02}};

#endif /*BENCHMARK_H_*/