/** @file lin/core/traits/vector.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for the core vector module. */

// TODO : Documentation for this entire file
// TODO : Add _vector_traits type

#ifndef LIN_CORE_TRAITS_VECTOR_HPP_
#define LIN_CORE_TRAITS_VECTOR_HPP_

#include "tensor.hpp"
#include "utilities.hpp"

namespace lin {
namespace internal {

/** @struct is_row_vector */
template <class C, typename = void>
struct is_row_vector : false_type { };

template <class C>
struct is_row_vector<C, enable_if_t<(
    has_fixed_rows<C>::value && (_traits<C>::Rows == 1) && (_traits<C>::MaxCols > 1)
  )>> : true_type { };

/** @struct is_col_vector */
template <class C, typename = void>
struct is_col_vector : false_type { };

template <class C>
struct is_col_vector<C, enable_if_t<(
    has_fixed_cols<C>::value && (_traits<C>::Cols == 1) && (_traits<C>::MaxRows > 1)
  )>> : true_type { };

/** @struct is_vector */
template <class C, typename = void>
struct is_vector : false_type { };

template <class C>
struct is_vector<C, enable_if_t<(
    is_col_vector<C>::value || is_row_vector<C>::value
  )>> : true_type { };

/** @struct _vector_traits */
template <class C, typename = void>
struct _vector_traits { };

template <class C>
struct _vector_traits<C, enable_if_t<is_row_vector<C>::value>> {
  typedef _traits_elem_t<C> Elem;
  constexpr static size_t Length = _traits<C>::Cols;
  constexpr static size_t MaxLength = _traits<C>::MaxCols;
};

template <class C>
struct _vector_traits<C, enable_if_t<is_col_vector<C>::value>> {
  typedef _traits_elem_t<C> Elem;
  constexpr static size_t Length = _traits<C>::Rows;
  constexpr static size_t MaxLength = _traits<C>::MaxRows;
};

/** @typedef _vector_traits_elem_t */
template <class C>
using _vector_traits_elem_t = typename _vector_traits<C>::Elem;

template <class C, class D, typename = void>
struct have_same_vector_dimensions_impl : false_type { };

template <class C, class D>
struct have_same_vector_dimensions_impl<C, D, enable_if_t<(
    (_vector_traits<C>::Length == _vector_traits<D>::Length) &&
    (_vector_traits<C>::MaxLength == _vector_traits<D>::MaxLength)
  )>> : true_type { };

/** @struct have_same_vector_dimensions */
template <class C, class D, typename = void>
struct have_same_vector_dimensions : false_type { };

template <class C, class D>
struct have_same_vector_dimensions<C, D, enable_if_t<(
    is_vector<C>::value && is_vector<D>::value
  )>> : have_same_vector_dimensions_impl<C, D> { };

/** @struct have_same_vector_traits */
template <class C, class D, typename = void>
struct have_same_vector_traits : false_type { };

template <class C, class D>
struct have_same_vector_traits<C, D, enable_if_t<(
    have_same_elements<C, D>::value && have_same_vector_dimensions<C, D>::value
  )>> : true_type { };

/** @struct vector_traits */
template <class C, typename = void>
struct vector_traits { };

template <class C>
struct vector_traits<C, enable_if_t<is_row_vector<C>::value || is_col_vector<C>::value>> {
  typedef _vector_traits_elem_t<C> Elem;
  typedef _evaluates_to_t<C> Eval;
  constexpr static size_t Length = _vector_traits<C>::Length;
  constexpr static size_t MaxLength = _vector_traits<C>::MaxLength;
};

/** @typedef vector_traits_elem_t */
template <class C>
using vector_traits_elem_t = typename _vector_traits<C>::Elem;

/** @typedef vector_traits_eval_t */
template <class C>
using vector_traits_eval_t = typename _vector_traits<C>::Eval;

}  // namespace internal
}  // namespace lin

#endif
