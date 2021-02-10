// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/operations/tensor_operations.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_OPERATIONS_TENSOR_OPERATIONS_HPP_
#define LIN_CORE_OPERATIONS_TENSOR_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "../types.hpp"
#include "functors.hpp"
#include "mapping_transpose.hpp"
#include "stream_element_wise_operator.hpp"
#include "stream_transpose.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @brief Tests if a type is a tensor.
 * 
 *  @tparam T Type.
 *  
 *  A type is determined to be a tensor type if it has traits. This is used to aid
 *  with selecting overloads for operation functions.
 * 
 *  @sa internal::has_traits
 *  @sa internal::matches_scalar
 * 
 *  @ingroup COREOPERATIONS
 */
template <typename T>
struct matches_tensor : has_traits<T> { };

/** @brief Tests if a type is a scalar.
 * 
 *  @tparam T Type.
 *  
 *  A type is determined to be a scalar if it isn't considered a tensor.This is
 *  used to aid with selecting overloads for operation functions.
 * 
 *  @sa internal::matches_tensor
 * 
 *  @ingroup COREOPERATIONS
 */
template <typename T>
struct matches_scalar : negation<matches_tensor<T>> { };

/** @brief Tests if a pair of types is a "tensor tensor" pair.
 * 
 *  @tparam T First type.
 *  @tparam U Second type.
 * 
 *  A pair of types is determined to be a "tensor tensor" pair if both are
 *  considered tensor types. This is used to aid with selecting overloads for
 *  operation functions.
 * 
 *  @sa internal::matches_tensor
 *  @sa internal::matches_tensor_scalar
 *  @sa internal::matches_scalar_tensor
 *  @sa internal::matches_scalar_scalar
 * 
 *  @ingroup COREOPERATIONS
 */
template <typename T, typename U>
struct matches_tensor_tensor
    : conjunction<matches_tensor<T>, matches_tensor<U>> { };

/** @brief Tests if a pair of types is a "tensor scalar" pair.
 * 
 *  @tparam T First type.
 *  @tparam U Second type.
 * 
 *  A pair of types is determined to be a "tensor scalar" pair if the first type
 *  is considered a tensor type and the second type is considered a scalar type.
 *  This is used to aid with selecting overloads for operation functions.
 * 
 *  @sa internal::matches_tensor
 *  @sa internal::matches_scalar
 *  @sa internal::matches_scalar_scalar
 *  @sa internal::matches_scalar_tensor
 *  @sa internal::matches_scalar_scalar
 * 
 *  @ingroup COREOPERATIONS
 */
template <typename T, typename U>
struct matches_tensor_scalar
    : conjunction<matches_tensor<T>, matches_scalar<U>> { };

/** @brief Tests if a pair of types is a "scalar tensor" pair.
 * 
 *  @tparam T First type.
 *  @tparam U Second type.
 * 
 *  A pair of types is determined to be a "tensor scalar" pair if the first type
 *  is considered a scalar type and the second type is considered a tensor type.
 *  This is used to aid with selecting overloads for operation functions.
 * 
 *  @sa internal::matches_tensor
 *  @sa internal::matches_scalar
 *  @sa internal::matches_scalar_scalar
 *  @sa internal::matches_tensor_scalar
 *  @sa internal::matches_scalar_scalar
 * 
 *  @ingroup COREOPERATIONS
 */
template <typename T, typename U>
struct matches_scalar_tensor
    : conjunction<matches_scalar<T>, matches_tensor<U>> { };

/** @brief Tests if a pair of types is a "scalar scalar" pair.
 * 
 *  @tparam T First type.
 *  @tparam U Second type.
 * 
 *  A pair of types is determined to be a "scalar scalar" pair if both are
 *  considered scalar types. This is used to aid with selecting overloads for
 *  operation functions.
 * 
 *  @sa internal::matches_scalar
 *  @sa internal::matches_scalar_scalar
 *  @sa internal::matches_tensor_scalar
 *  @sa internal::matches_scalar_tensor
 * 
 *  @ingroup COREOPERATIONS
 */
template <typename T, typename U>
struct matches_scalar_scalar
    : conjunction<matches_scalar<T>, matches_scalar<U>> { };

}  // namespace internal

/** @weakgroup COREOPERATIONS
 *  @{
 */

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto add(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  LIN_ASSERT(c.rows() == d.rows());
  LIN_ASSERT(c.cols() == d.cols());

  return internal::StreamElementWiseOperator<internal::add, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto add(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::add_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto add(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::add_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
constexpr auto add(T const &t, U const &u) {
  return internal::add()(t, u);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
inline constexpr auto cast(internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::cast<T>, C>(c);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar<U>::value, size_t> = 0>
inline constexpr auto cast(U const &u) {
  return internal::cast<T>()(u);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto divide(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  LIN_ASSERT(c.rows() == d.rows());
  LIN_ASSERT(c.cols() == d.cols());

  return internal::StreamElementWiseOperator<internal::divide, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto divide(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::divide_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto divide(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::divide_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto divide(T const &t, U const &u) {
  return internal::divide()(t, u);
}

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
constexpr auto fro(internal::Stream<C> const &c) {
  typename C::Traits::elem_t f = c(0) * c(0);
  for (size_t i = 1; i < c.size(); i++) f += c(i) * c(i);
  return f;
}

template <typename T, std::enable_if_t<
    internal::matches_scalar<T>::value, size_t> = 0>
constexpr auto fro(T const &t) {
  return t * t;
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto multiply(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  LIN_ASSERT(c.rows() == d.rows());
  LIN_ASSERT(c.cols() == d.cols());

  return internal::StreamElementWiseOperator<internal::multiply, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto multiply(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::multiply_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto multiply(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::multiply_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto multiply(T const &t, U const &u) {
  return internal::multiply()(t, u);
}

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
inline constexpr auto negate(internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::negate, C>(c);
}

template <typename T, std::enable_if_t<
    internal::matches_scalar<T>::value, size_t> = 0>
inline constexpr auto negate(T const &t) {
  return internal::negate()(t);
}

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
inline constexpr auto sign(internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::sign, C>(c);
}

template <typename T, std::enable_if_t<
    internal::matches_scalar<T>::value, size_t> = 0>
inline constexpr auto sign(T const &t) {
  return internal::sign()(t);
}

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
inline constexpr auto square(internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::square, C>(c);
}

template <typename T, std::enable_if_t<
    internal::matches_scalar<T>::value, size_t> = 0>
inline constexpr auto square(T const &t) {
  return internal::square()(t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto subtract(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  LIN_ASSERT(c.rows() == d.rows());
  LIN_ASSERT(c.cols() == d.cols());

  return internal::StreamElementWiseOperator<internal::subtract, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto subtract(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::subtract_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto subtract(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::subtract_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto subtract(T const &t, U const &u) {
  return internal::subtract()(t, u);
}

template <class C>
constexpr auto sum(internal::Stream<C> const &c) {
  typename C::Traits::elem_t x = c(0);
  for (lin::size_t i = 1; i < c.size(); i++) x += c(i);
  return x;
}

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
constexpr auto transpose(internal::Mapping<C> &c) {
  return internal::MappingTranspose<C>(c);
}

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
constexpr auto transpose(internal::Stream<C> const &c) {
  return internal::StreamTranspose<C>(c);
}

/** @}
 */

}  // namespace lin

#endif
