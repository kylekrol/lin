// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/diagonal_stream_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_DIAGONAL_STREAM_REFERENCE_HPP_
#define LIN_REFERENCES_DIAGONAL_STREAM_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Generic diagonal reference with read only access.
 *
 *  @tparam E Underlying referenced type.
 *
 *  This allows users to treat the diagonal elements of a stream as a column
 *  vector. The underlying stream must have traits making is a square matrix.
 *
 *  It's important to note, if the underlying stream goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::DiagonalMappingReference
 *  @sa internal::is_matrix
 *  @sa internal::is_square
 */
template <class E>
class DiagonalStreamReference : public Stream<DiagonalStreamReference<E>> {
  static_assert(is_vector<DiagonalStreamReference<E>>::value,
      "DiagonalStreamReference<...> types must have vector traits.");
  static_assert(conjunction<is_matrix<E>, is_square<E>>::value,
      "Underlying mapping for a diagonal reference must be a square matrix.");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<DiagonalStreamReference<E>> Traits;

  /** @brief %Vector traits information for this type.
   *
   *  @sa internal::vector_traits
   */
  typedef vector_traits<DiagonalStreamReference<E>> VectorTraits;

 private:
  Stream<E> const &_stream;

 protected:
  using Stream<DiagonalStreamReference<E>>::derived;

 public:
  using Stream<DiagonalStreamReference<E>>::size;
  using Stream<DiagonalStreamReference<E>>::eval;

  constexpr DiagonalStreamReference() = delete;
  constexpr DiagonalStreamReference(DiagonalStreamReference<E> const &) = default;
  constexpr DiagonalStreamReference(DiagonalStreamReference<E> &&) = default;
  constexpr DiagonalStreamReference<E> &operator=(DiagonalStreamReference<E> const &) = default;
  constexpr DiagonalStreamReference<E> &operator=(DiagonalStreamReference<E> &&) = default;

  /** @brief Constructs a new diagonal reference with the provided stream.
   *
   *  @param stream Underlying stream.
   *
   *  The provided stream must be square at runtime or lin assertion errors will
   *  be triggered.
   *
   *  Resizing the stream to be something other than square after construction
   *  invalidates the reference.
   */
  constexpr DiagonalStreamReference(Stream<E> const &stream)
  : _stream(stream) {
    LIN_ASSERT(stream.rows() == stream.cols());
  }

  /** @return Number of rows.
   *
   *  This value is determined based on the size of the underlying stream. If
   *  the stream is resized, the returned row count may changed. If the resized
   *  stream is no longer square, the diagonal reference is invalidated.
   */
  constexpr size_t rows() const {
    return _stream.rows();
  }

  /** @return Number of columns.
   *
   *  This always returns one.
   */
  constexpr size_t cols() const {
    return size_t(1);
  }

  /** @brief Provides read only access to tensor elements.
   *
   *  @param i Row index.
   *  @param j Column index.
   *
   *  @return Value of the tensor element.
   *
   *  The diagonal of the underlying stream is exposed as a column vector.
   *
   *  If the indices are out of bounds as defined by the reference's current
   *  dimensions, lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT(i >= 0 && i < rows());
    LIN_ASSERT(j >= 0 && j < cols());

    return _stream(i, i);
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
   *  If the index is out of bounds as defined by the reference's current size,
   *  lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    LIN_ASSERT(i >= 0 && i < size());

    return _stream(i, i);
  }
};

template <class E>
struct _elem<DiagonalStreamReference<E>> {
  typedef _elem_t<E> type;
};

template <class E>
struct _dims<DiagonalStreamReference<E>> {
  constexpr static size_t rows = E::Traits::rows;
  constexpr static size_t cols = 1;
  constexpr static size_t max_rows = E::Traits::max_rows;
  constexpr static size_t max_cols = 1;
};
}  // namespace internal
}  // namespace lin

#endif
