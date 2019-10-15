// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../base_reference.hpp"

namespace lin
{
namespace internal
{

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr BaseReference<R, C, MR, MC, _E>::BaseReference(Base<_E> &E, size_t i,
    size_t j, size_t r, size_t c)
: E(E), i(i), j(j)
{
  assert(i + r <= E.rows() /* Invalid dimension in BaseReference<...>::BaseReference */);
  assert(j + c <= E.cols() /* Invalid dimension in BaseReference<...>::BaseReference */);
  resize(r, c);
}

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr typename BaseReference<R, C, MR, MC, _E>::Traits::elem &
BaseReference<R, C, MR, MC, _E>::operator()(size_t i, size_t j)
{
  assert(i < rows() /* Invalid row index in BaseReference<...>::operator() */);
  assert(j < cols() /* Invalid col index in BaseReference<...>::operator() */);
  return E(this->i + i, this->j + j);
}

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr typename BaseReference<R, C, MR, MC, _E>::Traits::elem &
BaseReference<R, C, MR, MC, _E>::operator()(size_t i)
{
  return operator()(i / cols(), i % cols());
}
}  // namespace internal

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr internal::BaseReference<R, C, MR, MC, _E>
reference(internal::Base<_E> &E, size_t i, size_t j, size_t r, size_t c)
{
  return internal::BaseReference<R, C, MR, MC, _E>(E, i, j, r, c);
}

template <size_t R, size_t C, class _E>
constexpr internal::BaseReference<R, C, R, C, _E>
reference(internal::Base<_E> &E, size_t i, size_t j)
{
  return reference<R, C, R, C, _E>(E, i, j);
}
}  // namespace lin
