/** @file lin/core/traits/utilities.hpp
 *  @author Kyle Krol
 *  Helper template metaprogramming constructs for the traits module. */

// TODO : Documentation for this entire file
// TODO : Create and and and or helper struct

#ifndef LIN_CORE_TRAITS_UTILITIES_HPP_
#define LIN_CORE_TRAITS_UTILITIES_HPP_

#include <type_traits>

namespace lin {
namespace internal {

/** @typedef true_type */
typedef std::true_type true_type;

/** @typedef false_type */
typedef std::false_type false_type;

/** @typedef is_same */
template <typename T, typename U>
using is_same = std::is_same<T, U>;

/** @typedef enable_if */
template <bool B, typename T = void>
using enable_if = std::enable_if<B, T>;

/** @typedef enable_if_t */
template <bool B, typename T = void>
using enable_if_t = std::enable_if_t<B, T>;

/** @typedef void_t */
template <typename...>
using void_t = void;

template <template <typename...> class E, typename, typename... Ts>
struct _is_detected : false_type { };

template <template <typename...> class E, typename... Ts>
struct _is_detected<E, void_t<E<Ts...>>, Ts...> : true_type { };

/** @struct is_detected */
template <template <typename...> class E, typename... Ts>
struct is_detected : _is_detected<E, void, Ts...> { };

}  // namespace internal
}  // namespace lin

#endif
