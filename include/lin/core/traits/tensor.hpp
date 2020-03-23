/** @file lin/core/traits/tensor.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for the core tensor module. */

// TODO : Documentation for this entire file

#ifndef LIN_CORE_TRAITS_TENSOR_HPP_
#define LIN_CORE_TRAITS_TENSOR_HPP_

#include "utilities.hpp"

#include <cstddef>

namespace lin {

/** @typedef size_t */
typedef std::size_t size_t;

namespace internal {

/** @struct _traits */
template <class C, typename = void>
struct _traits;

/** @typedef _traits_elem_t */
template <class C>
using _traits_elem_t = typename _traits<C>::Elem;

/** @struct _evaluates_to */
template <class C, typename = void>
struct _evaluates_to;

/** @typedef _evaluates_to_t */
template <class C>
using _evaluates_to_t = typename _evaluates_to<C>::type;

/** @struct has_traits */
template <class C, typename = void>
struct has_traits : false_type { };

// TODO : Look into another test that may not depend on the Traits typedef
template <class C>
struct has_traits<C, void_t<typename C::Traits>> : true_type { };

/** @struct has_fixed_rows */
template <class C, typename = void>
struct has_fixed_rows : false_type { };

template <class C>
struct has_fixed_rows<C, enable_if_t<(
    (_traits<C>::Rows > 0) && (_traits<C>::Rows == _traits<C>::MaxRows)
  )>> : true_type { };

/** @struct has_fixed_cols */
template <class C, typename = void>
struct has_fixed_cols : false_type { };

template <class C>
struct has_fixed_cols<C, enable_if_t<(
    (_traits<C>::Cols > 0) && (_traits<C>::Cols == _traits<C>::MaxCols)
  )>> : true_type { };

/** @struct has_fixed_dimensions */
template <class C, typename = void>
struct has_fixed_dimensions : false_type { };

template <class C>
struct has_fixed_dimensions<C, enable_if_t<(
    has_fixed_rows<C>::value && has_fixed_cols<C>::value
  )>> : true_type { };

/** @struct has_bounded_rows */
template <class C, typename = void>
struct has_bounded_rows : false_type { };

template <class C>
struct has_bounded_rows<C, enable_if_t<(
    has_fixed_rows<C>::value || ((_traits<C>::Rows == 0) && (_traits<C>::MaxRows > 0))
  )>> : true_type { };

/** @struct has_bounded_cols */
template <class C, typename = void>
struct has_bounded_cols : false_type { };

template <class C>
struct has_bounded_cols<C, enable_if_t<(
    has_fixed_cols<C>::value || ((_traits<C>::Cols == 0) && (_traits<C>::MaxCols > 0))
  )>> : true_type { };

/** @struct has_bounded_dims */
template <class C, typename = void>
struct has_bounded_dimensions : false_type { };

template <class C>
struct has_bounded_dimensions<C, enable_if_t<(
    has_bounded_rows<C>::value && has_bounded_cols<C>::value
  )>> : true_type { };

/** @struct have_same_elements */
template <class C, class D>
struct have_same_elements : is_same<_traits_elem_t<C>, _traits_elem_t<D>> { };

/** @struct have_same_rows */
template <class C, class D, typename V = void>
struct have_same_rows : false_type { };

template <class C, class D>
struct have_same_rows<C, D, enable_if_t<(
    (_traits<C>::Rows == _traits<D>::Rows) && (_traits<C>::MaxRows == _traits<D>::MaxRows)
  )>> : true_type { };

/** @struct have_same_cols */
template <class C, class D, typename = void>
struct have_same_cols : false_type { };

template <class C, class D>
struct have_same_cols<C, D, enable_if_t<(
    (_traits<C>::Cols == _traits<D>::Cols) && (_traits<C>::MaxCols == _traits<D>::MaxCols)
  )>> : true_type { };

/** @struct have_same_dimensions */
template <class C, class D, typename = void>
struct have_same_dimensions : false_type { };

template <class C, class D>
struct have_same_dimensions<C, D, enable_if_t<(
    have_same_rows<C, D>::value && have_same_cols<C, D>::value
  )>> : true_type { };

/** @struct have_same_traits */
template <class C, class D, typename = void>
struct have_same_traits : false_type { };

template <class C, class D>
struct have_same_traits<C, D, enable_if_t<(
    have_same_elements<C, D>::value && have_same_dimensions<C, D>::value
  )>> : true_type { };

/** @struct has_valid_traits */
template <class C, typename = void>
struct has_valid_traits : false_type { };

template <class C>
struct has_valid_traits<C, enable_if_t<(
    has_bounded_dimensions<C>::value
  )>> : true_type { };

/** @struct is_tall */
template <class C, typename = void>
struct is_tall : false_type { };

template <class C>
struct is_tall<C, enable_if_t<(
    _traits<C>::MaxRows >= _traits<C>::MaxCols
  )>> : true_type { };

/** @struct is_short */
template <class C, typename = void>
struct is_short : false_type { };

template <class C>
struct is_short<C, enable_if_t<(
    _traits<C>::MaxRows <= _traits<C>::MaxCols
  )>> : true_type { };

/** @struct is_square */
template <class C, typename = void>
struct is_square : false_type { };

template <class C>
struct is_square<C, enable_if_t<(
    is_tall<C>::value && is_short<C>::value
  )>> : true_type { };

/** @struct traits */
template <class C>
struct traits {
  typedef _traits_elem_t<C> Elem;
  typedef _evaluates_to_t<C> Eval;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t Size = Rows * Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
  constexpr static size_t MaxSize = MaxRows * MaxCols;
};

/** @typedef traits_elem_t */
template <class C>
using traits_elem_t = typename traits<C>::Elem;

/** @typedef traits_eval_t */
template <class C>
using traits_eval_t = typename traits<C>::Eval;

}  // namespace internal
}  // namespace lin

#endif
