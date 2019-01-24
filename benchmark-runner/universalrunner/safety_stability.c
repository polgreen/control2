#include <stdio.h>
#include <stdlib.h>
#include "benchmark.h" //benchmark header file
#include "operators.h"

#ifdef CPROVER
#define __DSVERIFIER_assert(x) __CPROVER_assert(x, "")
#else
  #include <assert.h>
  #define __DSVERIFIER_assert(x) assert(x)
#endif

//#define NUMBERLOOPS 5 // Defined by benchmark script
#define INITIALSTATE_UPPERBOUND (__plant_precisiont)0.5
#define INITIALSTATE_LOWERBOUND (__plant_precisiont)-0.5
#define SAFE_STATE_UPPERBOUND (__plant_precisiont)1.5
#define SAFE_STATE_LOWERBOUND (__plant_precisiont)-1.5

//other plant variables
#ifdef CPROVER
extern const __controller_typet K_fxp[NSTATES]; //nondet controller
extern __plant_typet _controller_states[NSTATES]; //nondet initial states
#else
//const __controller_typet K_fxp[NSTATES] = { interval(0.0), interval(0.004638671875), interval(-0.00439453125) };
//const __controller_typet K_fxp[NSTATES] = { _CONTROLLER_INTERVALS };
__controller_typet K_fxp[NSTATES];
int NUMBERLOOPS;
__plant_typet _controller_states[NSTATES];
#endif
__plant_typet _controller_inputs;

//matrices for stability calculation
__plant_typet _AminusBK[NSTATES][NSTATES];

__plant_typet __CPROVER_EIGEN_poly[NSTATES + 1u];

//stablity calc

__plant_typet internal_pow(__plant_typet a, unsigned int b){

   __plant_typet acc = one_type;
   for (int i=0; i < b; i++){
    acc = mult(acc,a);
   }
   return acc;
}


int check_stability(){


 #if NSTATES==1
  if(greaterthan(_AminusBK[0][0], one_type) || lessthan(_AminusBK[0][0], minusone))
    {return 0;}
  else
    {return 1;}
#endif

#define __a __CPROVER_EIGEN_poly
#define __n NSTATES + 1u
   int lines = 2 * __n - 1;
   int columns = __n;
   __plant_typet m[lines][__n];
   int i,j;

   /* to put current values in stability counter-example
    * look for current_stability (use: --no-slice) */
   __plant_typet current_stability[__n];
   for (i=0; i < __n; i++){
     current_stability[i] = __a[i];
   }

   /* check the first constraint condition F(1) > 0 */
   __plant_typet sum = zero_type;
   for (i=0; i < __n; i++) {
     sum = add(sum, __a[i]);
   }
   if (lessthan_equaltozero(sum)){
  printf("[DEBUG] the first constraint of Jury criteria failed: (F(1) > 0)");
     return 0;
   }

   /* check the second constraint condition F(-1)*(-1)^n > 0 */
   sum = zero_type;
   for (i=0; i < __n; i++){
    sum = add(sum, mult(__a[i] , internal_pow(minusone, NSTATES-i) ));
   }
   sum = mult(sum,internal_pow(minusone, NSTATES) );

   if (lessthan_equaltozero(sum)){
    printf("[DEBUG] the second constraint of Jury criteria failed: (F(-1)*(-1)^n > 0)");
    return 0;
   }

   /* check the third constraint condition abs(a0 < an*(z^n)  */
   if(greaterthan( _abs(__a[__n-1]), __a[0])){
  // if (abs(__a[__n-1]) > __a[0]){
     printf("[DEBUG] the third constraint of Jury criteria failed: (abs(a0) < a_{n}*z^{n})");
     return 0;
   }

   /* check the fourth constraint of condition (Jury Table) */
   for (i=0; i < lines; i++){
    for (j=0; j < columns; j++){
      m[i][j] = zero_type;
    }
   }
   for (i=0; i < lines; i++){
    for (j=0; j < columns; j++){
     if (i == 0){
      m[i][j] = __a[j];
      continue;
     }
     if (i % 2 != 0 ){
       int x;
       for(x=0; x<columns;x++){
        m[i][x] = m[i-1][columns-x-1];
       }
       columns = columns - 1;
      j = columns;
     }else{
      m[i][j] = sub(m[i-2][j] , mult( div(m[i-2][columns] , m[i-2][0]) , m[i-1][j]) );
     }
    }
   }
   int first_is_positive = lessthanzero( m[0][0])? 0 : 1;
  // int first_is_positive =  m[0][0] >= 0 ? 1 : 0;
   for (i=0; i < lines; i++){
    if (i % 2 == 0){
      int line_is_positive = lessthanzero(m[i][0])? 0 : 1;
    // int line_is_positive = m[i][0] >= 0 ? 1 : 0;
     if (first_is_positive != line_is_positive){
      return 0;
     }
     continue;
    }
   }
   return 1;
}

