#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 5 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999800e-01),  interval(4.999825e-05),  interval(3.998003e-09),  interval(1.141658e-11),  interval(2.140609e-14)},
{ interval(0),  interval(9.999500e-01),  interval(1.598818e-04),  interval(6.847715e-07),  interval(1.712068e-09)},
{ interval(0),  interval(0),  interval(9.985730e-01),  interval(8.554183e-03),  interval(3.208850e-05)},
{ interval(0),  interval(0),  interval(0),  interval(9.975031e-01),  interval(7.486887e-03)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.990005e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.284580e-17), interval(1.284371e-12), interval(3.210168e-08), interval(1.123688e-05), interval(2.998500e-03)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.995007e+00,  2.998500e-03,  1.123688e-05,  3.210168e-08,  1.284371e-12,  1.284580e-17},
{ 9.980034e+00,  -1.198203e-02,  -2.247005e-05,  6.404752e-08,  1.282968e-11,  3.337126e-16},
{ -9.970063e+00,  1.795509e-02,  2.246630e-08,  -1.923662e-07,  -1.376265e-14,  8.464114e-16},
{ 4.980050e+00,  -1.195810e-02,  2.241768e-05,  6.419654e-08,  -1.281915e-11,  3.331571e-16},
{ -9.950145e-01,  2.986536e-03,  -1.120698e-05,  3.202044e-08,  -1.280515e-12,  1.280307e-17}};

#endif /*BENCHMARK_H_*/