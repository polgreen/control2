#include <cnl/fixed_point.h>
#include <iostream>
#include <limits>

typedef cnl::fixed_point<int16_t, -11u> __fxp_precision;


int main(void)
{
  std::cout.precision(1000); 
  double value; 
  __fxp_precision fxp_value;
   std::cout<<"epsilon " << std::numeric_limits<double>::epsilon() << ", size of long double  " <<sizeof(long double)<<std::endl ; 
   value = 0.49999999999999988897769753748434595763683319091796875;
   std::cout <<"Value as literal: " << value <<std::endl;
   value = 0.5*(1+std::numeric_limits<double>::epsilon());
   std::cout << "value as calculated with numeric limits: " << value << std::endl;
  
 
   fxp_value=static_cast<cnl::fixed_point<int16_t, -8> > (value);
   std::cout<<"value 1: "<< value<<" " << fxp_value<<std::endl; 
   value = 0.5*(1-std::numeric_limits<double>::epsilon());
   fxp_value=static_cast<cnl::fixed_point<int16_t, -8> > (value);
   std::cout<<"value 2: "<< value<<" " << fxp_value<<std::endl;    
}
