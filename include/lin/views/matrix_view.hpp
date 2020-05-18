// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/matrix_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_MATRIX_VIEW_HPP_
#define LIN_VIEWS_MATRIX_VIEW_HPP_

#include "../core.hpp"
#include "tensor_view.hpp"

namespace lin {

/** @brief Generic matrix view.
 * 
 *  @param T  %Matrix view element type.
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
 * 
 *  @ingroup VIEWS
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
class MatrixView : public internal::TensorView<MatrixView<T, R, C, MR, MC>> {
  static_assert(internal::is_matrix<Matrix<T, R, C, MR, MC>>::value,
      "Invalid MatrixView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef internal::traits<MatrixView<T, R, C, MR, MC>> Traits;

 protected:
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::derived;

 public:
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::TensorView;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::rows;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::cols;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::size;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::data;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::eval;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::resize;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::operator=;
  using internal::TensorView<MatrixView<T, R, C, MR, MC>>::operator();

  constexpr MatrixView() = default;
  constexpr MatrixView(MatrixView<T, R, C, MR, MC> const &) = default;
  constexpr MatrixView(MatrixView<T, R, C, MR, MC> &&) = default;
  constexpr MatrixView<T, R, C, MR, MC> &operator=(MatrixView<T, R, C, MR, MC> const &) = default;
  constexpr MatrixView<T, R, C, MR, MC> &operator=(MatrixView<T, R, C, MR, MC> &&) = default;
};

/** @weakgroup VIEWS
 *  @{
 */

/** @brief Generic float matrix view.
 * 
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows.
 *  @tparam MC Maximum columns.
 * 
 *  @sa internal::traits
 *  @sa MatrixView
 */
template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using MatrixViewf = MatrixView<float, R, C, MR, MC>;

typedef MatrixViewf<2, 2> MatrixView2x2f; ///< Two by two float matrix view.
typedef MatrixViewf<3, 2> MatrixView3x2f; ///< Three by two float matrix view.
typedef MatrixViewf<4, 2> MatrixView4x2f; ///< Four by two float matrix view.
typedef MatrixViewf<2, 3> MatrixView2x3f; ///< Two by three float matrix view.
typedef MatrixViewf<3, 3> MatrixView3x3f; ///< Three by three float matrix view.
typedef MatrixViewf<4, 3> MatrixView4x3f; ///< Four by three float matrix view.
typedef MatrixViewf<2, 4> MatrixView2x4f; ///< Two by four float matrix view.
typedef MatrixViewf<3, 4> MatrixView3x4f; ///< Three by four float matrix view.
typedef MatrixViewf<4, 4> MatrixView4x4f; ///< Four by four float matrix view.

/** @brief Generic double matrix view.
 * 
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows.
 *  @tparam MC Maximum columns.
 * 
 *  @sa internal::traits
 *  @sa MatrixView
 */
template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using MatrixViewd = MatrixView<double, R, C, MR, MC>;

typedef MatrixViewd<2, 2> MatrixView2x2d; ///< Two by two double matrix view.
typedef MatrixViewd<3, 2> MatrixView3x2d; ///< Three by two double matrix view.
typedef MatrixViewd<4, 2> MatrixView4x2d; ///< Four by two double matrix view.
typedef MatrixViewd<2, 3> MatrixView2x3d; ///< Two by three double matrix view.
typedef MatrixViewd<3, 3> MatrixView3x3d; ///< Three by three double matrix view.
typedef MatrixViewd<4, 3> MatrixView4x3d; ///< Four by three double matrix view.
typedef MatrixViewd<2, 4> MatrixView2x4d; ///< Two by four double matrix view.
typedef MatrixViewd<3, 4> MatrixView3x4d; ///< Three by four double matrix view.
typedef MatrixViewd<4, 4> MatrixView4x4d; ///< Four by four double matrix view.

/** @}
 */

namespace internal {

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
