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
struct is_matrix : std::integral_constant<bool, !is_vector<A>::value> { };

}  // namespace internal
}  // namespace lin

#endif
