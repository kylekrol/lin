/** @file lin/factorizations/qr.hpp
 *  @author Kyle Krol
 *  Defines a QR factorization algorithm for tensor types. */

// TODO : Documentation for this entire file

#ifndef LIN_FACTORIZATIONS_QR_HPP_
#define LIN_FACTORIZATIONS_QR_HPP_

#include "../core.hpp"
#include "../generators/constants.hpp"
#include "../references.hpp"

namespace lin {
namespace internal {

/** @struct can_qr
 *  Used to test whether or not the provided types can be fed to the QR
 *  factorization algorithm. */
template <class C, class D, class E, typename = void>
struct can_qr;

}  // namespace internal

/** @fn qr */
template <class C, class D, class E,
    internal::enable_if_t<internal::can_qr<C, D, E>::value, size_t> = 0>
constexpr int qr(internal::Stream<C> const &M, internal::Base<D> &Q, internal::Base<E> &R);

/** @fn qr */
template <class C, class D, class E,
    internal::enable_if_t<internal::can_qr<C, D, E>::value, size_t> = 0>
constexpr int qr(internal::Stream<C> const &M, internal::Tensor<D> &Q, internal::Tensor<E> &R);

}  // namespace lin

#include "inl/qr.inl"

#endif
