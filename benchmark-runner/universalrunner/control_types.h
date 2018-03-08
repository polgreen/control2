/*
 * control_types.h
 *
 *  Created on: 18 Jan 2017
 *      Author: elipol
 */

#define SINGLE_PREC

#ifndef CONTROL_TYPES_H_
#define CONTROL_TYPES_H_

#ifndef FIXEDBV // WARNING!!! HARD-CODED TO USE SINGLE PRECISION FLOATING POINT FOR CONTROLLER
   #define  _CONTROLLER_FLOAT_BITS 32
   #define  _CONTROLLER_MANTISSA_BITS 23
#endif



#ifdef CPROVER
    #ifndef FLOAT
      #ifdef INTERVAL
     //we never use interval and cprover
        __CPROVER_assert(0,"error");
      #else
        typedef __CPROVER_fixedbv[_PLANT_TOTAL_BITS][_PLANT_RADIX_BITS] __plant_precisiont;
        typedef __plant_precisiont __plant_typet;
        typedef __CPROVER_fixedbv[INT_BITS+FRAC_BITS][FRAC_BITS] __controller_precisiont;
        typedef  __controller_precisiont __controller_typet;
        #define plant_cast(x) ((__plant_typet)x)
        #define controller_cast(x) ((__controller_typet)x)
        #define interval(x) x
      #endif
  #else
    #ifdef INTERVAL
        //we never use interval and cprover
        __CPROVER_assert(0,"error");
    #else
       typedef __CPROVER_floatbv[_PLANT_TOTAL_BITS][_PLANT_MANTISSA_BITS] __plant_precisiont;
       typedef __plant_precisiont __plant_typet;
       typedef  __controller_precisiont __controller_typet;
       #define plant_cast(x) ((__plant_typet)x)
       #define controller_cast(x) ((__controller_typet)x)
      #define interval(x) x
    #endif
#endif
#else
  #ifndef FLOAT
     #ifdef INTERVAL
       typedef double __plant_precisiont;
        #include "intervals.h"
       typedef struct intervalt __plant_typet;
       typedef double __controller_precisiont; //fixed point arithmetic is implemented using doubles
       typedef struct intervalt __controller_typet;
       #define interval(x) interval_cast(x)
     #endif
    #ifndef INTERVAL
       typedef double __plant_precisiont;
       typedef __plant_precisiont __plant_typet;
       typedef double __controller_precisiont; //fixed point arithmetic is implemented using doubles
       typedef __controller_precisiont __controller_typet;
       #define interval(x) (x)
       #define plant_cast(x) x
       #define controller_cast(x) x
    #endif
  #else
    #ifdef INTERVAL
       typedef double __plant_precisiont;
        #include "float_interval.h"
       typedef struct intervalt __plant_typet;
	#ifdef SINGLE_PREC
       typedef float __controller_precisiont;
	#elif DOUBLE_PREC
       typedef double __controller_precisiont;
	#else
	  #error unsupported precisions
	#endif
       typedef struct intervalt __controller_typet;
      	  #define interval(x) interval_cast(x)
     #endif // end of interval def
  #endif //end of float def
#endif // end of not cprover def

#endif /* CONTROL_TYPES_H_ */
