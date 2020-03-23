/** @file lin/core/tensor/operations.hpp
 *  @author Kyle Krol
 *  Defines operations that can be done on all tensor types. */

#ifndef LIN_CORE_TENSOR_OPERATIONS_HPP_
#define LIN_CORE_TENSOR_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"

#include "stream.hpp"

namespace lin {
namespace internal {

/** @class StreamTranspose
 *  Represents a lazily evaluated transpose operation. */
template <class C>
class StreamTranspose;

}  // namespace internal

/** @fn transpose
 *  Gives the transpose of the provided tensor. */
template <class C>
constexpr internal::StreamTranspose<C> transpose(internal::Stream<C> const &c);

/** @fn fro
 *  Calculates the frobenius norm of the given tensor. The return type is the
 *  same of the element type of the stream. */
template <class C>
constexpr auto fro(internal::Stream<C> const &c);

}  // namespace lin

#include "inl/operations.inl"

#endif
