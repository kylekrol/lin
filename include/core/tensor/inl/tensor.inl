// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../tensor.hpp"

namespace lin
{
namespace internal
{

template <class D>
constexpr typename Tensor<D>::Traits::elem &Tensor<D>::operator()(size_t i, size_t j)
{
  assert(i < rows() /* Invalid row index in Tensor<...>::operator() */);
  assert(j < cols() /* Invalid col index in Tensor<...>::operator() */);
  return elements[i * cols() + j];
}

template <class D>
constexpr typename Tensor<D>::Traits::elem &Tensor<D>::operator()(size_t i)
{
  assert(i < size() /* Invalid size index in Tensor<...>::operator() */);
  return elements[i];
}

template <class D>
constexpr typename Tensor<D>::Traits::elem const *Tensor<D>::data() const
{
  return elements.data();
}

template <class D>
constexpr typename Tensor<D>::Traits::elem *Tensor<D>::data()
{
  return elements.data();
}

template <class D>
constexpr typename Tensor<D>::Traits::eval
Tensor<D>::rands(size_t r, size_t c, RandomsGenerator &randoms)
{
  typename Traits::eval T(r, c);
  for (size_t i = 0; i < T.size(); i++)
    T(i) = static_cast<typename Traits::elem>(randoms.next());
  return T;
}

template <class D>
constexpr Tensor<D>::Tensor(size_t r, size_t c)
{
  resize(r, c);
}

template <class D>
constexpr Tensor<D>::Tensor(std::initializer_list<typename Traits::elem> const &l)
{
  operator=(l);
}

template <class D>
constexpr Tensor<D>::Tensor(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
{
  resize(r, c);
  operator=(l);
}

template <class D> template <class _E>
constexpr Tensor<D>::Tensor(Stream<_E> const &E)
{
  resize(E.rows(), E.cols());
  operator=(E);
}
}  // namespace internal
}  // namespace lin
