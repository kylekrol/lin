/** @file lin/core/tensor/inl/stream.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/stream.hpp for more information. */

#include "../stream.hpp"

namespace lin {
namespace internal {

template <class D>
constexpr size_t Stream<D>::rows() const {
  return derived().rows();
}

template <class D>
constexpr size_t Stream<D>::cols() const {
  return derived().cols();
}

template <class D>
constexpr size_t Stream<D>::size() const {
  return rows() * cols();
}

template <class D>
constexpr traits_elem_t<D> Stream<D>::operator()(size_t i, size_t j) const {
  return derived()(i, j);
}

template <class D>
constexpr traits_elem_t<D> Stream<D>::operator()(size_t i) const {
  return derived()(i);
}

template <class D>
constexpr traits_eval_t<D> Stream<D>::eval() const {
  return traits_eval_t<D>(*this);
}

template <class D>
constexpr D const &Stream<D>::derived() const {
  return static_cast<D const &>(*this);
}

template <class D>
constexpr D &Stream<D>::derived() {
  return static_cast<D &>(*this);
}
}  // namespace internal
}  // namespace lin
