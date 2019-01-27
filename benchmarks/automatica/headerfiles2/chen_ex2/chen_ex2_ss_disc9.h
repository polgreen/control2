#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999670e-01),  interval(-2.731214e-05),  interval(-1.178498e-05),  interval(-5.795810e-06),  interval(-3.353218e-06),  interval(-2.288293e-06),  interval(-1.762667e-06),  interval(-5.859278e-07)},
{ interval(1.599974e-05),  interval(1.000000e+00),  interval(-9.428034e-11),  interval(-4.636671e-11),  interval(-2.682589e-11),  interval(-1.830644e-11),  interval(-1.410141e-11),  interval(-4.687448e-12)},
{ interval(1.279986e-10),  interval(1.600000e-05),  interval(1.000000e+00),  interval(-2.472898e-16),  interval(-1.430718e-16),  interval(-9.763463e-17),  interval(-7.520772e-17),  interval(-2.499979e-17)},
{ interval(3.413305e-16),  interval(6.400000e-11),  interval(8.000000e-06),  interval(1),  interval(-2.861440e-22),  interval(-1.952696e-22),  interval(-1.504157e-22),  interval(-4.999967e-23)},
{ interval(3.413311e-22),  interval(8.533333e-17),  interval(1.600000e-11),  interval(4.000000e-06),  interval(1),  interval(-1.562158e-28),  interval(-1.203327e-28),  interval(-3.999978e-29)},
{ interval(1.365326e-28),  interval(4.266667e-23),  interval(1.066667e-17),  interval(4.000000e-12),  interval(2.000000e-06),  interval(1),  interval(-4.011091e-35),  interval(-1.333327e-35)},
{ interval(2.275544e-35),  interval(8.533333e-30),  interval(2.666667e-24),  interval(1.333333e-18),  interval(1.000000e-12),  interval(1.000000e-06),  interval(1),  interval(-1.999989e-42)},
{ interval(3.413315e-42),  interval(1.422222e-36),  interval(5.333333e-31),  interval(3.333333e-25),  interval(3.333333e-19),  interval(5.000000e-13),  interval(1.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599974e-05), interval(1.279986e-10), interval(6.826610e-16), interval(1.365324e-21), interval(1.092261e-27), interval(3.640871e-34), interval(5.461303e-41), interval(9.102152e-48)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.999967e+00,  9.102152e-48,  5.461303e-41,  3.640871e-34,  1.092261e-27,  1.365324e-21,  6.826610e-16,  1.279986e-10,  1.599974e-05},
{ 2.799977e+01,  1.592877e-45,  6.171256e-39,  2.002470e-32,  2.512184e-26,  9.557171e-21,  -6.826836e-16,  -6.399944e-10,  -1.119982e-04},
{ -5.599931e+01,  2.793441e-44,  5.575950e-38,  6.881163e-32,  -9.830670e-27,  -3.686356e-20,  -6.143848e-15,  1.151996e-09,  3.359945e-04},
{ 6.999885e+01,  1.015338e-43,  6.362323e-38,  -8.920093e-32,  -1.037633e-25,  2.594133e-20,  1.706636e-14,  -6.400141e-10,  -5.599908e-04},
{ -5.599885e+01,  1.015334e-43,  -6.362374e-38,  -8.919968e-32,  1.037639e-25,  2.594048e-20,  -1.706641e-14,  -6.399648e-10,  5.599908e-04},
{ 2.799931e+01,  2.793411e-44,  -5.575909e-38,  6.881170e-32,  9.829805e-27,  -3.686323e-20,  6.143949e-15,  1.151966e-09,  -3.359945e-04},
{ -7.999769e+00,  1.592848e-45,  -6.171154e-39,  2.002442e-32,  -2.512160e-26,  9.557180e-21,  6.826272e-16,  -6.399845e-10,  1.119982e-04},
{ 9.999670e-01,  9.101992e-48,  -5.461183e-41,  3.640787e-34,  -1.092237e-27,  1.365297e-21,  -6.826498e-16,  1.279972e-10,  -1.599974e-05}};

#endif /*BENCHMARK_H_*/