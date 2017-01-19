#include <stdio.h>
struct implt
{
  int int_bits;
  int frac_bits;
};
struct implt impl={ .int_bits=14, .frac_bits=2};

#include "intervals.h"

int main()
{
  struct intervalt x,y,z;
  x.low=2.1;
  x.high=3.7;
  y.low=-2;
  y.high=1;
  get_bounds();
  printf("dbl_lsb=%f\n",_dbl_lsb);
  printf("fxp_one=%d\n",(int)_fxp_one);
  printf("x=[%f,%f]\n",x.low,x.high);
  printf("y=[%f,%f]\n",y.low,y.high);
  z=mult(x,x);
  printf("x*x=[%f,%f]\n",z.low,z.high);
  z=add(x,x);
  printf("x+x=[%f,%f]\n",z.low,z.high);
  z=sub(x,y);
  printf("x-y=[%f,%f]\n",z.low,z.high);
  z=mult(x,y);
  printf("x*y=[%f,%f]\n",z.low,z.high);
  z=posDiv(x,x);
  printf("x/x=[%f,%f]\n",z.low,z.high);
  fxp_interval_check(&x);
  printf("fxp_x=[%f,%f]\n",x.low,x.high);
  return 0;
}
