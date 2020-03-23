/** @file lin/core/tensor/base.hpp
 *  @author Kyle Krol
 *  Defines the base type which is a tensor read-write interface. */

// TODO : Make list assignment operator tolerant to more types and types check

#ifndef LIN_CORE_TENSOR_BASE_HPP_
#define LIN_CORE_TENSOR_BASE_HPP_

#include "../config.hpp"
#include "../traits.hpp"

#include "stream.hpp"

#include <initializer_list>
#include <utility>

namespace lin {
namespace internal {

/** @struct can_assign_types
 *  Tests if one type can be assigned to another. */
template <typename T, typename U>
struct can_assign_types;

/** @struct can_assign
 *  Tests if one tensor type can be assigned to another. */
template <class C, class D, typename V = void>
struct can_assign;

/** @class Base
 *  Representation of a tensor presenting read/write access to it's elements.
 *  Resizing is still not supported at this level. This class' main purpose is
 *  to facilitate block references. */
template <class D>
class Base : public Stream<D> {
 public:
  /* Import elements from Stream<D>. */
  using Stream<D>::rows;
  using Stream<D>::cols;
  using Stream<D>::size;
  using Stream<D>::eval;
  /* Include traits information from the derived type. */
  typedef traits<D> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Base() = default;
  constexpr Base(Base<D> const &) = default;
  constexpr Base(Base<D> &&) = default;
  constexpr Base<D> &operator=(Base<D> const &) = default;
  constexpr Base<D> &operator=(Base<D> &&) = default;
  /* Element access and write functions. */
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem &operator()(size_t i, size_t j);
  constexpr typename Traits::Elem operator()(size_t i) const;
  constexpr typename Traits::Elem &operator()(size_t i);
  /* Assignment extra assignment operators. */
  template <typename T, enable_if_t<can_assign_types<typename Traits::Elem, T>::value, size_t> = 0>
  constexpr D &operator=(std::initializer_list<T> const &list);
  template <class C, enable_if_t<can_assign<D, C>::value, size_t> = 0>
  constexpr D &operator=(Stream<C> const &stream);

 protected:
  /* Import elements from Stream<D>. */
  using Stream<D>::derived;
};
}  // namespace internal
}  // namespace lin

#include "inl/base.inl"

#endif
