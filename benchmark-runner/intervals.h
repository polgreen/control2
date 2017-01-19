//Warning! this file assumes rounding to -\infty

//typedef __CPROVER_fixedbv[32][16] __CPROVER_EIGEN_fixedbvt;
typedef double __CPROVER_EIGEN_fixedbvt;
//typedef __CPROVER_fixedbv[INT_BITS+FRAC_BITS][FRAC_BITS] __CPROVER_fxp_t;

#ifdef __CPROVER
typedef int64_t __CPROVER_fxp_t;
typedef int64_t fxp_t;
#endif

typedef __CPROVER_EIGEN_fixedbvt control_floatt; //added in by EP
typedef __CPROVER_EIGEN_fixedbvt control_typet;  //added in by EP
control_typet _zero = 0; //added in by EP
control_typet _one = 1;

struct intervalt
{
  control_typet low;
  control_typet high;
};

control_typet _dbl_max;
control_typet _dbl_min;
signed long int _fxp_max;
signed long int _fxp_min;
signed long int _fxp_one;
control_typet _dbl_lsb;

void get_bounds()
{
  if(impl.frac_bits >= 31)
    _fxp_one = 2147483647l;
  else
    _fxp_one = (1 << impl.frac_bits);
  _dbl_lsb=_one/(1 << impl.frac_bits);
  _fxp_min = -(1 << (impl.frac_bits + impl.int_bits -1));
  _fxp_max = (1 << (impl.frac_bits + impl.int_bits-1))-1;
  _dbl_max = (1 << (impl.int_bits-1))-1;//Integer part
  _dbl_max += (_one-_dbl_lsb);//Fractional part
  _dbl_min = -_dbl_max;
}

signed long int fxp_control_floatt_to_fxp(control_typet value)
{
  signed long int tmp;
  control_typet ftemp=value * _fxp_one;
  tmp = ftemp;
  control_typet residue=ftemp - tmp;
  if(value < _zero && (residue != _zero))
  {
    ftemp = ftemp - _one;
    tmp = ftemp;
  }
  return tmp;
}

void fxp_check(control_typet *value)
{
#ifdef __CPROVER
  control_typet tmp_value=*value;
  if (tmp_value < _zero) tmp_value=-tmp_value;
  verify_assume((~_dbl_max&tmp_value)==0);
#else
  *value=fxp_control_floatt_to_fxp(*value);
  *value/=_fxp_one;
#endif
}

void fxp_interval_check(struct intervalt *value)
{
  fxp_check(&(value->low));
  fxp_check(&(value->high));
  value->high+=_dbl_lsb;
}

#define add(z,x,y) z.low=x.low+y.low;z.high=x.high+y.high
#define sub(z,x,y) z.low=x.low-y.high;z.high=x.high-y.low

inline struct intervalt mult(struct intervalt x,struct intervalt y)
{
  struct intervalt z;
  z.low=x.low*y.low;
  z.high=(-x.low)*y.low;
  z.high=-z.high;
  control_floatt second=x.low*y.high;
  control_floatt third=x.high*y.low;
  control_floatt fourth=x.high*y.high;

  if (second<z.low) z.low=second;
  else if (second>=z.high)
  {  
    z.high=(-x.low)*y.high;
    z.high=-z.high;
  }
  if (third<z.low) z.low=third;
  else if (third>=z.high) 
  {
    z.high=(-x.high)*y.low;
    z.high=-z.high;
  }
  if (fourth<z.low) z.low=fourth;
  else if (fourth>=z.high) 
  {
    z.high=(-x.high)*y.high;
    z.high=-z.high;
  }
  return z;
}

inline struct intervalt posDiv(struct intervalt x, struct intervalt y)
{
  struct intervalt z;
  if (x.high<=_zero)
  {
    z.high=(-x.high)/y.high;
    z.high=-z.high;
    z.low=x.low/y.low;
  }
  else if (x.low>=_zero)
  {
    z.low=x.low/y.high;
    z.high=(-x.high)/y.low;
    z.high=-z.high;
  }
  else
  {
    z.low=x.low/y.low;
    z.high=(-x.high)/y.low;
    z.high=-z.high;
  }
  return z;
}