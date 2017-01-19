/*
 * benchmark.h
 *
 *  Created on: 18 Jan 2017
 *      Author: elipol
 */

#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#define INT_BITS 8
#define FRAC_BITS 8
#include "control_types.h"

#define NSTATES 3
#define NINPUTS 1
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ 0.9905,0.075687,0.021033 }, { 0.125,0,0 }, { 0,0.015625,0 }};
const __plant_typet _controller_B[NSTATES] = { 16, 0, 0 };



#endif /* BENCHMARK_H_ */
