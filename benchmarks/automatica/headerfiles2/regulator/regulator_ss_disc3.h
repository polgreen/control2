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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.998000e-01),  interval(4.998250e-04),  interval(3.980098e-07),  interval(1.131447e-08),  interval(2.121453e-10)},
{ interval(0),  interval(9.995001e-01),  interval(1.588232e-03),  interval(6.766564e-05),  interval(1.693012e-06)},
{ interval(0),  interval(0),  interval(9.858215e-01),  interval(8.404348e-02),  interval(3.161775e-03)},
{ interval(0),  interval(0),  interval(0),  interval(9.753099e-01),  interval(7.369961e-02)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(9.900498e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(1.274993e-12), interval(1.272923e-08), interval(3.174795e-05), interval(1.111966e-03), interval(2.985050e-02)};
const __plant_typet __char_poly_const[6][6] = 
 {{ 1,  0,  0,  0,  0,  0},
{ -4.950481e+00,  2.985050e-02,  1.111966e-03,  3.174795e-05,  1.272923e-08,  1.274993e-12},
{ 9.802697e+00,  -1.182209e-01,  -2.220285e-03,  6.196420e-05,  1.259093e-07,  3.287524e-11},
{ -9.705197e+00,  1.755708e-01,  2.196763e-05,  -1.880870e-04,  -1.345686e-09,  8.276068e-11},
{ 4.804231e+00,  -1.158811e-01,  2.169079e-03,  6.342130e-05,  -1.248805e-07,  3.233207e-11},
{ -9.512484e-01,  2.868062e-02,  -1.082727e-03,  3.095357e-05,  -1.235218e-08,  1.233210e-12}};

#endif /*BENCHMARK_H_*/