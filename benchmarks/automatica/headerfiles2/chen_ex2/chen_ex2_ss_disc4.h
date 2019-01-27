#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 8 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.835813e-01),  interval(-1.356741e-02),  interval(-5.849890e-03),  interval(-2.875788e-03),  interval(-1.663418e-03),  interval(-1.134976e-03),  interval(-8.741733e-04),  interval(-2.905597e-04)},
{ interval(7.934217e-03),  interval(9.999456e-01),  interval(-2.345639e-05),  interval(-1.153265e-05),  interval(-6.671267e-06),  interval(-4.552136e-06),  interval(-3.506243e-06),  interval(-1.165446e-06)},
{ interval(3.182443e-05),  interval(7.999855e-03),  interval(9.999999e-01),  interval(-3.079311e-08),  interval(-1.781353e-08),  interval(-1.215535e-08),  interval(-9.362728e-09),  interval(-3.112135e-09)},
{ interval(4.249101e-08),  interval(1.599985e-05),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-1.782763e-11),  interval(-1.216516e-11),  interval(-9.370381e-12),  interval(-3.114704e-12)},
{ interval(2.126305e-11),  interval(1.066661e-08),  interval(4.000000e-06),  interval(2.000000e-03),  interval(1.000000e+00),  interval(-4.868678e-15),  interval(-3.750194e-15),  interval(-1.246567e-15)},
{ interval(4.254950e-15),  interval(2.666657e-12),  interval(1.333333e-09),  interval(1.000000e-06),  interval(1.000000e-03),  interval(1),  interval(-6.252755e-19),  interval(-2.078429e-19)},
{ interval(3.547185e-19),  interval(2.666660e-16),  interval(1.666667e-13),  interval(1.666667e-10),  interval(2.500000e-07),  interval(5.000000e-04),  interval(1),  interval(-1.485029e-23)},
{ interval(2.534450e-23),  interval(2.222218e-20),  interval(1.666667e-17),  interval(2.083333e-14),  interval(4.166667e-11),  interval(1.250000e-07),  interval(5.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.934217e-03), interval(3.182443e-05), interval(8.498203e-08), interval(8.505220e-11), interval(3.403960e-14), interval(5.675496e-18), interval(4.055120e-22), interval(2.535031e-26)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.983527e+00,  2.535031e-26,  4.055120e-22,  5.675496e-18,  3.403960e-14,  8.505220e-11,  8.498203e-08,  3.182443e-05,  7.934217e-03},
{ 2.788480e+01,  6.250060e-24,  4.815569e-20,  3.113907e-16,  7.804805e-13,  5.922831e-10,  -8.638146e-08,  -1.592967e-04,  -5.553952e-02},
{ -5.565472e+01,  1.084307e-22,  4.324158e-19,  1.066131e-15,  -3.113873e-13,  -2.290234e-09,  -7.585393e-07,  2.874672e-04,  1.666186e-01},
{ 6.942507e+01,  3.937751e-22,  4.926975e-19,  -1.387214e-15,  -3.211359e-12,  1.621278e-09,  2.114047e-06,  -1.617405e-04,  -2.776976e-01},
{ -5.542561e+01,  3.930539e-22,  -4.946774e-19,  -1.377439e-15,  3.220668e-12,  1.594746e-09,  -2.117539e-06,  -1.556311e-04,  2.776976e-01},
{ 2.765569e+01,  1.078359e-22,  -4.308349e-19,  1.066597e-15,  2.979815e-13,  -2.279901e-09,  7.648232e-07,  2.838016e-04,  -1.666186e-01},
{ -7.885339e+00,  6.193030e-24,  -4.776169e-20,  3.092495e-16,  -7.767567e-13,  5.925624e-10,  8.289038e-08,  -1.580748e-04,  5.553952e-02},
{ 9.836354e-01,  2.502706e-26,  -4.005247e-22,  5.608999e-18,  -3.366722e-14,  8.421433e-11,  -8.428381e-08,  3.164988e-05,  -7.934217e-03}};

#endif /*BENCHMARK_H_*/