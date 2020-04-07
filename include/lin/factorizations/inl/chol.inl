/** @file lin/factorizations/inl/chol.inl
 *  @author Kyle Krol
 *  See %lin/factorizations/chol.hpp for more information. */

#include "../chol.hpp"

namespace lin {

// Source: https://en.wikipedia.org/wiki/Cholesky_decomposition
// Cholesky–Banachiewicz algorithm
template <class C, std::enable_if_t<internal::can_chol<C>::value, size_t>>
constexpr int chol(internal::Base<C> &L) {
  LIN_ASSERT(L.rows() == L.cols() /* L must be square */);

  // Useful traits information
  constexpr size_t C_MaxCols = C::Traits::MaxCols;

  // Set above the main diagonal to zeros
  for (size_t i = 0; i < L.rows(); i++)
    for (size_t j = i + 1; j < L.cols(); j++) L(i, j) = 0;

  // L(0, 0)
  L(0, 0) = std::sqrt(L(0, 0));

  // L(1:, :)
  for (size_t i = 1; i < L.rows(); i++) {
    // L(i, 0)
    L(i, 0) = L(i, 0) / L(0, 0);

    // L(i, 1:i-1)
    for (size_t j = 1; j < i; j++)
      // L(i, j)
      L(i, j) = ( L(i, j) -
          dot(ref<1, 0, 1, C_MaxCols>(L, j, 0, 1, j), ref<1, 0, 1, C_MaxCols>(L, i, 0, 1, j))
        ) / L(j, j);

    // L(i, i)
    L(i, i) = std::sqrt(L(i, i) - fro(ref<1, 0, 1, C_MaxCols>(L, i, 0, 1, i)));
  }

  return 0;
}
}  // namespace lin
