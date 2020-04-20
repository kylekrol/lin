/** @file lin/generators/identity.hpp
 *  @author Kyle Krol
 *  Defines a generator to create identity matrices. */

#ifndef LIN_GENERATORS_IDENTITY_HPP_
#define LIN_GENERATORS_IDENTITY_HPP_

#include "../core.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @class StreamIdentity */
template <typename T, size_t N, size_t MN>
class StreamIdentity;

}  // namespace internal

/** @fn identity */
template <typename T, size_t N, size_t MN = N>
constexpr internal::StreamIdentity<T, N, MN> identity(size_t n = MN);

/** @fn identity */
template <class C, std::enable_if_t<internal::is_square<C>::value, size_t> = 0>
constexpr auto identity(size_t n = C::Traits::MaxRows);

}  // namespace lin

#include "inl/identity.inl"

#endif
