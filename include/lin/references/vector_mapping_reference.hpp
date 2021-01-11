// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/vector_mapping_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_VECTOR_MAPPING_REFERENCE_HPP_
#define LIN_REFERENCES_VECTOR_MAPPING_REFERENCE_HPP_

#include "../core.hpp"
#include "tensor_mapping_reference.hpp"

namespace lin {
namespace internal {

/** @brief Generic vector reference with read and write access.
 *
 *  @tparam E  Underlying referenced type.
 *  @tparam N  Length at compile time.
 *  @tparam MN Maximum length at compile time.
 *
 *  The template parameters specify the reference's traits. The traits must
 *  qualify the type as a column vector.
 *
 *  It's important to note, if the underlying type goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::TensorMappingReference
 *  @sa internal::traits
 *  @sa internal::is_col_vector
 *
 *  @ingroup REFERENCES
 */
template <class E, size_t N, size_t MN>
class VectorMappingReference : public TensorMappingReference<VectorMappingReference<E, N, MN>, E> {
  static_assert(is_col_vector<VectorMappingReference<E, N, MN>>::value,
      "Derived types to VectorMappingReference<...> must have column vector traits");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<VectorMappingReference<E, N, MN>> Traits;

  /** @brief %Vector traits information for this type.
   *
   *  @sa internal::vector_traits
   */
  typedef vector_traits<VectorMappingReference<E, N, MN>> VectorTraits;

 protected:
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::derived;
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::resize;

 public:
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::TensorMappingReference;
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::rows;
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::cols;
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::size;
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::operator=;
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::operator();
  using TensorMappingReference<VectorMappingReference<E, N, MN>, E>::eval;

  constexpr VectorMappingReference() = delete;
  constexpr VectorMappingReference(VectorMappingReference<E, N, MN> const &) = default;
  constexpr VectorMappingReference(VectorMappingReference<E, N, MN> &&) = default;
  constexpr VectorMappingReference<E, N, MN> &operator=(VectorMappingReference<E, N, MN> const &) = default;
  constexpr VectorMappingReference<E, N, MN> &operator=(VectorMappingReference<E, N, MN> &&) = default;

  /** @brief Constructs a new vector reference with the provided mapping, anchor
   *         point, and length.
   *
   *  @param mapping Underlying mapping.
   *  @param i       Anchor point row index.
   *  @param j       Anchor point column index.
   *  @param n       Reference length.
   *
   *  The anchor point maps the tops left corner of the reference to an element
   *  in the underlying mapping.
   *
   *  The reference vector's traits must define a type that fits within the
   *  provided mapping given the anchor point. If this is not the case, lin
   *  assertion errors will be triggered.
   *
   *  Lin assertions errors will be triggered if the requested length isn't
   *  possible given the reference's traits.
   *
   *  @sa internal::traits
   */
  constexpr VectorMappingReference(Mapping<E> &mapping, size_t i, size_t j, size_t n)
  : TensorMappingReference<VectorMappingReference<E, N, MN>, E>(mapping, i, j, n, 1) { }
};

template <class E, size_t N, size_t MN>
struct _elem<VectorMappingReference<E, N, MN>> {
  typedef _elem_t<E> type;
};

template <class E, size_t N, size_t MN>
struct _dims<VectorMappingReference<E, N, MN>> {
  static constexpr size_t rows = N;
  static constexpr size_t cols = 1;
  static constexpr size_t max_rows = MN;
  static constexpr size_t max_cols = 1;
};

/** @brief Generic row vector reference with read and write access.
 *
 *  @tparam E  Underlying referenced type.
 *  @tparam N  Length at compile time.
 *  @tparam MN Maximum length at compile time.
 *
 *  The template parameters specify the reference's traits. The traits must
 *  qualify the type as a row vector.
 *
 *  It's important to note, if the underlying type goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::TensorMappingReference
 *  @sa internal::traits
 *  @sa internal::is_row_vector
 *
 *  @ingroup REFERENCES
 */
template <class E, size_t N, size_t MN>
class RowVectorMappingReference : public TensorMappingReference<RowVectorMappingReference<E, N, MN>, E> {
  static_assert(is_row_vector<RowVectorMappingReference<E, N, MN>>::value,
      "Derived types to RowVectorMappingReference<...> must have row vector traits");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<RowVectorMappingReference<E, N, MN>> Traits;

  /** @brief %Vector traits information for this type.
   *
   *  @sa internal::vector_traits
   */
  typedef vector_traits<RowVectorMappingReference<E, N, MN>> VectorTraits;

 protected:
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::derived;
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::resize;

 public:
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::TensorMappingReference;
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::rows;
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::cols;
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::size;
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::operator=;
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::operator();
  using TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>::eval;

  constexpr RowVectorMappingReference() = delete;
  constexpr RowVectorMappingReference(RowVectorMappingReference<E, N, MN> const &) = default;
  constexpr RowVectorMappingReference(RowVectorMappingReference<E, N, MN> &&) = default;
  constexpr RowVectorMappingReference<E, N, MN> &operator=(RowVectorMappingReference<E, N, MN> const &) = default;
  constexpr RowVectorMappingReference<E, N, MN> &operator=(RowVectorMappingReference<E, N, MN> &&) = default;

  /** @brief Constructs a new row vector reference with the provided mapping,
   *         anchor point, and length.
   *
   *  @param mapping Underlying mapping.
   *  @param i       Anchor point row index.
   *  @param j       Anchor point column index.
   *  @param n       Reference length.
   *
   *  The anchor point maps the tops left corner of the reference to an element
   *  in the underlying mapping.
   *
   *  The reference row vector's traits must define a type that fits within the
   *  provided mapping given the anchor point. If this is not the case, lin
   *  assertion errors will be triggered.
   *
   *  Lin assertions errors will be triggered if the requested length isn't
   *  possible given the reference's traits.
   *
   *  @sa internal::traits
   */
  constexpr RowVectorMappingReference(Mapping<E> &mapping, size_t i, size_t j, size_t n)
  : TensorMappingReference<RowVectorMappingReference<E, N, MN>, E>(mapping, i, j, 1, n) { }
};

template <class E, size_t N, size_t MN>
struct _elem<RowVectorMappingReference<E, N, MN>> {
  typedef _elem_t<E> type;
};

template <class E, size_t N, size_t MN>
struct _dims<RowVectorMappingReference<E, N, MN>> {
  static constexpr size_t rows = 1;
  static constexpr size_t cols = N;
  static constexpr size_t max_rows = 1;
  static constexpr size_t max_cols = MN;
};
}  // namespace internal
}  // namespace lin

#endif
