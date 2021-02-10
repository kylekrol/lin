// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/diagonal_mapping_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_DIAGONAL_MAPPING_REFERENCE_HPP_
#define LIN_REFERENCES_DIAGONAL_MAPPING_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Generic diagonal reference with read and write access.
 *
 *  @tparam E Underlying referenced type.
 *
 *  This allows users to treat the diagonal elements of a mapping as a column
 *  vector. The underlying mapping must have traits making is a square matrix.
 *
 *  It's important to note, if the underlying mapping goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::DiagonalMappingReference
 *  @sa internal::is_matrix
 *  @sa internal::is_square
 */
template <class E>
class DiagonalMappingReference : public Mapping<DiagonalMappingReference<E>> {
  static_assert(is_vector<DiagonalMappingReference<E>>::value,
      "DiagonalMappingReference<...> types must have vector traits.");
  static_assert(conjunction<is_matrix<E>, is_square<E>>::value,
      "Underlying mapping for a diagonal reference must be a square matrix.");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<DiagonalMappingReference<E>> Traits;

  /** @brief %Vector traits information for this type.
   *
   *  @sa internal::vector_traits
   */
  typedef vector_traits<DiagonalMappingReference<E>> VectorTraits;

 private:
  Mapping<E> &_mapping;

 protected:
  using Mapping<DiagonalMappingReference<E>>::derived;

 public:
  using Mapping<DiagonalMappingReference<E>>::size;
  using Mapping<DiagonalMappingReference<E>>::eval;
  using Mapping<DiagonalMappingReference<E>>::operator();
  using Mapping<DiagonalMappingReference<E>>::operator=;

  constexpr DiagonalMappingReference() = delete;
  constexpr DiagonalMappingReference(DiagonalMappingReference<E> const &) = default;
  constexpr DiagonalMappingReference(DiagonalMappingReference<E> &&) = default;
  constexpr DiagonalMappingReference<E> &operator=(DiagonalMappingReference<E> const &) = default;
  constexpr DiagonalMappingReference<E> &operator=(DiagonalMappingReference<E> &&) = default;

  /** @brief Constructs a new diagonal reference with the provided mapping.
   *
   *  @param mapping Underlying mapping.
   *
   *  The provided mapping must be square at runtime or lin assertion errors
   *  will be triggered.
   *
   *  Resizing the mapping to be something other than square after construction
   *  invalidates the reference.
   */
  constexpr DiagonalMappingReference(Mapping<E> &mapping)
  : _mapping(mapping) {
    LIN_ASSERT(mapping.rows() == mapping.cols());
  }

  /** @return Number of rows.
   *
   *  This value is determined based on the size of the underlying mapping. If
   *  the mapping is resized, the returned row count may changed. If the resized
   *  mapping is no longer square, the diagonal reference is invalidated.
   */
  constexpr size_t rows() const {
    return _mapping.rows();
  }

  /** @return Number of columns.
   *
   *  This always returns one.
   */
  constexpr size_t cols() const {
    return size_t(1);
  }

  /** @brief Provides read and write access to tensor elements.
   *
   *  @param i Row index.
   *  @param j Column index.
   *
   *  @return Reference to the tensor element.
   *
   *  The diagonal of the underlying stream is exposed as a column vector.
   *
   *  If the indices are out of bounds as defined by the reference's current
   *  dimensions, lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t &operator()(size_t i, size_t j) {
    LIN_ASSERT(i >= 0 && i < rows());
    LIN_ASSERT(j >= 0 && j < rows());

    return _mapping(i, i);
  }

  /** @brief Provides read and write access to tensor elements.
   *
   *  @param i Index.
   *
   *  @return Reference to the tensor element.
   *
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   *
   *  If the index is out of bounds as defined by the reference's current size,
   *  lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t &operator()(size_t i) {
    LIN_ASSERT(i >= 0 && i < size());

    return _mapping(i, i);
  }
};

template <class E>
struct _elem<DiagonalMappingReference<E>> {
  typedef _elem_t<E> type;
};

template <class E>
struct _dims<DiagonalMappingReference<E>> {
  constexpr static size_t rows = E::Traits::rows;
  constexpr static size_t cols = 1;
  constexpr static size_t max_rows = E::Traits::max_rows;
  constexpr static size_t max_cols = 1;
};
}  // namespace internal
}  // namespace lin

#endif
