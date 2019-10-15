// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../base.hpp"

namespace lin
{
namespace internal
{

template <class D>
constexpr typename Base<D>::Traits::elem Base<D>::operator()(size_t i, size_t j) const
{
  return const_cast<Base<D> &>(*this)(i, j);
}

template <class D>
constexpr typename Base<D>::Traits::elem Base<D>::operator()(size_t i) const
{
  return const_cast<Base<D> &>(*this)(i);
}

template <class D>
constexpr typename Base<D>::Traits::elem &Base<D>::operator()(size_t i, size_t j)
{
  return derived()(i, j);
}

template <class D>
constexpr typename Base<D>::Traits::elem &Base<D>::operator()(size_t i)
{
  return derived()(i);
}

template <class D>
constexpr D &Base<D>::operator=(std::initializer_list<typename Base<D>::Traits::elem> const &l)
{
  assert(size() == l.size() /* Incompatible size in Base<...>::operator= */);
  size_t i = 0;
  auto it = l.begin();
  while (it < l.end()) operator()(i++) = *(it++);
  return derived();
}

template <class D> template <class _E, typename std::enable_if<can_assign<D, _E>::value, size_t>::type>
constexpr D &Base<D>::operator=(Stream<_E> const &E)
{
  assert(rows() == E.rows() /* Incompatible rows in Base<_D>::operator= */);
  assert(cols() == E.cols() /* Incompatible cols in Base<_D>::operator= */);
  for (size_t i = 0; i < size(); i++) operator()(i) = E(i);
  return derived();
}
}  // namespace internal
}  // namespace lin
