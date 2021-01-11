// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/vector_stream_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_VECTOR_STREAM_REFERENCE_HPP_
#define LIN_REFERENCES_VECTOR_STREAM_REFERENCE_HPP_

#include "../core.hpp"
#include "tensor_stream_reference.hpp"

namespace lin {
namespace internal {

/** @brief Generic vector reference with read only access.
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
 *  @sa internal::TensorStreamReference
 *  @sa internal::traits
 *  @sa internal::is_col_vector
 *
 *  @ingroup REFERENCES
 */
template <class E, size_t N, size_t MN>
class VectorStreamReference : public TensorStreamReference<VectorStreamReference<E, N, MN>, E> {
  static_assert(is_col_vector<VectorStreamReference<E, N, MN>>::value,
      "Derived types to VectorStreamReference<...> must have column vector traits");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<VectorStreamReference<E, N, MN>> Traits;

  /** @brief %Vector traits information for this type.
   *
   *  @sa internal::vector_traits
   */
  typedef vector_traits<VectorStreamReference<E, N, MN>> VectorTraits;

 protected:
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::derived;
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::resize;

 public:
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::TensorStreamReference;
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::rows;
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::cols;
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::size;
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::operator=;
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::operator();
  using TensorStreamReference<VectorStreamReference<E, N, MN>, E>::eval;

  constexpr VectorStreamReference() = delete;
  constexpr VectorStreamReference(VectorStreamReference<E, N, MN> const &) = default;
  constexpr VectorStreamReference(VectorStreamReference<E, N, MN> &&) = default;
  constexpr VectorStreamReference<E, N, MN> &operator=(VectorStreamReference<E, N, MN> const &) = default;
  constexpr VectorStreamReference<E, N, MN> &operator=(VectorStreamReference<E, N, MN> &&) = default;

  /** @brief Constructs a new vector reference with the provided stream, anchor
   *         point, and length.
   *
   *  @param stream Underlying stream.
   *  @param i      Anchor point row index.
   *  @param j      Anchor point column index.
   *  @param n      Reference length.
   *
   *  The anchor point maps the tops left corner of the reference to an element
   *  in the underlying stream.
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
  constexpr VectorStreamReference(Stream<E> const &stream, size_t i, size_t j, size_t n)
  : TensorStreamReference<VectorStreamReference<E, N, MN>, E>(stream, i, j, n, 1) { }
};

template <class E, size_t N, size_t MN>
struct _elem<VectorStreamReference<E, N, MN>> {
  typedef _elem_t<E> type;
};

template <class E, size_t N, size_t MN>
struct _dims<VectorStreamReference<E, N, MN>> {
  static constexpr size_t rows = N;
  static constexpr size_t cols = 1;
  static constexpr size_t max_rows = MN;
  static constexpr size_t max_cols = 1;
};

/** @brief Generic row vector reference with read only access.
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
 *  @sa internal::TensorStreamReference
 *  @sa internal::traits
 *  @sa internal::is_row_vector
 *
 *  @ingroup REFERENCES
 */
template <class E, size_t N, size_t MN>
class RowVectorStreamReference : public TensorStreamReference<RowVectorStreamReference<E, N, MN>, E> {
  static_assert(is_row_vector<RowVectorStreamReference<E, N, MN>>::value,
      "Derived types to RowVectorStreamReference<...> must have row vector traits");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<RowVectorStreamReference<E, N, MN>> Traits;

  /** @brief %Vector traits information for this type.
   *
   *  @sa internal::vector_traits
   */
  typedef vector_traits<RowVectorStreamReference<E, N, MN>> VectorTraits;

 protected:
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::derived;
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::resize;

 public:
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::TensorStreamReference;
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::rows;
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::cols;
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::size;
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::operator=;
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::operator();
  using TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>::eval;

  constexpr RowVectorStreamReference() = delete;
  constexpr RowVectorStreamReference(RowVectorStreamReference<E, N, MN> const &) = default;
  constexpr RowVectorStreamReference(RowVectorStreamReference<E, N, MN> &&) = default;
  constexpr RowVectorStreamReference<E, N, MN> &operator=(RowVectorStreamReference<E, N, MN> const &) = default;
  constexpr RowVectorStreamReference<E, N, MN> &operator=(RowVectorStreamReference<E, N, MN> &&) = default;

  /** @brief Constructs a new row vector reference with the provided mapping,
   *         anchor point, and length.
   *
   *  @param stream Underlying stream.
   *  @param i      Anchor point row index.
   *  @param j      Anchor point column index.
   *  @param n      Reference length.
   *
   *  The anchor point maps the tops left corner of the reference to an element
   *  in the underlying stream.
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
  constexpr RowVectorStreamReference(Stream<E> const &stream, size_t i, size_t j, size_t n)
  : TensorStreamReference<RowVectorStreamReference<E, N, MN>, E>(stream, i, j, 1, n) { }
};

template <class E, size_t N, size_t MN>
struct _elem<RowVectorStreamReference<E, N, MN>> {
  typedef _elem_t<E> type;
};

template <class E, size_t N, size_t MN>
struct _dims<RowVectorStreamReference<E, N, MN>> {
  static constexpr size_t rows = 1;
  static constexpr size_t cols = N;
  static constexpr size_t max_rows = 1;
  static constexpr size_t max_cols = MN;
};
}  // namespace internal
}  // namespace lin

#endif
