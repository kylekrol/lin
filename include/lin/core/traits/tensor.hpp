// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/traits/tensor.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TRAITS_TENSOR_HPP_
#define LIN_CORE_TRAITS_TENSOR_HPP_

#include "utilities.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @brief Provides a tensor type's element type.
 *
 *  @tparam C %Tensor type.
 *
 *  This is an implentation details that allows the leaves of the %lin inheritance
 *  tree to make their element type information known. This type is in turn used
 *  to populate the traits type.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct _elem;

template <class C>
using _elem_t = typename _elem<C>::type;

/** @brief Provides a specific tensor type's evaluation type.
 *
 *  @tparam C %Tensor type.
 * 
 *  This is an implementation detail that allows the leaves %lin inheritance tree
 *  that store their elements directly in a backing array. This type is in turn
 *  used to populate the traits type.
 *
 *  @ingroup CORETRAITS
 */
template <class C, typename = void>
struct _eval;

template <class C>
using _eval_t = typename _eval<C>::type;

/** @brief Provides a specific tensor type's compile time dimensions.
 *
 *  @tparam C %Tensor type.
 *
 *  This is an implentation detail that allows the leaves of the %lin inheritance
 *  tree to make there element type information known. This type in in turn used
 *  to create the populate traits type.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct _dims;

/** @brief Collection of compile time information about a specific tensor class.
 *
 *  @tparam C %Tensor type.
 * 
 *  More details to come...
 *
 *  @sa internal::_elem
 *  @sa internal::_eval
 *  @sa internal::_dims
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct traits {
  /** @brief %Tensor's element type.
   * 
   *  This si the type returned when accessing tensor elements via
   *  internal::Stream::operator()().
   */
  typedef _elem_t<C> elem_t;
  /** @brief %Tensor's evalutation type.
   *
   *  This is the type returned when forcing the generation of a temporary with a
   *  call to internal::Stream::eval().
   *  
   *  This type will always be some sort of Matrix, RowVector, or Vector.
   */
  typedef _eval_t<C> eval_t;
  /** @brief Row count.
   * 
   *  Defines the number of rows a given tensor type has at compile time. If
   *  nonzero, the row dimension is fixed. If zero, the row dimension is allowed
   *  to vary.
   */
  static constexpr size_t rows = _dims<C>::rows;
  /** @brief Column count.
   *
   *  Defines the number of columns a given tensor type has at compile time. If
   *  nonzero, the column dimension is fixed. If zero, the column dimension is
   *  allowed to vary.
   */
  static constexpr size_t cols = _dims<C>::cols;
  /** @brief Total element count.
   *
   *  Defines the number of elements a given tensor type has at compile time. This
   *  is set as the row count time the column count.
   */
  static constexpr size_t size = rows * cols;
  /** @brief Max row count.
   * 
   *  Defines the maximum number of rows a given tensor type can have. This should
   *  be equal to the row count unless the row count is zero.
   */
  static constexpr size_t max_rows = _dims<C>::max_rows;
  /** @brief Max column count.
   * 
   *  Defines the maximum number of columns a given tensor type can have. This
   *  should be equal to the column count unless the column count is zero.
   */
  static constexpr size_t max_cols = _dims<C>::max_cols;
  /** @brief Max total element count.
   * 
   *  Defines the maximum number of elements a given tensor type can have. This
   *  is set as the max row count times the max column count.
   */
  static constexpr size_t max_size = max_rows * max_cols;
};

/** @ingroup TRAITS
 */
template <class C>
using traits_elem_t = typename traits<C>::elem_t;

/** @ingroup TRAITS
 */
template <class C>
using traits_eval_t = typename traits<C>::eval_t;

template <class C, typename = void>
struct _has_traits : std::false_type { };

template <class C>
struct _has_traits<C, void_t<typename C::Traits>> : std::true_type { };

