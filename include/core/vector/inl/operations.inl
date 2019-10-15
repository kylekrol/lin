// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../operations.hpp"

namespace lin
{

template <class _A, class _B,
    typename std::enable_if<internal::are_vector_traits_equal<_A, _B>::value, size_t>::type>
constexpr typename internal::elem<_A>::type dot(internal::Stream<_A> const &A,
    internal::Stream<_B> const &B)
{
  assert(A.size() == B.size() /* Incompatible size in dot(...) */);
  typename internal::elem<_A>::type x = A(0) * B(0);
  for (size_t i = 1; i < A.size(); i++) x += A(i) * B(i);
  return x;
}

template <class _A,
    typename std::enable_if<internal::is_vector<_A>::value, size_t>::type>
constexpr typename internal::elem<_A>::type norm(internal::Stream<_A> const &A)
{
  return sqrt(fro(A));
}
}  // namespace lin
