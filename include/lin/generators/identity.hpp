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

/** @brief
 *
 *  @return
 *
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr auto identity(size_t r = MR, size_t c = MC) {
  return internal::StreamIdentity<T, R, C, MR, MC>(r, c);
}

/** @brief
 *
 *  @return
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto identity(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  return identity<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols>(r, c);
}
}  // namespace lin

#endif
