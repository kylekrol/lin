// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_VECTOR_VECTOR_HPP_
#define LIN_INCLUDE_CORE_VECTOR_VECTOR_HPP_

#include "traits.hpp"
#include "../tensor/tensor.hpp"
#include "../tensor/traits.hpp"

#include <type_traits>

namespace lin
{

template <typename T, size_t N, size_t MN = N>
class RowVector : public internal::Tensor<RowVector<T, N, MN>>
{
  static_assert(internal::is_row_vector<RowVector<T, N, MN>>::value,
      "Invalid RowVector<...> template parameters.");

 public:
  typedef internal::traits<RowVector<T, N, MN>> Traits;
  using internal::Tensor<RowVector<T, N, MN>>::resize;
  using internal::Tensor<RowVector<T, N, MN>>::operator=;
  constexpr RowVector() = default;
  constexpr RowVector(size_t n);
  constexpr RowVector(size_t r, size_t c);
  constexpr RowVector(std::initializer_list<typename Traits::elem> const &l);
  constexpr RowVector(size_t n, std::initializer_list<typename Traits::elem> const &l);
  constexpr RowVector(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class _E>
  constexpr RowVector(internal::Stream<_E> const &E);
  constexpr void resize(size_t n);
};

template <size_t N, size_t MN = N>
using RowVectorf = RowVector<float, N, MN>;

typedef RowVectorf<2> RowVector2f;
typedef RowVectorf<3> RowVector3f;
typedef RowVectorf<4> RowVector4f;

template <size_t N, size_t MN = N>
using RowVectord = RowVector<double, N, MN>;

typedef RowVectord<2> RowVector2d;
typedef RowVectord<3> RowVector3d;
typedef RowVectord<4> RowVector4d;

template <typename T, size_t N, size_t MN = N>
class Vector : public internal::Tensor<Vector<T, N, MN>>
{
  static_assert(internal::is_col_vector<Vector<T, N, MN>>::value,
      "Invalid Vector<...> template parameters.");

 public:
  typedef internal::traits<Vector<T, N, MN>> Traits;
  using internal::Tensor<Vector<T, N, MN>>::resize;
  using internal::Tensor<Vector<T, N, MN>>::operator=;
  constexpr Vector() = default;
  constexpr Vector(size_t n);
  constexpr Vector(size_t r, size_t c);
  constexpr Vector(std::initializer_list<typename Traits::elem> const &l);
  constexpr Vector(size_t n, std::initializer_list<typename Traits::elem> const &l);
  constexpr Vector(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class _E>
  constexpr Vector(internal::Stream<_E> const &E);
  constexpr void resize(size_t n);
};

template <size_t N, size_t MN = N>
using Vectorf = Vector<float, N, MN>;

typedef Vectorf<2> Vector2f;
typedef Vectorf<3> Vector3f;
typedef Vectorf<4> Vector4f;

template <size_t N, size_t MN = N>
using Vectord = Vector<double, N, MN>;

typedef Vectord<2> Vector2d;
typedef Vectord<3> Vector3d;
typedef Vectord<4> Vector4d;

namespace internal
{

template <typename T, size_t N, size_t MN>
struct elem<RowVector<T, N, MN>>
{
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct dims<RowVector<T, N, MN>>
{
  enum {
    rows = 1,
    cols = N,
    max_rows = 1,
    max_cols = MN
  };
};

template <class A>
struct eval<A, typename std::enable_if<is_row_vector<A>::value>::type>
{
  typedef RowVector<
      typename elem<A>::type,
      dims<A>::cols,
      dims<A>::max_cols
    > type;
};

template <typename T, size_t N, size_t MN>
struct elem<Vector<T, N, MN>>
{
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct dims<Vector<T, N, MN>>
{
  enum {
    rows = N,
    cols = 1,
    max_rows = MN,
    max_cols = 1
  };
};

template <class A>
struct eval<A, typename std::enable_if<is_col_vector<A>::value>::type>
{
  typedef Vector<
      typename elem<A>::type,
      dims<A>::rows,
      dims<A>::max_rows
    > type;
};
}  // namespace internal
}  // namespace lin

#include "inl/vector.inl"

#endif
