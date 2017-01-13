

typedef __CPROVER_fixedbv[24][12] __CPROVER_EIGEN_fixedbvt;
typedef __CPROVER_fixedbv[12][6] __CPROVER_fxp_t;

__CPROVER_EIGEN_fixedbvt nondet_double(void);


#define NSTATES 4u
#define NINPUTS 1u
#define NOUTPUTS 1u
#define INITIALSTATE_UPPERBOUND 1.0
#define INITIALSTATE_LOWERBOUND 0.0
#define NUMBERLOOPS 50



typedef struct {
    __CPROVER_EIGEN_fixedbvt const A[NSTATES][NSTATES];
    __CPROVER_EIGEN_fixedbvt const B[NSTATES][NINPUTS];
    __CPROVER_EIGEN_fixedbvt const C[NOUTPUTS][NSTATES];
    __CPROVER_EIGEN_fixedbvt const D[NOUTPUTS][NINPUTS];

    __CPROVER_EIGEN_fixedbvt states[NSTATES];
    __CPROVER_EIGEN_fixedbvt outputs[NOUTPUTS];
    __CPROVER_EIGEN_fixedbvt inputs[NINPUTS];
    __CPROVER_EIGEN_fixedbvt const K[NSTATES];
    __CPROVER_EIGEN_fixedbvt const ref[NINPUTS];

  }digital_system_state_space;



 /* typedef struct {
     int int_bits;
     int frac_bits;
  } implementation;

  __CPROVER_fixedbv[int_bits+frac_bits][frac_bits] __CPROVER_fxp;

  const implementation impl = {
   .int_bits = 2,
   .frac_bits = 3
  };*/

  digital_system_state_space _controller=
  {
      .A = { { 0.974,0.0},{ 1.0,0.0}},
      .B = { { 0.25},{0.0} },
      .C = { { 0.157,0.008} },
      .D = { { 0.0 } },
     // .K = { 0.5, 1 },
      .K = { nondet_double(), nondet_double() },
      .inputs = { { 1.0 } },
      .ref = {{0.0}},
  };

  extern __CPROVER_fxp_t K_fxp[NSTATES];

  void inputs_equal_ref_minus_k_times_states(void)
  {
    __CPROVER_fxp_t states_fxp[NSTATES];
    __CPROVER_fxp_t result_fxp;
    __CPROVER_EIGEN_fixedbvt result_double;

    int k, i;
    for(k=0; k<NSTATES;k++)
      {states_fxp[k]= (__CPROVER_fxp_t)_controller.states[k];}

    for(i=0; i<NSTATES; i++)
        { result_fxp = result_fxp + (K_fxp[k] * states_fxp[k]);}

      result_double = (__CPROVER_EIGEN_fixedbvt)result_fxp;

    for(i=0; i<NINPUTS; i++)
        {_controller.inputs[i] = _controller.ref[i] - result_double;}
  }

  void outputs_equals_C_states_plus_D_inputs(void)
  {
    int i,j,k;


   for(i=0; i<NOUTPUTS; i++)
   {
     _controller.outputs[i]=0;
     for(j=0; j<NSTATES; j++)
         {_controller.outputs[i] = _controller.outputs[i] +
                     _controller.C[i][j]*_controller.states[j];}
     for(k=0; k<NINPUTS; k++)
     { _controller.outputs[i] = _controller.outputs[i] +
           _controller.D[i][j]*_controller.inputs[j];}

     }
  }

  void states_equals_A_states_plus_B_inputs(void)
  {
    __CPROVER_EIGEN_fixedbvt result[NSTATES];
    int i,j,k;
    for(i=0; i<NSTATES; i++)
       {
        result[i]=0;
         for(j=0; j<NSTATES; j++)
             {result[i] = result[i] +
                         _controller.A[i][j]*_controller.states[j];}
         for(k=0; k<NSTATES; k++)
         {
           result[i] = result[i] +
               _controller.B[i][j]*_controller.inputs[j];}
    }
    for(i=0; i<NSTATES; i++)
      {_controller.states[i] = result[i];}

  }


  fxp_ss_closed_loop_quantization_error(){

        ////// inputs = reference - K * states

              inputs_equal_ref_minus_k_times_states();
          /////output = C*states + D * inputs
              outputs_equals_C_states_plus_D_inputs();

          /////states = A*states + B*inputs
              states_equals_A_states_plus_B_inputs();

  }

  int main()
  {
    __CPROVER_EIGEN_fixedbvt upper_bound = 1000;
    __CPROVER_EIGEN_fixedbvt lower_bound = -1000;
    int k;
    int i,j,l;

    for(l=0; l<NSTATES; l++)//set initial states
      {_controller.states[l] = nondet_double();
      __CPROVER_assume(_controller.states[l]<INITIALSTATE_UPPERBOUND & _controller.states[l]>INITIALSTATE_LOWERBOUND);
      }

    for(i=0; i<NSTATES;i++){ //convert controller to fixed point
            K_fxp[i]= (__CPROVER_fxp_t)_controller.K[i];
    }
    printf("Initial states %f %f\n",_controller.states[0], _controller.states[1]);


    for(k=0; k<NUMBERLOOPS; k++)
        {fxp_ss_closed_loop_quantization_error(); //one time step
        for(i=0; i<NSTATES; i++){
         // __CPROVER_assert(_controller.states[i]<upper_bound && _controller.states[i]>lower_bound, "");
          }
        }



   printf("Final states %f %f\n",_controller.states[0], _controller.states[1]);
  __CPROVER_assert(0, " Successful");

  return 0;
  }
