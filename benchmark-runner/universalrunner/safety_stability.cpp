#define INTERVAL 1

#include "benchmark.h"
#include "fixedbv.h"

#include <boost/numeric/ublas/lu.hpp>

#include <stdlib.h>

#define INITIALSTATE_UPPERBOUND (__plant_precisiont)0.5
#define INITIALSTATE_LOWERBOUND (__plant_precisiont)-0.5
#define SAFE_STATE_UPPERBOUND (__plant_precisiont)1.0
#define SAFE_STATE_LOWERBOUND (__plant_precisiont)-1.0

static int NUMBERLOOPS;
static __plant_matrixt _controller_states(NSTATES, 1);
static __controller__matrixt K_fxp(NSTATES, 1);
static __plant_typet _state_poles[256][8];

static __plant_matrixt _controller_A_matrix(NSTATES, NSTATES);
static __plant_matrixt _controller_B_matrix(NSTATES, 1);

static bool check_safety()
{
  for(int k=0; k<NUMBERLOOPS; k++)
  {
    // inputs = -K*states
    const __controller__matrixt inputs=prod(-K_fxp,
        static_cast<__controller__matrixt >(_controller_states));

    for(int k=0; k<NSTATES; k++)
    {
      const __controller_typet &entry=inputs(k, 0);
      assert(entry.upper()<=INPUT_UPPERBOUND &&entry.lower()>=INPUT_LOWERBOUND);
    }

    // states = A*states + B*inputs
    _controller_states=prod(_controller_A_matrix, _controller_states)
        +prod(_controller_B_matrix, static_cast<__plant_matrixt >(inputs));

    printf("States: {%f %f}, {%f %f}, {%f %f}\n",
        _controller_states(0, 0).lower(), _controller_states(0, 0).upper(),
        _controller_states(1, 0).lower(), _controller_states(1, 0).upper(),
        _controller_states(2, 0).lower(), _controller_states(2, 0).upper());

    for(int i=0; i<NSTATES; i++)
    {
      if(_controller_states(i, 0).upper()>SAFE_STATE_UPPERBOUND
          ||_controller_states(i, 0).lower()<SAFE_STATE_LOWERBOUND)
      {
        return false;
      }
    }
  }
  return true;
}

static void safety_stability()
{
  assert(check_safety());
}

int main(int argc, char * const argv[])
{
#if NSTATES > 1

  for(int i=0; i<NSTATES; i++)
  {
    _controller_B_matrix(i, 1)=_controller_B[i];
    for(int j=0; j<NSTATES; j++)
      _controller_A_matrix(i, j)=_controller_A[i][j];
  }

  NUMBERLOOPS=atoi(argv[1]);
  for(int i=0; i<NSTATES; ++i)
    K_fxp(i, 0)=interval(atof(argv[2+i]));

  int npoles=1<<NSTATES;

  for(int i=0; i<npoles; i++)
    for(int j=0; j<NSTATES; j++)
      if(i>>j&1) _state_poles[i][j]=interval(INITIALSTATE_UPPERBOUND);
      else _state_poles[i][j]=interval(INITIALSTATE_LOWERBOUND);

  for(int poleIndex=0; poleIndex<npoles; ++poleIndex)
  {
    for(int stateIndex=0; stateIndex<NSTATES; ++stateIndex)
      _controller_states(stateIndex, 0)=_state_poles[poleIndex][stateIndex];
    safety_stability();
  }

#endif

  return 0;
}
