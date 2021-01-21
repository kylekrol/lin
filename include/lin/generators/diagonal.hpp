// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/diagonal.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_DIAGONAL_HPP_
#define LIN_GENERATORS_DIAGONAL_HPP_

#include "stream_diagonal.hpp"
#include "../core.hpp"

#include <limits>
#include <type_traits>

namespace lin {

/**
 */
template <class D, typename std::enable_if_t<internal::is_vector<D>::value, size_t> = 0>
constexpr auto diag(internal::Stream<D> const &stream) {
  return internal::StreamDiagonal<D>(stream);
}
}  // namespace lin

#endif
