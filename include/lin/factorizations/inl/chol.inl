/** @file lin/factorizations/inl/chol.inl
 *  @author Kyle Krol
 *  See %lin/factorizations/chol.hpp for more information. */

#include "../chol.hpp"

namespace lin {

// Source: https://en.wikipedia.org/wiki/Cholesky_decomposition
template <class C, class D, std::enable_if_t<internal::can_chol<C, D>::value, size_t>>
constexpr int chol(internal::Base<C> const &A, internal::Base<D> &L) {
  LIN_ASSERT(A.rows() == A.cols());
  LIN_ASSERT(L.rows() == L.cols());
  LIN_ASSERT(A.rows() == L.rows());

  L = zeros<D>(L.rows(), L.cols());
  
  L(0, 0) = std::sqrt(A(0, 0));
  for (size_t i = 1; i < L.rows(); i++) {
    L(i, 0) = A(i, 0) / L(0, 0);
    for (size_t j = 1; j < i; j++)
      L(i, j) = (A(i, j) - dot(
          ref<1, 0, 1, C::Traits::MaxCols>(L, j, 0, 1, j), ref<1, 0, 1, C::Traits::MaxCols>(L, i, 0, 1, j)
        )) / L(j, j);
    L(i, i) = std::sqrt(A(i, i) - fro(ref<1, 0, 1, C::Traits::MaxCols>(L, i, 0, 1, i)));
  }

  return 0;
}
}  // namespace lin
