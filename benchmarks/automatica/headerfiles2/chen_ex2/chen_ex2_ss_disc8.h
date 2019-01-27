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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.998350e-01),  interval(-1.365536e-04),  interval(-5.892150e-05),  interval(-2.897727e-05),  interval(-1.676503e-05),  interval(-1.144073e-05),  interval(-8.812757e-06),  interval(-2.929446e-06)},
{ interval(7.999340e-05),  interval(1.000000e+00),  interval(-2.356917e-09),  interval(-1.159120e-09),  interval(-6.706189e-10),  interval(-4.576414e-10),  interval(-3.525199e-10),  interval(-1.171811e-10)},
{ interval(3.199824e-09),  interval(8.000000e-05),  interval(1.000000e+00),  interval(-3.091027e-14),  interval(-1.788341e-14),  interval(-1.220394e-14),  interval(-9.400658e-15),  interval(-3.124871e-15)},
{ interval(4.266491e-14),  interval(1.600000e-09),  interval(4.000000e-05),  interval(1),  interval(-1.788355e-19),  interval(-1.220403e-19),  interval(-9.400735e-20),  interval(-3.124897e-20)},
{ interval(2.133263e-19),  interval(1.066667e-14),  interval(4.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-4.881640e-25),  interval(-3.760314e-25),  interval(-1.249966e-25)},
{ interval(4.266549e-25),  interval(2.666667e-20),  interval(1.333333e-15),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1),  interval(-6.267208e-31),  interval(-2.083282e-31)},
{ interval(3.555468e-31),  interval(2.666667e-26),  interval(1.666667e-21),  interval(1.666667e-16),  interval(2.500000e-11),  interval(5.000000e-06),  interval(1),  interval(-1.562457e-37)},
{ interval(2.666593e-37),  interval(2.222222e-32),  interval(1.666667e-27),  interval(2.083333e-22),  interval(4.166667e-17),  interval(1.250000e-11),  interval(5.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(7.999340e-05), interval(3.199824e-09), interval(8.532981e-14), interval(8.533052e-19), interval(3.413239e-24), interval(5.688748e-30), interval(4.266549e-36), interval(3.555419e-42)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.999835e+00,  3.555419e-42,  4.266549e-36,  5.688748e-30,  3.413239e-24,  8.533052e-19,  8.532981e-14,  3.199824e-09,  7.999340e-05},
{ 2.799885e+01,  6.221995e-40,  4.821135e-34,  3.128739e-28,  7.850207e-23,  5.972826e-18,  -8.534389e-14,  -1.599930e-08,  -5.599538e-04},
{ -5.599654e+01,  1.091140e-38,  4.355987e-33,  1.075109e-27,  -3.072422e-23,  -2.303862e-17,  -7.679050e-13,  2.879947e-08,  1.679861e-03},
{ 6.999423e+01,  3.965931e-38,  4.970157e-33,  -1.393712e-27,  -3.242352e-22,  1.621333e-17,  2.133140e-12,  -1.600176e-08,  -2.799769e-03},
{ -5.599423e+01,  3.965859e-38,  -4.970356e-33,  -1.393614e-27,  3.242446e-22,  1.621066e-17,  -2.133175e-12,  -1.599560e-08,  2.799769e-03},
{ 2.799654e+01,  1.091080e-38,  -4.355828e-33,  1.075114e-27,  3.071071e-23,  -2.303758e-17,  7.679683e-13,  2.879578e-08,  -1.679861e-03},
{ -7.998845e+00,  6.221423e-40,  -4.820736e-34,  3.128522e-28,  -7.849831e-23,  5.972855e-18,  8.530870e-14,  -1.599806e-08,  5.599538e-04},
{ 9.998350e-01,  3.555106e-42,  -4.266080e-36,  5.688091e-30,  -3.412864e-24,  8.532207e-19,  -8.532277e-14,  3.199648e-09,  -7.999340e-05}};

#endif /*BENCHMARK_H_*/