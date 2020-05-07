// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/operations/stream_element_wise_operator.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_STREAM_ELEMENT_WISE_OPERATOR_HPP_
#define LIN_CORE_STREAM_ELEMENT_WISE_OPERATOR_HPP_

#include "../config.hpp"
#include "../types/stream.hpp"

#include <tuple>
#include <type_traits>
#include <utility>

namespace lin {
namespace internal {

/** @brief Proxy to a lazily evalutated element wise operation.
 * 
 *  @tparam F  Functor type.
 *  @tparam Cs Arguments' tensor types.
 * 
 *  Details to come...
 * 
 *  @ingroup COREOPERATIONS
 */
template <class F, class... Cs>
class StreamElementWiseOperator : public Stream<StreamElementWiseOperator<F, Cs...>> {
  template <class G, class... Ds>
  struct can_element_wise_operate : conjunction<
      is_detected<G::template expression, _elem_t<Ds>...>,
      have_same_dimensions<Ds...>
    > { };

  static_assert(sizeof...(Cs) > 0,
      "Arguments pack to StreamElementWiseOperator<...> must contain at least one argument");
  static_assert(can_element_wise_operate<F, Cs...>::value,
      "Invalid StreamElementWiseOperator<...> parameters");

 private:
  /** @brief Element wise functor.
   */
  F const f;

  /** @brief Tuple of stream references.
   */
  std::tuple<Stream<Cs> const &...> const cs;

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamElementWiseOperator<F, Cs...>> Traits;

 private:
  template <typename T, T... S>
  inline constexpr typename Traits::elem_t apply(size_t i, size_t j, std::integer_sequence<T, S...>) const {
    return f(std::get<S>(cs)(i, j)...);
  }

  template <typename T, T... S>
  inline constexpr typename Traits::elem_t apply(size_t i, std::integer_sequence<T, S...>) const {
    return f(std::get<S>(cs)(i)...);
  }

 protected:
  using Stream<StreamElementWiseOperator<F, Cs...>>::derived;

 public:
  using Stream<StreamElementWiseOperator<F, Cs...>>::size;
  using Stream<StreamElementWiseOperator<F, Cs...>>::eval;
  
  constexpr StreamElementWiseOperator() = delete;
  constexpr StreamElementWiseOperator(StreamElementWiseOperator<F, Cs...> const &) = default;
  constexpr StreamElementWiseOperator(StreamElementWiseOperator<F, Cs...> &&) = default;
  constexpr StreamElementWiseOperator<F, Cs...> &operator=(StreamElementWiseOperator<F, Cs...> const &) = default;
  constexpr StreamElementWiseOperator<F, Cs...> &operator=(StreamElementWiseOperator<F, Cs...> &&) = default;

  /** @brief Constructs a proxy to an element wise tensor operation.
   * 
   *  @tparam Ts    Forwarded functor constructor arguments' types.
   *  @param  cs    %Tensor streams.
   *  @param  fargs Forwarded functor constructor arguments.
   */
  template <typename... Ts>
  constexpr StreamElementWiseOperator(Stream<Cs> const &... cs, Ts &&... fargs)
  : f(fargs...), cs(cs...) { }

  /** @return Number of rows in the tensor.
   */
  inline constexpr size_t rows() const {
    return std::get<0>(cs).rows();
  }

  /** @return Number of columns in the tensor.
   */
  inline constexpr size_t cols() const {
    return std::get<0>(cs).cols();
  }

  /** @brief Lazily evaluates the requested tensor element.
   * 
   *  @param i Row index.
   *  @param j Column index.
   * 
   *  @return Resulting value of the tensor element.
   * 
   *  You may want to consider for the creation of a value backed type to reduce
   *  overhead.
   * 
   *  @sa internal::Stream::eval
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    return apply(i, j, std::index_sequence_for<Cs...>());
  }

  /** @brief Lazily evaluates the requested tensor element.
   * 
   *  @param i Index.
   * 
   *  @return Resulting value of the tensor element.
   * 
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   * 
   *  You may want to consider for the creation of a value backed type to reduce
   *  overhead.
   * 
   *  @sa internal::Stream::eval
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    return apply(i, std::index_sequence_for<Cs...>());
  }
};

template <class F, class... Cs>
struct _elem<StreamElementWiseOperator<F, Cs...>> {
  typedef typename F::template expression<_elem_t<Cs>...> type;
};

template <class F, class C, class... Cs>
struct _dims<StreamElementWiseOperator<F, C, Cs...>> : _dims<C> { };

}  // namespace internal
}  // namespace lin

#endif
