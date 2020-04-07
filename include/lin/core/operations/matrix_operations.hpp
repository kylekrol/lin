/** @file lin/core/operations/matrix_operations.hpp
 *  @author Kyle Krol
 *  Defines all matrix operations included with the core module. */

#ifndef LIN_CORE_OPERATIONS_MATRIX_OPERATIONS_HPP_
#define LIN_CORE_OPERATIONS_MATRIX_OPERATIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "../types.hpp"

#include <type_traits>

namespace lin {

/** @fn trace */
template <class C, std::enable_if_t<internal::is_square<C>::value, size_t> = 0>
constexpr typename C::Traits::Elem trace(internal::Stream<C> const &c) {
  LIN_ASSERT(c.rows() == c.cols() /* Trace must be called on a square matrix */);
  typename C::Traits::Elem x = c(0, 0);
  for (lin::size_t i = 1; i < c.rows(); i++) x += c(i, i);
  return x;
}
}  // namespace lin

#endif
