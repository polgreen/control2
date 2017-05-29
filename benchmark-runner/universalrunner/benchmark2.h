/*
 * benchmark2.h
 *
 *  Created on: 20 Jan 2017
 *      Author: elipol
 */

#ifndef UNIVERSALRUNNER_BENCHMARK2_H_
#define UNIVERSALRUNNER_BENCHMARK2_H_

#define INT_BITS 8
#define FRAC_BITS 8
#include "control_types.h"

#define NSTATES 2
#define NINPUTS 1
#define NOUTPUTS 1
#define INPUT_UPPERBOUND (__plant_precisiont)1
#define INPUT_LOWERBOUND (__plant_precisiont)-1


const __plant_typet _controller_A[NSTATES][NSTATES] = {{ interval(2.2553),interval(-1)},{interval(1),interval(0) }};
const __plant_typet  _controller_B[NSTATES] = { interval(0.5),interval(0) };

//invpendulum_pendang_ss_disc1.ss




#endif /* UNIVERSALRUNNER_BENCHMARK2_H_ */
