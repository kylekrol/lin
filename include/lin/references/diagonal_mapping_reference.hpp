// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/diagonal_mapping_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_DIAGONAL_MAPPING_REFERENCE_HPP_
#define LIN_REFERENCES_DIAGONAL_MAPPING_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

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

  constexpr DiagonalMappingReference(Mapping<E> &mapping)
  : _mapping(mapping) {
    LIN_ASSERT(mapping.rows() == mapping.cols());
  }

  constexpr size_t rows() const {
    return _mapping.rows();
  }

  constexpr size_t cols() const {
    return size_t(1);
  }

  constexpr typename Traits::elem_t &operator()(size_t i, size_t j) {
    LIN_ASSERT(i >= 0 && i < rows());
    LIN_ASSERT(j >= 0 && j < rows());

    return _mapping(i, i);
  }

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