/** @brief Tests if a type has traits.
 * 
 *  @tparam C Type.
 * 
 *  A type is determined to have traits if `C::Traits` actually maps to a valid
 *  type. All tensor classes in lin have this class member.
 * 
 *  @sa internal::traits.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_traits : _has_traits<C> { };

/** @brief Tests if a tensor type has a fixed row count.
 *
 *  @tparam C %Tensor type.
 *
 *  A tensor type is determined to have fixed rows if its row count is equal to
 *  its max row count and both values are nonzero.
 *
 *  A tensor deemed to have fixed rows only has one valid row count at runtime.
 * 
 *  See internal::traits.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_fixed_rows : std::integral_constant<bool, (
    (_dims<C>::rows == _dims<C>::max_rows) && _dims<C>::rows
  )> { };

/** @brief Tests if a tensor type has a fixed column count.
 *
 *  @tparam C %Tensor type.
 *
 *  A tensor type is determined to have fixed columns if its column count is
 *  equal to its max column count and both values are nonzero.
 * 
 *  A tensor deemed to have fixed columns only has one valid column count at
 *  runtime.
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_fixed_cols : std::integral_constant<bool, (
    (_dims<C>::cols == _dims<C>::max_cols) && _dims<C>::cols
  )> { };

/** @brief Tests if a tensor type has fixed dimensions.
 *
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have fixed dimensions if it has both fixed rows
 *  and columns.
 * 
 *  @sa internal::has_fixed_rows
 *  @sa internal::has_fixed_cols
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_fixed_dimensions
    : conjunction<has_fixed_rows<C>, has_fixed_cols<C>> { };

/** @brief Tests is a tensor type has a strictly bounded row count.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have a strictly bounded row count if it's row
 *  count is zero and its max row count is nonzero.
 * 
 *  A tensor deemed to have a strictly bounded row count can have multiple row
 *  counts at runtime (assuming its max row count is greater than one).
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_strictly_bounded_rows
    : std::integral_constant<bool, (!_dims<C>::rows && _dims<C>::max_rows)> { };

/** @brief Tests if a tensor type has a strictly bounded column count.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have a strictly bounded column count if it's
 *  column count is zero and its max column count is nonzero.
 * 
 *  A tensor deemed to have a strictly bounded column count can have multiple
 *  column counts at runtime (assuming its max column count is great than one).
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_strictly_bounded_cols
    : std::integral_constant<bool, (!_dims<C>::cols && _dims<C>::max_cols)> { };

/** @brief Tests if a tensor type has strictly bounded dimensions.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have strictly bounded dimensions if it has both
 *  strictly bounded rows and columns.
 * 
 *  @sa internal::has_strictly_bounded_rows
 *  @sa internal::has_strictly_bounded_cols
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_strictly_bounded_dimensions : conjunction<
    has_strictly_bounded_rows<C>, has_strictly_bounded_cols<C>
  > { };

/** @brief Tests if a tensor type has a bounded row count.
 *
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have a bounded row count if it has a fixed or
 *  strictly bounded row count.
 * 
 *  @sa internal::has_fixed_rows
 *  @sa internal::has_strictly_bounded_rows
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_bounded_rows
    : disjunction<has_fixed_rows<C>, has_strictly_bounded_rows<C>> { };

/** @brief Tests if a tensor type has a bounded column count.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have a bounded column count if it has a fixed
 *  or strictly bounded column count.
 * 
 *  See internal::has_fixed_cols and internal::has_strictly_bounded_cols.
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_bounded_cols
    : disjunction<has_fixed_cols<C>, has_strictly_bounded_cols<C>> { };

/** @brief Tests if a tensor type has bounded dimensions.
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have bounded dimensions if it has both bounded
 *  rows and columns.
 * 
 *  @sa internal::has_bounded_rows
 *  @sa internal::has_bounded_cols
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_bounded_dimensions
    : conjunction<has_bounded_rows<C>, has_bounded_cols<C>> { };

/** @brief Tests if a tensor type's traits are valid.
 *
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to have valid traits if it has bounded dimensions
 *  and a trivial element type.
 * 
 *  @sa internal::has_bounded_dimensions
 *  @sa <a href="http://www.cplusplus.com/reference/type_traits/is_trivial/">std::is_trivial</a>
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct has_valid_traits : conjunction<
    has_bounded_dimensions<C>,
    std::is_trivial<typename _elem<C>::type>
  > { };

/** @brief Tests if a tensor type is "tall".
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be "tall" if its max row count is greater than
 *  or equal to its max column count.
 * 
 *  This serves to screen tensor types to ensure they can have more rows than
 *  columns (or the same number of rows as columns). An example use case would b
 *  in a std::enable_if guard on a function taking the QR factorization of a
 *  matrix. A precondition of this operation is that the matrix is "tall".
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_tall : std::integral_constant<bool, (
    _dims<C>::max_rows >= _dims<C>::max_cols
  )> { };

/** @brief Tests if a tensor type is "short".
 *  
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be "short" if its max row count is less than or
 *  equal to its max column count.
 * 
 *  This serves to screen tensor types to ensure theycan  have more columns than
 *  rows (or the same number of columns as rows).
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_short : std::integral_constant<bool, (
    _dims<C>::max_rows <= _dims<C>::max_cols
  )> { };

/** @brief Tests if a tensor type is "square".
 * 
 *  @tparam C %Tensor type.
 * 
 *  A tensor type is determined to be "short" if its both tall and short (i.e its
 *  max column count is equal to its max column count).
 * 
 *  This serves to screen tensor types to ensure they can have the same number of
 *  rows as columns. An example use case would be in a std::enable_if guard on a
 *  function taking the trace of a matrix. A prediction of this operation is the
 *  matrix being "square".
 * 
 *  @sa internal::is_tall
 *  @sa internal::is_short
 * 
 *  @ingroup CORETRAITS
 */
