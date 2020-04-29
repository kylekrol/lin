/** @file lin/queries/operations.hpp
 *  @author Kyle Krol
 *  Defines all operations included in the queries module. */

#ifndef LIN_QUERIES_OPERATIONS_HPP_
#define LIN_QUERIES_OPERATIONS_HPP_

#include "../core.hpp"
#include "functors.hpp"

#include <type_traits>

namespace lin {

/** @fn all
 *  @{ */
template <class C,
    std::enable_if_t<internal::matches_tensor<C>::value, size_t> = 0>
constexpr bool all(internal::Stream<C> const &c) {
  for (size_t i = 0; i < c.size(); i++) if (!c(i)) return false;
  return true;
}

template <typename T,
    std::enable_if_t<internal::matches_scalar<T>::value, size_t> = 0>
constexpr bool all(T const &t) {
  return bool(t);
}
/** @} */

/** @fn any
 *  @{ */
template <class C>
constexpr bool any(internal::Stream<C> const &c) {
  for (size_t i = 0; i < c.size(); i++) if (c(i)) return true;
  return false;
}

template <typename T,
    std::enable_if_t<internal::matches_scalar<T>::value, size_t> = 0>
constexpr bool any(T const &t) {
  return bool(t);
}
/** @} */

/** @fn equal_to
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto equal_to(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::equal_to, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto equal_to(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::equal_to_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto equal_to(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::equal_to_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto equal_to(T const &t, U const &u) {
  return internal::equal_to()(t, u);
}
/** @} */

/** @fn greater
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto greater(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::greater, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto greater(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::greater_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto greater(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::greater_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto greater(T const &t, U const &u) {
  return internal::greater()(t, u);
}
/** @} */

/** @fn greater_equal
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto greater_equal(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::greater_equal, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto greater_equal(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::greater_equal_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto greater_equal(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::greater_equal_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto greater_equal(T const &t, U const &u) {
  return internal::greater_equal()(t, u);
}
/** @} */

/** @fn less
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto less(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::less, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto less(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::less_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto less(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::less_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto less(T const &t, U const &u) {
  return internal::less()(t, u);
}
/** @} */

/** @fn less_equal
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto less_equal(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::less_equal, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto less_equal(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::less_equal_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto less_equal(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::less_equal_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto less_equal(T const &t, U const &u) {
  return internal::less_equal()(t, u);
}
/** @} */

/** @fn logical_and
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto logical_and(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::logical_and, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto logical_and(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::logical_and_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto logical_and(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::logical_and_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto logical_and(T const &t, U const &u) {
  return internal::logical_and()(t, u);
}
/** @} */

/** @fn logical_not
 *  @{ */
template <class C, std::enable_if_t<internal::matches_tensor<C>::value, size_t> = 0>
inline constexpr auto logical_not(internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::logical_not, C>(c);
}

template <typename T, std::enable_if_t<internal::matches_scalar<T>::value, size_t> = 0>
inline constexpr auto logical_not(T const &t) {
  return internal::logical_not()(t);
}
/** @} */

/** @fn logical_or
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto logical_or(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::logical_or, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto logical_or(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::logical_or_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto logical_or(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::logical_or_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto logical_or(T const &t, U const &u) {
  return internal::logical_or()(t, u);
}
/** @} */

/** @fn not_equal_to
 *  @{ */
template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto not_equal_to(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return internal::StreamElementWiseOperator<internal::not_equal_to, C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto not_equal_to(T const &t, internal::Stream<C> const &c) {
  return internal::StreamElementWiseOperator<internal::not_equal_to_st<T>, C>(c, t);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto not_equal_to(internal::Stream<C> const &c, T const &t) {
  return internal::StreamElementWiseOperator<internal::not_equal_to_ts<T>, C>(c, t);
}

template <typename T, typename U, std::enable_if_t<
    internal::matches_scalar_scalar<T, U>::value, size_t> = 0>
inline constexpr auto not_equal_to(T const &t, U const &u) {
  return internal::not_equal_to()(t, u);
}
/** @} */

}  // namespace lin

#endif
