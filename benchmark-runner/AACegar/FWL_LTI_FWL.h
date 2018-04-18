signed long int _fxp_max;
signed long int _fxp_min;
control_floatt _dbl_lsb;
control_floatt _transform_error;
control_floatt _sum_error;


#ifdef __CPROVER
  #ifdef _FIXEDBV
    typedef __CPROVER_fixedbv[_EXP_BITS][_FRAC_BITS] controller_floatt;
  #else
    typedef __CPROVER_floatbv[_EXP_BITS][_FRAC_BITS] controller_floatt;
  #endif
#endif
void get_bounds(struct implt impl)
{
  cnttype i;
#ifdef _FIXEDBV
  verify_assume((impl.int_bits+impl.frac_bits) <= 32);
  if(impl.frac_bits >= 31)
    impl.fxp_one = 2147483647l;
  else
    impl.fxp_one = (1 << impl.frac_bits);
  _fxp_max = (1 << (impl.int_bits+impl.frac_bits -1))-1;
  _fxp_min = -_fxp_max;
#ifdef __CPROVER
  int one=1;
  controller_floatt lsb=*(controller_floatt*)&one;
  _dbl_lsb=(control_floatt)lsb;
  impl.max = *(controller_floatt*)&_fxp_max;
#else
  _dbl_lsb=_one/impl.fxp_one;
  impl.max = _fxp_max*_dbl_lsb;
#endif
#else
  verify_assume((_EXP_BITS>_FRAC_BITS) && (_EXP_BITS<= 32));
  signed long int exp=(1 << (_EXP_BITS -_FRAC_BITS -1));
  impl.max=_one;
  for (i=0;i<exp;i++)
  {
    impl.max*=2;
  }
  exp=1 << _FRAC_BITS;
  _dbl_lsb=_one/impl.max;
  impl.max*=_one-_one/exp;
#endif
  impl.min = -impl.max;
#ifndef __CPROVER
  printf("min=%f\n",impl.min);
  printf("max=%f\n",impl.max);
#endif
#ifdef __CHECK_FP
  _transform_error=2*_dbl_lsb*_DIMENSION*_DIMENSION;
  _sum_error=2*_transform_error*_DIMENSION;
#else
  _transform_error=0;
  _sum_error=0;
#endif
}

int check_vector_bounds(vectort coeffs, struct implt impl)
{
  cnttype i;
  for( i=0; i < _DIMENSION; i++)
  {
#ifdef __CPROVER 
  #ifdef _FIXEDBV
    const control_floatt value=coeffs[i];
    verify_assume(value <= impl.max);
    verify_assume(value >= impl.min);
  #else
    const controller_floatt value=coeffs[i];
    coeffs[i]=value;
  #endif
#else
    printf("checking bounds\n");
    const control_floatt value=coeffs[i];
  #ifdef _FIXEDBV
    verify_assume(value <= impl.max);
    verify_assume(value >= impl.min);
  #endif
    if(value > impl.max) return 10;
    if(value < impl.min) return 10;
#endif  
  }
  return 0;
}

int check_matrix_bounds(matrixt coeffs,struct implt impl)
{
  cnttype i,j;
  for(i=0; i < _DIMENSION; i++)
  {
    for(j=0; j < _DIMENSION; j++)
    {
#ifdef __CPROVER
  #ifdef _FIXEDBV
      const control_floatt value=coeffs[i][j];
      verify_assume(value <= impl.max);
      verify_assume(value >= impl.min);
  #else
      const controller_floatt value=coeffs[i][j];
      coeffs[i][j]=value;
  #endif
#else
      const control_floatt value=coeffs[i][j];
      if(value > impl.max) return 10;
      if(value < impl.min) return 10;
#endif  
    }
  }
  return 0;
}

int check_bits()
{
#ifdef __CPROVER 
  #ifndef _FIXEDBV
    verify_assume(impl.frac_bits<=_FRACTION_WIDTH);
  #else
    verify_assume((impl.frac_bits<=_CONTORL_RADIX_WIDTH) && (impl.int_bits+implD.int_bits<_CONTROL_FLOAT_WIDTH-_CONTORL_RADIX_WIDTH));
  #endif
  verify_assume(impl.int_bits != 0);
#else
  if (impl.int_bits == 0) return 10;
#endif
  return 0;
}

signed long int fxp_control_floatt_to_fxp(control_floatt value,struct implt impl)
{
  signed long int tmp;
  control_floatt ftemp=value * impl.fxp_one;
  tmp = ftemp;
  control_floatt residue=ftemp - tmp;
  if(value < _zero && (residue != _zero))
  {
    ftemp = ftemp - _one;
    tmp = ftemp;
  }
  return tmp;
}

control_floatt fxp_check(control_floatt value,struct implt impl)
{
#ifdef __CPROVER
  #ifdef _FIXEDBV
    control_floatt tmp_value=value;
    if (tmp_value < _zero) tmp_value=-tmp_value;
    verify_assume((~impl.max&tmp_value)==0);
    return value;
  #else
    const controller_floatt fwl_value=value;
    verify_assume(fwl_value!=0);
    return fwl_value;
  #endif
#else
  #ifdef _FIXEDBV
    value=fxp_control_floatt_to_fxp(value,impl);
    value/=impl.fxp_one;
  #endif
  return value;
#endif
}

void fxp_check_coeffs(vectort f,struct implt impl)
{
  cnttype i;
#ifndef __CPROVER
  printf("checking coeffs\n");
#endif
  for(i=0; i < _DIMENSION; i++) f[i]=fxp_check(f[i],impl);
}

#ifdef USE_XTRANSFORM
int validation_cbmc()
{
  cnttype i;
  boundcbmcController();
  cnttype result;
#ifdef _USE_OBSERVER
  result = check_vector_bounds(observer_cbmc,implLW);  
  if (result != 0) return result;
#endif
  return check_vector_bounds(controller_cbmc,implKT);  
}
#else
int validation()
{
  cnttype i;
  fxp_check_coeffs(controller,implK);
  boundController();
  cnttype result;
#ifdef _USE_OBSERVER
  fxp_check_coeffs(observer,implL);
  result = check_vector_bounds(observer,implL);  
  if (result != 0) return result;
#endif
  return check_vector_bounds(controller,implK);  
}
#endif