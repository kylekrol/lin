// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../operations.hpp"

namespace lin
{
namespace internal
{

template <class _A, class _B>
constexpr Add<_A, _B>::Add(Stream<_A> const &A, Stream<_B> const &B)
: A(A), B(B)
{
  assert(A.rows() == B.rows() /* Invalid rows in Add<...>::Add */);
  assert(A.cols() == B.cols() /* Invalid cols in Add<...>::Add */);
}

template <class _A, class _B>
constexpr size_t Add<_A, _B>::rows() const
{
  return A.rows();
}

template <class _A, class _B>
constexpr size_t Add<_A, _B>::cols() const
{
  return A.cols();
}

template <class _A, class _B>
constexpr typename Add<_A, _B>::Traits::elem
Add<_A, _B>::operator()(size_t i, size_t j) const
{
  return A(i, j) + B(i, j);
}

template <class _A, class _B>
constexpr typename Add<_A, _B>::Traits::elem
Add<_A, _B>::operator()(size_t i) const
{
  return A(i) + B(i);
}

template <class _A, class _B>
constexpr Subtract<_A, _B>::Subtract(Stream<_A> const &A, Stream<_B> const &B)
: A(A), B(B)
{
  assert(A.rows() == B.rows() /* Invalid rows in Subtract<...>::Subtract */);
  assert(A.cols() == B.cols() /* Invalid cols in Subtract<...>::Subtract */);
}

template <class _A, class _B>
constexpr size_t Subtract<_A, _B>::rows() const
{
  return A.rows();
}

template <class _A, class _B>
constexpr size_t Subtract<_A, _B>::cols() const
{
  return A.cols();
}

template <class _A, class _B>
constexpr typename Subtract<_A, _B>::Traits::elem
Subtract<_A, _B>::operator()(size_t i, size_t j) const
{
  return A(i, j) - B(i, j);
}

template <class _A, class _B>
constexpr typename Subtract<_A, _B>::Traits::elem
Subtract<_A, _B>::operator()(size_t i) const
{
  return A(i) - B(i);
}

template <class _A>
constexpr ScaleMultiple<_A>::ScaleMultiple(Stream<_A> const &A, typename Traits::elem s)
: A(A), s(s) { }

template <class _A>
constexpr size_t ScaleMultiple<_A>::rows() const
{
  return A.rows();
}

template <class _A>
constexpr size_t ScaleMultiple<_A>::cols() const
{
  return A.cols();
}

template <class _A>
constexpr typename ScaleMultiple<_A>::Traits::elem
ScaleMultiple<_A>::operator()(size_t i, size_t j) const
{
  return A(i, j) * s;
}

template <class _A>
constexpr typename ScaleMultiple<_A>::Traits::elem
ScaleMultiple<_A>::operator()(size_t i) const
{
  return A(i) * s;
}

template <class _A>
constexpr ScaleDivide<_A>::ScaleDivide(Stream<_A> const &A, typename Traits::elem s)
: A(A), s(s) { }

template <class _A>
constexpr size_t ScaleDivide<_A>::rows() const
{
  return A.rows();
}

template <class _A>
constexpr size_t ScaleDivide<_A>::cols() const
{
  return A.cols();
}

template <class _A>
constexpr typename ScaleDivide<_A>::Traits::elem
ScaleDivide<_A>::operator()(size_t i, size_t j) const
{
  return A(i, j) / s;
}

template <class _A>
constexpr typename ScaleDivide<_A>::Traits::elem
ScaleDivide<_A>::operator()(size_t i) const
{
  return A(i) / s;
}

template <class _A, class _B>
constexpr Multiply<_A, _B>::Multiply(Stream<_A> const &A, Stream<_B> const &B)
: A(A), B(B)
{
  assert(A.cols() == B.rows() /* Incompatiblity in Multiply<...>::Multiplu */);
}

template <class _A, class _B>
constexpr size_t Multiply<_A, _B>::rows() const
{
  return A.rows();
}

template <class _A, class _B>
constexpr size_t Multiply<_A, _B>::cols() const
{
  return B.cols();
}

template <class _A, class _B>
constexpr typename Multiply<_A, _B>::Traits::elem
Multiply<_A, _B>::operator()(size_t i, size_t j) const
{
  typename Traits::elem x = A(i, 0) * B(0, j);
  for (size_t k = 1; k < A.cols(); k++) x += A(i, k) * B(k, j);
  return x;
}

template <class _A, class _B>
constexpr typename Multiply<_A, _B>::Traits::elem
Multiply<_A, _B>::operator()(size_t i) const
{
  return operator()(i / cols(), i % cols());
}

template <class _A>
constexpr Transpose<_A>::Transpose(Stream<_A> const &A)
: A(A) { }

template <class _A>
constexpr size_t Transpose<_A>::rows() const
{
  return A.cols();
}

template <class _A>
constexpr size_t Transpose<_A>::cols() const
{
  return A.rows();
}

template <class _A>
constexpr typename Transpose<_A>::Traits::elem
Transpose<_A>::operator()(size_t i, size_t j) const
{
  return A(j, i);
}

template <class _A>
constexpr typename Transpose<_A>::Traits::elem
Transpose<_A>::operator()(size_t i) const
{
  return operator()(i / cols(), i % cols());
}

template <class _A, class _B,
    typename std::enable_if<can_add<_A, _B>::value, size_t>::type>
constexpr Add<_A, _B> operator+(Stream<_A> const &A, Stream<_B> const &B)
{
  return Add<_A, _B>(A, B);
}

template <class _A, class _B,
    typename std::enable_if<can_subtract<_A, _B>::value, size_t>::type>
constexpr Subtract<_A, _B> operator-(Stream<_A> const &A, Stream<_B> const &B)
{
  return Subtract<_A, _B>(A, B);
}

template <class _A,
    typename std::enable_if<can_scale_multiple<_A>::value, size_t>::type>
constexpr ScaleMultiple<_A> operator*(Stream<_A> const &A, typename Stream<_A>::Traits::elem s)
{
  return ScaleMultiple<_A>(A, s);
}

template <class _A,
    typename std::enable_if<can_scale_multiple<_A>::value, size_t>::type>
constexpr ScaleMultiple<_A> operator*(typename Stream<_A>::Traits::elem s, Stream<_A> const &A)
{
  return (A * s);
}

template <class _A,
    typename std::enable_if<can_scale_divide<_A>::value, size_t>::type>
constexpr ScaleDivide<_A> operator/(Stream<_A> const &A, typename Stream<_A>::Traits::elem s)
{
  return ScaleDivide<_A>(A, s);
}

template <class _A, class _B,
    typename std::enable_if<can_multiply<_A, _B>::value, size_t>::type>
constexpr Multiply<_A, _B> operator*(Stream<_A> const &A, Stream<_B> const &B)
{
  return Multiply<_A, _B>(A, B);
}
}  // namespace internal

template <class _A,
    typename std::enable_if<internal::can_transpose<_A>::value, size_t>::type>
constexpr internal::Transpose<_A> transpose(internal::Stream<_A> const &A)
{
  return internal::Transpose<_A>(A);
}

template <class _A>
constexpr typename internal::Stream<_A>::Traits::elem fro(internal::Stream<_A> const &A)
{
  typename internal::Stream<_A>::Traits::elem x = A(0) * A(0);
  for (size_t i = 1; i < A.size(); i++) x += A(i) * A(i);
  return x;
}
}  // namespace lin
