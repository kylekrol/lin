/** @file lin/queries/operators.hpp
 *  @author Kyle Krol
 *  Defines all operators included in the queries module. */

#ifndef LIN_QUERIES_OPERATORS_HPP_
#define LIN_QUERIES_OPERATORS_HPP_

#include "../core.hpp"
#include "operations.hpp"

#include <type_traits>

namespace lin {
namespace internal {

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator==(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::equal_to(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator==(T const &t, internal::Stream<C> const &c) {
  return lin::equal_to(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator==(internal::Stream<C> const &c, T const &t) {
  return lin::equal_to(c, t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator>(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::greater(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator>(T const &t, internal::Stream<C> const &c) {
  return lin::greater(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator>(internal::Stream<C> const &c, T const &t) {
  return lin::greater(c, t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator>=(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::greater_equal(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator>=(T const &t, internal::Stream<C> const &c) {
  return lin::greater_equal(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator>=(internal::Stream<C> const &c, T const &t) {
  return lin::greater_equal(c, t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator<(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::less(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator<(T const &t, internal::Stream<C> const &c) {
  return lin::less(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator<(internal::Stream<C> const &c, T const &t) {
  return lin::less(c, t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator<=(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::less_equal(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator<=(T const &t, internal::Stream<C> const &c) {
  return lin::less_equal(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator<=(internal::Stream<C> const &c, T const &t) {
  return lin::less_equal(c, t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator&&(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::logical_and(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator&&(T const &t, internal::Stream<C> const &c) {
  return lin::logical_and(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator&&(internal::Stream<C> const &c, T const &t) {
  return lin::logical_and(c, t);
}

template <class C, std::enable_if_t<internal::matches_tensor<C>::value, size_t> = 0>
inline constexpr auto operator!(internal::Stream<C> const &c) {
  return lin::logical_not(c);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator||(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::logical_or(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator||(T const &t, internal::Stream<C> const &c) {
  return lin::logical_or(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator||(internal::Stream<C> const &c, T const &t) {
  return lin::logical_or(c, t);
}

template <class C, class D, std::enable_if_t<
    internal::matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator!=(internal::Stream<C> const &c, internal::Stream<D> const &d) {
  return lin::not_equal_to(c, d);
}

template <typename T, class C, std::enable_if_t<
    internal::matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator!=(T const &t, internal::Stream<C> const &c) {
  return lin::not_equal_to(t, c);
}

template <class C, typename T, std::enable_if_t<
    internal::matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator!=(internal::Stream<C> const &c, T const &t) {
  return lin::not_equal_to(c, t);
}
}  // namespace internal
}  // namespace lin

#endif
