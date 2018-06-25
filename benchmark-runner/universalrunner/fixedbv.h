#ifndef FIXEDBV_H_
#define FIXEDBV_H_

#define INTERVAL 1

#include "benchmark.h"

class __controller_precisiont
{
  cnl::fixed_point<__controller_base_typet, -FRAC_BITS> value;
public:
  __controller_precisiont();

  template<class T>
  __controller_precisiont(T value);

  __controller_precisiont operator-() const;

  operator __plant_precisiont() const;

  friend bool operator<(const __controller_precisiont &lhs,
      const __controller_precisiont &rhs);

  friend bool operator>(const __controller_precisiont &lhs,
      const __controller_precisiont &rhs);

  friend __controller_precisiont operator*(const __controller_precisiont &lhs,
      const __controller_precisiont &rhs);

  friend __controller_precisiont operator+(const __controller_precisiont &lhs,
      const __controller_precisiont &rhs);
};

#include "fixedbv.inc"

#endif /* FIXEDBV_H_ */
