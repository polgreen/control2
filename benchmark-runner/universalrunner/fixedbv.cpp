#include "fixedbv.h"

__controller_precisiont::__controller_precisiont() :
    value(0u)
{
}

__controller_precisiont __controller_precisiont ::operator-() const
{
  return -value;
}

__controller_precisiont::operator __plant_precisiont() const
{
  return static_cast<__plant_precisiont >(value);
}

bool operator<(const __controller_precisiont &lhs,
    const __controller_precisiont &rhs)
{
  return lhs.value<rhs.value;
}

bool operator>(const __controller_precisiont &lhs,
    const __controller_precisiont &rhs)
{
  return lhs.value>rhs.value;
}

__controller_precisiont operator*(const __controller_precisiont &lhs,
    const __controller_precisiont &rhs)
{
  return multiply(lhs.value, rhs.value);
}

__controller_precisiont operator+(const __controller_precisiont &lhs,
    const __controller_precisiont &rhs)
{
  return lhs.value + rhs.value;
}
