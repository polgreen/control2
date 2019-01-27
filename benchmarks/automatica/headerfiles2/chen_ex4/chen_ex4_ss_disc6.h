#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.995500e-01),  interval(-4.124531e-04),  interval(-2.296559e-04),  interval(-2.009437e-04),  interval(-1.240501e-04),  interval(-1.143333e-04),  interval(-7.146980e-05),  interval(-6.015544e-05),  interval(-4.149457e-05)},
{ interval(3.999100e-04),  interval(9.999999e-01),  interval(-4.593329e-08),  interval(-4.019094e-08),  interval(-2.481149e-08),  interval(-2.286814e-08),  interval(-1.429493e-08),  interval(-1.203196e-08),  interval(-8.299536e-09)},
{ interval(7.998800e-08),  interval(4.000000e-04),  interval(1.000000e+00),  interval(-5.358937e-12),  interval(-3.308298e-12),  interval(-3.049184e-12),  interval(-1.906056e-12),  interval(-1.604319e-12),  interval(-1.106646e-12)},
{ interval(5.332733e-12),  interval(4.000000e-08),  interval(2.000000e-04),  interval(1.000000e+00),  interval(-1.654178e-16),  interval(-1.524621e-16),  interval(-9.530472e-17),  interval(-8.021767e-17),  interval(-5.533356e-17)},
{ interval(2.666427e-16),  interval(2.666667e-12),  interval(2.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-6.098564e-21),  interval(-3.812241e-21),  interval(-3.208753e-21),  interval(-2.213376e-21)},
{ interval(5.332933e-21),  interval(6.666667e-17),  interval(6.666667e-13),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1),  interval(-6.353778e-26),  interval(-5.347960e-26),  interval(-3.688987e-26)},
{ interval(8.888289e-26),  interval(1.333333e-21),  interval(1.666667e-17),  interval(3.333333e-13),  interval(5.000000e-09),  interval(1.000000e-04),  interval(1),  interval(-8.021882e-31),  interval(-5.533439e-31)},
{ interval(6.666167e-31),  interval(1.111111e-26),  interval(1.666667e-22),  interval(4.166667e-18),  interval(8.333333e-14),  interval(2.500000e-09),  interval(5.000000e-05),  interval(1),  interval(-4.611061e-36)},
{ interval(2.777486e-36),  interval(4.166667e-32),  interval(6.944444e-28),  interval(2.083333e-23),  interval(5.208333e-19),  interval(2.083333e-14),  interval(6.250000e-10),  interval(2.500000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.998875e-05), interval(9.998500e-09), interval(1.333183e-12), interval(6.666067e-17), interval(2.666467e-21), interval(4.444144e-26), interval(6.666167e-31), interval(5.554972e-36), interval(3.240324e-41)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.999550e+00,  3.240324e-41,  5.554972e-36,  6.666167e-31,  4.444144e-26,  2.666467e-21,  6.666067e-17,  1.333183e-12,  9.998500e-09,  4.998875e-05},
{ 3.599640e+01,  5.480979e-39,  9.665705e-34,  7.465827e-29,  2.399684e-24,  5.865707e-20,  3.998980e-16,  -2.666967e-12,  -5.999250e-08,  -3.999100e-04},
{ -8.398740e+01,  1.608857e-37,  1.607532e-32,  6.052225e-28,  5.953932e-24,  -8.533253e-20,  -2.266265e-15,  -1.066217e-11,  1.399895e-07,  1.399685e-03},
{ 1.259748e+02,  9.730099e-37,  4.491238e-32,  9.590202e-29,  -1.928554e-23,  -2.292573e-19,  3.066373e-15,  4.532103e-11,  -1.400105e-07,  -2.799370e-03},
{ -1.259685e+02,  1.720400e-36,  -3.085972e-36,  -1.552984e-27,  2.089530e-27,  5.065527e-19,  -5.698718e-19,  -6.665167e-11,  5.248819e-11,  3.499213e-03},
{ 8.397480e+01,  9.729225e-37,  -4.491185e-32,  9.605478e-29,  1.928356e-23,  -2.293061e-19,  -3.065581e-15,  4.532523e-11,  1.399265e-07,  -2.799370e-03},
{ -3.598740e+01,  1.608567e-37,  -1.607300e-32,  6.051718e-28,  -5.954500e-24,  -8.529574e-20,  2.266049e-15,  -1.066637e-11,  -1.399475e-07,  1.399685e-03},
{ 8.996401e+00,  5.479517e-39,  -9.663279e-34,  7.464147e-29,  -2.399236e-24,  5.864987e-20,  -3.999220e-16,  -2.665167e-12,  5.998050e-08,  -3.999100e-04},
{ -9.995501e-01,  3.239699e-41,  -5.553639e-36,  6.664167e-31,  -4.442745e-26,  2.665667e-21,  -6.664267e-17,  1.332883e-12,  -9.997000e-09,  4.998875e-05}};

#endif /*BENCHMARK_H_*/