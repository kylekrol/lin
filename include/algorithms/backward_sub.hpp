// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_ALGORITHMS_BACKWARD_SUB_HPP_
#define LIN_INCLUDE_ALGORITHMS_BACKWARD_SUB_HPP_

#include "../core/core.hpp"

#include <cassert>
#include <type_traits>

// TODO : Evaluate again whether or not U and Y could be of type
//        internal::Stream<...>

namespace lin
{
namespace internal
{

/** @struct can_backward_sub
 *  True if the backward substitution function can be called on the specified
 *  template and false otherwise. To be compatible, _X and _Y must have
 *  compatible traits. Furthermore, the product of _U and _X must exist and
 *  result in the same traits as _Y. */
template <class _U, class _X, class _Y>
struct can_backward_sub
: public std::integral_constant<bool, (
    are_traits_equal<_X, _Y>::value && are_traits_equal<Multiply<_U, _X>, _Y>::value
  )> { };

}  // namespace internal

/** @fn backward_sub
 *  @param[in] U n by n upper-right triangular matrix.
 *  @param[out] X n by m matrix storing the solution (can be a vector).
 *  @param[in] Y n by m matrix (can be a vector).
 * 
 *  Solves the following linear system of equations U * X = Y where U and Y are
 *  given and U is knows to be an upper triangular matrix.
 * 
 *  REQUIRES: X is already resized to proper dimensions. */
template <class _U, class _X, class _Y,
    typename std::enable_if<internal::can_backward_sub<_U, _X, _Y>::value, size_t>::type = 0>
constexpr int backward_sub(internal::Base<_U> const &U, internal::Base<_X> &X,
    internal::Base<_Y> const &Y);

/** @fn backward_sub
 *  @param[in] U n by n upper-right triangular matrix.
 *  @param[out] X n by m matrix storing the solution (can be a vector).
 *  @param[in] Y n by m matrix (can be a vector).
 * 
 *  Solves the following linear system of equations U * X = Y where U and Y are
 *  given and U is knows to be an upper triangular matrix.
 * 
 *  Will resize X is required. */
template <class _U, class _X, class _Y,
    typename std::enable_if<internal::can_backward_sub<_U, _X, _Y>::value, size_t>::type = 0>
constexpr int backward_sub(internal::Base<_U> const &U, internal::Tensor<_X> &X,
    internal::Base<_Y> const &Y);

}  // namespace lin

#include "inl/backward_sub.inl"

#endif
