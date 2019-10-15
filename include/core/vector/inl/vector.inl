// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../vector.hpp"

namespace lin
{

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(size_t n)
: internal::Tensor<RowVector<T, N, MN>>(1, n) { }

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(size_t r, size_t c)
: internal::Tensor<RowVector<T, N, MN>>(r, c) { }

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<RowVector<T, N, MN>>(l) { }

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(size_t n,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<RowVector<T, N, MN>>(1, n, l) { }

template <typename T, size_t N, size_t MN>
constexpr RowVector<T, N, MN>::RowVector(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<RowVector<T, N, MN>>(r, c, l) { }

template <typename T, size_t N, size_t MN> template <class _E>
constexpr RowVector<T, N, MN>::RowVector(internal::Stream<_E> const &E)
: internal::Tensor<RowVector<T, N, MN>>(E) { }

template <typename T, size_t N, size_t MN>
constexpr void RowVector<T, N, MN>::resize(size_t n)
{
  resize(1, n);
}

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(size_t n)
: internal::Tensor<Vector<T, N, MN>>(n, 1) { }

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(size_t r, size_t c)
: internal::Tensor<Vector<T, N, MN>>(r, c) { }

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Vector<T, N, MN>>(l) { }

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(size_t n,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Vector<T, N, MN>>(n, 1, l) { }

template <typename T, size_t N, size_t MN>
constexpr Vector<T, N, MN>::Vector(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Vector<T, N, MN>>(r, c, l) { }

template <typename T, size_t N, size_t MN> template <class _E>
constexpr Vector<T, N, MN>::Vector(internal::Stream<_E> const &E)
: internal::Tensor<Vector<T, N, MN>>(E) { }

template <typename T, size_t N, size_t MN>
constexpr void Vector<T, N, MN>::resize(size_t n)
{
  resize(n, 1);
}
}  // namespace lin
