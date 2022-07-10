// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

//
// MIT License
//
// Copyright (c) 2020 kylekrol
// Copyright (c) 2020 Pathfinder for Autonomous Navigation (PAN)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

/** @file lin/substitutions.hpp
 *  @author Kyle Krol
 */

/** @defgroup SUBSTITUTIONS Substitutions
 *
 *  @brief Supports solving linear system in conjunction with matrix
 *         factorizations.
 */

#ifndef LIN_SUBSTITUTIONS_HPP_
#define LIN_SUBSTITUTIONS_HPP_

#include "core.hpp"
#include "references.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @internal
 *
 *  @brief Tests whether or not the backward substitution algorithm can be
 *         applied to a set of types.
 *
 *  @tparam C Upper triangular operator type.
 *  @tparam D Unknown matrix or vector type.
 *  @tparam E Know matrix or vector type.
 *
 *  @ingroup SUBSTITUTIONS
 */
template <class C, class D, class E>
struct can_backward_sub : conjunction<
    can_multiply<C, D>, have_same_elements<C, D, E>, have_same_dimensions<D, E>,
    is_square<C>
  > {};

/** @internal
 *
 *  @brief Tests whether or not the forward substitution algorithm can be
 *         applied to a set of types.
 *
 *  @tparam C Lower triangular operator type.
 *  @tparam D Unknown matrix or vector type.
 *  @tparam E Know matrix or vector type.
 *
 *  @ingroup SUBSTITUTIONS
 */
template <class C, class D, class E>
struct can_forward_sub : can_backward_sub<C, D, E> {};

} // namespace internal

/** @brief Solves a linear system using backward substitution.
 *
 *  @tparam C
 *  @tparam D
 *  @tparam E
 *
 *  @param U Upper triangular operator.
 *  @param X Unknown matrix or vector.
 *  @param Y Know matrix or vector.
 *
 *  @return Zero on success and some other value otherwise.
 *
 *  Solves a linear system of the following form:
 *
 *  \f[
 *    U X = Y
 *  \f]
 * 
 *  where \f$U\f$ is an upper triangular operator, \f$X\f$ is an unknow matrix
 *  or vector, and \f$Y\f$ is a known matrix or vector.
 *
 *  In order for the backward substitution to be valid, the matrix `U` must be
 *  in upper triangular form. The function itself does not check for this and
 *  simply assumes the elements below the main diagonal are all zero.
 *
 *  Lin assertion errors will be thrown if the dimensions of `X` are not the
 *  same as the dimensions of `Y`.
 *
 *  @sa internal::can_backward_sub
 *  @sa forward_sub
 *
 *  @ingroup SUBSTITUTIONS
 */
template <class C, class D, class E, typename =
    std::enable_if_t<internal::can_backward_sub<C, D, E>::value>>
constexpr size_t backward_sub(internal::Mapping<C> const &U, internal::Mapping<D> &X, internal::Mapping<E> const &Y) {
  LIN_ASSERT(U.rows() == U.cols());
  LIN_ASSERT(U.cols() == Y.rows());
  LIN_ASSERT(Y.rows() == X.rows());
  LIN_ASSERT(Y.cols() == X.cols());

  // Solve for the last row
  size_t m = U.rows() - 1;
  row(X, m) = row(Y, m) / U(m, m);

  // Solve for the other rows in descending order
  size_t n = m - 1;
  do {
    typedef typename C::Traits::elem_t Elem;
    typedef RowVector<Elem, 0, C::Traits::max_rows> T;
    typedef std::conditional_t<internal::is_col_vector<E>::value, Vector<Elem, 0, E::Traits::max_rows>, Matrix<Elem, 0, E::Traits::cols, E::Traits::max_rows, E::Traits::max_cols>> V;

    row(X, n) = (row(Y, n) - ref<T>(U, n, n + 1, m - n) * ref<V>(X, n + 1, 0, m - n, X.cols())) / U(n, n);
  } while (n--);

  // TODO : Change this to a meaningfull error code
  return 0;
}

/** @brief Solves a linear system using backward substitution.
 *
 *  @tparam C
 *  @tparam D
 *  @tparam E
 *
 *  @param U Upper triangular operator.
 *  @param X Unknown matrix or vector.
 *  @param Y Know matrix or vector.
 *
 *  @return Zero on success and some other value otherwise.
 *
 *  Solves a linear system of the following form:
 *
 *  \f[
 *    U X = Y
 *  \f]
 * 
 *  where \f$U\f$ is an upper triangular operator, \f$X\f$ is an unknow matrix
 *  or vector, and \f$Y\f$ is a known matrix or vector.
 *
 *  In order for the backward substitution to be valid, the matrix `U` must be
 *  in upper triangular form. The function itself does not check for this and
 *  simply assumes the elements below the main diagonal are all zero.
 *
 *  @sa internal::can_backward_sub
 *  @sa forward_sub
 *
 *  @ingroup SUBSTITUTIONS
 */
