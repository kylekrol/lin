/** @file lin/substitutions/backward_substitution.hpp
 *  @author Kyle Krol
 *  Defines a backward substitution algorithm for tensor types. */

// TODO : Documentation for this entire fil

#ifndef LIN_SUBSTITUTIONS_BACKWARD_SUBSTITUTION_HPP_
#define LIN_SUBSTITUTIONS_BACKWARD_SUBSTITUTION_HPP_

#include "../core.hpp"
#include "../references.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @struct can_backward_sub */
template <class C, class D, class E>
struct can_backward_sub : conjunction<
    have_same_elements<C, D, E>,
    is_square<C>,
    can_multiply<C, D>,
    have_same_dimensions<D, E>
  > { };

}  // namespace internal

/** @fn backward_sub */
template <class C, class D, class E, std::enable_if_t<
    internal::can_backward_sub<C, D, E>::value, size_t> = 0>
constexpr int backward_sub(internal::Mapping<C> const &U, internal::Mapping<D> &X,
    internal::Mapping<E> const &Y);

/** @fn backward_sub */
template <class C, class D, class E, std::enable_if_t<
    internal::can_backward_sub<C, D, E>::value, size_t> = 0>
constexpr int backward_sub(internal::Mapping<C> const &U, internal::Base<D> &X,
    internal::Mapping<E> const &Y);

}  // namespace lin

#include "inl/backward_substitution.inl"

#endif
