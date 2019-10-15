// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_OPERATIONS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_OPERATIONS_HPP_

#include "stream.hpp"
#include "traits.hpp"

#include <cassert>
#include <type_traits>

namespace lin
{
namespace internal
{

template <class _A, class _B>
class Add : public Stream<Add<_A, _B>>
{
 public:
  typedef traits<Add<_A, _B>> Traits;
  constexpr Add() = delete;
  constexpr Add(Stream<_A> const &A, Stream<_B> const &B);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<_A> const &A;
  Stream<_B> const &B;
};

template <class _A, class _B>
struct can_add : public are_traits_equal<_A, _B> { };

template <class _A, class _B>
struct elem<Add<_A, _B>> : public elem<_A> { };

template <class _A, class _B>
struct dims<Add<_A, _B>, typename std::enable_if<can_add<_A, _B>::value>::type>
: public dims<_A> { };

template <class _A, class _B>
class Subtract : public Stream<Subtract<_A, _B>>
{
 public:
  typedef traits<Subtract<_A, _B>> Traits;
  constexpr Subtract() = delete;
  constexpr Subtract(Stream<_A> const &A, Stream<_B> const &B);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<_A> const &A;
  Stream<_B> const &B;
};

template <class _A, class _B>
struct can_subtract : public are_traits_equal<_A, _B> { };

template <class _A, class _B>
struct elem<Subtract<_A, _B>> : public elem<_A> { };

template <class _A, class _B>
struct dims<Subtract<_A, _B>, typename std::enable_if<can_subtract<_A, _B>::value>::type>
: public dims<_A> { };

template <class _A>
class ScaleMultiple : public Stream<ScaleMultiple<_A>>
{
 public:
  typedef traits<ScaleMultiple<_A>> Traits;
  constexpr ScaleMultiple() = delete;
  constexpr ScaleMultiple(Stream<_A> const &A, typename Traits::elem s);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<_A> const &A;
  typename Traits::elem const s;
};

template <class _A>
struct can_scale_multiple : public std::true_type { };

template <class _A>
struct elem<ScaleMultiple<_A>> : public elem<_A> { };

template <class _A>
struct dims<ScaleMultiple<_A>, typename std::enable_if<can_scale_multiple<_A>::value>::type>
: public dims<_A> { };

template <class _A>
class ScaleDivide : public Stream<ScaleDivide<_A>>
{
 public:
  typedef traits<ScaleDivide<_A>> Traits;
  constexpr ScaleDivide() = delete;
  constexpr ScaleDivide(Stream<_A> const &A, typename Traits::elem s);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<_A> const &A;
  typename Traits::elem const s;
};

template <class _A>
struct can_scale_divide : public std::true_type { };

template <class _A>
struct elem<ScaleDivide<_A>> : public elem<_A> { };

template <class _A>
struct dims<ScaleDivide<_A>, typename std::enable_if<can_scale_divide<_A>::value>::type>
: public dims<_A> { };

template <class _A, class _B>
class Multiply : public Stream<Multiply<_A, _B>>
{
 public:
  typedef traits<Multiply<_A, _B>> Traits;
  constexpr Multiply() = delete;
  constexpr Multiply(Stream<_A> const &A, Stream<_B> const &B);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<_A> const &A;
  Stream<_B> const &B;
};

template <class _A, class _B>
struct can_multiply
: public std::integral_constant<bool, (
    (dims<_A>::cols == dims<_B>::rows) &&
    (dims<_A>::max_cols == dims<_B>::max_rows) &&
    are_elem_equal<_A, _B>::value
  )> { };

template <class _A, class _B>
struct elem<Multiply<_A, _B>> : public elem<_A> { };

template <class _A, class _B>
struct dims<Multiply<_A, _B>, typename std::enable_if<can_multiply<_A, _B>::value>::type>
{
  enum {
    rows = dims<_A>::rows,
    cols = dims<_B>::cols,
    max_rows = dims<_A>::max_rows,
    max_cols = dims<_B>::max_cols
  };
};

template <class _A>
class Transpose : public Stream<Transpose<_A>>
{
 public:
  typedef traits<Transpose<_A>> Traits;
  constexpr Transpose() = delete;
  constexpr Transpose(Stream<_A> const &A);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<_A> const &A;
};

template <class _A>
struct can_transpose : public std::true_type { };

template <class _A>
struct elem<Transpose<_A>> : public elem<_A> { };

template <class _A>
struct dims<Transpose<_A>, typename std::enable_if<can_transpose<_A>::value>::type>
{
  enum {
    rows = dims<_A>::cols,
    cols = dims<_A>::rows,
    max_rows = dims<_A>::max_cols,
    max_cols = dims<_A>::max_rows
  };
};

template <class _A, class _B,
    typename std::enable_if<can_add<_A, _B>::value, size_t>::type = 0>
constexpr Add<_A, _B> operator+(Stream<_A> const &A, Stream<_B> const &B);

template <class _A, class _B,
    typename std::enable_if<can_subtract<_A, _B>::value, size_t>::type = 0>
constexpr Subtract<_A, _B> operator-(Stream<_A> const &A, Stream<_B> const &B);

template <class _A,
    typename std::enable_if<can_scale_multiple<_A>::value, size_t>::type = 0>
constexpr ScaleMultiple<_A> operator*(Stream<_A> const &A, typename Stream<_A>::Traits::elem s);

template <class _A,
    typename std::enable_if<can_scale_multiple<_A>::value, size_t>::type = 0>
constexpr ScaleMultiple<_A> operator*(typename Stream<_A>::Traits::elem s, Stream<_A> const &A);

template <class _A,
    typename std::enable_if<can_scale_divide<_A>::value, size_t>::type = 0>
constexpr ScaleDivide<_A> operator/(Stream<_A> const &A, typename Stream<_A>::Traits::elem s);

template <class _A, class _B,
    typename std::enable_if<can_multiply<_A, _B>::value, size_t>::type = 0>
constexpr Multiply<_A, _B> operator*(Stream<_A> const &A, Stream<_B> const &B);

}  // namespace internal

template <class _A,
    typename std::enable_if<internal::can_transpose<_A>::value, size_t>::type = 0>
constexpr internal::Transpose<_A> transpose(internal::Stream<_A> const &A);

template <class _A>
constexpr typename internal::Stream<_A>::Traits::elem fro(internal::Stream<_A> const &A);

}  // namespace lin

#include "inl/operations.inl"

#endif
