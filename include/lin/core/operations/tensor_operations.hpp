/** @file lin/core/operations/tensor_operations.hpp
 *  @author Kyle Krol
 *  Defines all tensor operations included with the core module. */

#ifndef LIN_CORE_OPERATIONS_TENSOR_OPERATIONS_HPP_
#define LIN_CORE_OPERATIONS_TENSOR_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "../types.hpp"
#include "element_wise_operator.hpp"
#include "functors.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @struct matches_tensor */
template <typename T>
struct matches_tensor : has_traits<T> { };

template <typename T>
struct matches_scalar : negation<has_traits<T>> { };

/** @struct matches_tensor_tensor */
template <typename T, typename U>
struct matches_tensor_tensor
    : conjunction<has_traits<T>, has_traits<U>> { };

/** @struct matches_tensor_scalar */
template <typename T, typename U>
struct matches_tensor_scalar
    : conjunction<has_traits<T>, negation<has_traits<U>>> { };

/** @struct matches_scalar_tensor */
template <typename T, typename U>
struct matches_scalar_tensor
    : conjunction<negation<has_traits<T>>, has_traits<U>> { };

/** @struct matches_scalar_scalar */
template <typename T, typename U>
struct matches_scalar_scalar
    : conjunction<negation<has_traits<T>>, negation<has_traits<U>>> { };

/** @class StreamTranspose
 *  Represents a lazily evaluated transpose operation. */
template <class C>
class StreamTranspose;

}  // namespace internal

/** @fn add
 *  @{ */
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
/** @} */

/** @fn cast
 *  @{ */
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
/** @} */

/** @fn divide
 *  @{ */
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
/** @} */

/** @fn fro */
template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
constexpr typename C::Traits::Elem fro(internal::Stream<C> const &c);

/** @fn multiply
 *  @{ */
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
/** @} */

/** @fn negate
 *  @{ */
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
/** @} */

/** @fn sign
 *  @{ */
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
/** @} */

/** @fn square
 *  @{ */
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
/** @} */

/** @fn subtract
 *  @{ */
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
/** @} */

/** @fn sum */
template <class C>
constexpr typename C::Traits::Elem sum(internal::Stream<C> const &c) {
  typename C::Traits::Elem x = c(0);
  for (lin::size_t i = 1; i < c.size(); i++) x += c(i);
  return x;
}

/** @fn transpose */
template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t> = 0>
constexpr auto transpose(internal::Stream<C> const &c) {
  return internal::StreamTranspose<C>(c);
}
}  // namespace lin

#include "inl/tensor_operations.inl"

#endif
