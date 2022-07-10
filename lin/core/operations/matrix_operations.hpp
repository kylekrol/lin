// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/operations/matrix_operations.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_OPERATIONS_MATRIX_OPERATIONS_HPP_
#define LIN_CORE_OPERATIONS_MATRIX_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "../types/stream.hpp"

#include <type_traits>

namespace lin {

/** @weakgroup COREOPERATIONS
 *  @{
 */

template <class C, std::enable_if_t<internal::is_square<C>::value, size_t> = 0>
constexpr auto trace(internal::Stream<C> const &c) {
  LIN_ASSERT(c.rows() == c.cols());

  typename C::Traits::elem_t x = c(0, 0);
  for (lin::size_t i = 1; i < c.rows(); i++) x += c(i, i);
  return x;
}

/** @}
 */

}  // namespace lin

#endif
