/** @file lin/core/types/inl/stream.inl
 *  @author Kyle Krol
 *  See %lin/core/types/stream.hpp for more information. */

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

#ifdef LIN_DESKTOP
template <class C>
std::ostream &operator<<(std::ostream &os, Stream<C> const &stream) {
  for (size_t i = 0; i < stream.rows() - 1; i++) {
    for (size_t j = 0; j < stream.cols() - 1; j++)
      os << stream(i, j) << " ";
    os << stream(i, stream.cols() - 1) << "\n";
  }
  for (size_t j = 0; j < stream.cols() - 1; j++)
    os << stream(stream.rows() - 1, j) << " ";
  os << stream(stream.rows() - 1, stream.cols() - 1) << "\n";
  return os;
}
#endif

}  // namespace internal
}  // namespace lin
