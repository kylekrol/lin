/** @file lin/core/tensor/inl/base.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/base.hpp for more information. */

#include "../base.hpp"

namespace lin {
namespace internal {

template <class D>
constexpr traits_elem_t<D> Base<D>::operator()(size_t i, size_t j) const {
  return const_cast<Base<D> &>(*this)(i, j);
}

template <class D>
constexpr traits_elem_t<D> &Base<D>::operator()(size_t i, size_t j) {
  return derived()(i, j);
}

template <class D>
constexpr traits_elem_t<D> Base<D>::operator()(size_t i) const {
  return const_cast<Base<D> &>(*this)(i);
}

template <class D>
constexpr traits_elem_t<D> &Base<D>::operator()(size_t i) {
  return derived()(i);
}

template <class D>
template <typename T, std::enable_if_t<can_assign_types<traits_elem_t<D>, T>::value, size_t>>
constexpr D &Base<D>::operator=(std::initializer_list<T> const &list) {
  LIN_ASSERT(list.size() == size() /* Invalid arguments passed to Base<...>::operator= */);
  size_t i = 0;
  for (auto const &l : list) (*this)(i++) = l;
  return derived();
}

template <class D>
template <class C, std::enable_if_t<can_assign<D, C>::value, size_t>>
constexpr D &Base<D>::operator=(Stream<C> const &stream) {
  LIN_ASSERT(stream.rows() == rows() /* Invalid arguments passed to Base<...>::operator= */);
  LIN_ASSERT(stream.cols() == cols() /* Invalid arguments passed to Base<...>::operator= */);
  for (size_t i = 0; i < size(); i++) (*this)(i) = stream(i);
  return derived();
}
}  // namespace internal
}  // namespace lin
