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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.673243e-01),  interval(-2.695817e-02),  interval(-1.161492e-02),  interval(-5.707530e-03),  interval(-3.300569e-03),  interval(-2.251692e-03),  interval(-1.734091e-03),  interval(-5.763330e-04)},
{ interval(1.573773e-02),  interval(9.997834e-01),  interval(-9.337196e-05),  interval(-4.589515e-05),  interval(-2.654464e-05),  interval(-1.811092e-05),  interval(-1.394876e-05),  interval(-4.636191e-06)},
{ interval(1.265989e-04),  interval(1.599884e-02),  interval(9.999995e-01),  interval(-2.454017e-07),  interval(-1.419457e-07),  interval(-9.685178e-08),  interval(-7.459652e-08),  interval(-2.479456e-08)},
{ interval(3.385284e-07),  interval(6.399768e-05),  interval(7.999999e-03),  interval(1.000000e+00),  interval(-2.843412e-10),  interval(-1.940162e-10),  interval(-1.494371e-10),  interval(-4.967108e-11)},
{ interval(3.390879e-10),  interval(8.533148e-08),  interval(1.600000e-05),  interval(4.000000e-03),  interval(1.000000e+00),  interval(-1.553799e-13),  interval(-1.196800e-13),  interval(-3.978062e-14)},
{ interval(1.357845e-13),  interval(4.266605e-11),  interval(1.066667e-08),  interval(4.000000e-06),  interval(2.000000e-03),  interval(1),  interval(-3.992438e-17),  interval(-1.327063e-17)},
{ interval(2.264854e-17),  interval(8.533245e-15),  interval(2.666667e-12),  interval(1.333333e-09),  interval(1.000000e-06),  interval(1.000000e-03),  interval(1),  interval(-1.896922e-21)},
{ interval(3.237414e-21),  interval(1.422211e-18),  interval(5.333333e-16),  interval(3.333333e-13),  interval(3.333333e-10),  interval(5.000000e-07),  interval(1.000000e-03),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.573773e-02), interval(1.265989e-04), interval(6.770569e-07), interval(1.356352e-09), interval(1.086276e-12), interval(3.623767e-16), interval(5.179862e-20), interval(6.477795e-24)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.967107e+00,  6.477795e-24,  5.179862e-20,  3.623767e-16,  1.086276e-12,  1.356352e-09,  6.770569e-07,  1.265989e-04,  1.573773e-02},
{ 2.777018e+01,  1.594162e-21,  6.138457e-18,  1.983360e-14,  2.482946e-11,  9.396314e-09,  -6.993117e-07,  -6.343796e-04,  -1.101641e-01},
{ -5.531185e+01,  2.760606e-20,  5.499519e-17,  6.765667e-14,  -1.009605e-11,  -3.642455e-08,  -5.993318e-06,  1.147700e-03,  3.304924e-01},
{ 6.885525e+01,  1.000702e-19,  6.242125e-17,  -8.836252e-14,  -1.017704e-10,  2.593780e-08,  1.675927e-05,  -6.537690e-04,  -5.508207e-01},
{ -5.485741e+01,  9.970394e-20,  -6.292396e-17,  -8.712160e-14,  1.023613e-10,  2.509575e-08,  -1.681467e-05,  -6.052956e-04,  5.508207e-01},
{ 2.731574e+01,  2.730406e-20,  -5.459379e-17,  6.771577e-14,  9.245131e-12,  -3.609660e-08,  6.093036e-06,  1.118616e-03,  -3.304924e-01},
{ -7.772342e+00,  1.565202e-21,  -6.038422e-18,  1.956177e-14,  -2.459310e-11,  9.405179e-09,  6.439128e-07,  -6.246849e-04,  1.101641e-01},
{ 9.675386e-01,  6.313647e-24,  -5.053234e-20,  3.539348e-16,  -1.062639e-12,  1.329760e-09,  -6.659771e-07,  1.252140e-04,  -1.573774e-02}};

#endif /*BENCHMARK_H_*/