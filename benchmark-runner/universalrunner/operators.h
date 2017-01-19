/*
 * operators.h
 *
 *  Created on: 18 Jan 2017
 *      Author: elipol
 */

#ifndef OPERATORS_H_
#define OPERATORS_H_

#define controller_mult(x,y) ((x) *(y))
#define mult(x,y) ( (x) * (y))
#define mult3(x,y,z) ((x) * (y) * (z))

#define abs(a) ( (a) < 0 ? -(a) : (a))
#define add(x,y) ( (x) + (y))
#define add3(x,y,z) ( (x) + (y) + (z))
#define lessthanequalto(x,y) ((x) <= (y))
#define greaterthan(x,y) ( (x) > (y))
#define lessthan(x,y) ((x) < (y))
#define zero(x) ((x) = 0)
#define div(x,y) ( (x) / (y))
#define sub(x,y) ( (x) - (y))




#endif /* OPERATORS_H_ */
