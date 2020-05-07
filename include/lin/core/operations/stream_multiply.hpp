// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/operations/stream_multiply.hpp
 *  @author Kyle Krol
 */

#include "../config.hpp"
#include "../traits.hpp"
#include "../types/stream.hpp"

#ifndef LIN_CORE_OPERATIONS_STREAM_MULTIPLY_HPP_
#define LIN_CORE_OPERATIONS_STREAM_MULTIPLY_HPP_

namespace lin {
namespace internal {

template <class C, class D, typename = void>
struct can_multiply : std::false_type { };

template <class C, class D>
struct can_multiply<C, D, std::enable_if_t<(
    is_detected<multiply::template expression, _elem_t<C>, _elem_t<D>>::value &&
    (_dims<C>::cols == _dims<D>::rows) &&
    (_dims<C>::max_cols == _dims<D>::max_rows)
  )>> : std::true_type { };

/** @brief Proxy to a lazily evalutated tensor multiplication operation.
 * 
 *  @tparam C %Tensor type.
 *  @tparam D %Tensor type.
 * 
 *  Details to come...
 * 
 *  @ingroup COREOPERATIONS
 */
template <class C, class D>
class StreamMultiply : public Stream<StreamMultiply<C, D>> {
 private:
  /** @brief %Tensor stream.
   */
  Stream<C> const &c;

  /** @brief %Tensor stream.
   */
  Stream<D> const &d;

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamMultiply<C, D>> Traits;

 protected:
  using Stream<StreamMultiply<C, D>>::derived;

 public:
  using Stream<StreamMultiply<C, D>>::size;
  using Stream<StreamMultiply<C, D>>::eval;

  constexpr StreamMultiply() = delete;
  constexpr StreamMultiply(StreamMultiply<C, D> const &) = default;
  constexpr StreamMultiply(StreamMultiply<C, D> &&) = default;
  constexpr StreamMultiply<C, D> &operator=(StreamMultiply<C, D> const &) = default;
  constexpr StreamMultiply<C, D> &operator=(StreamMultiply<C, D> &&) = default;

  /** @brief Constructs a proxy to a tensor multiplication operation.
   * 
   *  @param c %Tensor stream.
   *  @param d %Tensor stream.
   */
  constexpr StreamMultiply(Stream<C> const &c, Stream<D> const &d)
  : c(c), d(d) {
    LIN_ASSERT(c.cols() == d.rows());
  }

  /** @return Number of rows in the tensor.
   */
  constexpr size_t rows() const {
    return c.rows();
  }

  /** @return Number of columns in the tensor.
   */
  constexpr size_t cols() const {
    return d.cols();
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
    typename Traits::elem_t x = c(i, 0) * d(0, j);
    for (size_t k = 1; k < c.cols(); k++) x += c(i, k) * d(k, j);
    return x;
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
    return (*this)(i / cols(), i % cols());
  }
};

template <class C, class D>
struct _elem<StreamMultiply<C, D>> {
  typedef typename multiply::template expression<
      typename _elem<C>::type, typename _elem<D>::type
    > type;
};

template <class C, class D>
struct _dims<StreamMultiply<C, D>> {
  static constexpr size_t rows = _dims<C>::rows;
  static constexpr size_t cols = _dims<D>::cols;
  static constexpr size_t max_rows = _dims<C>::max_rows;
  static constexpr size_t max_cols = _dims<D>::max_cols;
};
}  // namespace internal
}  // namespace lin

#endif
