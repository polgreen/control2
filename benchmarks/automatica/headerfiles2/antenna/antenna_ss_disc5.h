#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.974509e-01),  interval(-1.452058e-03),  interval(-9.817321e-04),  interval(-4.307003e-04),  interval(0),  interval(0)},
{ interval(3.195921e-03),  interval(9.999977e-01),  interval(-1.571348e-06),  interval(-6.894136e-07),  interval(0),  interval(0)},
{ interval(2.557824e-06),  interval(1.599999e-03),  interval(1.000000e+00),  interval(-3.677654e-10),  interval(0),  interval(0)},
{ interval(6.822315e-10),  interval(6.399998e-07),  interval(8.000000e-04),  interval(1.000000e+00),  interval(0),  interval(0)},
{ interval(2.132245e-15),  interval(2.666666e-12),  interval(5.000000e-09),  interval(1.250000e-05),  interval(1),  interval(0)},
{ interval(2.665533e-21),  interval(4.166666e-18),  interval(1.041667e-14),  interval(3.906250e-11),  interval(6.250000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.496813e-05), interval(3.996601e-08), interval(2.131974e-11), interval(4.264491e-15), interval(1.066213e-20), interval(1.110686e-26)};
const __plant_typet __char_poly_const[7][7] = 
 {{ 1,  0,  0,  0,  0,  0,  0},
{ -5.997449e+00,  1.110686e-26,  1.066213e-20,  4.264491e-15,  2.131974e-11,  3.996601e-08,  2.496813e-05},
{ 1.498725e+01,  6.328730e-25,  2.664355e-19,  3.835650e-14,  2.126538e-11,  -1.199320e-07,  -1.248407e-04},
{ -1.997450e+01,  3.351888e-24,  4.260052e-19,  -4.264489e-14,  -1.704220e-10,  8.006784e-08,  2.496813e-04},
{ 1.497451e+01,  3.350671e-24,  -4.262406e-19,  -4.257970e-14,  1.704763e-10,  7.972827e-08,  -2.496813e-04},
{ -5.987262e+00,  6.321797e-25,  -2.662182e-19,  3.834563e-14,  -2.134687e-11,  -1.197622e-07,  1.248407e-04},
{ 9.974532e-01,  1.108705e-26,  -1.064402e-20,  4.257971e-15,  -2.129257e-11,  3.993205e-08,  -2.496813e-05}};

#endif /*BENCHMARK_H_*/