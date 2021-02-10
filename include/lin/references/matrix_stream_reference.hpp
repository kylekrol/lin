// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/matrix_stream_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_MATRIX_STREAM_REFERENCE_HPP_
#define LIN_REFERENCES_MATRIX_STREAM_REFERENCE_HPP_

#include "../core.hpp"
#include "tensor_stream_reference.hpp"

namespace lin {
namespace internal {

/** @brief Generic matrix reference with read-only access.
 *
 *  @tparam E  Underlying referenced type.
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows at compile time.
 *  @tparam MC Maximum columns at compile time.
 *
 *  The template parameters specify the reference's traits. The traits must
 *  qualify the type as a matrix.
 *
 *  It's important to note, if the underlying type goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::TensorStreamReference
 *  @sa internal::traits
 *  @sa internal::is_matrix
 *
 *  @ingroup REFERENCES
 */
template <class E, size_t R, size_t C, size_t MR, size_t MC>
class MatrixStreamReference : public TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E> {
  static_assert(is_matrix<MatrixStreamReference<E, R, C, MR, MC>>::value,
      "Derived types to MatrixStreamReference<...> must have matrix traits");

 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<MatrixStreamReference<E, R, C, MR, MC>> Traits;

 protected:
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::derived;
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::resize;

 public:
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::TensorStreamReference;
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::rows;
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::cols;
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::size;
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::operator=;
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::operator();
  using TensorStreamReference<MatrixStreamReference<E, R, C, MR, MC>, E>::eval;

  constexpr MatrixStreamReference() = delete;
  constexpr MatrixStreamReference(MatrixStreamReference<E, R, C, MR, MC> const &) = default;
  constexpr MatrixStreamReference(MatrixStreamReference<E, R, C, MR, MC> &&) = default;
  constexpr MatrixStreamReference<E, R, C, MR, MC> &operator=(MatrixStreamReference<E, R, C, MR, MC> const &) = default;
  constexpr MatrixStreamReference<E, R, C, MR, MC> &operator=(MatrixStreamReference<E, R, C, MR, MC> &&) = default;
};

template <class E, size_t R, size_t C, size_t MR, size_t MC>
struct _elem<MatrixStreamReference<E, R, C, MR, MC>> {
  typedef _elem_t<E> type;
};

template <class E, size_t R, size_t C, size_t MR, size_t MC>
struct _dims<MatrixStreamReference<E, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

#endif