#define __m _AminusBK


#if PREPROCESSING
void __CPROVER_EIGEN_preprocessed_charpoly(void){
  for(int i=0; i<NSTATES+1; i++)
  {
    __CPROVER_EIGEN_poly[i] = __char_poly_const[i][0];
    for(int j=0; j<NSTATES; j++)
    {
      __CPROVER_EIGEN_poly[i] = add(__CPROVER_EIGEN_poly[i], mult(__char_poly_const[i][j+1],K_fxp[j]));
    }
  }
}
#else
#include "charpolys.h"
#endif

void __CPROVER_EIGEN_charpoly(void){

  #if NSTATES==1
  //do nothing
 #elif PREPROCESSING
   __CPROVER_EIGEN_preprocessed_charpoly();
 #else
 generate_charpoly();
#endif

  // Normalise
  __plant_typet max_coefficient=zero_type;
  for (int i = 0; i <= NSTATES; ++i)
    if (lessthan(max_coefficient, __CPROVER_EIGEN_poly[i]))
      max_coefficient=__CPROVER_EIGEN_poly[i];

  for (int i = 0; i <= NSTATES; ++i)
    __CPROVER_EIGEN_poly[i]=div(__CPROVER_EIGEN_poly[i], max_coefficient);
}

void A_minus_B_K()
{
  for (int i=0;i<NSTATES; i++) { //rows of B
      for (int j=0; j<NSTATES; j++) { //columns of K
        _AminusBK[i][j] = sub( _controller_A[i][j], mult(_controller_B[i] , plant_cast(K_fxp[j])  ));
          }
      }
}

void closed_loop(void)
{
  A_minus_B_K();
}


void inputs_equal_ref_minus_k_times_states(void)
  {
    //single input
    __controller_typet result_fxp=zero_type;

     for(int k=0; k<NSTATES; k++)
     {
    	   result_fxp = add (result_fxp, mult(K_fxp[k] , controller_cast(_controller_states[k])));
        _controller_inputs = sub(zero_type, plant_cast(result_fxp));
        __DSVERIFIER_assert(_controller_inputs <= INPUT_UPPERBOUND && _controller_inputs >= INPUT_LOWERBOUND);
  }
 }

__plant_typet states_equals_A_states_plus_B_inputs_result[NSTATES];

void states_equals_A_states_plus_B_inputs(void)
{

  #ifdef CPROVER
      __CPROVER_array_set(states_equals_A_states_plus_B_inputs_result, zero_type);
  #else
    for(int i=0; i<NSTATES; i++)
      states_equals_A_states_plus_B_inputs_result[i] = zero_type;
  #endif

   for(int i=0; i<NSTATES; i++)
   {
     //states_equals_A_states_plus_B_inputs_result[i]=0;
    for(int k=0; k<NSTATES; k++) {
      states_equals_A_states_plus_B_inputs_result[i] = add(states_equals_A_states_plus_B_inputs_result[i] , mult( _controller_A[i][k],_controller_states[k]));
    }
    states_equals_A_states_plus_B_inputs_result[i] = add(states_equals_A_states_plus_B_inputs_result[i] , mult( _controller_B[i],_controller_inputs));
   }

#ifdef CPROVER
   __CPROVER_array_copy(_controller_states, states_equals_A_states_plus_B_inputs_result);
   /*for(i=0; i<NSTATES; i++)
       {_controller_states[i] = states_equals_A_states_plus_B_inputs_result[i];}*/
  __DSVERIFIER_assert( _controller_states[0]<=SAFE_STATE_UPPERBOUND && _controller_states[0]>=SAFE_STATE_LOWERBOUND);
  __DSVERIFIER_assert( _controller_states[1]<=SAFE_STATE_UPPERBOUND && _controller_states[1]>=SAFE_STATE_LOWERBOUND);
  #if NSTATES==3 || NSTATES==4
      __DSVERIFIER_assert( _controller_states[2]<=SAFE_STATE_UPPERBOUND && _controller_states[2]>=SAFE_STATE_LOWERBOUND);
  #endif
  #if NSTATES==4
      __DSVERIFIER_assert( _controller_states[3]<=SAFE_STATE_UPPERBOUND && _controller_states[3]>=SAFE_STATE_LOWERBOUND);
  #endif
#else
  for(int i=0; i<NSTATES; i++)
       {_controller_states[i] = states_equals_A_states_plus_B_inputs_result[i];
       __DSVERIFIER_assert( _controller_states[i]<=SAFE_STATE_UPPERBOUND && _controller_states[i]>=SAFE_STATE_LOWERBOUND);
       }
#endif
 }



