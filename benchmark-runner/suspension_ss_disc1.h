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

#define NSTATES 4u
#define NINPUTS 1u
#define NOUTPUTS 1u
#define INITIALSTATE_UPPERBOUND (__CPROVER_fixedbv[24][12])0.1
#define INITIALSTATE_LOWERBOUND (__CPROVER_fixedbv[24][12])-0.1
#define INPUT_UPPERBOUND (__CPROVER_fixedbv[24][12])1
#define INPUT_LOWERBOUND (__CPROVER_fixedbv[24][12])-1
#define NUMBERLOOPS 10 //number of timesteps to check safety spec over
#define INT_BITS 8
#define FRAC_BITS 8
#define SAFE_STATE_UPPERBOUND (__CPROVER_fixedbv[24][12])1
#define SAFE_STATE_LOWERBOUND (__CPROVER_fixedbv[24][12])-1

typedef __CPROVER_fixedbv[INT_BITS+FRAC_BITS][FRAC_BITS] __CPROVER_fxp_t;
//typedef __CPROVER_fixedbv[24][12] __CPROVER_fxp_t;
//__CPROVER_EIGEN_fixedbvt nondet_double(void);
extern  __CPROVER_fxp_t K_fxp[NSTATES];
__CPROVER_EIGEN_fixedbvt _AminusBK[NSTATES][NSTATES];


const __CPROVER_EIGEN_fixedbvt _controller_A[NSTATES][NSTATES] = {{-5.915e-06, -2.7472e-06, 3.3912e-52, -1.264e-208},{3.8147e-06,0,0,0},{0,3.8147e-06,0,0;0,0,3.8147e-06,0} };
const __CPROVER_EIGEN_fixedbvt _controller_B[NSTATES] = { { 131072.0 },{0.0},{0.0} };
extern const __CPROVER_EIGEN_fixedbvt _controller_K[NSTATES];
__CPROVER_EIGEN_fixedbvt _controller_inputs;
extern __CPROVER_EIGEN_fixedbvt _controller_states[NSTATES];



#endif /* BENCHMARK_H_ */