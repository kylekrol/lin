// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/matrix.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_MATRIX_HPP_
#define LIN_CORE_TYPES_MATRIX_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "tensor.hpp"

#include <type_traits>

namespace lin {

/** @brief Generic matrix.
 * 
 *  @tparam T  %Matrix element type.
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows at compile time.
 *  @tparam MC Maximum columns at compile time.
 * 
 *  The template parameters specify the matrix's traits. The traits must qualify
 *  this type as a matrix.
 * 
 *  @sa internal::traits
 *  @sa internal::is_matrix
 *
 *  @ingroup CORETYPES
 */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
class Matrix : public internal::Tensor<Matrix<T, R, C, MR, MC>> {
  static_assert(internal::is_matrix<Matrix<T, R, C, MR, MC>>::value,
      "Invalid Matrix<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef internal::traits<Matrix<T, R, C, MR, MC>> Traits;

 protected:
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::derived;

 public:
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::Tensor;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::rows;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::cols;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::size;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::data;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::eval;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::resize;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::operator=;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::operator();

  constexpr Matrix(Matrix<T, R, C, MR, MC> const &) = default;
  constexpr Matrix(Matrix<T, R, C, MR, MC> &&) = default;
  constexpr Matrix<T, R, C, MR, MC> &operator=(Matrix<T, R, C, MR, MC> const &) = default;
  constexpr Matrix<T, R, C, MR, MC> &operator=(Matrix<T, R, C, MR, MC> &&) = default;
};

/** @weakgroup CORETYPES
 *  @{
 */

/** @brief Generic float matrix.
 * 
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows.
 *  @tparam MC Maximum columns.
 * 
 *  @sa internal::traits
 *  @sa Matrix
 */
template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using Matrixf = Matrix<float, R, C, MR, MC>;

typedef Matrixf<2, 2> Matrix2x2f; ///< Two by two float matrix.
typedef Matrixf<3, 2> Matrix3x2f; ///< Three by two float matrix.
typedef Matrixf<4, 2> Matrix4x2f; ///< Four by two float matrix.
typedef Matrixf<2, 3> Matrix2x3f; ///< Two by three float matrix.
typedef Matrixf<3, 3> Matrix3x3f; ///< Three by three float matrix.
typedef Matrixf<4, 3> Matrix4x3f; ///< Four by three float matrix.
typedef Matrixf<2, 4> Matrix2x4f; ///< Two by four float matrix.
typedef Matrixf<3, 4> Matrix3x4f; ///< Three by four float matrix.
typedef Matrixf<4, 4> Matrix4x4f; ///< Four by four float matrix.

/** @brief Generic double matrix.
 * 
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows.
 *  @tparam MC Maximum columns.
 * 
 *  @sa internal::traits
 *  @sa Matrix
 */
template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using Matrixd = Matrix<double, R, C, MR, MC>;

typedef Matrixd<2, 2> Matrix2x2d; ///< Two by two double matrix.
typedef Matrixd<3, 2> Matrix3x2d; ///< Three by two double matrix.
typedef Matrixd<4, 2> Matrix4x2d; ///< Four by two double matrix.
typedef Matrixd<2, 3> Matrix2x3d; ///< Two by three double matrix.
typedef Matrixd<3, 3> Matrix3x3d; ///< Three by three double matrix.
typedef Matrixd<4, 3> Matrix4x3d; ///< Four by three double matrix.
typedef Matrixd<2, 4> Matrix2x4d; ///< Two by four double matrix.
typedef Matrixd<3, 4> Matrix3x4d; ///< Three by four double matrix.
typedef Matrixd<4, 4> Matrix4x4d; ///< Four by four double matrix.

/** @}
 */

namespace internal {

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _elem<Matrix<T, R, C, MR, MC>> {
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _dims<Matrix<T, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};

template <class C>
struct _eval<C, std::enable_if_t<is_matrix<C>::value>> {
  typedef Matrix<
      _elem_t<C>,
      _dims<C>::rows,
      _dims<C>::cols,
      _dims<C>::max_rows,
      _dims<C>::max_cols
    > type;
};
}  // namespace internal
}  // namespace lin

#endif
