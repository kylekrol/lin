/** @file lin/core/types/vector.hpp
 *  @author Kyle Krol
 *  Defines the user-facing vector and row vector types. */

// TODO : Documentation for the vector and row vector classes

#ifndef LIN_CORE_TYPES_VECTOR_HPP_
#define LIN_CORE_TYPES_VECTOR_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "tensor.hpp"

#include <initializer_list>
#include <type_traits>

namespace lin {

/** @class Vector */
template <typename T, size_t N, size_t MN = N>
class Vector : public internal::Tensor<Vector<T, N, MN>> {
  static_assert(internal::is_col_vector<Vector<T, N, MN>>::value, "Invalid Vector<...> parameters");

 public:
  /* Import elements from internal::Tensor<Vector<T, N, MN>>. */
  using internal::Tensor<Vector<T, N, MN>>::rows;
  using internal::Tensor<Vector<T, N, MN>>::cols;
  using internal::Tensor<Vector<T, N, MN>>::size;
  using internal::Tensor<Vector<T, N, MN>>::eval;
  using internal::Tensor<Vector<T, N, MN>>::resize;
  using internal::Tensor<Vector<T, N, MN>>::operator=;
  using internal::Tensor<Vector<T, N, MN>>::operator();
  /* Include traits and vector traits information. */
  typedef internal::traits<Vector<T, N, MN>> Traits;
  typedef internal::vector_traits<Vector<T, N, MN>> VectorTraits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Vector(Vector<T, N, MN> const &) = default;
  constexpr Vector(Vector<T, N, MN> &&) = default;
  constexpr Vector<T, N, MN> &operator=(Vector<T, N, MN> const &) = default;
  constexpr Vector<T, N, MN> &operator=(Vector<T, N, MN> &&) = default;
  /* Vector constructor(s). */
  constexpr Vector(size_t n = VectorTraits::MaxLength);
  constexpr Vector(size_t r, size_t c);
  template <typename U>
  constexpr Vector(std::initializer_list<U> const &list);
  template <typename U>
  constexpr Vector(size_t n, std::initializer_list<U> const &list);
  template <typename U>
  constexpr Vector(size_t r, size_t c, std::initializer_list<U> const &list);
  template <class C>
  constexpr Vector(internal::Stream<C> const &stream);
  /* Custom vector resize function. */
  constexpr void resize(size_t n);

 protected:
  /* Import elements from internal::Tensor<Vector<T, N, MN>>. */
  using internal::Tensor<Vector<T, N, MN>>::derived;
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

/** @class RowVector */
template <typename T, size_t N, size_t MN = N>
class RowVector : public internal::Tensor<RowVector<T, N, MN>> {
  static_assert(internal::is_row_vector<RowVector<T, N, MN>>::value, "Invalid RowVector<...> parameters");

 public:
  /* Import elements from internal::Tensor<RowVector<T, N, MN>>. */
  using internal::Tensor<RowVector<T, N, MN>>::rows;
  using internal::Tensor<RowVector<T, N, MN>>::cols;
  using internal::Tensor<RowVector<T, N, MN>>::size;
  using internal::Tensor<RowVector<T, N, MN>>::eval;
  using internal::Tensor<RowVector<T, N, MN>>::resize;
  using internal::Tensor<RowVector<T, N, MN>>::operator=;
  using internal::Tensor<RowVector<T, N, MN>>::operator();
  /* Include traits and vector traits information. */
  typedef internal::traits<RowVector<T, N, MN>> Traits;
  typedef internal::vector_traits<RowVector<T, N, MN>> VectorTraits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr RowVector(RowVector<T, N, MN> const &) = default;
  constexpr RowVector(RowVector<T, N, MN> &&) = default;
  constexpr RowVector<T, N, MN> &operator=(RowVector<T, N, MN> const &) = default;
  constexpr RowVector<T, N, MN> &operator=(RowVector<T, N, MN> &&) = default;
  /* RowVector constructor(s). */
  constexpr RowVector(size_t n = VectorTraits::MaxLength);
  constexpr RowVector(size_t r, size_t c);
  template <typename U>
  constexpr RowVector(std::initializer_list<U> const &list);
  template <typename U>
  constexpr RowVector(size_t n, std::initializer_list<U> const &list);
  template <typename U>
  constexpr RowVector(size_t r, size_t c, std::initializer_list<U> const &list);
  template <class C> 
  constexpr RowVector(internal::Stream<C> const &stream);
  /* Custom row vector resize function. */
  constexpr void resize(size_t n);

 protected:
  /* Import elements from internal::Tensor<RowVector<T, N, MN>>. */
  using internal::Tensor<RowVector<T, N, MN>>::derived;
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

}  // namespace lin

#include "inl/vector.inl"

#endif
