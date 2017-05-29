/*
 * check_gaps_between_discrete_points.cpp
 *
 *  Created on: 19 Jan 2017
 *      Author: elipol
 */

#include <stdio.h>
#include "dcmotor_ss_disc1.h"
#include "fixedpoint.h"
#include <cmath>


typedef double __plant_typet;
typedef fxp_t __controller_typet;

//typedef __CPROVER_fixedbv[INT_BITS+FRAC_BITS][FRAC_BITS] __controller_typet;

#define INITIALSTATE_UPPERBOUND (__plant_typet)0.5
#define INITIALSTATE_LOWERBOUND (__plant_typet)-0.5
#define SAFE_STATE_UPPERBOUND (__plant_typet)1
#define SAFE_STATE_LOWERBOUND (__plant_typet)-1



__plant_typet _AminusBK[NSTATES][NSTATES];
 __controller_typet K_fxp[NSTATES];
__plant_typet _controller_inputs;
__plant_typet _controller_states[NSTATES];
__plant_typet exp_max_eigen_norm;
__plant_typet max_eigen_norm; //PASCAL this value to come from your discrete_step_k


void inputs_equal_ref_minus_k_times_states(void)
  {
    __controller_typet states_fxp[NSTATES];
    //inputs_equal_ref_minus_k_times_states_result_fxp
    //single input
    __controller_typet result_fxp=0;

     for(int k=0; k<NSTATES; k++)
        { result_fxp += (K_fxp[k] * (__controller_typet)_controller_states[k]);}

        _controller_inputs = -(__plant_typet)result_fxp;
       // __CPROVER_assume(_controller_inputs<INPUT_UPPERBOUND && _controller_inputs>INPUT_LOWERBOUND);
  }

__plant_typet states_equals_A_states_plus_B_inputs_result[NSTATES]; //default init at 0

void states_equals_A_states_plus_B_inputs(void)
 {
   //int i,k;
   for(int i=0; i<NSTATES; i++)
   {
     //states_equals_A_states_plus_B_inputs_result[i]=0;
    for(int k=0; k<NSTATES; k++) {
      states_equals_A_states_plus_B_inputs_result[i] += _controller_A[i][k]*_controller_states[k];
      states_equals_A_states_plus_B_inputs_result[i] += _controller_B[i]*_controller_inputs;
    }
   }

   for(int i=0; i<NSTATES; i++)
       {_controller_states[i] = states_equals_A_states_plus_B_inputs_result[i];}
 }


int check_gap()
{ //upper bound is e ^ max lamba * t, t is 1 time step
  for(int i=0; i<NSTATES; i++)
  {
    if( exp_max_eigen_norm - _controller_states[i]< SAFE_STATE_LOWERBOUND ||
        exp_max_eigen_norm + _controller_states[i] > SAFE_STATE_UPPERBOUND)
      return 0;
  }
  return 1;
}

int check_safety(void)
{

  for(int j=0; j<NSTATES; j++) //set initial states and reference
  {


  }

  for(int k=0; k<NUMBERLOOPS; k++)
  {
    inputs_equal_ref_minus_k_times_states(); //update inputs one time step
    states_equals_A_states_plus_B_inputs(); //update states one time step

    for(int i=0; i<NSTATES; i++)
    {
      if(_controller_states[i]>SAFE_STATE_UPPERBOUND || _controller_states[i]<SAFE_STATE_LOWERBOUND)
        {return 0;}
      else
      {
        if(check_gap()==0)
          return 0;
      }
    }
  }
  return 1;
}

void exp_max_eigen_norm()
{
  exp_max_eigen_norm = exp(max_eigen_norm);
}

int main(void) {
  max_eigen_norm=0.01;
  if(check_safety()!=0)
    return 0;
}
