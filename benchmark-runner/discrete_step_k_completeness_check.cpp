#include <Eigen/Eigenvalues>
#include <eigen3/unsupported/Eigen/MPRealSupport>
#include <mpfr.h>
#include <iostream>

typedef mpfr::mpreal realt;
typedef realt __CPROVER_EIGEN_fixedbvt;
#include "spec.h"

using namespace Eigen;
using namespace std;
using namespace mpfr;

#define EXIT_INCREASE_K 2
#define PRECISION 256
#define K_SIZE_ARG_INDEX 1u

typedef Matrix<realt, NSTATES, NSTATES> matrixt;

// TODO: Read actual K
//const realt _controller_K[] = { 0.0234375,-0.1328125, 0.00390625 };
const realt _controller_K[] = { 0.0234375,0.1328125, 0.00390625 };

int main(const int argc, const char * const argv[]) {
  const realt two = "2.0";
  const realt two_pi = const_pi() * two;
  const realt imaginary_offset = pow(two, -PRECISION/4);
  if (argc < 2) return EXIT_FAILURE;
  mpreal::set_default_prec(PRECISION);
  const realt K_SIZE = argv[K_SIZE_ARG_INDEX];
  Matrix<realt, NSTATES, NSTATES> A;
  for (size_t i = 0; i < NSTATES; ++i) {
    for (size_t j = 0; j < NSTATES; ++j) {
      A(i, j) = _controller_A[i][j];
    }
  }
  Matrix<realt, NSTATES, 1> B;
  for (size_t i = 0; i < NSTATES; ++i) {
    B(i) = _controller_B[i];
  }
  Matrix<realt, 1, NSTATES> K;
  for (size_t i = 0; i < NSTATES; ++i) {
    K[i] = _controller_K[i];
  }
  matrixt result = A - B * K;
  EigenSolver<matrixt> eigenSpace(result);
  if (Success != eigenSpace.info())
    return EXIT_FAILURE;
  const EigenSolver<matrixt>::EigenvalueType eigenvalues = eigenSpace.eigenvalues();
  cout << "num_eigenvalues: " << eigenvalues.size() << endl;
  for (size_t i=0; i < eigenvalues.size(); ++i) {
    cout << "eigenvalue: " << eigenvalues[i] << endl;
    const realt imag_value = std::imag(eigenvalues[i]);
    cout << "imag_value: " << imag_value << endl;
    cout << "imaginary_offset: " << imaginary_offset << endl;
    if (abs(imag_value) <= imaginary_offset) continue;
    const realt angle = std::arg(eigenvalues[i]);
    const realt expected = abs(two_pi / angle);
    cout << "expected_k_size=" << expected << endl;
    cout << "actual_k_size=" << K_SIZE << endl;
    if (expected > K_SIZE)
      return EXIT_INCREASE_K;
  }
  return EXIT_SUCCESS;
}
