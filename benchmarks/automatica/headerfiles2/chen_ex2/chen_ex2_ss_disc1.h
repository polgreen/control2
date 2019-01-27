#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.100  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-2.738458e-01),  interval(-6.442057e-01),  interval(-2.076715e-01),  interval(-8.512254e-02),  interval(-4.384109e-02),  interval(-2.769801e-02),  interval(-2.011897e-02),  interval(-6.388891e-03)},
{ interval(1.744593e-01),  interval(8.597649e-02),  interval(-3.463982e-01),  interval(-1.583393e-01),  interval(-8.770304e-02),  interval(-5.822401e-02),  interval(-4.394765e-02),  interval(-1.438490e-02)},
{ interval(3.928038e-01),  interval(9.846171e-01),  interval(7.565048e-01),  interval(-1.141398e-01),  interval(-6.419447e-02),  interval(-4.303548e-02),  interval(-3.271947e-02),  interval(-1.076901e-02)},
{ interval(1.470329e-01),  interval(4.996573e-01),  interval(7.432983e-01),  interval(9.731055e-01),  interval(-1.523257e-02),  interval(-1.025722e-02),  interval(-7.824016e-03),  interval(-2.581530e-03)},
{ interval(1.762324e-02),  interval(7.310616e-02),  interval(1.549977e-01),  interval(3.976107e-01),  interval(9.986412e-01),  interval(-9.173770e-04),  interval(-7.010949e-04),  interval(-2.316607e-04)},
{ interval(7.907351e-04),  interval(3.833796e-03),  interval(1.048808e-02),  interval(3.991430e-02),  interval(1.999511e-01),  interval(9.999669e-01),  interval(-2.529116e-05),  interval(-8.364893e-06)},
{ interval(1.427608e-05),  interval(7.886537e-05),  interval(2.639820e-04),  interval(1.332041e-03),  interval(9.999261e-03),  interval(9.999950e-02),  interval(9.999996e-01),  interval(-1.267755e-07)},
{ interval(2.163635e-07),  interval(1.338505e-06),  interval(5.298425e-06),  interval(3.331648e-05),  interval(3.333237e-04),  interval(4.999993e-03),  interval(9.999999e-02),  interval(1.000000e+00)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.744593e-01), interval(3.928038e-01), interval(2.940658e-01), interval(7.049297e-02), interval(6.325881e-03), interval(2.284174e-04), interval(3.461816e-06), interval(4.529081e-08)};
const __plant_typet __char_poly_const[9][9] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0},
{ -5.540349e+00,  4.529081e-08,  3.461816e-06,  2.284174e-04,  6.325881e-03,  7.049297e-02,  2.940658e-01,  3.928038e-01,  1.744593e-01},
{ 1.328433e+01,  7.861377e-06,  2.753747e-04,  7.769509e-03,  7.666871e-02,  1.184399e-01,  -9.599375e-01,  -2.225656e+00,  -1.334740e+00},
{ -1.798786e+01,  9.599550e-05,  1.574719e-03,  1.120502e-02,  -1.273345e-01,  -9.713792e-01,  4.457765e-01,  5.100501e+00,  4.302556e+00},
{ 1.502925e+01,  2.439910e-04,  6.471294e-04,  -2.950493e-02,  -1.093953e-01,  1.301005e+00,  1.878232e+00,  -5.866718e+00,  -7.606807e+00},
{ -7.925934e+00,  1.691943e-04,  -1.687657e-03,  -4.823743e-03,  2.313187e-01,  -3.262774e-01,  -3.064201e+00,  3.226732e+00,  7.989257e+00},
{ 2.573539e+00,  3.199665e-05,  -7.594262e-04,  1.314577e-02,  -4.711357e-02,  -3.703578e-01,  1.689129e+00,  -3.489521e-01,  -4.995111e+00},
{ -4.698435e-01,  1.258179e-06,  -5.330972e-05,  1.958317e-03,  -2.976878e-02,  1.683327e-01,  -2.263024e-01,  -4.136191e-01,  1.724123e+00},
{ 3.688317e-02,  3.478509e-09,  -2.914073e-07,  2.163325e-05,  -7.011698e-04,  9.743579e-03,  -5.676305e-02,  1.349077e-01,  -2.537372e-01}};

#endif /*BENCHMARK_H_*/