/** @file lin/core/operations/inl/element_wise_operator.inl
 *  @author Kyle Krol
 *  See %lin/core/operations/element_wise_operator.hpp for more information. */

#include "../element_wise_operator.hpp"

namespace lin {
namespace internal {

template <class F, class... Cs>
struct can_element_wise_operate : conjunction<
    is_detected<F::template expression, _traits_elem_t<Cs>...>,
    have_same_dimensions<Cs...>
  > { };

template <class F, class... Cs>
template <typename... Ts>
constexpr StreamElementWiseOperator<F, Cs...>::StreamElementWiseOperator(Stream<Cs> const &... cs, Ts &&... fargs)
: f(fargs...), cs(cs...) { }

template <class F, class... Cs>
constexpr size_t StreamElementWiseOperator<F, Cs...>::rows() const {
  return std::get<0>(cs).rows();
}

template <class F, class... Cs>
constexpr size_t StreamElementWiseOperator<F, Cs...>::cols() const {
  return std::get<0>(cs).cols();
}

template <class F, class... Cs>
constexpr traits_elem_t<StreamElementWiseOperator<F, Cs...>>
StreamElementWiseOperator<F, Cs...>::operator()(size_t i, size_t j) const {
  return apply(i, j, std::index_sequence_for<Cs...>());
}

template <class F, class... Cs>
constexpr traits_elem_t<StreamElementWiseOperator<F, Cs...>>
StreamElementWiseOperator<F, Cs...>::operator()(size_t i) const {
  return apply(i, std::index_sequence_for<Cs...>());
}

template <class F, class... Cs>
template <typename T, T... S>
inline constexpr traits_elem_t<StreamElementWiseOperator<F, Cs...>>
StreamElementWiseOperator<F, Cs...>::apply(size_t i,size_t j, std::integer_sequence<T, S...>) const {
  return f(std::get<S>(cs)(i, j)...);
}

template <class F, class... Cs>
template <typename T, T... S>
inline constexpr traits_elem_t<StreamElementWiseOperator<F, Cs...>>
StreamElementWiseOperator<F, Cs...>::apply(size_t i, std::integer_sequence<T, S...>) const {
  return f(std::get<S>(cs)(i)...);
}

template <class F, class C, class... Cs>
struct _traits<StreamElementWiseOperator<F, C, Cs...>> : _traits<C> {
  typedef typename F::template expression<_traits_elem_t<C>, _traits_elem_t<Cs>...> Elem;
};
}  // namespace internal
}  // namespace lin
