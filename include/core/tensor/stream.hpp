// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_STREAM_HPP_
#define LIN_INCLUDE_CORE_TENSOR_STREAM_HPP_

#include "traits.hpp"

#include <cassert>

#ifdef LIN_DESKTOP
#include <iostream>
#endif

namespace lin
{
namespace internal
{

template <class D>
class Stream
{
  static_assert(is_traits_valid<D>::value, "Invalid stream traits detected");

 public:
  typedef traits<D> Traits;
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr size_t size() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;
  constexpr typename Traits::eval evaluate() const;

 protected:
  constexpr Stream() = default;
  constexpr D const &derived() const;
  constexpr D &derived();
};

#ifdef LIN_DESKTOP
template <class _A>
inline std::ostream &operator<<(std::ostream &os, Stream<_A> const &A);
#endif

}  // namespace internal
}  // namespace lin

#include "inl/stream.inl"

#endif
