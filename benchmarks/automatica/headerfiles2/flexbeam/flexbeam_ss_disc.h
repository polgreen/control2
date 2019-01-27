#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(-3.912489e-01),  interval(9.666474e-01),  interval(1.233748e-01),  interval(4.853548e-01),  interval(6.489433e-04),  interval(0)},
{ interval(-6.555047e-01),  interval(-4.320541e-01),  interval(-4.377886e-01),  interval(1.841438e-01),  interval(2.462635e-04),  interval(0)},
{ interval(-1.243767e-01),  interval(-3.354948e-01),  interval(-8.819479e-01),  interval(-4.496676e-01),  interval(-6.010301e-04),  interval(0)},
{ interval(3.035536e-01),  interval(-4.329214e-02),  interval(7.625154e-01),  interval(-8.529562e-01),  interval(-2.477184e-03),  interval(0)},
{ interval(7.819472e-02),  interval(1.435367e-02),  interval(2.801392e-01),  interval(5.512542e-02),  interval(9.997395e-01),  interval(0)},
{ interval(4.112065e-03),  interval(1.477769e-03),  interval(1.532266e-02),  interval(9.147085e-03),  interval(1.249913e-01),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(-6.555047e-01), interval(-2.487534e-01), interval(6.071071e-01), interval(2.502231e+00), interval(2.631721e-01), interval(8.748429e-03)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ 5.584676e-01,  8.748429e-03,  2.631721e-01,  2.502231e+00,  6.071071e-01,  -2.487534e-01,  -6.555047e-01},
{ -1.060472e+00,  7.565592e-02,  6.632602e-01,  -4.628136e-01,  -1.156733e+00,  5.932912e-01,  9.394730e-01},
{ -1.633580e+00,  1.320625e-01,  1.164195e-01,  -2.882960e+00,  2.681768e-01,  -1.870234e-01,  5.341699e-01},
{ -1.744956e-01,  1.119814e-01,  -3.582362e-01,  -1.254109e+00,  6.433488e-02,  -5.112435e-01,  -6.850567e-01},
{ 7.023347e-01,  5.162025e-02,  -5.160819e-01,  4.971968e-01,  6.581945e-01,  4.541594e-01,  -7.127648e-01},
{ 6.077449e-01,  5.632207e-03,  -1.685338e-01,  1.600455e+00,  -4.410807e-01,  -1.004303e-01,  5.796833e-01}};

#endif /*BENCHMARK_H_*/