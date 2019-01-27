#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.500  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 7 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(8.695454e-02),  interval(1.966070e-01),  interval(2.358323e-01),  interval(2.240171e-01),  interval(1.211090e-01),  interval(7.434083e-02),  interval(3.531357e-02)},
{ interval(-8.035800e-01),  interval(-6.664017e-01),  interval(-3.852541e-01),  interval(-4.545102e-02),  interval(5.482046e-02),  interval(6.641370e-02),  interval(4.058508e-02)},
{ interval(-4.617680e-01),  interval(-8.346975e-01),  interval(-1.113739e+00),  interval(-1.338699e+00),  interval(-5.743154e-01),  interval(-2.993053e-01),  interval(-1.288744e-01)},
{ interval(7.331520e-01),  interval(5.718880e-01),  interval(2.928922e-01),  interval(-2.116188e-01),  interval(-5.711808e-01),  interval(-3.252668e-01),  interval(-1.490430e-01)},
{ interval(8.478893e-01),  interval(9.781842e-01),  interval(1.107337e+00),  interval(1.336194e+00),  interval(6.760153e-01),  interval(-1.901422e-01),  interval(-8.885058e-02)},
{ interval(2.527305e-01),  interval(3.429210e-01),  interval(4.893788e-01),  interval(8.646454e-01),  interval(9.326740e-01),  interval(9.598435e-01),  interval(-1.895874e-02)},
{ interval(2.696355e-02),  interval(4.107398e-02),  interval(6.898606e-02),  interval(1.555225e-01),  interval(2.443888e-01),  interval(4.966183e-01),  interval(9.983930e-01)}};
const __plant_typet _controller_B[NSTATES] = {interval(-1.004475e-01), interval(-1.154420e-01), interval(3.665760e-01), interval(4.239447e-01), interval(2.527305e-01), interval(5.392709e-02), interval(4.571144e-03)};
const __plant_typet __char_poly_const[8][8] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0},
{ -7.294464e-01,  4.571144e-03,  5.392709e-02,  2.527305e-01,  4.239447e-01,  3.665760e-01,  -1.154420e-01,  -1.004475e-01},
{ 2.761755e-01,  1.735466e-01,  7.290358e-01,  7.501396e-01,  -5.938323e-01,  -1.262336e+00,  9.898529e-02,  2.580396e-01},
{ -1.439034e-01,  5.514939e-01,  3.789429e-01,  -1.452828e+00,  -5.726510e-01,  1.428952e+00,  3.046932e-01,  -2.653961e-01},
{ 3.923056e-02,  3.979616e-01,  -7.679341e-01,  -2.493781e-01,  1.082754e+00,  -3.595110e-01,  -5.297458e-01,  1.316872e-01},
{ -1.703735e-02,  8.056930e-02,  -3.632329e-01,  5.941248e-01,  -1.912959e-01,  -3.315491e-01,  2.834432e-01,  -1.210788e-02},
{ 1.635882e-03,  3.863834e-03,  -3.048590e-02,  1.034875e-01,  -1.438417e-01,  1.452224e-01,  -2.904887e-02,  -1.686209e-02},
{ -5.530844e-04,  1.632978e-05,  -2.529335e-04,  1.723358e-03,  -5.077436e-03,  1.264610e-02,  -1.288501e-02,  5.086731e-03}};

#endif /*BENCHMARK_H_*/