// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/constants.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_CONSTANTS_HPP_
#define LIN_GENERATORS_CONSTANTS_HPP_

#include "stream_constants.hpp"
#include "../core.hpp"

#include <limits>
#include <type_traits>

namespace lin {

/** @brief
 *
 *  @sa nans
 *  @sa ones
 *  @sa zeros
 * 
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr auto consts(T t, size_t r = MR, size_t c = MC) {
  return internal::StreamConstants<T, R, C, MR, MC>(t, r, c);
}

/** @brief
 *
 *  @sa nans
 *  @sa ones
 *  @sa zeros
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto consts(typename C::Traits::elem_t t, size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  return consts<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols>(t, r, c);
}

/** @brief
 *
 *  @sa consts
 *  @sa nans
 *  @sa zeros
 * 
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr auto nans(size_t r = MR, size_t c = MC) {
  // Ensure quiet NaN values are supported
  static_assert(std::numeric_limits<T>::has_quiet_NaN, "Quiet NaN must be supported!");

  return consts<T, R, C, MR, MC>(std::numeric_limits<T>::quiet_NaN(), r, c);
}

/** @brief
 *
 *  @sa consts
 *  @sa nans
 *  @sa zeros
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto nans(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  return nans<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols>(r, c);
}

/** @brief
 *
 *  @sa consts
 *  @sa nans
 *  @sa zeros
 * 
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr auto ones(size_t r = MR, size_t c = MC) {
  return consts<T, R, C, MR, MC>(T(1), r, c);
}

/** @brief
 *
 *  @sa consts
 *  @sa nans
 *  @sa zeros
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto ones(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  return ones<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols>(r, c);
}

/** @brief
 *
 *  @sa consts
 *  @sa nans
 *  @sa ones
 * 
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr auto zeros(size_t r = MR, size_t c = MC) {
  return consts<T, R, C, MR, MC>(T(0), r, c);
}

/** @brief
 *
 *  @sa consts
 *  @sa nans
 *  @sa ones
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto zeros(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  return zeros<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols>(r, c);
}
}  // namespace lin

#endif