template <class C, class D, class E, typename =
    std::enable_if_t<internal::can_backward_sub<C, D, E>::value>>
constexpr size_t backward_sub(internal::Mapping<C> const &U, internal::Base<D> &X, internal::Mapping<E> const &Y) {
  X.resize(Y.rows(), Y.cols());
  return backward_sub(U, static_cast<internal::Mapping<D> &>(X), Y);
}

/** @brief Solves a linear system using forward substitution.
 *
 *  @tparam C
 *  @tparam D
 *  @tparam E
 *
 *  @param L Lower triangular operator.
 *  @param X Unknown matrix or vector.
 *  @param Y Known matrix or vector.
 *
 *  @return Zero on success and some other value otherwise.
 *
 *  Solves a linear system of the following form:
 *
 *  \f[
 *    L X = Y
 *  \f]
 * 
 *  where \f$L\f$ is a lower triangular operator, \f$X\f$ is an unknow matrix or
 *  vector, and \f$Y\f$ is a known matrix or vector.
 *
 *  In order for the forward substitution to be valid, the matrix `L` must be in
 *  lower triangular form. The function itself does not check for this and
 *  simply assumes the elements above the main diagonal are all zero.
 *
 *  Lin assertion errors will be thrown if the dimensions of `X` are not the
 *  same as the dimensions of `Y`.
 *
 *  @sa internal::can_forward_sub
 *  @sa backward_sub
 *
 *  @ingroup SUBSTITUTIONS
 */
template <class C, class D, class E, typename =
    std::enable_if_t<internal::can_forward_sub<C, D, E>::value>>
constexpr size_t forward_sub(internal::Mapping<C> const &L, internal::Mapping<D> &X, internal::Mapping<E> const &Y) {
  LIN_ASSERT(L.rows() == L.cols());
  LIN_ASSERT(L.cols() == Y.rows());
  LIN_ASSERT(Y.rows() == X.rows());
  LIN_ASSERT(Y.cols() == X.cols());

  // Solve for the first row
  row(X, 0) = row(Y, 0) / L(0, 0);

  // Solve for other rows in ascending order
  for (size_t n = 1; n < X.rows(); n++) {
    typedef typename C::Traits::elem_t Elem;
    typedef RowVector<Elem, 0, C::Traits::max_cols> T;
    typedef std::conditional_t<internal::is_col_vector<E>::value, Vector<Elem, 0, E::Traits::max_rows>, Matrix<Elem, 0, E::Traits::cols, E::Traits::max_rows, E::Traits::max_cols>> V;

    row(X, n) = (row(Y, n) - ref<T>(L, n, 0, n) * ref<V>(X, 0, 0, n, X.cols())) / L(n, n);
  }

  // TODO : Change this to a meaningfull error code
  return 0;
}

/** @brief Solves a linear system using forward substitution.
 *
 *  @tparam C
 *  @tparam D
 *  @tparam E
 *
 *  @param L Lower triangular operator.
 *  @param X Unknow matrix or vector.
 *  @param Y Known matrix or vector.
 *
 *  @return Zero on success and some other value otherwise.
 *
 *  Solves a linear system of the following form:
 *
 *  \f[
 *    L X = Y
 *  \f]
 * 
 *  where \f$L\f$ is a lower triangular operator, \f$X\f$ is an unknow matrix or
 *  vector, and \f$Y\f$ is a known matrix or vector.
 *
 *  In order for the forward substitution to be valid, the matrix `L` must be in
 *  lower triangular form. The function itself does not check for this and
 *  simply assumes the elements above the main diagonal are all zero.
 *
 *  @sa internal::can_forward_sub
 *  @sa backward_sub
 *
 *  @ingroup SUBSTITUTIONS
 */
template <class C, class D, class E, typename =
    std::enable_if_t<internal::can_forward_sub<C, D, E>::value>>
constexpr size_t forward_sub(internal::Mapping<C> const &L, internal::Base<D> &X, internal::Mapping<E> const &Y) {
  X.resize(Y.rows(), Y.cols());
  return forward_sub(L, static_cast<internal::Mapping<D> &>(X), Y);
}
} // namespace lin

#endif
