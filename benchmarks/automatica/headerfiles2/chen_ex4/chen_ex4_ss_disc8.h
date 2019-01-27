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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999550e-01),  interval(-4.124953e-05),  interval(-2.296843e-05),  interval(-2.009733e-05),  interval(-1.240700e-05),  interval(-1.143533e-05),  interval(-7.148292e-06),  interval(-6.016716e-06),  interval(-4.150297e-06)},
{ interval(3.999910e-05),  interval(1.000000e+00),  interval(-4.593708e-10),  interval(-4.019487e-10),  interval(-2.481416e-10),  interval(-2.287080e-10),  interval(-1.429668e-10),  interval(-1.203352e-10),  interval(-8.300657e-11)},
{ interval(7.999880e-10),  interval(4.000000e-05),  interval(1.000000e+00),  interval(-5.359331e-15),  interval(-3.308564e-15),  interval(-3.049450e-15),  interval(-1.906231e-15),  interval(-1.604475e-15),  interval(-1.106758e-15)},
{ interval(5.333273e-15),  interval(4.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-1.654285e-20),  interval(-1.524728e-20),  interval(-9.531172e-21),  interval(-8.022392e-21),  interval(-5.533804e-21)},
{ interval(2.666643e-20),  interval(2.666667e-15),  interval(2.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-6.098919e-26),  interval(-3.812474e-26),  interval(-3.208961e-26),  interval(-2.213525e-26)},
{ interval(5.333293e-26),  interval(6.666667e-21),  interval(6.666667e-16),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1),  interval(-6.354128e-32),  interval(-5.348273e-32),  interval(-3.689211e-32)},
{ interval(8.888829e-32),  interval(1.333333e-26),  interval(1.666667e-21),  interval(3.333333e-16),  interval(5.000000e-11),  interval(1.000000e-05),  interval(1),  interval(-8.022403e-38),  interval(-5.533813e-38)},
{ interval(6.666617e-38),  interval(1.111111e-32),  interval(1.666667e-27),  interval(4.166667e-22),  interval(8.333333e-17),  interval(2.500000e-11),  interval(5.000000e-06),  interval(1),  interval(-4.611497e-44)},
{ interval(2.777749e-44),  interval(4.166667e-39),  interval(6.944444e-34),  interval(2.083333e-28),  interval(5.208333e-23),  interval(2.083333e-17),  interval(6.250000e-12),  interval(2.500000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.999888e-06), interval(9.999850e-11), interval(1.333318e-15), interval(6.666607e-21), interval(2.666647e-26), interval(4.444414e-32), interval(6.666617e-38), interval(5.555497e-44), interval(3.240699e-50)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.999955e+00,  3.240699e-50,  5.555497e-44,  6.666617e-38,  4.444414e-32,  2.666647e-26,  6.666607e-21,  1.333318e-15,  9.999850e-11,  4.999888e-06},
{ 3.599964e+01,  5.481431e-48,  9.666571e-42,  7.466583e-36,  2.399968e-30,  5.866571e-25,  3.999898e-20,  -2.666697e-15,  -5.999925e-10,  -3.999910e-05},
{ -8.399874e+01,  1.609052e-46,  1.607753e-40,  6.053223e-35,  5.955393e-30,  -8.533325e-25,  -2.266626e-19,  -1.066622e-14,  1.399989e-09,  1.399969e-04},
{ 1.259975e+02,  9.731677e-46,  4.492124e-40,  9.599020e-36,  -1.928855e-29,  -2.293257e-24,  3.066637e-19,  4.533210e-14,  -1.400010e-09,  -2.799937e-04},
{ -1.259969e+02,  1.720748e-45,  -3.086597e-45,  -1.553298e-34,  2.089953e-34,  5.066553e-24,  -5.699872e-24,  -6.666517e-14,  5.249882e-14,  3.499921e-04},
{ 8.399748e+01,  9.731589e-46,  -4.492119e-40,  9.600548e-36,  1.928836e-29,  -2.293306e-24,  -3.066558e-19,  4.533252e-14,  1.399927e-09,  -2.799937e-04},
{ -3.599874e+01,  1.609023e-46,  -1.607730e-40,  6.053172e-35,  -5.955450e-30,  -8.532957e-25,  2.266605e-19,  -1.066664e-14,  -1.399948e-09,  1.399969e-04},
{ 8.999640e+00,  5.481285e-48,  -9.666328e-42,  7.466415e-36,  -2.399924e-30,  5.866499e-25,  -3.999922e-20,  -2.666517e-15,  5.999805e-10,  -3.999910e-05},
{ -9.999550e-01,  3.240637e-50,  -5.555364e-44,  6.666417e-38,  -4.444274e-32,  2.666567e-26,  -6.666427e-21,  1.333288e-15,  -9.999700e-11,  4.999888e-06}};

#endif /*BENCHMARK_H_*/