/** @file lin/factorizations/chol.hpp
 *  @author Kyle Krol
 *  Defines a cholesky factorization algorithm for tensor types. */

// TODO : Documentation for this entire file

#ifndef LIN_FACTORIZATIONS_CHOL_HPP_
#define LIN_FACTORIZATIONS_CHOL_HPP_

#include "../core.hpp"
#include "../generators/constants.hpp"
#include "../references.hpp"

#include <cmath>
#include <type_traits>

namespace lin {
namespace internal {

/** @struct can_chol */
template <class C, class D>
struct can_chol : conjunction<have_same_dimensions<C, D>, is_matrix<C>, is_square<C>> { };

}  // namespace internal

/** @fn chol */
template <class C, class D, std::enable_if_t<internal::can_chol<C, D>::value, size_t> = 0>
constexpr int chol(internal::Base<C> const &A, internal::Base<D> &L);

}  // namespace lin

#include "inl/chol.inl"

#endif
