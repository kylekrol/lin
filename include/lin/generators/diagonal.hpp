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

/** @brief Creates a diagonal stream from a vector stream.
 *
 *  @tparam D Underlying type.
 *
 *  @param stream Underlying vector stream.
 *
 *  @return Instance of an internal::StreamDiagonal
 *
 *  @sa internal::is_vector
 */
template <class D, typename std::enable_if_t<internal::is_vector<D>::value, size_t> = 0>
constexpr auto diag(internal::Stream<D> const &stream) {
  return internal::StreamDiagonal<D>(stream);
}
}  // namespace lin

#endif
