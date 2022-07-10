// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/traits/matrix.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TRAITS_MATRIX_HPP_
#define LIN_CORE_TRAITS_MATRIX_HPP_

#include "utilities.hpp"
#include "vector.hpp"

namespace lin {
namespace internal {

/** @brief Tests if a tensor type is a matrix.
 *  
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be a matrix if it's not a vector.
 * 
 *  @sa internal::is_vector
 *  
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_matrix : negation<is_vector<C>> { };

}  // namespace internal
}  // namespace lin

#endif
