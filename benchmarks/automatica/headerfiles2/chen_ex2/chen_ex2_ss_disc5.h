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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.967033e-01),  interval(-2.727688e-03),  interval(-1.176804e-03),  interval(-5.787011e-04),  interval(-3.347971e-04),  interval(-2.284645e-04),  interval(-1.759818e-04),  interval(-5.849713e-05)},
{ interval(1.597362e-03),  interval(9.999978e-01),  interval(-9.418995e-07),  interval(-4.631978e-07),  interval(-2.679790e-07),  interval(-1.828698e-07),  interval(-1.408621e-07),  interval(-4.682346e-08)},
{ interval(1.278593e-06),  interval(1.599999e-03),  interval(1.000000e+00),  interval(-2.471020e-10),  interval(-1.429598e-10),  interval(-9.755678e-11),  interval(-7.514694e-11),  interval(-2.497938e-11)},
{ interval(3.410518e-10),  interval(6.399998e-07),  interval(8.000000e-04),  interval(1.000000e+00),  interval(-2.859648e-14),  interval(-1.951450e-14),  interval(-1.503184e-14),  interval(-4.996701e-15)},
{ interval(3.411081e-14),  interval(8.533331e-11),  interval(1.600000e-07),  interval(4.000000e-04),  interval(1),  interval(-1.561328e-18),  interval(-1.202678e-18),  interval(-3.997801e-19)},
{ interval(1.364583e-18),  interval(4.266666e-15),  interval(1.066667e-11),  interval(4.000000e-08),  interval(2.000000e-04),  interval(1),  interval(-4.009146e-23),  interval(-1.332674e-23)},
{ interval(2.274430e-23),  interval(8.533332e-20),  interval(2.666667e-16),  interval(1.333333e-12),  interval(1.000000e-08),  interval(1.000000e-04),  interval(1),  interval(-1.998901e-28)},
{ interval(3.411457e-28),  interval(1.422222e-24),  interval(5.333333e-21),  interval(3.333333e-17),  interval(3.333333e-13),  interval(5.000000e-09),  interval(1.000000e-04),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.597362e-03), interval(1.278593e-06), interval(6.821037e-10), interval(1.364433e-13), interval(1.091666e-17), interval(3.639087e-22), interval(5.458331e-27), interval(9.095217e-32)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -7.996701e+00,  9.095217e-32,  5.458331e-27,  3.639087e-22,  1.091666e-17,  1.364433e-13,  6.821037e-10,  1.278593e-06,  1.597362e-03},
{ 2.797691e+01,  1.591727e-29,  6.166233e-25,  2.000573e-20,  2.509271e-16,  9.541125e-13,  -6.843537e-10,  -6.394369e-06,  -1.118153e-02},
{ -5.593075e+01,  2.790403e-28,  5.568862e-24,  6.869617e-20,  -9.857386e-17,  -3.681987e-12,  -6.128807e-09,  1.151577e-05,  3.354460e-02},
{ 6.988460e+01,  1.013864e-27,  6.349415e-24,  -8.911739e-20,  -1.035643e-15,  2.594130e-12,  1.703571e-08,  -6.414049e-06,  -5.590766e-02},
{ -5.588462e+01,  1.013494e-27,  -6.354513e-24,  -8.899204e-20,  1.036242e-15,  2.585583e-12,  -1.704134e-08,  -6.364850e-06,  5.590766e-02},
{ 2.793079e+01,  2.787331e-28,  -5.564796e-24,  6.870253e-20,  9.771021e-17,  -3.678658e-12,  6.138928e-09,  1.148625e-05,  -3.354460e-02},
{ -7.976934e+00,  1.588800e-29,  -6.156037e-25,  1.997803e-20,  -2.506872e-16,  9.542025e-13,  6.787310e-10,  -6.384529e-06,  1.118153e-02},
{ 9.967054e-01,  9.079224e-32,  -5.446336e-27,  3.630691e-22,  -1.089267e-17,  1.361734e-13,  -6.809791e-10,  1.277187e-06,  -1.597362e-03}};

#endif /*BENCHMARK_H_*/