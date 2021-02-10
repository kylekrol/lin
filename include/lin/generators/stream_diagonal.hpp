// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/stream_diagonal.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_STREAM_DIAGONAL_HPP_
#define LIN_GENERATORS_STREAM_DIAGONAL_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Tensor stream where all elements are zeros expects the elements on
 *         on the diagonal specified by an underlying stream.
 *
 *  @tparam E Underlying vector stream.
 *
 *  This allows a user to sparesly define a square matrix stream where all
 *  elements evaluate to zero except for the those along the diagonal, which are
 *  specified by the elements of an underlying vector.
 *
 *  Note the if the underlying vector goes out of scope the diagonal stream is
 *  invalidated.
 *
 *  @sa internal::is_matrix
 *  @sa internal::is_square
 *
 *  @ingroup GENERATORS
 */
template <class E>
class StreamDiagonal : public Stream<StreamDiagonal<E>> {
  static_assert(conjunction<is_matrix<StreamDiagonal<E>>, is_square<StreamDiagonal<E>>>::value,
      "StreamDiagonal must have square, matrix traits");
  static_assert(is_vector<E>::value,
      "Backing type for a StreamDiagonal must have vector traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamDiagonal<E>> Traits;

 private:
  Stream<E> const &_stream;

 protected:
  using Stream<StreamDiagonal<E>>::derived;

 public:
  using Stream<StreamDiagonal<E>>::size;
  using Stream<StreamDiagonal<E>>::eval;

  constexpr StreamDiagonal() = delete;
  constexpr StreamDiagonal(StreamDiagonal<E> const &) = default;
  constexpr StreamDiagonal(StreamDiagonal<E> &&) = default;
  constexpr StreamDiagonal<E> &operator=(StreamDiagonal<E> const &) = default;
  constexpr StreamDiagonal<E> &operator=(StreamDiagonal<E> &&) = default;

  /** @brief Constructs a new diagonal stream from the provided vector stream.
   *
   *  @param stream Underlying vector stream
   *
   *  The provided vector streams length will determine the runtime dimensions
   *  of the diagonal stream.
   *
   *  Changes in element values and dimensions of the underlying vector stream
   *  will be reflected in the stream itself. The underlying stream must be in
   *  scope for the stream to be valid.
   */
  constexpr StreamDiagonal(Stream<E> const &stream)
  : _stream(stream) { }

  /** @return Number of rows.
   *
   *  Equals the size of the underlying vector.
   */
  constexpr size_t rows() const {
    return _stream.size();
  }

  /** @return Number of rows.
   *
   *  Equals the size of the underlying vector.
   */
  constexpr size_t cols() const {
    return _stream.size();
  }

  /** @brief Provides read only access to tensor elements.
   *
   *  @param i Row index.
   *  @param j Column index.
   *
   *  @return Value of the tensor element.
   *
   *  Zero if off the main diagonal and specified by the underlying vector
   *  stream otherwise.
   * 
   *  If the indices are out of bounds as defined by the stream's current
   *  dimensions, lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT(0 <= i && i <= rows());
    LIN_ASSERT(0 <= j && j <= cols());

    return i == j ? _stream(i) : typename Traits::elem_t(0);
  }

  /** @brief Provides read only access to tensor elements.
   *
   *  @param i Index.
   *
   *  @return Value of the tensor element.
   *
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   *
   *  Zero if off the main diagonal and specified by the underlying vector
   *  stream otherwise.
   *
   *  If the index is out of bounds as defined by the stream's current size, lin
   *  assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    LIN_ASSERT(0 <= i && i <= size());

    return (*this)(i / cols(), i % cols());
  }
};

template <class E>
struct _elem<StreamDiagonal<E>> {
  typedef _elem_t<E> type;
};

template <class E>
struct _dims<StreamDiagonal<E>> {
  static constexpr size_t rows = _vector_dims<E>::length;
  static constexpr size_t cols = _vector_dims<E>::length;
  static constexpr size_t max_rows = _vector_dims<E>::max_length;
  static constexpr size_t max_cols = _vector_dims<E>::max_length;
};
}  // namespace internal
}  // namespace lin

#endif
