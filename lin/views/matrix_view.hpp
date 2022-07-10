// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/matrix_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_MATRIX_VIEW_HPP_
#define LIN_VIEWS_MATRIX_VIEW_HPP_

#include "../core.hpp"
#include "tensor_view.hpp"

namespace lin {
namespace internal {

/** @brief Generic matrix view.
 * 
 *  @tparam T  %Matrix view element type.
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows at compile time.
 *  @tparam MC Maximum columns at compile time.
 * 
 *  The template parameters specify the matrix view's traits. The traits must
 *  qualify this type as a matrix.
 * 
 *  @sa internal::traits
 *  @sa internal::is_matrix
 *  @sa internal::TensorView
 * 
 *  @ingroup VIEWS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
class MatrixView : public TensorView<MatrixView<T, R, C, MR, MC>> {
  static_assert(is_matrix<Matrix<T, R, C, MR, MC>>::value,
      "Invalid MatrixView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<MatrixView<T, R, C, MR, MC>> Traits;

 protected:
  using TensorView<MatrixView<T, R, C, MR, MC>>::derived;

 public:
  using TensorView<MatrixView<T, R, C, MR, MC>>::TensorView;
  using TensorView<MatrixView<T, R, C, MR, MC>>::rows;
  using TensorView<MatrixView<T, R, C, MR, MC>>::cols;
  using TensorView<MatrixView<T, R, C, MR, MC>>::size;
  using TensorView<MatrixView<T, R, C, MR, MC>>::data;
  using TensorView<MatrixView<T, R, C, MR, MC>>::eval;
  using TensorView<MatrixView<T, R, C, MR, MC>>::resize;
  using TensorView<MatrixView<T, R, C, MR, MC>>::operator=;
  using TensorView<MatrixView<T, R, C, MR, MC>>::operator();

  constexpr MatrixView() = default;
  constexpr MatrixView(MatrixView<T, R, C, MR, MC> const &) = default;
  constexpr MatrixView(MatrixView<T, R, C, MR, MC> &&) = default;
  constexpr MatrixView<T, R, C, MR, MC> &operator=(MatrixView<T, R, C, MR, MC> const &) = default;
  constexpr MatrixView<T, R, C, MR, MC> &operator=(MatrixView<T, R, C, MR, MC> &&) = default;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _elem<MatrixView<T, R, C, MR, MC>> {
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _dims<MatrixView<T, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

#endif
