#include <cnl/fixed_point.h>
#include <iostream>
#include <limits>

typedef cnl::fixed_point<int16_t, -11u> __fxp_precision;


int main(void)
{
  std::cout.precision(100);
  long double value;
  __fxp_precision fxp_value;
  
   value = 0.5*(1+std::numeric_limits<double>::epsilon());

   fxp_value=static_cast<cnl::fixed_point<int16_t, -8> > (value);
   std::cout<<"value 1: "<< value<<" " << fxp_value<<std::endl; 
   value = 0.5*(std::numeric_limits<double>::epsilon() -1);
   fxp_value=static_cast<cnl::fixed_point<int16_t, -8> > (value);
   std::cout<<"value 2: "<< value<<" " << fxp_value<<std::endl;    
}
