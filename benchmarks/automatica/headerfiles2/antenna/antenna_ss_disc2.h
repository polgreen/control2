#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.050  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 6 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-8.711057e-03),  interval(-4.556058e-01),  interval(-2.471989e-01),  interval(-9.678597e-02),  interval(0),  interval(0)},
{ interval(7.181799e-01),  interval(5.635886e-01),  interval(-2.589583e-01),  interval(-1.065001e-01),  interval(0),  interval(0)},
{ interval(3.951309e-01),  interval(6.739599e-01),  interval(9.224477e-01),  interval(-3.249211e-02),  interval(0),  interval(0)},
{ interval(6.027523e-02),  interval(1.468146e-01),  interval(3.917221e-01),  interval(9.964968e-01),  interval(0),  interval(0)},
{ interval(1.015423e-04),  interval(3.163666e-04),  interval(1.239210e-03),  interval(6.245404e-03),  interval(1),  interval(0)},
{ interval(6.660350e-08),  interval(2.513995e-07),  interval(1.296297e-06),  interval(9.763149e-06),  interval(3.125000e-03),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(5.610781e-03), interval(6.173921e-03), interval(1.883601e-03), interval(2.030846e-04), interval(2.664140e-07), interval(1.435085e-10)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -4.473822e+00,  1.435085e-10,  2.664140e-07,  2.030846e-04,  1.883601e-03,  6.173921e-03,  5.610781e-03},
{ 8.560338e+00,  6.684290e-09,  5.200001e-06,  1.276269e-03,  -3.180020e-04,  -2.062132e-02,  -2.844866e-02},
{ -9.060840e+00,  2.913199e-08,  5.644700e-06,  -1.856557e-03,  -9.349443e-03,  2.074407e-02,  5.762828e-02},
{ 5.615386e+00,  2.427916e-08,  -7.535666e-06,  -8.334653e-04,  1.112033e-02,  -2.434766e-04,  -5.830065e-02},
{ -1.920493e+00,  3.869829e-09,  -3.461563e-06,  1.116102e-03,  -2.338332e-03,  -1.012957e-02,  2.945723e-02},
{ 2.794310e-01,  5.772288e-11,  -1.138861e-07,  9.456652e-05,  -9.981562e-04,  4.076376e-03,  -5.946968e-03}};

#endif /*BENCHMARK_H_*/