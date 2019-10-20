// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_VECTOR_TRAITS_HPP_
#define LIN_INCLUDE_CORE_VECTOR_TRAITS_HPP_

#include "../tensor/traits.hpp"

#include <type_traits>

namespace lin
{
namespace internal
{

template <class A>
struct is_row_vector
: std::integral_constant<bool, (
    has_fixed_rows<A>::value && (dims<A>::rows == 1) && (dims<A>::max_cols > 1)
  )> { };

template <class A>
struct is_col_vector
: std::integral_constant<bool, (
    has_fixed_cols<A>::value && (dims<A>::cols == 1) && (dims<A>::max_rows > 1)
  )> { };

template <class A>
struct is_vector
: std::integral_constant<bool, is_row_vector<A>::value || is_col_vector<A>::value> { };

template <class A, typename T = void>
struct vector_traits;

template <class A>
struct vector_traits<A, typename std::enable_if<is_row_vector<A>::value>::type>
{
  enum {
    size = traits<A>::cols,
    max_size = traits<A>::max_cols
  };
  typedef typename traits<A>::elem elem;
};

template <class A>
struct vector_traits<A, typename std::enable_if<is_col_vector<A>::value>::type>
{
  enum {
    size = traits<A>::rows,
    max_size = traits<A>::max_rows
  };
  typedef typename traits<A>::elem elem;
};

template <class A, class B, typename T = void>
struct are_vector_traits_equal : std::false_type { };

template <class A, class B>
struct are_vector_traits_equal<A, B,
    typename std::enable_if<is_vector<A>::value && is_vector<B>::value>::type>
: std::integral_constant<bool, (
    (vector_traits<A>::size == vector_traits<B>::size) &&
    (vector_traits<A>::max_size == vector_traits<B>::max_size) &&
    are_elem_equal<A, B>::value
  )> { };

}  // namespace internal
}  // namespace lin

#endif
