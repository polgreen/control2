/*
 * benchmark.h
 *
 *  Created on: 18 Jan 2017
 *      Author: elipol
 */
//dcmotor_ss_disc2.ss
#ifndef BENCHMARK_H_
#define BENCHMARK_H_

typedef __CPROVER_fixedbv[24][12] __CPROVER_EIGEN_fixedbvt;

#define NSTATES 3u
#define NINPUTS 1u
#define NOUTPUTS 1u
#define INPUT_UPPERBOUND (__CPROVER_EIGEN_fixedbvt)1
#define INPUT_LOWERBOUND (__CPROVER_EIGEN_fixedbvt)-1
#define NUMBERLOOPS 5 //number of timesteps to check safety spec over
#define INT_BITS 8
#define FRAC_BITS 8

const __CPROVER_EIGEN_fixedbvt _controller_A[NSTATES][NSTATES] = {{0.9905,0.075687,0.021033},{0.125,0,0},{0,0.015625,0} };
const __CPROVER_EIGEN_fixedbvt _controller_B[NSTATES] = { { 16.0 },{0.0},{0.0} };

#endif /* BENCHMARK_H_ */
