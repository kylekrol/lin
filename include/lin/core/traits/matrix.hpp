/** @file lin/core/traits/matrix.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for the core matrix module. */

// TODO : Documentation for this entire file

#ifndef LIN_CORE_TRAITS_MATRIX_HPP_
#define LIN_CORE_TRAITS_MATRIX_HPP_

#include "tensor.hpp"
#include "utilities.hpp"
#include "vector.hpp"

namespace lin {
namespace internal {

/** @struct is_matrix */
template <class C, typename V = void>
struct is_matrix : false_type { };

template <class C>
struct is_matrix<C, enable_if_t<(!is_vector<C>::value)>> : true_type { };

}  // namespace internal
}  // namespace lin

#endif
