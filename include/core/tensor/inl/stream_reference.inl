// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../stream_reference.hpp"

namespace lin
{
namespace internal
{

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr StreamReference<R, C, MR, MC, _E>::StreamReference(
    Stream<_E> const &E, size_t i, size_t j, size_t r, size_t c)
: E(E), i(i), j(j)
{
  assert(i + r <= E.rows() /* Invalid dimension in StreamReference<...>::StreamReference */);
  assert(j + c <= E.cols() /* Invalid dimension in StreamReference<...>::StreamReference */);
  resize(r, c);
}

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr typename StreamReference<R, C, MR, MC, _E>::Traits::elem
StreamReference<R, C, MR, MC, _E>::operator()(size_t i, size_t j) const
{
  assert(i < rows() /* Invalid row index in StreamReference<...>::operator() */);
  assert(j < cols() /* Invalid col index in StreamReference<...>::operator() */);
  return E(this->i + i, this->j + j);
}

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr typename StreamReference<R, C, MR, MC, _E>::Traits::elem
StreamReference<R, C, MR, MC, _E>::operator()(size_t i) const
{
  return operator()(i / cols(), i % cols());
}
}  // namespace internal

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr internal::StreamReference<R, C, MR, MC, _E>
reference(internal::Stream<_E> const &E, size_t i, size_t j, size_t r, size_t c)
{
  return internal::StreamReference<R, C, MR, MC, _E>(E, i, j, r, c);
}

template <size_t R, size_t C, class _E>
constexpr internal::StreamReference<R, C, R, C, _E>
reference(internal::Stream<_E> const &E, size_t i, size_t j)
{
  return reference<R, C, R, C, _E>(E, i, j);
}
}  // namespace lin
