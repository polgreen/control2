#include <stdio.h>
#include <stdlib.h>
#include "intervals.h"

#define NSTATES 3u
#define NINPUTS 1u
#define NOUTPUTS 1u
#define INITIALSTATE_UPPERBOUND 0.1
#define INITIALSTATE_LOWERBOUND -0.1
#define INPUT_UPPERBOUND 0.5
#define INPUT_LOWERBOUND -0.5
#define NUMBERLOOPS  15 //number of timesteps to check safety spec over
#define INT_BITS 7
#define FRAC_BITS 3
#define SAFE_STATE_UPPERBOUND 1
#define SAFE_STATE_LOWERBOUND -1



typedef struct {
   int int_bits;
   int frac_bits;
} implementation;

typedef struct {
    __CPROVER_EIGEN_fixedbvt const A[NSTATES][NSTATES];
    __CPROVER_EIGEN_fixedbvt const B[NSTATES][NINPUTS];
    __CPROVER_EIGEN_fixedbvt const C[NOUTPUTS][NSTATES];
    __CPROVER_EIGEN_fixedbvt const D[NOUTPUTS][NINPUTS];

    __CPROVER_EIGEN_fixedbvt states[NSTATES];
    __CPROVER_EIGEN_fixedbvt outputs[NOUTPUTS];
    __CPROVER_EIGEN_fixedbvt inputs [NINPUTS];
    __CPROVER_EIGEN_fixedbvt const K[NINPUTS][NSTATES];
    __CPROVER_EIGEN_fixedbvt const ref[NINPUTS];
} continuous_time_system;

continuous_time_system _controller=
{
    .A = { { 4.6764e-166,0.0,0.0}, { 5.1253e-144,0.0,0.0}, { 0,2.5627e-144,0.0} },
    .B = { { 0.125},{0.0},{0.0} },
    .C = { { 0.16,-5.9787e-32,0.0 } },
    .D = { { 0.0 } },
    //.K = { { nondet_double(), nondet_double(), nondet_double() } },
    .K = { { 1072.1259765625, 1665.046875, -2047.998779296875 } },
    .inputs = {  1.0  },
    .ref = {0.0},
};

const implementation impl = {
 .int_bits = 2,
 .frac_bits = 3
};

static const double scale_factor[31] = { 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0,
        128.0, 256.0, 512.0, 1024.0, 2048.0, 4096.0, 8192.0, 16384.0, 32768.0,
        65536.0, 131072.0, 262144.0, 524288.0, 1048576.0, 2097152.0, 4194304.0,
        8388608.0, 16777216.0, 33554432.0, 67108864.0, 134217728.0,
        268435456.0, 536870912.0, 1073741824.0 };

static const double scale_factor_inv[31] = { 1.0, 0.5, 0.25, 0.125, 0.0625,
        0.03125, 0.015625, 0.0078125, 0.00390625, 0.001953125, 0.0009765625,
        0.00048828125, 0.000244140625, 0.0001220703125, 0.00006103515625,
        0.000030517578125, 0.000015258789063, 0.000007629394531,
        0.000003814697266, 0.000001907348633, 0.000000953674316,
        0.000000476837158, 0.000000238418579, 0.000000119209290,
        0.000000059604645, 0.000000029802322, 0.000000014901161,
        0.000000007450581, 0.000000003725290, 0.000000001862645,
        0.000000000931323 };


fxp_t fxp_double_to_fxp(__CPROVER_EIGEN_fixedbvt value) {
    fxp_t tmp;
    double ftemp = value * scale_factor[impl.frac_bits];
    tmp = (fxp_t) ftemp;
    return tmp;
}

__CPROVER_EIGEN_fixedbvt fxp_to_double(fxp_t fxp) {
  __CPROVER_EIGEN_fixedbvt f;
    int f_int = (int) fxp;
    f = f_int * scale_factor_inv[impl.frac_bits];
    return f;
}

fxp_t fxp_quantize(fxp_t aquant) {
    return (fxp_t) aquant;
}

fxp_t fxp_mult(fxp_t amult, fxp_t bmult) {
    fxp_t tmpmult, tmpmultprec;
    tmpmult = (fxp_t)((fxp_t)(amult)*(fxp_t)(bmult));
    if (tmpmult >= 0) {
        tmpmultprec = (tmpmult + ((tmpmult & 1 << (impl.frac_bits - 1)) << 1)) >> impl.frac_bits;
    } else {
        tmpmultprec = -(((-tmpmult) + (((-tmpmult) & 1 << (impl.frac_bits - 1)) << 1)) >> impl.frac_bits);
    }
    tmpmultprec = fxp_quantize(tmpmultprec);
    return tmpmultprec;
}


