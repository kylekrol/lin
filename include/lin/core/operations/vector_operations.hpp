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

template <class C, class D>
struct can_cross : conjunction<
    have_same_vector_dimensions<C, D, Vector3f>,
    is_detected<multiply::expression, _elem_t<C>, _elem_t<D>>
  > { };

template <class C, class D>
struct can_dot : conjunction<
    have_same_vector_dimensions<C, D>,
    is_detected<multiply::expression, _elem_t<C>, _elem_t<D>>
  > { };

template <class C>
struct can_norm : is_vector<C> { };

}  // namespace internal

template <class C, class D, std::enable_if_t<internal::can_cross<C, D>::value, size_t> = 0>
constexpr auto cross(internal::Stream<C> const &u, internal::Stream<D> const &v) {

  typedef typename internal::multiply::template expression<internal::_elem_t<C>, internal::_elem_t<D>> T;

  return std::conditional_t<
      internal::is_col_vector<C>::value,
      Vector<T, internal::_vector_dims<C>::length, internal::_vector_dims<C>::max_length>,
      RowVector<T, internal::_vector_dims<C>::length, internal::_vector_dims<C>::max_length>>({
    u(1) * v(2) - u(2) * v(1),
    u(2) * v(0) - u(0) * v(2),
    u(0) * v(1) - u(1) * v(0)
  });
}

template <class C, class D, std::enable_if_t<internal::can_dot<C, D>::value, size_t> = 0>
constexpr auto dot(internal::Stream<C> const &u, internal::Stream<D> const &v) {
  LIN_ASSERT(u.size() == v.size());

  typedef internal::multiply::expression<internal::_elem_t<C>, internal::_elem_t<D>> T;

  T x = u(0) * v(0);
  for (size_t i = 1; i < u.size(); i++) x += u(i) * v(i);
  return x;
}

template <class C, std::enable_if_t<internal::can_norm<C>::value, size_t> = 0>
constexpr auto norm(internal::Stream<C> const &u) {
  return std::sqrt(fro(u));
}
}  // namespace lin

#endif
