/** @file lin/core/tensor/inl/tensor.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/tensor.hpp for more information. */

#include "../tensor.hpp"

namespace lin {
namespace internal {

template <class D>
constexpr Tensor<D>::Tensor(size_t r, size_t c) {
  resize(r, c);
}

template <class D>
constexpr Tensor<D>::Tensor(std::initializer_list<traits_elem_t<D>> const &list) {
  derived() = list;
}

template <class D>
constexpr Tensor<D>::Tensor(size_t r, size_t c, std::initializer_list<traits_elem_t<D>> const &list) {
  resize(r, c);
  derived() = list;
}

template <class D>
template <class C>
constexpr Tensor<D>::Tensor(Stream<C> const &stream) {
  resize(stream.rows(), stream.cols());
  derived() = stream;
}

template <class D>
constexpr traits_elem_t<D> &Tensor<D>::operator()(size_t i, size_t j) {
  LIN_ASSERT(0 <= i && i <= rows() /* Invalid argument passed to Tensor<...>::operator() */);
  LIN_ASSERT(0 <= j && j <= cols() /* Invalid argument passed to Tensor<...>::operator() */);
  return elems[i * cols() + j];
}

template <class D>
constexpr traits_elem_t<D> &Tensor<D>::operator()(size_t i) {
  LIN_ASSERT(0 <= i && i <= size() /* Invalid argument passed to Tensor<...>::operator() */);
  return elems[i];
}
}  // namespace internal
}  // namespace lin
