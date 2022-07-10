// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/const_matrix_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_CONST_MATRIX_VIEW_HPP_
#define LIN_VIEWS_CONST_MATRIX_VIEW_HPP_

#include "../core.hpp"
#include "const_tensor_view.hpp"

namespace lin {
namespace internal {

/** @brief Generic constant matrix view.
 * 
 *  @tparam T  Constant matrix view element type.
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
class ConstMatrixView : public ConstTensorView<ConstMatrixView<T, R, C, MR, MC>> {
  static_assert(is_matrix<Matrix<T, R, C, MR, MC>>::value,
      "Invalid ConstMatrixView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<ConstMatrixView<T, R, C, MR, MC>> Traits;

 protected:
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::derived;

 public:
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::ConstTensorView;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::rows;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::cols;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::size;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::data;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::eval;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::resize;
  using ConstTensorView<ConstMatrixView<T, R, C, MR, MC>>::operator();

  constexpr ConstMatrixView() = delete;
  constexpr ConstMatrixView(ConstMatrixView<T, R, C, MR, MC> const &) = default;
  constexpr ConstMatrixView(ConstMatrixView<T, R, C, MR, MC> &&) = default;
  constexpr ConstMatrixView<T, R, C, MR, MC> &operator=(ConstMatrixView<T, R, C, MR, MC> const &) = default;
  constexpr ConstMatrixView<T, R, C, MR, MC> &operator=(ConstMatrixView<T, R, C, MR, MC> &&) = default;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _elem<ConstMatrixView<T, R, C, MR, MC>> {
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _dims<ConstMatrixView<T, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

#endif
