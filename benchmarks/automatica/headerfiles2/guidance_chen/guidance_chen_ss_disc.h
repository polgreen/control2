#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(3.559639e+00),  interval(-2.139854e+00),  interval(1.010599e+00),  interval(-5.351533e-01),  interval(4.677532e-01)},
{ interval(2.109608e+00),  interval(1.031311e-01),  interval(4.150847e-01),  interval(-2.163640e-01),  interval(1.869722e-01)},
{ interval(8.432607e-01),  interval(7.279585e-01),  interval(1.124401e+00),  interval(-6.423778e-02),  interval(5.513414e-02)},
{ interval(1.243299e-01),  interval(2.179208e-01),  interval(5.145547e-01),  interval(9.925303e-01),  interval(6.382506e-03)},
{ interval(3.598207e-03),  interval(9.645715e-03),  interval(3.159787e-02),  interval(1.248222e-01),  interval(1.000151e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(6.592524e-02), interval(2.635190e-02), interval(7.770617e-03), interval(8.995518e-04), interval(2.134115e-05)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -6.779854e+00,  2.134115e-05,  8.995518e-04,  7.770617e-03,  2.635190e-02,  6.592524e-02},
{ 1.851813e+01,  7.258692e-04,  1.273165e-02,  3.077228e-02,  -3.383309e-02,  -2.613010e-01},
{ -2.558365e+01,  2.416149e-03,  5.272763e-03,  -6.725412e-02,  -5.658996e-02,  3.876970e-01},
{ 1.796083e+01,  1.252765e-03,  -1.650076e-02,  1.110760e-02,  1.092694e-01,  -2.551110e-01},
{ -5.147238e+00,  6.361270e-05,  -2.403204e-03,  1.760363e-02,  -4.519822e-02,  6.278986e-02}};

#endif /*BENCHMARK_H_*/