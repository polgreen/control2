/*
 * control_types.h
 *
 *  Created on: 18 Jan 2017
 *      Author: elipol
 */

#ifndef CONTROL_TYPES_H_
#define CONTROL_TYPES_H_

#ifdef CPROVER
    #ifdef INTERVAL
      #include "intervals.h"
      typedef   __CPROVER_fixedbv[24][12] __plant_precisiont;
      typedef   struct intervalt __plant_typet;
      typedef   __CPROVER_fixedbv[24][12] __controller_precisiont;
      typedef   struct intervalt __controller_typet;
    #else
      typedef __CPROVER_fixedbv[24][12] __plant_precisiont;
      typedef __plant_precisiont __plant_typet;
      typedef __CPROVER_fixedbv[INT_BITS+FRAC_BITS][FRAC_BITS] __controller_precisiont;
      typedef  __controller_precisiont __controller_typet;
        #define plant_cast(x) ((__plant_typet)x)
        #define controller_cast(x) ((__controller_typet)x)
    #endif
/*#else
  #include "fixedpoint.h"
  #ifdef INTERVAL
     typedef double __plant_precisiont;
     typedef intervalt __plant_typet;
     typedef fxp_t __controller_precisiont;
     typedef intervalt __controller_typet;
   #else
     typedef double __plant_typet;
     typedef fxp_t __controller_typet;
      #define plant_cast(x) ((__plant_typet)x)
      #define controller_cast(x) ((__controller_typet)x)
   #endif*/
#endif

#endif /* CONTROL_TYPES_H_ */
