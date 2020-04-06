/** @file lin/core/operations/inl/vector_operations.inl
 *  @author Kyle Krol
 *  See %lin/core/operations/vector_operations.hpp for more information. */

#include "../vector_operations.hpp"

namespace lin {

template <class C, class D, std::enable_if_t<internal::can_cross<C, D>::value, size_t>>
constexpr auto cross(internal::Stream<C> const &u, internal::Stream<D> const &v) {
  typedef typename internal::multiply::template expression<internal::_traits_elem_t<C>, internal::traits_elem_t<D>> T;
  return std::conditional_t<
      internal::is_col_vector<C>::value,
      Vector<T, internal::_vector_traits<C>::Length, internal::_vector_traits<C>::MaxLength>,
      RowVector<T, internal::_vector_traits<C>::Length, internal::_vector_traits<C>::MaxLength>>({
    u(1) * v(2) - u(2) * v(1),
    u(2) * v(0) - u(0) * v(2),
    u(0) * v(1) - u(1) * v(0)
  });
}

template <class C, class D, std::enable_if_t<internal::can_dot<C, D>::value, size_t>>
constexpr auto dot(internal::Stream<C> const &u, internal::Stream<D> const &v) {
  typedef internal::multiply::expression<typename C::Traits::Elem, typename D::Traits::Elem> T;
  LIN_ASSERT(u.size() == v.size() /* Invalid vectors passed to dot(...) */);
  T x = u(0) * v(0);
  for (size_t i = 1; i < u.size(); i++) x += u(i) * v(i);
  return x;
}
}  // namespace lin