int check_safety(void)
{

  for(int k=0; k<NUMBERLOOPS; k++)
  {

    inputs_equal_ref_minus_k_times_states(); //update inputs one time step //this is still needed for INTERVALS because it enforces bounds on the input
    states_equals_A_states_plus_B_inputs(); //update states one time step

    for(int i=0; i<NSTATES; i++)
    {
      if(_controller_states[i]>SAFE_STATE_UPPERBOUND || _controller_states[i]<SAFE_STATE_LOWERBOUND)
        {return 0;}
    }
  }
  return 1;
}

#ifdef CPROVER
void assume_corner_cases_for_states_with_loops(void)
{
  for(int i=0; i<NSTATES; i++)
  {
    __CPROVER_assume(_controller_states[i]==INITIALSTATE_UPPERBOUND || _controller_states[i]==INITIALSTATE_LOWERBOUND);
  }
}



void assume_corner_cases_for_states(void) {
  #if NSTATES == 1
  __CPROVER_assume(_controller_states[0] == INITIALSTATE_UPPERBOUND || _controller_states[0] == INITIALSTATE_LOWERBOUND);
  #elif NSTATES == 2
  __CPROVER_assume(_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND
                || _controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND
                || _controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND
                || _controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND);
  #elif NSTATES == 3
  __CPROVER_assume(_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND
                || _controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND
                || _controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND
                || _controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND
                || _controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND
                || _controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND
                || _controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND
                || _controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND);
  #elif NSTATES == 4
  __CPROVER_assume((_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_UPPERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_UPPERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_UPPERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_UPPERBOUND)
                || (_controller_states[0] == INITIALSTATE_LOWERBOUND && _controller_states[1] == INITIALSTATE_LOWERBOUND && _controller_states[2] == INITIALSTATE_LOWERBOUND && _controller_states[3] == INITIALSTATE_LOWERBOUND));
  #else
    assume_corner_cases_for_states_with_loops();
  #endif
}
#endif

void assert_nonzero_controller(void) {
  int nonzero_coefficients=0;
  for (int i = 0; i < NSTATES; ++i) {
    if (!equaltozero(K_fxp[i])) ++nonzero_coefficients;
  }
  __DSVERIFIER_assert(nonzero_coefficients > 0);
}

void safety_stability(void) {
  closed_loop(); //calculate A - BK
#if NSTATES < 9  
  __CPROVER_EIGEN_charpoly();
  __DSVERIFIER_assert(check_stability());
#endif
#if NSTATES != 1
  __DSVERIFIER_assert(check_safety());
#endif

#ifdef CPROVER
  __controller_typet K_fxp_trace[NSTATES] = { controller_cast(0.0) };
  __CPROVER_array_copy(K_fxp_trace, K_fxp);
#endif
}

#ifndef CPROVER
 __plant_typet _state_poles[256][8];
#endif

int main(int argc, const char *argv[]) {
#ifdef CPROVER
  assume_corner_cases_for_states();
  safety_stability();
#else
  NUMBERLOOPS=atoi(argv[1]);

  for (int i = 0; i < NSTATES; ++i) {
    K_fxp[i]=interval(atof(argv[2+i]));
  }

  int npoles = 1;
  for (int i=0; i < NSTATES; i++){
   npoles = npoles*2;
  }

    for(int i=0; i<npoles; i++)
    {
      for(int j=0; j<NSTATES; j++)
      {
        if(i>>j & 1)
        _state_poles[i][j] = interval(INITIALSTATE_UPPERBOUND);
        else
          _state_poles[i][j] = interval(INITIALSTATE_LOWERBOUND);
      }
    }

  for (int poleIndex = 0; poleIndex < npoles; ++poleIndex)
  {
	  // get states
    for (int stateIndex = 0; stateIndex < NSTATES; ++stateIndex)
    	  _controller_states[stateIndex] = _state_poles[poleIndex][stateIndex];

    safety_stability();

  }
#endif

 return 0;
}
