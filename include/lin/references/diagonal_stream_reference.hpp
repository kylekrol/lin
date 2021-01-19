// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/diagonal_stream_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_DIAGONAL_STREAM_REFERENCE_HPP_
#define LIN_REFERENCES_DIAGONAL_STREAM_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

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

  constexpr DiagonalStreamReference(Stream<E> const &stream)
  : _stream(stream) {
    LIN_ASSERT(stream.rows() == stream.cols());
  }

  constexpr size_t rows() const {
    return _stream.rows();
  }

  constexpr size_t cols() const {
    return size_t(1);
  }

  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT(i >= 0 && i < rows());
    LIN_ASSERT(j >= 0 && j < rows());

    return _stream(i, i);
  }

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
