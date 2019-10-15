// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_ALGORITHMS_QR_HPP_
#define LIN_INCLUDE_ALGORITHMS_QR_HPP_

#include "../core/core.hpp"

#include <cassert>
#include <type_traits>

namespace lin
{
namespace internal
{

/** @struct can_qr
 *  True if the qr factorization function can be called on the specified
 *  template and false otherwise. To be compatible, _M and _Q must have
 *  identical traits. Furthermore, the product of _Q and _R must exist and
 *  result in traits identical to _M - i.e. because M = Q * R. */
template <class _M, class _Q, class _R>
struct can_qr
: public std::integral_constant<bool, (
    are_traits_equal<_M, _Q>::value && are_traits_equal<_M, Multiply<_Q, _R>>::value
  )> { };

}  // namespace internal

/** @fn qr
 *  @param[in] M m by n matrix where m >= n.
 *  @param[out] Q Orthonormal m by n matrix where m >= n.
 *  @param[out] R Upper triangular n by n matrix.
 * 
 *  Calculates the QR factorization of M and stores the result in Q and R.
 * 
 *  REQUIRES: Q and R are already sized to the proper dimensions. */
template <class _M, class _Q, class _R,
    typename std::enable_if<internal::can_qr<_M, _Q, _R>::value, size_t>::type = 0>
constexpr int qr(internal::Stream<_M> const &M, internal::Base<_Q> &Q, internal::Base<_R> &R);

/** @fn qr
 *  @param[in] M m by n matrix where m >= n.
 *  @param[out] Q Orthonormal m by n matrix where m >= n.
 *  @param[out] R Upper triangular n by n matrix.
 * 
 *  Calculates the QR factorization of M and stores the result in Q and R.
 * 
 *  Will resize Q and R if required. */
template <class _M, class _Q, class _R,
    typename std::enable_if<internal::can_qr<_M, _Q, _R>::value, size_t>::type = 0>
constexpr int qr(internal::Stream<_M> const &M, internal::Tensor<_Q> &Q, internal::Tensor<_R> &R);

}  // namespace lin

#include "inl/qr.inl"

#endif
