// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/traits/utilities.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TRAITS_UTILITIES_HPP_
#define LIN_CORE_TRAITS_UTILITIES_HPP_

#include <type_traits>

namespace lin {
namespace internal {

/** @brief Template metaprogramming construct used to detect ill formed types.
 */
template <typename...>
using void_t = void;

template <template <typename...> class E, typename, typename... Ts>
struct _is_detected : std::false_type { };

template <template <typename...> class E, typename... Ts>
struct _is_detected<E, void_t<E<Ts...>>, Ts...> : std::true_type { };

/** @brief Tests if a given expression can be instantiated.
 *
 *  @tparam E  Template expression type.
 *  @tparam Ts Set of types we try to instantiate `E` with.
 *
 *  An example use case is given here:
 *
 *  ~~~{.cpp}
 *  #include <lin/core/traits/utilities.hpp>
 *  #include <utility>
 *
 *  template <typename T, typename U>
 *  using add_expr = decltype(std::declval<T &>() + std::declval<U &>());
 *
 *  static_assert(lin::internal::is_detected<add_expr, double, float>::value, "doubles and floats should add");
 *  ~~~
 */
template <template <typename...> class E, typename... Ts>
struct is_detected : _is_detected<E, void, Ts...> { };

/** @brief Logical AND operation for template metaprogramming.
 *
 *  @tparam Cs Set of input types.
 *
 *  If no types are given, the disjunction defaults to false. If one type is
 *  given, it acts as an identity operation.
 */
template <class... Cs>
struct conjunction;

template <>
struct conjunction<> : std::true_type { };

template <class C>
struct conjunction<C> : C { };

template <class C, class... Cs>
struct conjunction<C, Cs...>
    : std::conditional_t<C::value, conjunction<Cs...>, std::false_type> { };

/** @brief Logical OR operation for template metaprogramming.
 *
 *  @tparam Cs Set of input types.
 *
 *  If no types are given, the conjunction defaults to true. If one type is
 *  given, it acts as an identity operation.
 */
template <class... Cs>
struct disjunction;

template <>
struct disjunction<> : std::false_type { };

template <class C>
struct disjunction<C> : C { };

template <class C, class... Cs>
struct disjunction<C, Cs...>
    : std::conditional_t<C::value, std::true_type, disjunction<Cs...>> { };

/** @brief Logical NOT operation for template metaprogramming.
 *
 *  @tparam C Input type.
 */
template <class C>
struct negation
    : std::conditional_t<C::value, std::false_type, std::true_type> { };

}  // namespace internal
}  // namespace lin

#endif
