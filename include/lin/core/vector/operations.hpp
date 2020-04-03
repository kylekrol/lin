/** @file lin/core/tensor/operations.hpp
 *  @author Kyle Krol
 *  Defines operations that can be done on all vector types. */

// TODO : Documentation for the norm function

#ifndef LIN_CORE_VECTOR_OPERATIONS_HPP_
#define LIN_CORE_VECTOR_OPERATIONS_HPP_

#include "../tensor/stream.hpp"
#include "../tensor/operations.hpp"
#include "../traits.hpp"

#include "vector.hpp"

#include <cmath>
#include <type_traits>  // Move this out of here

namespace lin {
namespace internal {

/** @struct can_cross
 *  Tests if two vectors can be crossed with eachother. */
template <class C, class D, typename = void>
struct can_cross;

/** @struct can_dot
 *  Tests if two vectors can be dotted with eachother. */
template <class C, class D, typename = void>
struct can_dot;

/** @struct can_norm */
template <class C, typename = void>
struct can_norm;

}  // namespace internal

/** @fn cross
 *  Calculates the cross product of two vectors. The return type will have
 *  identical dimensions to the first argument and an element type determined
 *  by multiplying the first argument's element type with the second's. */
template <class C, class D, internal::enable_if_t<internal::can_cross<C, D>::value, size_t> = 0>
constexpr auto cross(internal::Stream<C> const &u, internal::Stream<D> const &d);

/** @fn dot
 *  Calculates the inner product of two vectors. The return type is the same as
 *  the result of multiplying the first stream's element type with the second
 *  stream's element type. */
template <class C, class D, internal::enable_if_t<internal::can_dot<C, D>::value, size_t> = 0>
constexpr auto dot(internal::Stream<C> const &u, internal::Stream<D> const &v);

/** @fn norm
 *  Calculates the norm of a vector. */
template <class C, internal::enable_if_t<internal::can_norm<C>::value, size_t> = 0>
constexpr typename C::Traits::Elem norm(internal::Stream<C> const &u);

}  // namespace lin

#include "inl/operations.inl"

#endif
