control_floatt _dbl_max;
control_floatt _dbl_min;
signed long int _fxp_max;
signed long int _fxp_min;
signed long int _fxp_one;
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
void get_bounds()
{
  cnttype i;
#ifdef _FIXEDBV
  verify_assume((impl.int_bits+impl.frac_bits) <= 32);
  if(impl.frac_bits >= 31)
    _fxp_one = 2147483647l;
  else
  _fxp_one = (1 << impl.frac_bits);
  _fxp_max = (1 << (impl.int_bits+impl.frac_bits -1))-1;
  _fxp_min = -_fxp_max;
#ifdef __CPROVER
  int one=1;
  controller_floatt lsb=*(controller_floatt*)&one;
  _dbl_lsb=(control_floatt)lsb;
  _dbl_max = *(controller_floatt*)&_fxp_max;
#else
  _dbl_lsb=_one/_fxp_one;
  _dbl_max = _fxp_max*_dbl_lsb;
#endif
#else
  verify_assume((_EXP_BITS>_FRAC_BITS) && (_EXP_BITS<= 32));
  signed long int exp=(1 << (_EXP_BITS -_FRAC_BITS -1));
  _dbl_max=_one;
  for (i=0;i<exp;i++)
  {
    _dbl_max*=2;
  }
  exp=1 << _FRAC_BITS;
  _dbl_lsb=_one/_dbl_max;
  _dbl_max*=_one-_one/exp;
#endif
  _dbl_min = -_dbl_max;
#ifndef __CPROVER
  printf("min=%f\n",_dbl_min);
  printf("max=%f\n",_dbl_max);
#endif
#ifdef __CHECK_FP
  _transform_error=2*_dbl_lsb*_DIMENSION*_DIMENSION;
  _sum_error=2*_transform_error*_DIMENSION;
#else
  _transform_error=0;
  _sum_error=0;
#endif
}

int check_vector_bounds(vectort coeffs)
{
  cnttype i;
  for( i=0; i < _DIMENSION; i++)
  {
#ifdef __CPROVER 
  #ifdef _FIXEDBV
    const control_floatt value=coeffs[i];
    verify_assume(value <= _dbl_max);
    verify_assume(value >= _dbl_min);
  #else
    const controller_floatt value=coeffs[i];
    coeffs[i]=value;
  #endif
#else
    printf("checking bounds\n");
    const control_floatt value=coeffs[i];
  #ifdef _FIXEDBV
    verify_assume(value <= _dbl_max);
    verify_assume(value >= _dbl_min);
  #endif
    if(value > _dbl_max) return 10;
    if(value < _dbl_min) return 10;
#endif  
  }
  return 0;
}

int check_matrix_bounds(matrixt coeffs)
{
  cnttype i,j;
  for(i=0; i < _DIMENSION; i++)
  {
    for(j=0; j < _DIMENSION; j++)
    {
#ifdef __CPROVER
  #ifdef _FIXEDBV
      const control_floatt value=coeffs[i][j];
      verify_assume(value <= _dbl_max);
      verify_assume(value >= _dbl_min);
  #else
      const controller_floatt value=coeffs[i][j];
      coeffs[i][j]=value;
  #endif
#else
      const control_floatt value=coeffs[i][j];
      if(value > _dbl_max) return 10;
      if(value < _dbl_min) return 10;
#endif  
    }
  }
  return 0;
}

int check_bits()
{
#ifdef __CPROVER 
  #ifndef _FIXEDBV
    verify_assume((impl.frac_bits<=_FRACTION_WIDTH) && (impl.int_bits+impl.mult_bits<_EXPONENT_WIDTH));
  #else
    verify_assume((impl.frac_bits<=_CONTORL_RADIX_WIDTH) && (impl.int_bits+impl.mult_bits<_CONTROL_FLOAT_WIDTH));
  #endif
  verify_assume(impl.int_bits != 0);
#else
  if (impl.int_bits == 0) return 10;
#endif
  return 0;
}

signed long int fxp_control_floatt_to_fxp(control_floatt value)
{
  signed long int tmp;
  control_floatt ftemp=value * _fxp_one;
  tmp = ftemp;
  control_floatt residue=ftemp - tmp;
  if(value < _zero && (residue != _zero))
  {
    ftemp = ftemp - _one;
    tmp = ftemp;
  }
  return tmp;
}

control_floatt fxp_check(control_floatt value)
{
#ifdef __CPROVER
  #ifdef _FIXEDBV
    control_floatt tmp_value=value;
    if (tmp_value < _zero) tmp_value=-tmp_value;
    verify_assume((~_dbl_max&tmp_value)==0);
    return value;
  #else
    const controller_floatt fwl_value=value;
    verify_assume(fwl_value!=0);
    return fwl_value;
  #endif
#else
  #ifdef _FIXEDBV
    value=fxp_control_floatt_to_fxp(value);
    value/=_fxp_one;
  #endif
  return value;
#endif
}

void fxp_check_coeffs(vectort f)
{
  cnttype i;
  for(i=0; i < _DIMENSION; i++) f[i]=fxp_check(f[i]);
}

int validation()
{
  cnttype i;
  control_floatt max=0;
  for (i=0;i<_DIMENSION;i++) {
    if (plant.coeffs[i]>max) max=plant.coeffs[i];
    else if (-plant.coeffs[i]>max) max=-plant.coeffs[i];
  }
  unsigned int max_int=max;
  cnttype mult_bits=12;
  while (max_int>0) 
  {
    mult_bits++;
    max_int>>=1;
  }
  fxp_check_coeffs(controller);
  boundController();
  cnttype result = check_bits();
  if (result != 0) return 10;
#ifdef _USE_OBSERVER
  fxp_check_coeffs(observer);
//  result = check_vector_bounds(observer);  
  if (result != 0) return result;
#endif
  return check_vector_bounds(controller);  
}
