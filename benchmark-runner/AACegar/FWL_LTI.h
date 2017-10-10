//#define __CPROVER
//#define _FIXEDBV
#ifdef __CPROVER
#ifndef _FIXEDBV
  #ifndef _EXPONENT_WIDTH
    #define _EXPONENT_WIDTH 16
  #endif
  #ifndef _FRACTION_WIDTH
  #define _FRACTION_WIDTH 11
  #endif
  typedef __CPROVER_floatbv[_EXPONENT_WIDTH][_FRACTION_WIDTH] control_floatt;
  control_floatt _imp_max=(((1 <<(_EXPONENT_WIDTH-1))-1)<<1)+1;
#else
  #ifndef _CONTROL_FLOAT_WIDTH
    #define _CONTROL_FLOAT_WIDTH 32
  #endif
  #ifndef _CONTORL_RADIX_WIDTH
    #define _CONTORL_RADIX_WIDTH _CONTROL_FLOAT_WIDTH / 2
  #endif
  typedef __CPROVER_fixedbv[_CONTROL_FLOAT_WIDTH][_CONTORL_RADIX_WIDTH] control_floatt;
  control_floatt _imp_max=(((1 <<(_CONTROL_FLOAT_WIDTH-1))-1)<<1)+1;
#endif
  typedef unsigned char cnttype;
  const control_floatt _zero=0.0;
  const control_floatt _one=1.0;
#else
  #define _FIXEDBV
  typedef double control_floatt;
  typedef unsigned int cnttype;
  const control_floatt _zero=0.0;
  const control_floatt _one=1.0;
  #include <stdlib.h>
  #include <stdio.h> 
#endif

typedef struct implt
{
  cnttype int_bits;
  cnttype frac_bits;
  control_floatt max;
  control_floatt min;
  control_floatt scale;
  signed long int fxp_one;
};

void verify_assume(_Bool expression)
{
#ifdef __CPROVER
  __CPROVER_assume(expression != (_Bool)0);
#else
  printf("assumes %d\n", (int)expression);
  assert(expression);
#endif
}

void verify_assert(_Bool expression)
{
  /* assertion expression */
#ifdef __CPROVER
  __CPROVER_assert(expression,"");
#else
  assert(expression);
#endif
}

