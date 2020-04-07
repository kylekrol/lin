/** @file lin/substitutions/inl/backward_substitution.inl
 *  @author Kyle Krol
 *  See %lin/substitutions/backward_substitution.hpp for more information. */

#include "../backward_substitution.hpp"

namespace lin {

/** @fn backward_sub */
template <class C, class D, class E, std::enable_if_t<
    internal::can_backward_sub<C, D, E>::value, size_t>>
constexpr int backward_sub(internal::Base<C> const &U, internal::Base<D> &X,
    internal::Base<E> const &Y) {
  LIN_ASSERT(U.rows() == U.cols() /* U isn't square in backward_sub(...) */);
  LIN_ASSERT(U.cols() == Y.rows() /* Y rows don't match in backward_sub(...) */);
  LIN_ASSERT(Y.rows() == X.rows() /* X rows don't match in backward_sub(...) */);
  LIN_ASSERT(Y.cols() == X.cols() /* X cols don't match in backward_sub(...) */);

  typedef internal::traits<C> TU;
  typedef internal::traits<E> TY;

  // Solve for the last rows
  // It's trivially the last row of Y divided by the bottom right element of U
  const size_t m = U.rows() - 1;
  ref_row(X, m) = ref_row(Y, m) / U(m, m);

  // Solve for the other rows in descending order
  for (size_t n = m - 1;; n--) {
    ref_row(X, n) = (
            ref_row(Y, n) - (ref<1, 0, 1, TU::MaxRows>(U, n, n + 1, 1, m - n) * 
                ref<0, TY::Cols, TY::MaxRows, TY::MaxCols>(X, n + 1, 0, m - n, X.cols()))
        ) / U(n, n);
    if (n == 0) break;  // Must perform this check here for unsigned value
  }

  return 0;  // TODO : Return an actual error code
}

/** @fn backward_sub */
template <class C, class D, class E, std::enable_if_t<
    internal::can_backward_sub<C, D, E>::value, size_t>>
constexpr int backward_sub(internal::Base<C> const &U, internal::Tensor<D> &X,
    internal::Base<E> const &Y) {
  X.resize(Y.rows(), Y.cols());
  return backward_sub(U, static_cast<internal::Base<D> &>(X), Y);
}
}  // namespace lin
