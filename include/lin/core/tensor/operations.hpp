/** @file lin/core/tensor/operations.hpp
 *  @author Kyle Krol
 *  Defines operations that can be done on all tensor types. */

#ifndef LIN_CORE_TENSOR_OPERATIONS_HPP_
#define LIN_CORE_TENSOR_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"

#include "stream.hpp"

#include <cmath>

namespace lin {
namespace internal {

/** @class StreamTranspose
 *  Represents a lazily evaluated transpose operation. */
template <class C>
class StreamTranspose;

/** @class StreamTranspose
 *  Represents a lazily evaluated sign operation. */
template <class C>
class StreamSign;

}  // namespace internal

/** @fn all
 *  Returns true if all of the elements of the stream satisfy the specified
 *  condition. */
template <class C>
constexpr bool all(internal::Stream<C> const &c, bool (*f)(typename C::Traits::Elem const &));

/** @fn any
 *  Returns true if any of the elements of the stream satisfy the specified
 *  condition. */
template <class C>
constexpr bool any(internal::Stream<C> const &c, bool (*f)(typename C::Traits::Elem const &));

/** @fn fro
 *  Calculates the frobenius norm of the given tensor. The return type is the
 *  same of the element type of the stream. */
template <class C>
constexpr auto fro(internal::Stream<C> const &c);

/** @fn sign */
template <class C>
constexpr internal::StreamSign<C> sign(internal::Stream<C> const &c);

/** @fn transpose
 *  Gives the transpose of the provided tensor. */
template <class C>
constexpr internal::StreamTranspose<C> transpose(internal::Stream<C> const &c);

}  // namespace lin

#include "inl/operations.inl"

#endif
