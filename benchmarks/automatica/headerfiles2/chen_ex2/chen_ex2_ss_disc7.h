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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.996700e-01),  interval(-2.730894e-04),  interval(-1.178344e-04),  interval(-5.795009e-05),  interval(-3.352741e-05),  interval(-2.287961e-05),  interval(-1.762407e-05),  interval(-5.858408e-06)},
{ interval(1.599736e-04),  interval(1.000000e+00),  interval(-9.427212e-09),  interval(-4.636245e-09),  interval(-2.682334e-09),  interval(-1.830467e-09),  interval(-1.410003e-09),  interval(-4.686984e-10)},
{ interval(1.279859e-08),  interval(1.600000e-04),  interval(1.000000e+00),  interval(-2.472727e-13),  interval(-1.430616e-13),  interval(-9.762755e-14),  interval(-7.520219e-14),  interval(-2.499794e-14)},
{ interval(3.413052e-13),  interval(6.400000e-09),  interval(8.000000e-05),  interval(1),  interval(-2.861277e-18),  interval(-1.952582e-18),  interval(-1.504068e-18),  interval(-4.999670e-19)},
{ interval(3.413108e-18),  interval(8.533333e-14),  interval(1.600000e-09),  interval(4.000000e-05),  interval(1),  interval(-1.562083e-23),  interval(-1.203268e-23),  interval(-3.999780e-24)},
{ interval(1.365258e-23),  interval(4.266667e-19),  interval(1.066667e-14),  interval(4.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-4.010915e-29),  interval(-1.333267e-29)},
{ interval(2.275443e-29),  interval(8.533333e-25),  interval(2.666667e-20),  interval(1.333333e-15),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1),  interval(-1.999890e-35)},
{ interval(3.413146e-35),  interval(1.422222e-30),  interval(5.333333e-26),  interval(3.333333e-21),  interval(3.333333e-16),  interval(5.000000e-11),  interval(1.000000e-05),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.599736e-04), interval(1.279859e-08), interval(6.826103e-13), interval(1.365243e-17), interval(1.092207e-22), interval(3.640709e-28), interval(5.461033e-34), interval(9.101521e-40)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.999670e+00,  9.101521e-40,  5.461033e-34,  3.640709e-28,  1.092207e-22,  1.365243e-17,  6.826103e-13,  1.279859e-08,  1.599736e-04},
{ 2.799769e+01,  1.592773e-37,  6.170799e-32,  2.002297e-26,  2.511919e-21,  9.555711e-17,  -6.828356e-13,  -6.399437e-08,  -1.119815e-03},
{ -5.599307e+01,  2.793165e-36,  5.575305e-31,  6.880113e-26,  -9.833103e-22,  -3.685958e-16,  -6.142479e-12,  1.151958e-07,  3.359446e-03},
{ 6.998845e+01,  1.015204e-35,  6.361148e-31,  -8.919334e-26,  -1.037452e-20,  2.594133e-16,  1.706357e-11,  -6.401408e-08,  -5.599076e-03},
{ -5.598845e+01,  1.015167e-35,  -6.361659e-31,  -8.918078e-26,  1.037512e-20,  2.593277e-16,  -1.706413e-11,  -6.396480e-08,  5.599076e-03},
{ 2.799307e+01,  2.792857e-36,  -5.574898e-31,  6.880177e-26,  9.824454e-22,  -3.685625e-16,  6.143493e-12,  1.151662e-07,  -3.359446e-03},
{ -7.997690e+00,  1.592480e-37,  -6.169778e-32,  2.002020e-26,  -2.511679e-21,  9.555802e-17,  6.822725e-13,  -6.398451e-08,  1.119815e-03},
{ 9.996701e-01,  9.099920e-40,  -5.459832e-34,  3.639868e-28,  -1.091966e-22,  1.364973e-17,  -6.824977e-13,  1.279718e-08,  -1.599736e-04}};

#endif /*BENCHMARK_H_*/