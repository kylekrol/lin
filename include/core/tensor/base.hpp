// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_BASE_HPP_
#define LIN_INCLUDE_CORE_TENSOR_BASE_HPP_

#include "stream.hpp"
#include "traits.hpp"

#include <initializer_list>
#include <type_traits>

namespace lin
{
namespace internal
{

template <class A, class B>
struct can_assign : public are_traits_equal<A, B> { };

template <class D>
class Base : public Stream<D>
{
 public:
  typedef traits<D> Traits;
  using Stream<D>::rows;
  using Stream<D>::cols;
  using Stream<D>::size;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;
  constexpr typename Traits::elem &operator()(size_t i, size_t j);
  constexpr typename Traits::elem &operator()(size_t i);
  constexpr D &operator=(std::initializer_list<typename Traits::elem> const &l);
  template <class _E, typename std::enable_if<can_assign<D, _E>::value, size_t>::type = 0>
  constexpr D &operator=(Stream<_E> const &E);

 protected:
  using Stream<D>::derived;
  constexpr Base() = default;
};
}  // namespace internal
}  // namespace lin

#include "inl/base.inl"

#endif
