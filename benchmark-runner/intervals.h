
typedef double control_floatt; //added in by EP
typedef double control_typet;  //added in by EP
control_typet _zero = 0; //added in by EP

struct intervalt
{
  control_typet low;
  control_typet high;
};

#define add(z,x,y) z.low=x.low+y.low;z.high=x.high+y.high
#define sub(z,x,y) z.low=x.low-y.high;z.high=x.high-y.low

inline struct intervalt mult(struct intervalt x,struct intervalt y)
//inline void mult(intervalt z,intervalt x,intervalt y)
{
  struct intervalt z;
  z.low=x.low*y.low;
//  z.high=first;
  control_floatt second=x.low*y.high;
  control_floatt third=x.high*y.low;
  control_floatt fourth=x.high*y.high;

  if (second<z.low) z.low=second;
  else if (second>z.high) z.high=second;
  if (third<z.low) z.low=third;
  else if (third>z.high) z.high=third;
  if (fourth<z.low) z.low=fourth;
  else if (fourth>z.high) z.high=fourth;

  return z;
}

inline struct intervalt posDiv(struct intervalt x, struct intervalt y)
//inline void posDiv(intervalt z,intervalt x,intervalt y)
{
  struct intervalt z;
  if (x.high<=_zero)
  {
    z.high=x.high/y.high;
    z.low=x.low/y.low;
  }
  else if (x.low>=_zero)
  {
    z.low=x.low/y.high;
    z.high=x.high/y.low;
  }
  else
  {
    z.low=x.low/y.low;
    z.high=x.high/y.low;
  }
  return z;
}
