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
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(9.999100e-01),  interval(-8.249812e-05),  interval(-4.593624e-05),  interval(-4.019400e-05),  interval(-2.481357e-05),  interval(-2.287021e-05),  interval(-1.429629e-05),  interval(-1.203317e-05),  interval(-8.300408e-06)},
{ interval(7.999640e-05),  interval(1.000000e+00),  interval(-1.837466e-09),  interval(-1.607777e-09),  interval(-9.925544e-10),  interval(-9.148201e-10),  interval(-5.718594e-10),  interval(-4.813338e-10),  interval(-3.320213e-10)},
{ interval(3.199904e-09),  interval(8.000000e-05),  interval(1.000000e+00),  interval(-4.287430e-14),  interval(-2.646828e-14),  interval(-2.439536e-14),  interval(-1.524969e-14),  interval(-1.283566e-14),  interval(-8.853967e-15)},
{ interval(4.266571e-14),  interval(1.600000e-09),  interval(4.000000e-05),  interval(1),  interval(-2.646837e-19),  interval(-2.439546e-19),  interval(-1.524975e-19),  interval(-1.283572e-19),  interval(-8.854007e-20)},
{ interval(4.266590e-19),  interval(2.133333e-14),  interval(8.000000e-10),  interval(4.000000e-05),  interval(1),  interval(-1.951641e-24),  interval(-1.219983e-24),  interval(-1.026860e-24),  interval(-7.083227e-25)},
{ interval(1.706641e-24),  interval(1.066667e-19),  interval(5.333333e-15),  interval(4.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-4.066617e-30),  interval(-3.422872e-30),  interval(-2.361079e-30)},
{ interval(5.688812e-30),  interval(4.266667e-25),  interval(2.666667e-20),  interval(2.666667e-15),  interval(2.000000e-10),  interval(2.000000e-05),  interval(1),  interval(-1.026860e-35),  interval(-7.083227e-36)},
{ interval(8.533205e-36),  interval(7.111111e-31),  interval(5.333333e-26),  interval(6.666667e-21),  interval(6.666667e-16),  interval(1.000000e-10),  interval(1.000000e-05),  interval(1),  interval(-1.180531e-41)},
{ interval(7.110962e-42),  interval(5.333333e-37),  interval(4.444444e-32),  interval(6.666667e-27),  interval(8.333333e-22),  interval(1.666667e-16),  interval(2.500000e-11),  interval(5.000000e-06),  interval(1)}};
const __plant_typet _controller_B[NSTATES] = {interval(9.999550e-06), interval(3.999880e-10), interval(1.066643e-14), interval(1.066647e-19), interval(8.533205e-25), interval(2.844406e-30), interval(8.533205e-36), interval(1.422192e-41), interval(1.659217e-47)};
const __plant_typet __char_poly_const[10][10] = 
 {{ 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
{ -8.999910e+00,  1.659217e-47,  1.422192e-41,  8.533205e-36,  2.844406e-30,  8.533205e-25,  1.066647e-19,  1.066643e-14,  3.999880e-10,  9.999550e-06},
{ 3.599928e+01,  2.806467e-45,  2.474617e-39,  9.557118e-34,  1.535960e-28,  1.877272e-23,  6.399674e-19,  -2.133381e-14,  -2.399940e-09,  -7.999640e-05},
{ -8.399748e+01,  8.238237e-44,  4.115785e-38,  7.747983e-33,  3.811348e-28,  -2.730662e-23,  -3.626538e-18,  -8.532613e-14,  5.599916e-09,  2.799874e-04},
{ 1.259950e+02,  4.982529e-43,  1.149958e-37,  1.228549e-33,  -1.234446e-27,  -7.338180e-23,  4.906573e-18,  3.626470e-13,  -5.600084e-09,  -5.599748e-04},
{ -1.259937e+02,  8.810033e-43,  -1.580302e-42,  -1.988177e-32,  2.675080e-32,  1.621260e-22,  -1.823918e-22,  -5.333093e-13,  4.199811e-13,  6.999685e-04},
{ 8.399496e+01,  4.982439e-43,  -1.149956e-37,  1.228940e-33,  1.234421e-27,  -7.338493e-23,  -4.906319e-18,  3.626537e-13,  5.599412e-09,  -5.599748e-04},
{ -3.599748e+01,  8.237940e-44,  -4.115667e-38,  7.747853e-33,  -3.811420e-28,  -2.730426e-23,  3.626469e-18,  -8.533285e-14,  -5.599580e-09,  2.799874e-04},
{ 8.999280e+00,  2.806317e-45,  -2.474493e-39,  9.556688e-34,  -1.535902e-28,  1.877226e-23,  -6.399750e-19,  -2.133093e-14,  2.399844e-09,  -7.999640e-05},
{ -9.999100e-01,  1.659153e-47,  -1.422124e-41,  8.532693e-36,  -2.844227e-30,  8.532693e-25,  -1.066590e-19,  1.066595e-14,  -3.999760e-10,  9.999550e-06}};

#endif /*BENCHMARK_H_*/