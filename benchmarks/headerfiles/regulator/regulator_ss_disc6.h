#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.010  
// No controller needed, safe and stable, completeness k with no controller =  1 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.980020e-01),  interval(4.982532e-03),  interval(3.807211e-05),  interval(1.035206e-05),  interval(1.940302e-06)},
{ interval(0),  interval(9.950125e-01),  interval(1.487199e-02),  interval(6.012859e-03),  interval(1.514779e-03)},
{ interval(0),  interval(0),  interval(8.669274e-01),  interval(7.046022e-01),  interval(2.728587e-01)},
{ interval(0),  interval(0),  interval(0),  interval(7.788008e-01),  interval(6.301832e-01)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.048374e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.183613e-07), interval(1.164654e-04), interval(2.843851e-02), interval(1.002434e-01), interval(2.854877e-01)};
const __plant_typet __char_poly_const[6][6] = 
 {{ -1,  0,  0,  0,  0,  0},
{ 4.543580e+00,  -1.183613e-07,  -1.164654e-04,  -2.843851e-02,  -1.002434e-01,  -2.854877e-01},
{ -8.240619e+00,  -2.835006e-06,  -1.044852e-03,  -4.397104e-02,  1.974848e-01,  1.038816e+00},
{ 7.457129e+00,  -6.624801e-06,  1.077006e-04,  1.501277e-01,  -1.762191e-02,  -1.412636e+00},
{ -3.366743e+00,  -2.399990e-06,  9.625705e-04,  -5.564693e-02,  -1.564150e-01,  8.507134e-01},
{ 6.066520e-01,  -8.482145e-08,  8.622152e-05,  -2.207278e-02,  7.679530e-02,  -1.914064e-01}};

#endif /*BENCHMARK_H_*/