template <class C>
struct is_square : conjunction<is_tall<C>, is_short<C>> { };

/** @brief Tests if a set of tensor types all have the same element type.
 *
 *  @tparam Cs %Tensor types.
 *
 *  If less than two tensor types are given, it defaults to true.
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_elements;

template <class C, class... Cs>
struct have_same_elements<C, Cs...>
    : conjunction<std::is_same<_elem_t<C>, _elem_t<Cs>>...> { };

template <class C>
struct have_same_elements<C> : std::true_type { };

template <>
struct have_same_elements<> : std::true_type { };

/** @brief Tests if a set of tensor types all have the same row traits.
 *
 *  @tparam Cs %Tensor types.
 *
 *  Two tensors are determined to have the same rows if they have the same row and
 *  max row counts.
 *
 *  If less than two tensor types are given, it defaults to true.
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_rows;

template <class C, class... Cs>
struct have_same_rows<C, Cs...> : conjunction<
    std::integral_constant<bool, (
        (_dims<C>::rows == _dims<Cs>::rows) &&
        (_dims<C>::max_rows == _dims<Cs>::max_rows)
      )>...
  > { };

template <class C>
struct have_same_rows<C> : std::true_type { };

template <>
struct have_same_rows<> : std::true_type { };

/** @brief Tests if a set of tensor types all have the same column traits.
 * 
 *  @tparam Cs %Tensor types.
 * 
 *  Two tensors are determined to have the same columns if they have the same
 *  column and max column counts.
 * 
 *  If less than two tensor types are given, it defaults to true.
 * 
 *  @sa internal::traits
 * 
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_cols;

template <class C, class... Cs>
struct have_same_cols<C, Cs...> : conjunction<
    std::integral_constant<bool, (
        (_dims<C>::cols == _dims<Cs>::cols) &&
        (_dims<C>::max_cols == _dims<Cs>::max_cols)
      )>...
  > { };

template <class C>
struct have_same_cols<C> : std::true_type { };

template <>
struct have_same_cols<> : std::true_type { };

/** @brief Tests if a set of tensor types all have the same dimensions.
 * 
 *  @tparam Cs %Tensor types.
 * 
 *  Two tensors are determined to have the same dimensions if they are also
 *  determined to have the same rows and the same columns.
 * 
 *  If less than two tensor types are given, it defaults to true.
 * 
 *  @sa internal::have_same_rows
 *  @sa internal::have_same_cols
 * 
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_dimensions
    : conjunction<have_same_rows<Cs...>, have_same_cols<Cs...>> { };

/** @brief Tests if a set of tensor types all have the same traits.
 * 
 *  @tparam Cs %Tensor types.
 * 
 *  Two tensors are determined to have the same traits if they are also determined
 *  to have the same dimensions and the same element types.
 * 
 *  If less than two tensor types are given, it defaults to true.
 * 
 *  @sa internal::have_same_dimensions
 *  @sa internal::have_same_elements
 * 
 *  @ingroup CORETRAITS
 */
template <class... Cs>
struct have_same_traits
    : conjunction<have_same_dimensions<Cs...>, have_same_elements<Cs...>> { };

}  // namespace internal
}  // namespace lin

#endif
