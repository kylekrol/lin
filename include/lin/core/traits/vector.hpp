// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/traits/vector.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TRAITS_VECTOR_HPP_
#define LIN_CORE_TRAITS_VECTOR_HPP_

#include "tensor.hpp"
#include "utilities.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @brief Tests if a tensor type is a row vector.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be a row vector if its row count is fixed at
 *  one row and it can have at least two columns.
 * 
 *  A tensor type deemed to be a row vector will evaluate to a RowVector.
 * 
 *  @sa internal::has_fixed_rows
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_row_vector : std::integral_constant<bool, (
    has_fixed_rows<C>::value &&
    (_dims<C>::rows == 1) &&
    (_dims<C>::max_cols > 1)
  )> { };

/** @brief Tests if a tensor type is a column vector.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be a column vector if its column count is fixed
 *  at one column and it can have at least two rows.
 * 
 *  A tensor type deemed to be a column vector will evaluate to a Vector.
 * 
 *  @sa internal::has_fixed_cols
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_col_vector : std::integral_constant<bool, (
    has_fixed_cols<C>::value &&
    (_dims<C>::cols == 1) &&
    (_dims<C>::max_rows > 1)
  )> { };

/** @brief Tests if a tensor type is a vector.
 *
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be a vector if it's either a row vector or
 *  column vector.
 * 
 *  @sa internal::is_row_vector 
 *  @sa internal::is_col_vector.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_vector : disjunction<is_row_vector<C>, is_col_vector<C>> { };

template <class C, typename = void>
struct _vector_dims;

template <class C>
struct _vector_dims<C, std::enable_if_t<is_row_vector<C>::value>> {
  static constexpr size_t length = _dims<C>::cols;
  static constexpr size_t max_length = _dims<C>::max_cols;
};

template <class C>
struct _vector_dims<C, std::enable_if_t<is_col_vector<C>::value>> {
  static constexpr size_t length = _dims<C>::rows;
  static constexpr size_t max_length = _dims<C>::max_rows;
};

/** @brief Collection of compile time information describing a tensor type which
 *         is deemed a vector.
 * 
 *  @tparam C %Vector type.
 * 
 *  More details to come.
 * 
 *  @sa internal::is_vector
 *  @sa internal::traits.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct vector_traits {
  static_assert(is_vector<C>::value,
      "lin::internal::vector_traits can only be populated for vector types");
  /** @brief %Vector's element type.
   */
  typedef _elem_t<C> elem_t;
  /** @brief %Vector's evaluation type.
   * 
   *  This is the type returned when forcing the generation of a temporary with a
   *  call to Stream::eval().
   */
  typedef _eval_t<C> eval_t;
  /** @brief %Vector length.
   * 
   *  Defines the number of elements a given vector type has. If nonzero, the
   *  element count is fixed. If zero, the number of elements is allowed to vary.
   */
  static constexpr size_t length = _vector_dims<C>::length;
  /** @brief Max vector length.
   *
   *  Defines the maximum number of elements a given vector type can have. This
   *  should be equal to the length unless the length is nonzero.
   */
  static constexpr size_t max_length = _vector_dims<C>::max_length;
};

template <class C, class D>
struct _have_same_vector_dimensions : std::integral_constant<bool, (
    (_vector_dims<C>::length == _vector_dims<D>::length) &&
    (_vector_dims<C>::max_length == _vector_dims<D>::max_length)
  )> { };

/** @brief Tests if a set of vector types all have the same dimensions.
 * 
 *  @tparam Cs %Vector types.
 * 
 *  Two vectors are determined to have the same dimensions if they have the same
 *  length and max length.
 * 
 *  If less than two vector types are given, it defaults to true.
 *
 *  @sa internal::is_vector
 *  @sa internal::vector_traits
 * 
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_vector_dimensions;

template <>
struct have_same_vector_dimensions<> : std::true_type { };

template <class C>
struct have_same_vector_dimensions<C> : std::true_type {
  static_assert(is_vector<C>::value,
      "lin::internal::have_same_vector_dimensions cannot be passed a non-vector type");
};

template <class C, class... Cs>
struct have_same_vector_dimensions<C, Cs...>
    : conjunction<_have_same_vector_dimensions<C, Cs>...> { };

/** @brief Tests if a set of vector types all have the same vector traits.
 * 
 *  @tparam Cs %Vector types.
 * 
 *  Two vectors are determined to have the same vector traits if they have the
 *  same vector dimensions and element types.
 * 
 *  If less than two vector are given, it defaults to true.
 * 
 *  @sa internal::is_vector
 *  @sa internal::have_same_elements
 *  @sa internal::have_same_vector_dimensions
 *
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_vector_traits : conjunction<
    have_same_elements<Cs...>, have_same_vector_dimensions<Cs...>
  > { };

}  // namespace internal
}  // namespace lin

#endif
