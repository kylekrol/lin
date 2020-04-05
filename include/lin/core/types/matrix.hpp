/** @file lin/core/types/matrix.hpp
 *  @author Kyle Krol
 *  Defines the user-facing matrix types. */

// TODO : Documentation for the matrix class

#ifndef LIN_CORE_TYPES_MATRIX_HPP_
#define LIN_CORE_TYPES_MATRIX_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "tensor.hpp"

#include <initializer_list>
#include <type_traits>

namespace lin {

/** @class Matrix */
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
class Matrix : public internal::Tensor<Matrix<T, R, C, MR, MC>> {
  static_assert(internal::is_matrix<Matrix<T, R, C, MR, MC>>::value, "Invalid Matrix<...> parameters");

 public:
  /* Import elements from internal::Tensor<Matrix<T, R, C, MR, MC>>. */
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::rows;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::cols;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::size;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::eval;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::resize;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::operator=;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::operator();
  /* Include traits information. */
  typedef internal::traits<Matrix<T, R, C, MR, MC>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Matrix(Matrix<T, R, C, MR, MC> const &) = default;
  constexpr Matrix(Matrix<T, R, C, MR, MC> &&) = default;
  constexpr Matrix<T, R, C, MR, MC> &operator=(Matrix<T, R, C, MR, MC> const &) = default;
  constexpr Matrix<T, R, C, MR, MC> &operator=(Matrix<T, R, C, MR, MC> &&) = default;
  /* Vector constructor(s). */
  constexpr Matrix(size_t r = Traits::MaxRows, size_t c = Traits::MaxCols);
  template <typename U>
  constexpr Matrix(std::initializer_list<U> const &list);
  template <typename U>
  constexpr Matrix(size_t r, size_t c, std::initializer_list<U> const &list);
  template <class D>
  constexpr Matrix(internal::Stream<D> const &stream);

 protected:
  /* Import elements from internal::Tensor<Matrix<T, R, C, MR, MC>>. */
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::derived;
};

template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using Matrixf = Matrix<float, R, C, MR, MC>;

typedef Matrixf<2, 2> Matrix2x2f;
typedef Matrixf<3, 2> Matrix3x2f;
typedef Matrixf<4, 2> Matrix4x2f;
typedef Matrixf<2, 3> Matrix2x3f;
typedef Matrixf<3, 3> Matrix3x3f;
typedef Matrixf<4, 3> Matrix4x3f;
typedef Matrixf<2, 4> Matrix2x4f;
typedef Matrixf<3, 4> Matrix3x4f;
typedef Matrixf<4, 4> Matrix4x4f;

template <size_t R, size_t C, size_t MR = R, size_t MC = C>
using Matrixd = Matrix<double, R, C, MR, MC>;

typedef Matrixd<2, 2> Matrix2x2d;
typedef Matrixd<3, 2> Matrix3x2d;
typedef Matrixd<4, 2> Matrix4x2d;
typedef Matrixd<2, 3> Matrix2x3d;
typedef Matrixd<3, 3> Matrix3x3d;
typedef Matrixd<4, 3> Matrix4x3d;
typedef Matrixd<2, 4> Matrix2x4d;
typedef Matrixd<3, 4> Matrix3x4d;
typedef Matrixd<4, 4> Matrix4x4d;

}  // namespace lin

#include "inl/matrix.inl"

#endif
