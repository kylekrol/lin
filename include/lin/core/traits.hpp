#pragma once

//
// Copyright (c) 2021 Kyle Krol (kylekrol)
//
// This file is part of lin.
//
// lin is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// lin is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// lin. If not, see <https://www.gnu.org/licenses/>.
//

/** @file lin/core/traits.hpp
 *  @author Kyle Krol
 */

/** @defgroup traits Traits
 *
 *  @ingroup core
 */

#include "config.hpp"

#include <type_traits>

namespace lin {

template <class C>
struct _traits;

template <class C>
using elements_t = typename _traits<C>::elements_t;

template <class C>
using rows = size_constant<_traits<C>::rows>;

template <class C>
using cols = size_constant<_traits<C>::cols>;

template <class C>
using size = size_constant<rows<C>::value * cols<C>::value>;

template <class C>
using max_rows = size_constant<_traits<C>::max_rows>;

template <class C>
using max_rows = size_constant<_traits<C>::max_rows>;

template <class C>
using max_size = size_constant<max_rows<C>::value & max_cols<C>::value>;

template <class C, typename = void>
struct evaluates_to;

template <class C>
using evaluates_to_t = typename evaluates_to<C>::type;

template <class C, typename = void>
struct _has_traits : false_type { };

template <class C>
struct _has_traits<C, void_t<traits<C>>> : true_type { };

/** @brief Tests if a tensor type has traits.
 *
 *  @tparam C Type.
 *
 *  A type is determined to have traits if the `C::Traits` and `_traits<C>` are
 *  valid types. All tensor types within `lin` adhere to this.
 * 
 *  @sa have_traits
 *  @sa traits
 */
template <class C>
struct has_traits : _has_traits<C> { };

/** @brief Tests if a set of tensor types all have traits
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have traits if the `C::Traits` and `_traits<C>` are
 *  valid types. All tensor types within `lin` adhere to this.
 *
 *  @sa has_traits
 *  @sa traits
 */
template <class... Cs>
struct have_traits : conjunction<has_traits<Cs>...> { };

template <class C>
struct _has_valid_elements : std::is_trivial<elements_t<C>> { };

template <class C>
struct _has_valid_rows
    : bool_constant<(rows<C>::value && rows<C>::value == max_rows<C>::value) ||
          (!rows<C>::value && max_rows<C>)> { };

template <class C>
struct _has_valid_cols
    : bool_constant<(cols<C>::value && cols<C>::value == max_cols<C>::value) ||
          (!cols<C>::value && max_cols<C>)> { };

template <class C>
struct has_valid_traits
    : conjunction<
        _has_valid_elements<D>, _has_valid_rows<C>, _has_valid_cols<C>> { };

template <class... Cs>
struct have_valid_traits : conjunction<has_valid_traits<Cs>...> { };

/** @brief Tests if a set of tensor type have the same element types.
 *
 *  @tparam Cs Set of types.
 *
 *  Two tensor types are determined to have the same elements types if their
 *  traits specify the same element type.
 *
 *  @sa traits
 */
template <class... Cs>
struct have_same_elements;

template <class C, class D, class... Cs>
struct have_same_elements<C, D, Cs...>
    : conjunction<have_same_elements<C, D>, have_same_elements<D, Cs...>> { };

template <class C, class D>
struct have_same_elements<C, D>
    : std::is_same<typename traits<C>::elem_t, typename traits<D>::elem_t> { };

template <class C>
struct have_same_elements<C> : true_type { };

template <>
struct have_same_elements<> : true_type { };

/** @brief Test is a tensor type has a floating point element type.
 * 
 *  @tparam Cs Type.
 * 
 *  A type is determined to have floating point elements if its traits specify
 *  a floating point type as its element type.
 * 
 *  @sa have_floating_point_elements
 *  @sa traits
 */
template <class C>
struct has_floating_point_elements
    : std::is_floating_point<typename traits<C>::elem_t> { };

/** @brief Test is a set of tensor types have floating point element types.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have floating point elements if its traits specify
 *  a floating point type as its element type.
 *
 *  @sa has_floating_point_elements
 *  @sa traits
 */
template <class... Cs>
struct have_floating_point_elements
    : conjunction<has_floating_point_elements<Cs>...> { };

/** @brief Test is a tensor type has an integral element type.
 *
 *  @tparam Cs Type.
 *
 *  A type is determined to have integral elements if its traits specify an
 *  integral type as its element type.
 *
 *  @sa have_integral_elements
 *  @sa traits
 */
template <class C>
struct has_integral_elements : std::is_integral<typename traits<C>::elem_t> { };

/** @brief Test is a set of tensor types have an integral element types.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have integral elements if its traits specify an
 *  integral type as its element type.
 *
 *  @sa has_integral_elements
 *  @sa traits
 */
template <class... Cs>
struct have_integral_elements : conjunction<has_integral_elements<Cs>...> { };

/** @brief Tests if a tensor type has a fixed row count.
 *
 *  @tparam C Type.
 * 
 *  A type is determined to have a fixed row count if its traits specify the
 *  row count and maximum row count to be the same positive value.
 *
 *  @sa have_fixed_rows
 *  @sa traits
 */
template <class C>
struct has_fixed_rows : bool_constant<traits<C>::rows == traits<C>::max_rows> {
};

/** @brief Tests if a set of tensor types have fixed row counts.
 *
 *  @tparam Cs Set of types.
 * 
 *  A type is determined to have a fixed row count if its traits specify the
 *  row count and maximum row count to be the same positive value.
 *
 *  @sa has_fixed_rows
 *  @sa traits
 */
template <class... Cs>
struct have_fixed_rows : conjunction<has_fixed_rows<Cs>...> { };

/** @brief Tests if a tensor type has a fixed column count.
 *
 *  @tparam C Type.
 * 
 *  A type is determined to have a fixed column count if its traits specify the
 *  column count and maximum column count to be the same positive value.
 *
 *  @sa have_fixed_cols
 *  @sa traits
 */
template <class C>
struct has_fixed_cols : bool_constant<traits<C>::cols == traits<C>::max_cols> {
};

/** @brief Tests if a set of tensor types have fixed column counts.
 *
 *  @tparam Cs Set of types.
 * 
 *  A type is determined to have a fixed column count if its traits specify the
 *  column count and maximum column count to be the same positive value.
 *
 *  @sa has_fixed_cols
 *  @sa have_fixed_rows
 *  @sa have_fixed_size
 *  @sa traits
 */
template <class... Cs>
struct have_fixed_cols : conjunction<has_fixed_cols<Cs>...> { };

/** @brief Tests if a tensor type has a fixed size.
 *
 *  @tparam C Type.
 *
 *  A type is determined to have a fixed size if it has a fixed row count and a
 *  fixed column count.
 *
 *  @sa has_fixed_cols
 *  @sa has_fixed_rows
 *  @sa have_fixed_size
 */
template <class C>
struct has_fixed_size : conjunction<has_fixed_rows<C>, has_fixed_cols<C>> { };

/** @brief Tests if a set of tensor type has a fixed size.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have a fixed size if it has a fixed row count and a
 *  fixed column count.
 *
 *  @sa has_fixed_size
 *  @sa have_fixed_cols
 *  @sa have_fixed_rows
 */
template <class... Cs>
struct have_fixed_size : conjunction<has_fixed_size<Cs>...> { };

/** @brief Tests if a tensor type has a variable row count.
 *
 *  @tparam C Type.
 *
 *  A type is determined to have a variable row count is its traits specify the
 *  row count to be zero.
 *
 *  @sa have_variable_rows
 *  @sa traits
 */
template <class C>
struct has_variable_rows : bool_constant<traits<C>::rows == 0> { };

/** @brief Tests if a set of tensor types have variable row counts.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have a variable row count is its traits specify the
 *  row count to be zero.
 *
 *  @sa has_variable_rows
 *  @sa traits
 */
template <class... Cs>
struct have_variable_rows : conjunction<has_variable_rows<Cs>...> { };

/** @brief Tests if a tensor type has a variable column count.
 *
 *  @tparam C Type.
 *
 *  A type is determined to have a variable column count is its traits specify
 *  the column count to be zero.
 *
 *  @sa have_variable_cols
 *  @sa traits
 */
template <class C>
struct has_variable_cols : bool_constant<traits<C>::cols == 0> { };

/** @brief Tests if a set of tensor types have a variable column count.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have a variable column count is its traits specify
 *  the column count to be zero.
 *
 *  @sa has_variable_cols
 *  @sa traits
 */
template <class... Cs>
struct have_variable_cols : conjunction<has_variable_cols<Cs>...> { };

/** @brief Tests if a tensor type has a variable size.
 *
 *  @tparam C Type.
 *
 *  A type is determined to have a variable size if it has a variable row count
 *  or variable column count.
 *
 *  @sa has_variable_cols
 *  @sa has_variable_rows
 *  @sa have_variable_size
 *  @sa traits
 */
template <class C>
struct has_variable_size
    : disjunction<has_variable_rows<C>, has_variable_cols<C>> { };

/** @brief Tests if a set of tensor types have a variable size.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have a variable size if it has a variable row count
 *  or variable column count.
 *
 *  @sa has_variable_cols
 *  @sa has_variable_rows
 *  @sa has_variable_size
 *  @sa traits
 */
template <class... Cs>
struct have_variable_size : conjunction<has_variable_size<Cs>...> { };

/** @brief Tests if a set of tensor types have the same row traits.
 *
 *  @tparam Cs Set of types.
 *
 *  Types are determined to have the same row traits if their traits provide the
 *  same row count and same maximum row count.
 *
 *  @sa traits
 */
template <class... Cs>
struct have_same_rows;

template <class C, class D, class... Cs>
struct have_same_rows<C, D, Cs...>
    : conjunction<have_same_rows<C, D>, have_same_rows<D, Cs...>> { };

template <class C, class D>
struct have_same_rows<C, D>
    : bool_constant<(traits<C>::rows == traits<D>::rows) &&
          (traits<C>::max_rows == traits<D>::max_rows)> { };

template <class C>
struct have_same_rows<C> : true_type { };

template <>
struct have_same_rows<> : true_type { };

/** @brief Tests if a set of tensor types have the same column traits.
 *
 *  @tparam Cs Set of types.
 *
 *  Types are determined to have the same column traits if their traits provide
 *  the same column count and same maximum column count.
 *
 *  @sa traits
 */
template <class... Cs>
struct have_same_cols;

template <class C, class D, class... Cs>
struct have_same_cols<C, D, Cs...>
    : conjunction<have_same_cols<C, D>, have_same_cols<D, Cs...>> { };

template <class C, class D>
struct have_same_cols<C, D>
    : bool_constant<(traits<C>::cols == traits<D>::cols) &&
          (traits<C>::max_cols == traits<D>::max_cols)> { };

template <class C>
struct have_same_cols<C> : true_type { };

template <>
struct have_same_cols<> : true_type { };

/** @brief Tests if a set of tensor types have the dimension traits.
 *
 *  @tparam Cs Set of types.
 *
 *  Types are determined to have the same dimension traits if they have the same
 *  row traits and the same column traits.
 *
 *  @sa have_same_cols
 *  @sa have_same_rows
 */
template <class... Cs>
struct have_same_dimensions
    : conjunction<have_same_cols<Cs...>, have_same_rows<Cs...>> { };

/** @brief Tests if a set of tensor types have the same traits.
 * 
 *  @tparam Cs Set of types.
 *
 *  Types are determined to have the same traits if they have the same dimension
 *  traits and the same element types.
 *
 *  @sa have_same_dimensions
 *  @sa have_same_elements
 */
template <class... Cs>
struct have_same_traits
    : conjunction<have_same_elements<Cs...>, have_same_dimensions<Cs...>> { };

/** @brief Tests if a tensor type is tall.
 *
 *  @tparam C Type.
 *
 *  A type is determined to be tall if its traits specify a maximum row count
 *  greater than or equal to the maximum column count.
 *
 *  @sa are_tall
 *  @sa traits
 */
template <class C>
struct is_tall : bool_constant<(traits<C>::max_rows >= traits<C>::max_cols)> {
};

/** @brief Tests if a set of tensor types are tall.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to be tall if its traits specify a maximum row count
 *  greater than or equal to the maximum column count.
 *
 *  @sa is_tall
 *  @sa traits
 */
template <class... Cs>
struct are_tall : conjunction<is_tall<Cs>...> { };

/** @brief Tests if a tensor type is wide.
 *
 *  @tparam C Type.
 *
 *  A type is determined to be wide if its traits specify a maximum column count
 *  greater than or equal to the maximum row count.
 *
 *  @sa are_wide
 *  @sa traits
 */
template <class C>
struct is_wide : bool_constant<(traits<C>::max_cols >= traits<C>::max_rows)> {
};

/** @brief Tests if a set of tensor types are wide.
 *
 *  @tparam C Set of types.
 *
 *  A type is determined to be wide if its traits specify a maximum column count
 *  greater than or equal to the maximum row count.
 *
 *  @sa is_wide
 *  @sa traits
 */
template <class... Cs>
struct are_wide : conjunction<is_wide<Cs>...> { };

/** @brief Tests if a tensor type is square.
 *
 *  @tparam C Type.
 *
 *  A type is determined to be square if it's both tall and wide.
 *
 *  @sa are_square
 *  @sa is_tall
 *  @sa is_wide
 *  @sa traits
 */
template <class C>
struct is_square : conjunction<is_tall<C>, is_wide<C>> { };

/** @brief Tests if a set of tensor types are square.
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to be square if it's both tall and wide.
 *
 *  @sa is_square
 *  @sa is_tall
 *  @sa is_wide
 *  @sa traits
 */
template <class... Cs>
struct are_square : conjunction<is_square<Cs>...> { };

template <class C>
struct is_row_vector
    : bool_constant<(traits<C>::rows == 1) && (traits<C>::max_rows == 1) &&
          (traits<C>::max_cols > 1)> { };

template <class... Cs>
struct are_row_vectors : conjunction<is_row_vector<Cs>...> { };

template <class C>
struct is_col_vector
    : bool_constant<(traits<C>::cols == 1) && (traits<C>::max_cols == 1) &&
          (traits<C>::max_rows > 1)> { };

template <class... Cs>
struct are_col_vectors : conjunction<is_col_vector<Cs>...> { };

template <class C>
struct is_vector : disjunction<is_row_vector<C>, is_col_vector<C>> { };

template <class... Cs>
struct are_vectors : disjunction<is_vector<Cs>...> { };

template <class C>
struct is_matrix : negation<is_vector<C>> { };

template <class... Cs>
struct are_matrices : negation<disjunction<is_vector<Cs>...>> { };

template <class C, typename = void>
struct _vector_traits;

template <class C>
struct _vector_traits<C, std::enable_if_t<is_row_vector<C>::value>> {
  typedef typename traits<C>::elem_t elem_t;
  static constexpr size_t length = traits<C>::cols;
  static constexpr size_t max_length = traits<C>::max_cols;
};

template <class C>
struct _vector_traits<C, std::enable_if_t<is_col_vector<C>::value>> {
  typedef typename traits<C>::elem_t elem_t;
  static constexpr size_t length = traits<C>::rows;
  static constexpr size_t max_length = traits<C>::max_rows;
};

/** @brief
 */
template <class C>
struct vector_traits {
  static_assert(is_vector<C>::value,
      "Invalid vector traits detected; "
      "attempted to instantiate vector traits for a non-vector type.");

