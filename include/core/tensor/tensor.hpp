// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_TENSOR_HPP_
#define LIN_INCLUDE_CORE_TENSOR_TENSOR_HPP_

#include "base.hpp"
#include "generators.hpp"
#include "traits.hpp"

#include <array>
#include <cassert>
#include <initializer_list>

#if defined(LIN_DESKTOP) && !defined(LIN_RANDOM_SEED)
#include <ctime>
#endif

namespace lin
{
namespace internal
{

template <class D>
class Tensor : public Base<D>, public Dimensions<D>
{
 public:
  typedef traits<D> Traits;
  using Dimensions<D>::rows;
  using Dimensions<D>::cols;
  using Dimensions<D>::resize;
  using Base<D>::size;
  using Base<D>::operator=;
  using Base<D>::operator();
  constexpr typename Traits::elem &operator()(size_t i, size_t j);
  constexpr typename Traits::elem &operator()(size_t i);
  constexpr typename Traits::elem const *data() const;
  constexpr typename Traits::elem *data();


  constexpr static typename Traits::eval rands(size_t r = Traits::max_rows,
      size_t c = Traits::max_cols, RandomsGenerator &randoms = rand);

 protected:
  using Base<D>::derived;
  constexpr Tensor() = default;
  constexpr Tensor(size_t r, size_t c);
  constexpr Tensor(std::initializer_list<typename Traits::elem> const &l);
  constexpr Tensor(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class _E>
  constexpr Tensor(Stream<_E> const &E);

 private:
  std::array<typename Traits::elem, Traits::max_size> elements;
};
}  // namespace internal
}  // namespace lin

#include "inl/tensor.inl"

#endif
