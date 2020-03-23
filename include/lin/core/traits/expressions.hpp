/** @file lin/core/traits/expressions.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for expression handling. */

// TODO : Documentation for this whole file

#ifndef LIN_CORE_TRAITS_EXPRESSIONS_HPP_
#define LIN_CORE_TRAITS_EXPRESSIONS_HPP_

#include <utility>

namespace lin {
namespace internal {

/** @typedef assign_expr */
template <typename T, typename U>
using assign_expr = decltype(std::declval<T &>() = std::declval<U &>());

/** @typedef add_expr */
template <typename T, typename U>
using add_expr = decltype(std::declval<T &>() + std::declval<U &>());

/** @typedef subtract_expr */
template <typename T, typename U>
using subtract_expr = decltype(std::declval<T &>() - std::declval<U &>());

/** @typedef multiply_expr */
template <typename T, typename U>
using multiply_expr = decltype(std::declval<T &>() * std::declval<U &>());

/** @typedef divide_expr */
template <typename T, typename U>
using divide_expr = decltype(std::declval<T &>() / std::declval<U &>());

/** @typedef negate_expr */
template <typename T>
using negate_expr = decltype(-std::declval<T &>());

}  // namespace internal
}  // namespace lin

#endif
