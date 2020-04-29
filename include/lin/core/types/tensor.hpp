/** @file lin/core/types/base.hpp
 *  @author Kyle Krol
 *  Defines the tensor type which is a tensor value-backed, read-write
 *  interface. */

#ifndef LIN_CORE_TYPES_TENSOR_HPP_
#define LIN_CORE_TYPES_TENSOR_HPP_

#include "../config.hpp"
#include "../traits.hpp"

#include "base.hpp"
#include "dimensions.hpp"
#include "stream.hpp"

#include <initializer_list>
#include <type_traits>

namespace lin {
namespace internal {

/** @class Tensor
 *  Representation of a tensor presenting read/write access directly to an
 *  element backing array. Resizing is supported. */
template <class D>
class Tensor : public Base<D>, public Dimensions<D> {
 public:
  /* Import elements from Base<D>. */
  using Base<D>::size;
  using Base<D>::eval;
  using Base<D>::operator=;
  using Base<D>::operator();
  /* Import elements from Dimensions<D>. */
  using Dimensions<D>::rows;
  using Dimensions<D>::cols;
  using Dimensions<D>::resize;
  /* Include traits information from the derived type. */
  typedef traits<D> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Tensor(Tensor<D> const &) = default;
  constexpr Tensor(Tensor<D> &&) = default;
  constexpr Tensor<D> &operator=(Tensor<D> const &) = default;
  constexpr Tensor<D> &operator=(Tensor<D> &&) = default;
  /* Tensor constructor(s). */
  constexpr Tensor(size_t r = Traits::MaxRows, size_t c = Traits::MaxCols);
  template <typename T>
  constexpr Tensor(std::initializer_list<T> const &list);
  template <typename T>
  constexpr Tensor(size_t r, size_t c, std::initializer_list<T> const &list);
  template <class C, std::enable_if_t<have_same_dimensions<D, C>::value, size_t> = 0>
  constexpr Tensor(Stream<C> const &stream);
  /* Elements access and read/write functions. */
  constexpr typename Traits::Elem &operator()(size_t i, size_t j);
  constexpr typename Traits::Elem &operator()(size_t i);

 protected:
  /* Import elements from Base<D>. */
  using Base<D>::derived;

 private:
  typename Traits::Elem elems[Traits::MaxSize] = { static_cast<typename Traits::Elem>(0) };
};
}  // namespace internal
}  // namespace lin

#include "inl/tensor.inl"

#endif
