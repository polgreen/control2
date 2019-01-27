#ifndef BENCHMARK_H_ 
#define BENCHMARK_H_ 

// time discretisation 0.000  
#ifndef INT_BITS 
#define INT_BITS 8
#define FRAC_BITS 8
#endif
#define NSTATES 9 
#include "control_types.h"
#define NINPUTS 1 
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)10000
#define INPUT_LOWERBOUND (__plant_precisiont)-10000
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999910e-01),  interval(-8.249981e-06),  interval(-4.593737e-06),  interval(-4.019518e-06),  interval(-2.481436e-06),  interval(-2.287101e-06),  interval(-1.429682e-06),  interval(-1.203364e-06),  interval(-8.300744e-07)},
{ interval(7.999964e-06),  interval(1.000000e+00),  interval(-1.837497e-11),  interval(-1.607809e-11),  interval(-9.925758e-12),  interval(-9.148414e-12),  interval(-5.718734e-12),  interval(-4.813463e-12),  interval(-3.320303e-12)},
{ interval(3.199990e-11),  interval(8.000000e-06),  interval(1),  interval(-4.287493e-17),  interval(-2.646870e-17),  interval(-2.439579e-17),  interval(-1.524997e-17),  interval(-1.283591e-17),  interval(-8.854147e-18)},
{ interval(4.266657e-17),  interval(1.600000e-11),  interval(4.000000e-06),  interval(1),  interval(-2.646871e-23),  interval(-2.439580e-23),  interval(-1.524998e-23),  interval(-1.283592e-23),  interval(-8.854151e-24)},
{ interval(4.266659e-23),  interval(2.133333e-17),  interval(8.000000e-12),  interval(4.000000e-06),  interval(1),  interval(-1.951664e-29),  interval(-1.219998e-29),  interval(-1.026874e-29),  interval(-7.083323e-30)},
{ interval(1.706664e-29),  interval(1.066667e-23),  interval(5.333333e-18),  interval(4.000000e-12),  interval(2.000000e-06),  interval(1),  interval(-4.066662e-36),  interval(-3.422912e-36),  interval(-2.361108e-36)},
{ interval(5.688881e-36),  interval(4.266667e-30),  interval(2.666667e-24),  interval(2.666667e-18),  interval(2.000000e-12),  interval(2.000000e-06),  interval(1),  interval(-1.026874e-42),  interval(-7.083323e-43)},
{ interval(8.533321e-43),  interval(7.111111e-37),  interval(5.333333e-31),  interval(6.666667e-25),  interval(6.666667e-19),  interval(1.000000e-12),  interval(1.000000e-06),  interval(1),  interval(-1.180553e-49)},
{ interval(7.111096e-50),  interval(5.333333e-44),  interval(4.444444e-38),  interval(6.666667e-32),  interval(8.333333e-26),  interval(1.666667e-19),  interval(2.500000e-13),  interval(5.000000e-07),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.999955e-07), interval(3.999988e-12), interval(1.066664e-17), interval(1.066665e-23), interval(8.533321e-30), interval(2.844441e-36), interval(8.533321e-43), interval(1.422219e-49), interval(1.659255e-56)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.999991e+00,  1.659255e-56,  1.422219e-49,  8.533321e-43,  2.844441e-36,  8.533321e-30,  1.066665e-23,  1.066664e-17,  3.999988e-12,  9.999955e-07},
{ 3.599993e+01,  2.806513e-54,  2.474662e-47,  9.557312e-41,  1.535996e-34,  1.877327e-28,  6.399967e-23,  -2.133338e-17,  -2.399994e-11,  -7.999964e-06},
{ -8.399975e+01,  8.238437e-53,  4.115899e-46,  7.748238e-40,  3.811535e-34,  -2.730666e-28,  -3.626654e-22,  -8.533261e-17,  5.599992e-11,  2.799987e-05},
{ 1.259995e+02,  4.982690e-52,  1.150004e-45,  1.228775e-40,  -1.234485e-33,  -7.338618e-28,  4.906657e-22,  3.626647e-16,  -5.600008e-11,  -5.599975e-05},
{ -1.259994e+02,  8.810390e-52,  -1.580366e-51,  -1.988258e-39,  2.675188e-39,  1.621326e-27,  -1.823992e-27,  -5.333309e-16,  4.199981e-16,  6.999969e-05},
{ 8.399950e+01,  4.982681e-52,  -1.150004e-45,  1.228814e-40,  1.234482e-33,  -7.338649e-28,  -4.906632e-22,  3.626654e-16,  5.599941e-11,  -5.599975e-05},
{ -3.599975e+01,  8.238407e-53,  -4.115887e-46,  7.748225e-40,  -3.811542e-34,  -2.730643e-28,  3.626647e-22,  -8.533329e-17,  -5.599958e-11,  2.799987e-05},
{ 8.999928e+00,  2.806498e-54,  -2.474649e-47,  9.557269e-41,  -1.535990e-34,  1.877323e-28,  -6.399975e-23,  -2.133309e-17,  2.399984e-11,  -7.999964e-06},
{ -9.999910e-01,  1.659249e-56,  -1.422212e-49,  8.533269e-43,  -2.844423e-36,  8.533269e-30,  -1.066659e-23,  1.066659e-17,  -3.999976e-12,  9.999955e-07}};

#endif /*BENCHMARK_H_*/