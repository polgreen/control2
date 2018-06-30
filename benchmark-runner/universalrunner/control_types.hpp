#ifndef CONTROL_TYPES_HPP_
#define CONTROL_TYPES_HPP_

#include <boost/numeric/interval.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#ifndef FLOAT
#include <cnl/fixed_point.h>
#else
#include <half.hpp>
#endif

typedef double __plant_precisiont;

#define CONTROL_WIDTH (INT_BITS + FRAC_BITS)

#ifndef FLOAT

#if CONTROL_WIDTH == 8u
typedef uint8_t __controller_base_typet;
#elif CONTROL_WIDTH == 16u
typedef uint16_t __controller_base_typet;
#elif CONTROL_WIDTH == 32u
typedef uint32_t __controller_base_typet;
#elif CONTROL_WIDTH == 64u
typedef uint32_t __controller_base_typet;
#else
#error "Unsupported controller width."
#endif

#else

#if CONTROL_WIDTH == 16u
typedef half_float::half __controller_base_typet;
#elif CONTROL_WIDTH == 32u
typedef float __controller_base_typet;
#elif CONTROL_WIDTH == 64u
typedef double __controller_base_typet;
#else
#error "Unsupported controller width."
#endif

#endif

class __controller_precisiont;

typedef boost::numeric::interval<__plant_precisiont> __plant_typet;
typedef boost::numeric::interval<__controller_precisiont> __controller_typet;
#define interval(x) boost::numeric::interval<decltype(x)>(x)

typedef boost::numeric::ublas::matrix<__plant_typet> __plant_matrixt;
typedef boost::numeric::ublas::matrix<__controller_typet> __controller__matrixt;

#endif /* CONTROL_TYPES_HPP_ */