fxp_t fxp_add(fxp_t aadd, fxp_t badd) {
    fxp_t tmpadd;
    tmpadd = ((fxp_t)(aadd) + (fxp_t)(badd));
    tmpadd = fxp_quantize(tmpadd);
    return tmpadd;
}


/* adds two matrices, fixed point version */
void fxp_add_matrix( unsigned int lines,  unsigned int columns, fxp_t m1[4][4], fxp_t m2[4][4], fxp_t result[4][4]){
    unsigned int i, j;
    for (i = 0; i < lines; i++)
        for (j = 0; j < columns; j++) {
        result[i][j] = fxp_add(m1[i][j] , m2[i][j]);
    }
}

/* multiplies two matrices, fixed point version */
void fxp_matrix_multiplication( unsigned int i1, unsigned int j1, unsigned int i2, unsigned int j2, fxp_t m1[4][4], fxp_t m2[4][4], fxp_t m3[4][4]){
    unsigned int i, j, k;
    if (j1 == i2) { //Checking if the multiplication is possible
        // Initialising Matrix 3
        for (i=0; i<i1; i++) {
            for (j=0; j<j2; j++) {
                m3[i][j] = 0;
            }
        }
        //Calculating multiplication result
        for (i=0;i<i1; i++) {
            for (j=0; j<j2; j++) {
                for (k=0; k<j1; k++) {
                    m3[i][j] = fxp_add( m3[i][j], fxp_mult(m1[i][k] , m2[k][j]));
                }
            }
        }
    } else {
        printf("\nError! Operation invalid, please enter with valid matrices.\n");
    }
}

void inputs_equal_ref_minus_k_times_states(__CPROVER_fxp_t K_fxp[NINPUTS][NSTATES])
  {
      
	__CPROVER_fxp_t states_fxp[NSTATES];
    __CPROVER_fxp_t result_fxp[NINPUTS];

    int k, i;
    for(k=0; k<NSTATES;k++)
      {states_fxp[k]= fxp_double_to_fxp(_controller.states[k]);}

    for(i=0; i<NINPUTS; i++)
    {
      for(k=0; k<NSTATES; k++)
        { result_fxp[i] = result_fxp[i] + (K_fxp[i][k] * states_fxp[k]);}
    }

    for(i=0; i<NINPUTS; i++)
     {
        _controller.inputs[i] = _controller.ref[i] - fxp_to_double(result_fxp[i]);
     }
  
}

void states_equals_A_states_plus_B_inputs(void)
 {
   __CPROVER_EIGEN_fixedbvt result[NSTATES];
   int i,k;
   for(i=0; i<NSTATES; i++)
   {
    result[i]=0;
    for(k=0; k<NSTATES; k++)
         {result[i] = result[i] + _controller.A[i][k]*_controller.states[k];}
    for(k=0; k<NSTATES; k++)
         {result[i] = result[i] +_controller.B[i][k]*_controller.inputs[k];}
   }
   for(i=0; i<NSTATES; i++)
       {_controller.states[i] = result[i];}

 }


int check_safety(void)
{
  int i,j,k;
	__CPROVER_fxp_t K_fxp[NINPUTS][NSTATES];

  for(j=0; j<NSTATES; j++)//set initial states and reference
  {
    _controller.states[j] = 0;
  }
  
  for(i=0; i<NINPUTS;i++)
  {
    for(j=0; j<NSTATES; j++)//convert controller to fixed point
      { K_fxp[i][j]= fxp_double_to_fxp(_controller.K[i][j]);}
  }

  for(k=0; k<NUMBERLOOPS; k++)
  {
    inputs_equal_ref_minus_k_times_states(K_fxp); //update inputs one time step
    states_equals_A_states_plus_B_inputs(); //update states one time step

    for(i=0; i<NSTATES; i++)
    {
      if(_controller.states[i]>SAFE_STATE_UPPERBOUND || _controller.states[i]<SAFE_STATE_LOWERBOUND)
      {
        printf("Failed discrete safety check, states %i is %f \n", i, _controller.states[i]);
        return 0;
      }
    }
  }
  return 1;
}

int main()
{
	if(check_safety()==0)
		printf("UNSAFE \n");
	else
		printf("SAFE \n");
return 0;
}


