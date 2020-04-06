/** @file lin/core/traits/tensor.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for the core tensor module. */

// TODO : Documentation for this entire file

#ifndef LIN_CORE_TRAITS_TENSOR_HPP_
#define LIN_CORE_TRAITS_TENSOR_HPP_

#include "../config.hpp"
#include "utilities.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @struct _traits
 *  Backend traits implementation defined for all children of the tensor stream
 *  class. From this information, an evaluation type and full traits struct will
 *  be generated. */
template <class C, typename = void>
struct _traits;

/** @typedef _traits_elem_t */
template <class C>
using _traits_elem_t = typename _traits<C>::Elem;

/** @struct _evaluates_to
 *  Backend traits implementation defined for all value backed children of the
 *  tensor stream class (essentially just the vector and matrix classes). This
 *  struct allows a evaluation type to be assigned to all streams and helps
 *  generate the full traits struct. */
template <class C, typename = void>
struct _evaluates_to;

/** @typedef _evaluates_to_t */
template <class C>
using _evaluates_to_t = typename _evaluates_to<C>::Eval;

/** @struct traits
 *  Colleciton of compile time traits for tensor types. This includes dimension
 *  information, element type, and evaluation type. Traits will also be
 *  accesible via the ::Traits member of all tensor types. */
template <class C>
struct traits {
  typedef _traits_elem_t<C> Elem;
  typedef _evaluates_to_t<C> Eval;
  constexpr static size_t
    Rows = _traits<C>::Rows,
    Cols = _traits<C>::Cols,
    Size = Rows * Cols,
    MaxRows = _traits<C>::MaxRows,
    MaxCols = _traits<C>::MaxCols,
    MaxSize = MaxRows * MaxCols;
};

/** @typedef traits_elem_t */
template <class C>
using traits_elem_t = typename traits<C>::Elem;

/** @typedef traits_eval_t */
template <class C>
using traits_eval_t = typename traits<C>::Eval;

/** @struct has_traits
 *  Tests if a given type has tensor traits. Currently this relies on the
 *  existance of a ::Traits member within C. */
template <class C, typename = void>
struct has_traits;

/** @struct has_fixed_rows */
template <class C, typename = void>
struct has_fixed_rows;

/** @struct has_fixed_cols */
template <class C, typename = void>
struct has_fixed_cols;

/** @struct has_fixed_dimensions */
template <class C>
struct has_fixed_dimensions
    : conjunction<has_fixed_rows<C>, has_fixed_cols<C>> { };

/** @struct has_bounded_rows */
template <class C, typename = void>
struct has_bounded_rows;

/** @struct has_bounded_cols */
template <class C, typename = void>
struct has_bounded_cols;

/** @struct has_bounded_dims */
template <class C>
struct has_bounded_dimensions
    : conjunction<has_bounded_rows<C>, has_bounded_cols<C>> { };

/** @struct have_same_elements */
template <class... Cs>
struct have_same_elements;

/** @struct have_same_rows */
template <class... Cs>
struct have_same_rows;

/** @struct have_same_cols */
template <class... Cs>
struct have_same_cols;

/** @struct have_same_dimensions */
template <class... Cs>
struct have_same_dimensions;

/** @struct have_same_traits */
template <class... Cs>
struct have_same_traits;

/** @struct has_valid_traits */
template <class C, typename = void>
struct has_valid_traits;

/** @struct is_tall */
template <class C, typename = void>
struct is_tall;

/** @struct is_short */
template <class C, typename = void>
struct is_short;

/** @struct is_square */
template <class C>
struct is_square : conjunction<is_tall<C>, is_short<C>> { };

}  // namespace internal
}  // namespace lin

#include "inl/tensor.inl"

#endif
