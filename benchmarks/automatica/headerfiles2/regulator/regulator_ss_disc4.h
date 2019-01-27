#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.001  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999000e-01),  interval(2.499563e-04),  interval(9.975078e-08),  interval(1.421383e-09),  interval(1.332544e-11)},
{ interval(0),  interval(9.997500e-01),  interval(7.970510e-04),  interval(1.702878e-05),  interval(2.129462e-07)},
{ interval(0),  interval(0),  interval(9.928854e-01),  interval(4.243627e-02),  interval(7.969596e-04)},
{ interval(0),  interval(0),  interval(0),  interval(9.875778e-01),  interval(3.717339e-02)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.950125e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(4.000966e-14), interval(7.995427e-10), interval(3.992992e-06), interval(2.796151e-04), interval(1.496256e-02)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.975126e+00,  1.496256e-02,  2.796151e-04,  3.992992e-06,  7.995427e-10,  4.000966e-14},
{ 9.900697e+00,  -5.955269e-02,  -5.587693e-04,  7.889328e-06,  7.951860e-09,  1.035930e-12},
{ -9.851337e+00,  8.888413e-02,  2.780386e-06,  -2.380658e-05,  -4.258074e-11,  2.618743e-12},
{ 4.901085e+00,  -5.896043e-02,  5.522882e-04,  7.981539e-06,  -7.919305e-09,  1.027337e-12},
{ -9.753197e-01,  1.466643e-02,  -2.759144e-04,  3.942720e-06,  -7.876122e-10,  3.934862e-14}};

#endif /*BENCHMARK_H_*/