/** @file lin/core/operations/element_wise_operator.hpp
 *  @author Kyle Krol
 *  Defines the element wise operator stream. */

// TODO : Documentation for this entire file

#ifndef LIN_CORE_OPERATIONS_ELEMENT_WISE_OPERATOR_HPP_
#define LIN_CORE_OPERATIONS_ELEMENT_WISE_OPERATOR_HPP_

#include "../config.hpp"
#include "../types.hpp"

#include <tuple>
#include <utility>

namespace lin {
namespace internal {

/** @struct can_element_wise_operate */
template <class F, class... Cs>
struct can_element_wise_operate;

/** @class StreamElementWiseOperator */
template <class F, class... Cs>
class StreamElementWiseOperator : public Stream<StreamElementWiseOperator<F, Cs...>> {
  static_assert(sizeof...(Cs) > 0, "Argument pack must contain at least one type");
  static_assert(can_element_wise_operate<F, Cs...>::value, "Can't element wise operated on the given types");

 public:
  /* Import elements from Stream<StreamElementWiseOperator<F, Cs...>>. */
  using Stream<StreamElementWiseOperator<F, Cs...>>::size;
  using Stream<StreamElementWiseOperator<F, Cs...>>::eval;
  /* Include traits information. */
  typedef traits<StreamElementWiseOperator<F, Cs...>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamElementWiseOperator() = delete;
  constexpr StreamElementWiseOperator(StreamElementWiseOperator<F, Cs...> const &) = default;
  constexpr StreamElementWiseOperator(StreamElementWiseOperator<F, Cs...> &&) = default;
  constexpr StreamElementWiseOperator<F, Cs...> &operator=(StreamElementWiseOperator<F, Cs...> const &) = default;
  constexpr StreamElementWiseOperator<F, Cs...> &operator=(StreamElementWiseOperator<F, Cs...> &&) = default;
  /* StreamElementWiseOperator constructor(s). */
  template <typename... Ts>
  constexpr StreamElementWiseOperator(Stream<Cs> const &... cs, Ts &&... fargs);
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamElementWiseOperator<F, Cs...>>. */
  using Stream<StreamElementWiseOperator<F, Cs...>>::derived;

 private:
  /* Private member variables. */
  F const f;
  std::tuple<Stream<Cs> const &...> const cs;
  /* Private helper functions. */
  template <typename T, T... S>
  inline constexpr typename Traits::Elem apply(size_t i, size_t j, std::integer_sequence<T, S...>) const;
  template <typename T, T... S>
  inline constexpr typename Traits::Elem apply(size_t i, std::integer_sequence<T, S...>) const;
};
}  // namespace internal
}  // namespace lin

#include "inl/element_wise_operator.inl"

#endif
