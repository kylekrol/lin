/** @file lin/substitutions/forward_substitution.hpp
 *  @author Kyle Krol
 *  Defines a backward substitution algorithm for tensor types. */

#ifndef LIN_SUBSTITUTIONS_FORWARD_SUBSTITUTION_HPP_
#define LIN_SUBSTITUTIONS_FORWARD_SUBSTITUTION_HPP_

#include "../core.hpp"
#include "../references.hpp"
#include "../generators/constants.hpp"

namespace lin {
namespace internal {

template <class C, class D, class E>
struct can_forward_sub : conjunction<
    have_same_elements<C, D, E>,
    is_square<C>,
    can_multiply<C, D>,
    have_same_dimensions<D, E>
  > { };

}  // namespace internal

/** @fn forward_sub */
template <class C, class D, class E, std::enable_if_t<
    internal::can_forward_sub<C, D, E>::value, size_t> = 0>
constexpr int forward_sub(internal::Base<C> const &L, internal::Base<D> &X,
    internal::Base<E> const &Y);

/** @fn forward_sub */
template <class C, class D, class E, std::enable_if_t<
    internal::can_forward_sub<C, D, E>::value, size_t> = 0>
constexpr int forward_sub(internal::Base<C> const &L, internal::Tensor<D> &X,
    internal::Base<E> const &Y);

}  // namespace lin

#include "inl/forward_substitution.inl"

#endif
