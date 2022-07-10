// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/operations/stream_transpose.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_OPERATIONS_STREAM_TRANSPOSE_HPP_
#define LIN_CORE_OPERATIONS_STREAM_TRANSPOSE_HPP_

namespace lin {
namespace internal {

/** @brief Proxy to a lazily evalutated transpose operation.
 * 
 *  @tparam Cs %Tensor type.
 * 
 *  Details to come...
 * 
 *  @ingroup COREOPERATIONS
 */
template <class C>
class StreamTranspose : public Stream<StreamTranspose<C>> {
 private:
  /** @brief Stream reference.
   */
  Stream<C> const &c;

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamTranspose<C>> Traits;

 protected:
  using Stream<StreamTranspose<C>>::derived;

 public:
  using Stream<StreamTranspose<C>>::size;
  using Stream<StreamTranspose<C>>::eval;

  constexpr StreamTranspose() = delete;
  constexpr StreamTranspose(StreamTranspose<C> const &) = default;
  constexpr StreamTranspose(StreamTranspose<C> &&) = default;
  constexpr StreamTranspose<C> &operator=(StreamTranspose<C> const &) = default;
  constexpr StreamTranspose<C> &operator=(StreamTranspose<C> &&) = default;

  /** @brief Constructs a proxy to a tensor transpose operation.
   * 
   *  @param c %Tensor stream.
   */
  constexpr StreamTranspose(Stream<C> const &c)
  : c(c) { }

  /** @return Number of rows in the tensor.
   */
  constexpr size_t rows() const {
    return c.cols();
  }

  /** @return Number of columns in the tensor.
   */
  constexpr size_t cols() const {
    return c.rows();
  }

  /** @brief Lazily evaluates the requested tensor element.
   * 
   *  @param i Row index.
   *  @param j Column index.
   * 
   *  @return Resulting value of the tensor element.
   * 
   *  @sa internal::TensorStream::eval
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    return c(j, i);
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
   *  @sa internal::TensorStream::eval
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    return (*this)(i / cols(), i % cols());
  }
};

template <class C>
struct _elem<StreamTranspose<C>> : _elem<C> { };

template <class C>
struct _dims<StreamTranspose<C>> {
  static constexpr size_t rows = _dims<C>::cols;
  static constexpr size_t cols = _dims<C>::rows;
  static constexpr size_t max_rows = _dims<C>::max_cols;
  static constexpr size_t max_cols = _dims<C>::max_rows;
};
}  // namespace internal
}  // namespace lin

#endif
