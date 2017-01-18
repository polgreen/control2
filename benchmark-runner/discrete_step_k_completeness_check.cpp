#include <Eigen/Eigenvalues>
#include <eigen3/unsupported/Eigen/MPRealSupport>
#include <mpfr.h>

using namespace Eigen;
using namespace std;
using namespace mpfr;

typedef mpreal realt;
typedef Matrix<realt, Dynamic, Dynamic> matrixt;
typedef Matrix<realt, Dynamic, 1> vectort;

#define EXIT_INCREASE_K 2
#define PRECISION 256u

int main(const int argc, const char * const argv[]) {
  const realt two = "2.0";
  const realt two_pi = const_pi() * two;
  const realt imaginary_offset = pow(two, -PRECISION/4);
  if (argc < 2) return EXIT_FAILURE;
  mpreal::set_default_prec(PRECISION);
  // TODO: Read A, B, K, K_SIZE
  matrixt A;
  matrixt B;
  vectort K;
  const realt K_SIZE = "0.0";
  matrixt result = A - B * K;
  EigenSolver<matrixt> eigenSpace(result);
  if (Success != eigenSpace.info())
    return EXIT_FAILURE;
  const EigenSolver<matrixt>::EigenvalueType eigenvalues = eigenSpace.eigenvalues();
  for (size_t i=0; i < eigenvalues.size(); ++i) {
    const realt imag_value = std::imag(eigenvalues[i]);
    if (imag_value <= imaginary_offset) continue;
    const realt angle = std::arg(eigenvalues[i]);
    const realt expected = two_pi / angle;
    if (expected > K_SIZE) return EXIT_INCREASE_K;
  }
  return EXIT_SUCCESS;
}