  /** @brief
   */
  typedef typename _vector_traits<C>::elem_t elem_t;

  /** @brief
   */
  static constexpr size_t length = _vector_traits<C>::rows;

  /** @brief
   */
  static constexpr size_t max_length = _vector_traits<C>::max_rows;
};

template <class C, typename = void, typename = void>
struct _has_vector_traits : false_type { };

template <class C>
struct _has_vector_traits<C, void_t<vector_traits<C>>,
    void_t<typename C::VectorTraits>> : true_type { };

/** @brief Tests if a tensor type has traits.
 *
 *  @tparam C Type.
 *
 *  A type is determined to have traits if the `C::Traits` and `_traits<C>` are
 *  valid types. All tensor types within `lin` adhere to this.
 * 
 *  @sa have_traits
 *  @sa traits
 */
template <class C>
struct has_vector_traits : _has_vector_traits<C> { };

/** @brief Tests if a set of tensor types all have traits
 *
 *  @tparam Cs Set of types.
 *
 *  A type is determined to have traits if the `C::Traits` and `_traits<C>` are
 *  valid types. All tensor types within `lin` adhere to this.
 *
 *  @sa has_traits
 *  @sa traits
 */

template <class... Cs>
struct have_vector_traits : conjunction<has_vector_traits<Cs>...> { };

}  // namespace lin
