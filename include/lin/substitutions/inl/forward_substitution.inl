/** @file lin/substitutions/inl/forward_substitution.inl
 *  @author Kyle Krol
 *  See %lin/substitutions/forward_substitution.hpp for more information. */

#include "../forward_substitution.hpp"

namespace lin {

// Source: https://algowiki-project.org/en/Forward_substitution
template <class C, class D, class E, std::enable_if_t<
    internal::can_forward_sub<C, D, E>::value, size_t>>
constexpr int forward_sub(internal::Mapping<C> const &L, internal::Mapping<D> &X,
    internal::Mapping<E> const &Y) {
  LIN_ASSERT(L.rows() == L.cols() /* L isn't square in forward_sub(...) */);
  LIN_ASSERT(L.cols() == Y.rows() /* Y rows don't match in forward_sub(...) */);
  LIN_ASSERT(Y.rows() == X.rows() /* X rows don't match in forward_sub(...) */);
  LIN_ASSERT(Y.cols() == X.cols() /* X cols don't match in forward_sub(...) */);

  // Useful traits information
  constexpr size_t C_max_cols = C::Traits::max_cols;
  constexpr size_t E_cols     = E::Traits::cols;
  constexpr size_t E_max_rows = E::Traits::max_rows;
  constexpr size_t E_max_cols = E::Traits::max_cols;

  // X(0, :)
  lin::ref_row(X, 0) = lin::ref_row(Y, 0) / L(0, 0);

  // X(1:, :)
  for (size_t i = 1; i < X.rows(); i++)
    // X(i, :)
    lin::ref_row(X, i) = ( lin::ref_row(Y, i) - lin::ref<1, 0, 1, C_max_cols>(L, i, 0, 1, i) *
        lin::ref<0, E_cols, E_max_rows, E_max_cols>(X, 0, 0, i, X.cols())
      ) / L(i, i);

  return 0;
}

template <class C, class D, class E, std::enable_if_t<
    internal::can_forward_sub<C, D, E>::value, size_t>>
constexpr int forward_sub(internal::Mapping<C> const &L, internal::Base<D> &X,
    internal::Mapping<E> const &Y) {
  X.resize(Y.rows(), Y.cols());
  return forward_sub(L, static_cast<internal::Mapping<D> &>(X), Y);
}
}  // namespace lin
