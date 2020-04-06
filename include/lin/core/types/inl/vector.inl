/** @file lin/core/types/inl/vector.inl
 *  @author Kyle Krol
 *  See %lin/core/types/vector.hpp for more information. */

#include "../vector.hpp"

namespace lin {
namespace internal {

template <typename T, size_t N, size_t MN>
struct _traits<Vector<T, N, MN>> {
  typedef T Elem;
  constexpr static size_t
    Rows = N,
    Cols = 1,
    MaxRows = MN,
    MaxCols = 1;
};

template <class C>
struct _evaluates_to<C, std::enable_if_t<is_col_vector<C>::value>> {
  typedef Vector<
      _traits_elem_t<C>,
      _vector_traits<C>::Length,
      _vector_traits<C>::MaxLength
    > Eval;
};

template <typename T, size_t N, size_t MN>
struct _traits<RowVector<T, N, MN>> {
  typedef T Elem;
  constexpr static size_t
    Rows = 1,
    Cols = N,
    MaxRows = 1,
    MaxCols = MN;
};

template <class C>
struct _evaluates_to<C, std::enable_if_t<is_row_vector<C>::value>> {
  typedef RowVector<
      _traits_elem_t<C>,
      _vector_traits<C>::Length,
      _vector_traits<C>::MaxLength
    > Eval;
};
}  // namespace internal

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(size_t n) : internal::Tensor<Vector<T, N, MN>>(n, 1) { }

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(size_t r, size_t c) : internal::Tensor<Vector<T, N, MN>>(r, c) { }

template <typename T, size_t N, size_t MN>
template <typename U>
constexpr Vector<T, N, MN>::Vector(std::initializer_list<U> const &list)
: internal::Tensor<Vector<T, N, MN>>(list) { }

template <typename T, size_t N, size_t MN>
template <typename U>
constexpr Vector<T, N, MN>::Vector(size_t n, std::initializer_list<U> const &list)
: internal::Tensor<Vector<T, N, MN>>(n, 1, list) { }

template <typename T, size_t N, size_t MN>
template <typename U>
constexpr Vector<T, N, MN>::Vector(size_t r, size_t c, std::initializer_list<U> const &list)
: internal::Tensor<Vector<T, N, MN>>(r, c, list) { }

template <typename T, size_t N, size_t MN>
template <class C>
constexpr Vector<T, N, MN>::Vector(internal::Stream<C> const &stream)
: internal::Tensor<Vector<T, N, MN>>(stream) { }

template <typename T, size_t N, size_t MN>
constexpr void Vector<T, N, MN>::resize(size_t n) {
  resize(n, 1);
}

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(size_t n)
: internal::Tensor<RowVector<T, N, MN>>(1, n) { }

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(size_t r, size_t c)
: internal::Tensor<RowVector<T, N, MN>>(r, c) { }

template <typename T, size_t N, size_t MN>
template <typename U>
constexpr RowVector<T, N, MN>::RowVector(std::initializer_list<U> const &list)
: internal::Tensor<RowVector<T, N, MN>>(list) { }

template <typename T, size_t N, size_t MN>
template <typename U>
constexpr RowVector<T, N, MN>::RowVector(size_t n, std::initializer_list<U> const &list)
: internal::Tensor<RowVector<T, N, MN>>(1, n, list) { }

template <typename T, size_t N, size_t MN>
template <typename U>
constexpr RowVector<T, N, MN>::RowVector(size_t r, size_t c, std::initializer_list<U> const &list)
: internal::Tensor<RowVector<T, N, MN>>(r, c, list) { }

template <typename T, size_t N, size_t MN>
template <class C>
constexpr RowVector<T, N, MN>::RowVector(internal::Stream<C> const &stream)
: internal::Tensor<RowVector<T, N, MN>>(stream) { }

template <typename T, size_t N, size_t MN>
constexpr void RowVector<T, N, MN>::resize(size_t n) {
  resize(1, n);
}
}  // namespace lin
