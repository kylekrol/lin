/** @file lin/core/tensor/operations.hpp
 *  @author Kyle Krol
 *  See %lin/core/tensor/operations.hpp for more information. */

#include "../operations.hpp"

namespace lin {
namespace internal {

template <class C, class D, typename>
struct can_cross : false_type { };

template <class C, class D>
struct can_cross<C, D, enable_if_t<(
    have_same_vector_dimensions<C, Vector3f>::value &&
    have_same_vector_dimensions<D, Vector3f>::value &&
    is_detected<multiply_expr, _traits_elem_t<C>, _traits_elem_t<D>>::value
  )>> : true_type { };

template <class C, class D, typename>
struct can_dot : false_type { };

template <class C, class D>
struct can_dot<C, D, enable_if_t<(
    have_same_vector_dimensions<C, D>::value &&
    is_detected<multiply_expr, _traits_elem_t<C>, _traits_elem_t<D>>::value
  )>> : true_type { };

template <class C, typename>
struct can_norm : false_type { };

template <class C>
struct can_norm<C, enable_if_t<(
    is_vector<C>::value
  )>> : true_type { };

}  // namespace internal

template <class C, class D, internal::enable_if_t<internal::can_cross<C, D>::value, size_t>>
constexpr auto cross(internal::Stream<C> const &u, internal::Stream<D> const &v) {
  typedef internal::multiply_expr<typename C::Traits::Elem, typename D::Traits::Elem> T;
  return Vector<T, 3>({
    u(1) * v(2) - u(2) * v(1),
    u(2) * v(0) - u(0) * v(2),
    u(0) * v(1) - u(1) * v(0)
  });
}

template <class C, class D, internal::enable_if_t<internal::can_dot<C, D>::value, size_t>>
constexpr auto dot(internal::Stream<C> const &u, internal::Stream<D> const &v) {
  typedef internal::multiply_expr<typename C::Traits::Elem, typename D::Traits::Elem> T;
  LIN_ASSERT(u.size() == v.size() /* Invalid vectors passed to dot(...) */);
  T x = u(0) * v(0);
  for (size_t i = 1; i < u.size(); i++) x += u(i) * v(i);
  return x;
}

template <class C, internal::enable_if_t<internal::can_norm<C>::value, size_t>>
constexpr typename C::Traits::Elem norm(internal::Stream<C> const &u) {
  return std::sqrt(fro(u));
}
}  // namespace lin
