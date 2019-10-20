// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_VECTOR_OPERATIONS_HPP_
#define LIN_INCLUDE_CORE_VECTOR_OPERATIONS_HPP_

#include "../tensor/stream.hpp"
#include "traits.hpp"

#include <cassert>
#include <cmath>  // TODO : Perhaps overkill for embedded systems
#include <type_traits>

namespace lin
{
namespace internal
{

template <class _A, class _B>
struct can_cross
: public std::integral_constant<bool, (
    are_vector_traits_equal<_A, _B>::value && (vector_traits<_A>::size == 3)
  )> { };

}  // namespace internal

template <class _A, class _B,
    typename std::enable_if<internal::are_vector_traits_equal<_A, _B>::value, size_t>::type = 0>
constexpr typename internal::elem<_A>::type dot(internal::Stream<_A> const &A,
    internal::Stream<_B> const &B);

template <class _A,
    typename std::enable_if<internal::is_vector<_A>::value, size_t>::type = 0>
constexpr typename internal::elem<_A>::type norm(internal::Stream<_A> const &A);

template <class _A, class _B,
    typename std::enable_if<internal::can_cross<_A, _B>::value, size_t>::type = 0>
constexpr typename internal::eval<_A>::type cross(internal::Stream<_A> const &A,
    internal::Stream<_B> const &B);

}  // namespace lin

#include "inl/operations.inl"

#endif
