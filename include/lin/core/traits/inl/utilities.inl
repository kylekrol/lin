/** @file lin/core/traits/inl/utilities.inl
 *  @author Kyle Krol
 *  See %lin/core/traits/utilities.hpp for more information. */

#include "../utilities.hpp"

namespace lin {
namespace internal {

template <template <typename...> class E, typename, typename... Ts>
struct _is_detected : std::false_type { };

template <template <typename...> class E, typename... Ts>
struct _is_detected<E, void_t<E<Ts...>>, Ts...> : std::true_type { };

template <template <typename...> class E, typename... Ts>
struct is_detected : _is_detected<E, void, Ts...> { };

template <>
struct conjunction<> : std::true_type { };

template <class C>
struct conjunction<C> : C { };

template <class C, class... Cs>
struct conjunction<C, Cs...>
    : std::conditional_t<C::value, conjunction<Cs...>, std::false_type> { };

template <>
struct disjunction<> : std::false_type { };

template <class C>
struct disjunction<C> : C { };

template <class C, class... Cs>
struct disjunction<C, Cs...>
    : std::conditional_t<C::value, std::true_type, disjunction<Cs...>> { };

template <class C>
struct negation
    : std::conditional_t<C::value, std::false_type, std::true_type> { };

}  // namespace internal
}  // namespace lin
