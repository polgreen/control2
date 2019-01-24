
#define INTERVAL 1

#include "benchmark.h"
#include "fixedbv.h"
#include <limits>
#include <boost/numeric/ublas/lu.hpp>

#include <cstdlib>

#define INITIALSTATE_UPPERBOUND (__plant_precisiont)0.5
#define INITIALSTATE_LOWERBOUND (__plant_precisiont)-0.5
#define SAFE_STATE_UPPERBOUND (__plant_precisiont)1.5
#define SAFE_STATE_LOWERBOUND (__plant_precisiont)-1.5

static int NUMBERLOOPS;
static __plant_matrixt _controller_states(NSTATES, 1);
static __controller__matrixt K_fxp(1, NSTATES);
static __plant_typet _state_poles[256][8];

static __plant_matrixt _controller_A_matrix(NSTATES, NSTATES);
static __plant_matrixt _controller_B_matrix(NSTATES, 1);

template<class T>
std::string to_string(const boost::numeric::ublas::matrix<T> &matrix)
{
  std::ostringstream oss;
  oss.precision(10);
  for(size_t i=0; i < matrix.size1(); ++i)
  {
    for(size_t j=0; j< matrix.size2(); ++j)
      oss << '(' << matrix(i, j).lower() << ',' << matrix(i, j).upper() << ") ";
    oss << std::endl;
  }
  return oss.str();
}

static bool check_safety()
{
    std::cout << "Initial states: " << to_string(_controller_states) << std::endl;

  for(int k=0; k<NUMBERLOOPS; k++)
  {
    // inputs = -K*states
    const __controller__matrixt inputs=prod(-K_fxp,
        static_cast<__controller__matrixt >(_controller_states));

    std::cout<<"K "<< to_string(K_fxp) << std::endl;
//    std::cout<<" states " << to_string(_controller_states) << std::endl;    
    std::cout<<"inputs "<< to_string(inputs) << std::endl;
   
    for(size_t i=0; i<inputs.size1(); ++i)
      for(size_t j=0; j<inputs.size2(); ++j)
      {
        const __controller_typet &e=inputs(i, j);
        assert(e.upper()<=INPUT_UPPERBOUND &&e.lower()>=INPUT_LOWERBOUND);
      }
  
   
    // states = A*states + B*inputs
    _controller_states=prod(_controller_A_matrix, _controller_states)
        +prod(_controller_B_matrix, static_cast<__plant_matrixt >(inputs));

    std::cout << "States "<<k<<" :" << to_string(_controller_states) << std::endl;

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

boost::numeric::interval<__plant_precisiont> get_plant_interval(__plant_precisiont x)
{
  
  double epsilon_high = x *(std::numeric_limits<double>::epsilon()+1);
  double epsilon_low = x*(1 - std::numeric_limits<double>::epsilon());
  if(epsilon_high == epsilon_low)
    return boost::numeric::interval<__plant_precisiont>(epsilon_low); 
  else
  {
    if(epsilon_low < epsilon_high)
    {
       boost::numeric::interval<__plant_precisiont> interval_x(epsilon_low, epsilon_high);
      return interval_x;
    }
    else
    {
      boost::numeric::interval<__plant_precisiont> interval_x(epsilon_high, epsilon_low);
      return interval_x;
    }
  }
}

boost::numeric::interval<__plant_precisiont> get_plant_interval(__plant_typet x)
{
  double epsilon_high = x.upper()*(std::numeric_limits<double>::epsilon()+1);
  double epsilon_low = x.lower()*(1 - std::numeric_limits<double>::epsilon());
  
  if(epsilon_high == epsilon_low)
  {
    return boost::numeric::interval<__plant_precisiont>(epsilon_low);
  }
  else
  {
    if(epsilon_low < epsilon_high)
    {
      boost::numeric::interval<__plant_precisiont> interval_x(epsilon_low, epsilon_high);
      return interval_x;
    }
    else 
    {
      boost::numeric::interval<__plant_precisiont> interval_x(epsilon_high, epsilon_low);
      return interval_x;
    }
  }
}


int main(int argc, char * const argv[])
{
#if NSTATES > 1
std::cout.precision(10);
  for(int i=0; i<NSTATES; i++)
  {
    _controller_B_matrix(i, 0)=get_plant_interval(_controller_B[i]);
    for(int j=0; j<NSTATES; j++)
      _controller_A_matrix(i, j)=get_plant_interval(_controller_A[i][j]);
  }

  std::cout << "A: " << to_string(_controller_A_matrix) << std::endl;
  std::cout<< "B: "<< to_string(_controller_B_matrix) << std::endl;

  NUMBERLOOPS=atoi(argv[1]);
  
  for(int i=0; i<NSTATES; ++i)
    K_fxp(0, i)=get_plant_interval(atof(argv[2+i]));
  
  std::cout<<"K: "<< to_string(K_fxp)<<std::endl;
  

  int npoles=1<<NSTATES;
  
  for(int i=0; i<npoles; i++)
    for(int j=0; j<NSTATES; j++)
      if(i>>j&1)
      { 
        _state_poles[i][j]=get_plant_interval(INITIALSTATE_UPPERBOUND);
      }
      else
      { 
        _state_poles[i][j]=get_plant_interval(INITIALSTATE_LOWERBOUND);
      }  


  for(int poleIndex=0; poleIndex<npoles; ++poleIndex)
  {
    for(int stateIndex=0; stateIndex<NSTATES; ++stateIndex)
    {
      _controller_states(stateIndex, 0)=_state_poles[poleIndex][stateIndex];
//      std::cout<<" state " << _controller_states(stateIndex, 0).upper()<< " "<< _controller_states(stateIndex, 0).lower()<<std::endl;
    }
    safety_stability();
  }

#endif

  return 0;
}
