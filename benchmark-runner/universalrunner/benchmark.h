/*
 * benchmark.h
 *
 *  Created on: 18 Jan 2017
 *      Author: elipol
 */

#ifndef BENCHMARK_H_
#define BENCHMARK_H_
#define INTERVAL 1
#ifndef INT_BITS
  #define INT_BITS 6
  #define FRAC_BITS 10
#endif
#define NSTATES 2
#include "control_types.h"

#define NINPUTS 1
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1
const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(1.00003),interval(-0.00003)},
                                                        {interval (1),interval(0) }};
const __plant_typet _controller_B[NSTATES] = { interval(0.0078125), interval(0) };



#endif /* BENCHMARK_H_ */
