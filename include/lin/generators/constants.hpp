/** @file lin/generators/constants.hpp
 *  @author Kyle Krol
 *  Defines generators to create matrices and vector whose elements are a
 *  single, constant value. */

// TODO : Documentation for this whole fil

#ifndef LIN_GENERATORS_CONSTANTS_HPP_
#define LIN_GENERATORS_CONSTANTS_HPP_

#include "../core.hpp"

#include <limits>
#include <type_traits>

namespace lin {
namespace internal {

/** @class StreamConstants */
template <typename T, size_t R, size_t C, size_t MR, size_t MC>
class StreamConstants;

}  // namespace internal

/** @fn consts */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr internal::StreamConstants<T, R, C, MR, MC> consts(T t, size_t r = MR, size_t c = MC);

/** @fn consts */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto consts(typename C::Traits::elem_t t, size_t r = C::Traits::max_rows,
    size_t c = C::Traits::max_cols);

/** @fn ones */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr internal::StreamConstants<T, R, C, MR, MC> ones(size_t r = MR, size_t c = MC);

/** @fn ones */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto ones(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols);

/** @fn zeros */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr internal::StreamConstants<T, R, C, MR, MC> zeros(size_t r = MR, size_t c = MC);

/** @fn zeros */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto zeros(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols);

/** @fn nans */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C, std::enable_if_t<
    std::numeric_limits<T>::has_quiet_NaN, size_t> = 0>
constexpr internal::StreamConstants<T, R, C, MR, MC> nans(size_t r = MR, size_t c = MC);

/** @fn nans */
template <class C, std::enable_if_t<(internal::has_traits<C>::value &&
    std::numeric_limits<typename C::Traits::elem_t>::has_quiet_NaN), size_t> = 0>
constexpr auto nans(size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols);

}  // namespace lin

#include "inl/constants.inl"

#endif
