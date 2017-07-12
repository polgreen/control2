#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 5.000000e-01 
// No controller needed, safe and stable, completeness k with no controller =  11 
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.907386e+00),  interval(-1.100237e+00),  interval(9.497812e-01),  interval(-6.916872e-01),  interval(4.292989e-01),  interval(-4.201466e-01),  interval(3.615775e-01),  interval(-2.303903e-01),  interval(1.777439e-01)},
{ interval(2),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(1),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(5.000000e-01),  interval(0),  interval(0)},
{ interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(0),  interval(2.500000e-01),  interval(0)}};
const __plant_typet _controller_B[NSTATES] = {interval(2.500000e-01), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0), interval(0)};
const __plant_typet __char_poly_const[10][10] = 
 {{ -1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ 1.907386e+00,  0,  0,  0,  0,  0,  0,  0,  0,  -2.500000e-01},
{ -2.200475e+00,  0,  0,  0,  0,  0,  0,  0,  -5.000000e-01,  0},
{ 1.899562e+00,  0,  0,  0,  0,  0,  0,  -5.000000e-01,  0,  0},
{ -1.383374e+00,  0,  0,  0,  0,  0,  -5.000000e-01,  0,  0,  0},
{ 8.585977e-01,  0,  0,  0,  0,  -5.000000e-01,  0,  0,  0,  0},
{ -4.201466e-01,  0,  0,  0,  -2.500000e-01,  0,  0,  0,  0,  0},
{ 1.807887e-01,  0,  0,  -1.250000e-01,  0,  0,  0,  0,  0,  0},
{ -5.759757e-02,  0,  -6.250000e-02,  0,  0,  0,  0,  0,  0,  0},
{ 1.110900e-02,  -1.562500e-02,  0,  0,  0,  0,  0,  0,  0,  0}};

#endif /*BENCHMARK_H_*/