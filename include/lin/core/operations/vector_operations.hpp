/** @file lin/core/operations/vector_operations.hpp
 *  @author Kyle Krol
 *  Defines all vector operations included with the core module. */

// TODO : Documentation for this entire file
// TODO : Clean up the interface a bit if possible

#ifndef LIN_CORE_OPERATIONS_VECTOR_OPERATIONS_HPP_
#define LIN_CORE_OPERATIONS_VECTOR_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "../types/stream.hpp"
#include "../types/vector.hpp"
#include "functors.hpp"
#include "tensor_operations.hpp"

#include <cmath>
#include <type_traits> 

namespace lin {
namespace internal {

/** @struct can_cross */
template <class C, class D>
struct can_cross : conjunction<
    have_same_vector_dimensions<C, D, Vector3f>,
    is_detected<multiply::expression, _traits_elem_t<C>, _traits_elem_t<D>>
  > { };

/** @struct can_dot */
template <class C, class D>
struct can_dot : conjunction<
    have_same_vector_dimensions<C, D>,
    is_detected<multiply::expression, _traits_elem_t<C>, _traits_elem_t<D>>
  > { };

/** @struct can_norm */
template <class C>
struct can_norm : is_vector<C> { };

}  // namespace internal

/** @fn cross */
template <class C, class D, std::enable_if_t<internal::can_cross<C, D>::value, size_t> = 0>
constexpr auto cross(internal::Stream<C> const &u, internal::Stream<D> const &d);

/** @fn dot */
template <class C, class D, std::enable_if_t<internal::can_dot<C, D>::value, size_t> = 0>
constexpr auto dot(internal::Stream<C> const &u, internal::Stream<D> const &v);

/** @fn norm */
template <class C, std::enable_if_t<internal::can_norm<C>::value, size_t> = 0>
constexpr auto norm(internal::Stream<C> const &u) {
  return std::sqrt(fro(u));
}
}  // namespace lin

#include "inl/vector_operations.inl"

#endif
