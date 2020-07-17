// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/identity.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_IDENTITY_HPP_
#define LIN_GENERATORS_IDENTITY_HPP_

#include "stream_identity.hpp"
#include "../core.hpp"

#include <type_traits>

namespace lin {

/** @brief Creates a stream which evaluates to an identity matrix.
 *
 *  @tparam T  %Stream element type.
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows at compile time.
 *  @tparam MC Maximum columns at compile time.
 *
 *  @param[in] r Row count.
 *  @param[in] c Column count.
 *
 *  @return Identity stream.
 *
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr auto identity(size_t r = MR, size_t c = MC) {
  return internal::StreamIdentity<T, R, C, MR, MC>(r, c);
}

/** @brief Creates a stream which evaluates to an identity matrix.
 *
 *  @tparam C Tensor type whose traits the returned stream will mimic.
 *
 *  @param[in] r Row count.
 *  @param[in] c Column count.
 *
 *  @return Identity stream.
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto identity(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  return identity<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols>(r, c);
}
}  // namespace lin

#endif
