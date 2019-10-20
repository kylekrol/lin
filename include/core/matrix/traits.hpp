// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_MATRIX_TRAITS_HPP_
#define LIN_INCLUDE_CORE_MATRIX_TRAITS_HPP_

#include "../tensor/traits.hpp"
#include "../vector/traits.hpp"

#include <type_traits>

namespace lin
{
namespace internal
{

template <class A>
struct is_matrix : public std::integral_constant<bool, !is_vector<A>::value> { };

template <class A>
struct is_tall : public std::integral_constant<bool, (dims<A>::max_rows >= dims<A>::max_cols)> { };

template <class A>
struct is_short : public std::integral_constant<bool, (dims<A>::max_rows <= dims<A>::max_cols)> { };

template <class A>
struct is_square
: public std::integral_constant<bool, (
    (dims<A>::rows == dims<A>::cols) && (dims<A>::max_cols == dims<A>::max_rows)
  )> { };

}  // namespace internal
}  // namespace lin

#endif
