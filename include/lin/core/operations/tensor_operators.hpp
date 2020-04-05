/** @file lin/core/operations/tensor_operators.hpp
 *  @author Kyle Krol
 *  Defines operator wrappers around some of the tensor operations functors and
 *  a few unique operators. */

#ifndef LIN_CORE_OPERATIONS_TENSOR_OPERATORS_HPP_
#define LIN_CORE_OPERATIONS_TENSOR_OPERATORS_HPP_

#include "../config.hpp"
#include "../types.hpp"
#include "functors.hpp"
#include "tensor_operations.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @fn operator+
 *  @{ */
template <class C, class D, std::enable_if_t<
    matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator+(Stream<C> const &c, Stream<D> const &d) {
  return lin::add(c, d);
}

template <typename T, class C, std::enable_if_t<
    matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator+(T const &t, Stream<C> const &c) {
  return lin::add(t, c);
}

template <class C, typename T, std::enable_if_t<
    matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator+(Stream<C> const &c, T const &t) {
  return lin::add(c, t);
}
/** @} */

/** @fn operator- */
template <class C, std::enable_if_t<matches_tensor<C>::value, size_t> = 0>
inline constexpr auto operator-(Stream<C> const &c) {
  return lin::negate(c);
}

/** @fn operator-
 *  @{ */
template <class C, class D, std::enable_if_t<
    matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator-(Stream<C> const &c, Stream<D> const &d) {
  return lin::subtract(c, d);
}

template <typename T, class C, std::enable_if_t<
    matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator-(T const &t, Stream<C> const &c) {
  return lin::subtract(t, c);
}

template <class C, typename T, std::enable_if_t<
    matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator-(Stream<C> const &c, T const &t) {
  return lin::subtract(c, t);
}
/** @} */

/** @struct can_multiply */
template <class C, class D, typename = void>
struct can_multiply;

/** @class StreamMultiply */
template <class C, class D>
class StreamMultiply;

/** @fn operator*
 *  @{ */
template <class C, class D, std::enable_if_t<
    can_multiply<C, D>::value, size_t> = 0>
inline constexpr auto operator*(Stream<C> const &c, Stream<D> const &d) {
  LIN_ASSERT(c.cols() == d.rows());
  return StreamMultiply<C, D>(c, d);
}

template <typename T, class C, std::enable_if_t<
    matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator*(T const &t, Stream<C> const &c) {
  return lin::multiply(t, c);
}

template <class C, typename T, std::enable_if_t<
    matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator*(Stream<C> const &c, T const &t) {
  return lin::multiply(c, t);
}
/** @} */

/** @fn operator/
 *  @{ */
template <class C, class D, std::enable_if_t<
    matches_tensor_tensor<C, D>::value, size_t> = 0>
inline constexpr auto operator/(Stream<C> const &c, Stream<D> const &d) {
  return lin::divide(c, d);
}

template <typename T, class C, std::enable_if_t<
    matches_scalar_tensor<T, C>::value, size_t> = 0>
inline constexpr auto operator/(T const &t, Stream<C> const &c) {
  return lin::divide(t, c);
}

template <class C, typename T, std::enable_if_t<
    matches_tensor_scalar<C, T>::value, size_t> = 0>
inline constexpr auto operator/(Stream<C> const &c, T const &t) {
  return lin::divide(c, t);
}
/** @} */

}  // namespace internal
}  // namespace lin

#include "inl/tensor_operators.inl"

#endif
