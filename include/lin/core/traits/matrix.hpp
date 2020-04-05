/** @file lin/core/traits/matrix.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for the core matrix module. */

#ifndef LIN_CORE_TRAITS_MATRIX_HPP_
#define LIN_CORE_TRAITS_MATRIX_HPP_

#include "tensor.hpp"
#include "utilities.hpp"
#include "vector.hpp"

namespace lin {
namespace internal {

/** @struct is_matrix
 *  Test if a type is a vector type. We'll treat anything not considered a
 *  vector as if it's a matrix. */
template <class C>
struct is_matrix : negation<is_vector<C>> { };

}  // namespace internal
}  // namespace lin

#endif
