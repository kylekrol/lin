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

/** @typedef void_t */
template <typename...>
using void_t = void;

/** @struct is_detected
 *  Tests if a given expression can be instantiated with the specified types. */
template <template <typename...> class E, typename... Ts>
struct is_detected;

/** @struct conjunction
 *  Essentially performs a logical and operation on a set of types. The provided
 *  types are expected to be true or false types. If no types are specified, the
 *  resulting type is true. */
template <class... Cs>
struct conjunction;

/** @struct disjuntion
 *  Essentially performs a logical or operation on a set of types. The provided
 *  types are expected to be true or false types. If no types are specified, the
 *  resulting type is false. */
template <class... Cs>
struct disjunction;

/** @struct negation
 *  Essentially performs a logical not operation on the specified type. The
 *  provided type is expected to be a true or false type. */
template <class C>
struct negation;

/** @struct all */
template <template <class> class C, class... Cs>
struct all : conjunction<C<Cs>...> { };

/** @struct any */
template <template <class> class C, class... Cs>
struct any : disjunction<C<Cs>...> { };

}  // namespace internal
}  // namespace lin

#include "inl/utilities.inl"

#endif
