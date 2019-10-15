// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_MATRIX_MATRIX_HPP_
#define LIN_INCLUDE_CORE_MATRIX_MATRIX_HPP_

#include "traits.hpp"
#include "../tensor/tensor.hpp"
#include "../tensor/traits.hpp"

#include <type_traits>

namespace lin
{

template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
class Matrix : public internal::Tensor<Matrix<T, R, C, MR, MC>>
{
  static_assert(internal::is_matrix<Matrix<T, R, C, MR, MC>>::value,
      "Invalid Matrix<...> template parameters.");

 public:
  typedef internal::traits<Matrix<T, R, C, MR, MC>> Traits;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::resize;
  using internal::Tensor<Matrix<T, R, C, MR, MC>>::operator=;
  constexpr Matrix() = default;
  constexpr Matrix(size_t r, size_t c);
  constexpr Matrix(std::initializer_list<typename Traits::elem> const &l);
  constexpr Matrix(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class _E>
  constexpr Matrix(internal::Stream<_E> const &E);
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

namespace internal
{

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct elem<Matrix<T, R, C, MR, MC>>
{
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct dims<Matrix<T, R, C, MR, MC>>
{
  enum {
    rows = R,
    cols = C,
    max_rows = MR,
    max_cols = MC
  };
};

template <class A>
struct eval<A, typename std::enable_if<is_matrix<A>::value>::type>
{
  typedef Matrix<
      typename elem<A>::type,
      dims<A>::rows,
      dims<A>::cols,
      dims<A>::max_rows,
      dims<A>::max_cols
    > type;
};
}  // namespace internal
}  // namespace lin

#include "inl/matrix.inl"

#endif
