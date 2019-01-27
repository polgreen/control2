#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.998500e-01),  interval(-7.749616e-05),  interval(-4.921590e-05),  interval(-4.187231e-05),  interval(-2.245940e-05),  interval(-1.429584e-05),  interval(-7.030723e-06)},
{ interval(1.599880e-04),  interval(1.000000e+00),  interval(-3.937348e-09),  interval(-3.349856e-09),  interval(-1.796793e-09),  interval(-1.143695e-09),  interval(-5.624719e-10)},
{ interval(6.399680e-09),  interval(8.000000e-05),  interval(1.000000e+00),  interval(-8.933046e-14),  interval(-4.791502e-14),  interval(-3.049889e-14),  interval(-1.499944e-14)},
{ interval(8.533013e-14),  interval(1.600000e-09),  interval(4.000000e-05),  interval(1),  interval(-4.791535e-19),  interval(-3.049912e-19),  interval(-1.499955e-19)},
{ interval(8.533077e-19),  interval(2.133333e-14),  interval(8.000000e-10),  interval(4.000000e-05),  interval(1),  interval(-2.439941e-24),  interval(-1.199970e-24)},
{ interval(3.413248e-24),  interval(1.066667e-19),  interval(5.333333e-15),  interval(4.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-3.999910e-30)},
{ interval(5.688761e-30),  interval(2.133333e-25),  interval(1.333333e-20),  interval(1.333333e-15),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.999850e-05), interval(1.599920e-09), interval(4.266507e-14), interval(4.266539e-19), interval(3.413248e-24), interval(1.137752e-29), interval(1.706624e-35)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -6.999850e+00,  1.706624e-35,  1.137752e-29,  3.413248e-24,  4.266539e-19,  4.266507e-14,  1.599920e-09,  1.999850e-05},
{ 2.099910e+01,  1.945527e-33,  6.371281e-28,  8.191573e-23,  3.413090e-18,  -6.399674e-18,  -6.399760e-09,  -1.199910e-04},
{ -3.499775e+01,  1.936958e-32,  2.787362e-27,  5.119189e-23,  -8.106283e-18,  -3.839632e-13,  8.000000e-09,  2.999775e-04},
{ 3.499700e+01,  3.925039e-32,  -7.338116e-32,  -2.730462e-22,  3.839712e-22,  6.826155e-13,  -7.999400e-13,  -3.999700e-04},
{ -2.099775e+01,  1.936885e-32,  -2.787331e-27,  5.120043e-23,  8.105835e-18,  -3.839792e-13,  -7.998800e-09,  2.999775e-04},
{ 6.999100e+00,  1.945381e-33,  -6.370875e-28,  8.191198e-23,  -3.413065e-18,  6.399366e-18,  6.399280e-09,  -1.199910e-04},
{ -9.998500e-01,  1.706453e-35,  -1.137633e-29,  3.412907e-24,  -4.266155e-19,  4.266187e-14,  -1.599840e-09,  1.999850e-05}};

#endif /*BENCHMARK_H_*/