// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_TRAITS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_TRAITS_HPP_

#include <type_traits>

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__) || \
    defined(__unix__) || defined(_POSIX_VERION)
#define LIN_DESKTOP
#endif

namespace lin
{

typedef unsigned int size_t;

namespace internal
{

template <class A, typename T = void>
struct elem;

template <class A>
struct is_elem_valid
: public std::integral_constant<bool, (
    std::is_same<typename elem<A>::type, float>::value ||
    std::is_same<typename elem<A>::type, double>::value
  )> { };

template <class A, class B>
struct are_elem_equal
: public std::is_same<typename elem<A>::type, typename elem<B>::type> { };

template <class A, typename T = void>
struct eval;

template <class A>
struct is_eval_valid
: public std::true_type { };

template <class A, class B>
struct are_eval_equal
: public std::is_same<typename eval<A>::type, typename eval<B>::type> { };

template <class A, typename T = void>
struct dims;

template <class A>
struct has_fixed_rows
: public std::integral_constant<bool, (
    (dims<A>::rows == dims<A>::max_rows) && (dims<A>::rows > 0)
  )> { };

template <class A>
struct has_fixed_cols
: public std::integral_constant<bool, (
    (dims<A>::cols == dims<A>::max_cols) && (dims<A>::cols > 0)
  )> { };

template <class A>
struct has_fixed_size
: public std::integral_constant<bool, has_fixed_rows<A>::value && has_fixed_cols<A>::value> { };

template <class A>
struct has_static_rows
: public std::integral_constant<bool, (dims<A>::rows == 0) && (dims<A>::max_rows > 0)> { };

template <class A>
struct has_static_cols
: public std::integral_constant<bool, (dims<A>::cols == 0) && (dims<A>::max_cols > 0)> { };

template <class A>
struct has_static_size
: public std::integral_constant<bool, (
    (has_static_rows<A>::value && has_static_cols<A>::value) ||
    (has_static_rows<A>::value && has_fixed_cols<A>::value) ||
    (has_fixed_rows<A>::value && has_static_cols<A>::value)
  )> { };

template <class A>
struct is_dims_valid
: public std::integral_constant<bool, has_fixed_size<A>::value || has_static_size<A>::value> { };

template <class A, class B>
struct are_dims_equal
: public std::integral_constant<bool, (
    (dims<A>::rows == dims<B>::rows) && (dims<A>::cols == dims<B>::cols) &&
    (dims<A>::max_rows == dims<B>::max_rows) && (dims<A>::max_cols == dims<B>::max_cols)
  )> { };

template <class A>
struct traits
{
  enum {
    rows = dims<A>::rows,
    cols = dims<A>::cols,
    max_rows = dims<A>::max_rows,
    max_cols = dims<A>::max_cols,
    max_size = max_rows * max_cols
  };
  typedef typename elem<A>::type elem;
  typedef typename eval<A>::type eval;
};

template <class A>
struct is_traits_valid
: public std::integral_constant<bool, (
    is_elem_valid<A>::value && is_eval_valid<A>::value && is_dims_valid<A>::value
  )> { };

template <class A, class B>
struct are_traits_equal
: public std::integral_constant<bool, (
    are_elem_equal<A, B>::value && are_eval_equal<A, B>::value && are_dims_equal<A, B>::value
  )> { };

}  // namespace internal
}  // namespace lin

#endif
