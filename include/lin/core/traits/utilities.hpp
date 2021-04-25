#pragma once

//
// Copyright (c) 2021 Kyle Krol (kylekrol)
//
// This file is part of lin.
//
// lin is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// lin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lin. If not, see <https://www.gnu.org/licenses/>.
//

/** @file lin/core/traits/utilities.hpp
 *  @author Kyle Krol
 */

#include "../config.hpp"

#include <type_traits>

namespace lin {

/** @brief Template metaprogramming boolean constant.
 *
 *  @tparam B Boolean constant.
 */
template <bool B>
using bool_constant = std::integral_constant<bool, B>;

/** @brief Alias to the standard library's implementation of conditional.
 */
template <bool B, typename T, typename U>
using conditional = std::conditional<B, T, U>;

/** @brief Alias to the standard library's implementation of conditional_t.
 */
template <bool B, typename T, typename U>
using conditional_t = typename conditional<T, U, V>::type;

/** @brief Alias to the standard library's implementation of enable_if.
 */
template <bool B, typename T = void>
using enable_if = std::enable_if<B, T>;

/** @brief Alias to the standard library's implementation of enable_if_t.
 */
template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

/** @brief Template metaprogramming lin size constant.
 *
 *  @tparam S Constant value.
 */
template <size_t S>
using size_constant = std::integral_constant<size_t, S>;

/** @brief Alias to the standard library's implementation of true_type.
 */
using true_type = std::true_type;

/** @brief Alias to the standard library's implementation of true_type.
 */
using false_type = std::false_type;

/** @brief Maps a set of types to the type void.
 */
template <typename...>
using void_t = void;

/** @brief Logical and operation for template metaprogramming.
 *
 *  @tparam Cs Set of input types.
 *
 *  If no type if specified, the conjunction defaults to true. If one type is
 *  given, the conjunction behaves as an identity operation.
 */
template <class... Cs>
struct conjunction;

template <class C, class... Cs>
struct conjunction<C, Cs...>
  : std::conditional_t<C::value, conjunction<Cs...>, false_type> { };

template <class C>
struct conjunction<C>
  : C { };

template <>
struct conjunction<>
  : true_type { };

/** @brief Logical or operation for template metaprogramming.
 *
 *  @tparam Cs Set of input types.
 *
 *  If no type if specified, the disjunction defaults to false. If one type is
 *  given, the disjunction behaves as an identity operation.
 */
template <class... Cs>
struct disjunction;

template <class C, class... Cs>
struct disjunction<C, Cs...>
  : std::conditional_t<C::value, true_type, disjunction<Cs...>> { };

template <class C>
struct disjunction<C>
  : C { };

template <>
struct disjunction<>
  : false_type { };

/** @brief Logical not operation for template metaprogramming.
 *
 *  @tparam C Input type.
 */
template <class C>
struct negation
  : std::conditional_t<C::value, false_type, true_type> { };

template <template <typename...> class E, typename, typename... Ts>
struct _is_detected
  : false_type { };

template <template <typename...> class E, typename... Ts>
struct _is_detected<E, void_t<E<Ts...>>, Ts...>
  : true_type { };

/** @brief Determines if a given expression can be instantiated.
 *
 *  @tparam E  Template expression type.
 *  @tparam Ts Set of types we try to instantiate the expression with.
 *
 *  An example use case is given here:
 *
 *  ~~~{.cpp}
 *  #include <lin/core/traits.hpp>
 *  #include <utility>
 *
 *  template <typename T, typename U>
 *  using add_expr = decltype(std::declval<T &>() + std::declval<U &>());
 *
 *  static_assert(lin::is_detected<add_expr, double, float>::value,
 *      "doubles and floats should add");
 *  ~~~
 */
template <template <typename...> class E, typename... Ts>
struct is_detected
  : _is_detected<E, void, Ts...> { };

}  // namespace lin
