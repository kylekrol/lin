/** @file lin/core/traits/vector.hpp
 *  @author Kyle Krol
 *  Template metaprogramming constructs for the core vector module. */

// TODO : Documentation for this entire file

#ifndef LIN_CORE_TRAITS_VECTOR_HPP_
#define LIN_CORE_TRAITS_VECTOR_HPP_

#include "tensor.hpp"
#include "utilities.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @struct is_row_vector */
template <class C, typename = void>
struct is_row_vector;

/** @struct is_col_vector */
template <class C, typename = void>
struct is_col_vector;

/** @struct is_vector */
template <class C>
struct is_vector : disjunction<is_row_vector<C>, is_col_vector<C>> { };

/** @struct _vector_traits */
template <class C, typename = void>
struct _vector_traits;

/** @typedef _vector_traits_elem_t */
template <class C>
using _vector_traits_elem_t = typename _vector_traits<C>::Elem;

/** @struct vector_traits
 *  @{ */
template <class C, typename = void>
struct vector_traits { };

template <class C>
struct vector_traits<C, std::enable_if_t<is_vector<C>::value>> {
  typedef _vector_traits_elem_t<C> Elem;
  typedef _evaluates_to_t<C> Eval;
  constexpr static size_t
    Length = _vector_traits<C>::Length,
    MaxLength = _vector_traits<C>::MaxLength;
};
/** @} */

/** @typedef vector_traits_elem_t */
template <class C>
using vector_traits_elem_t = typename _vector_traits<C>::Elem;

/** @typedef vector_traits_eval_t */
template <class C>
using vector_traits_eval_t = typename _vector_traits<C>::Eval;

/** @struct has_vector_traits */
template <class C, typename = void>
struct has_vector_traits;

/** @struct have_same_vector_dimensions */
template <class... Cs>
struct have_same_vector_dimensions;

/** @struct have_same_vector_traits */
template <class... Cs>
struct have_same_vector_traits;

}  // namespace internal
}  // namespace lin

#include "inl/vector.inl"

#endif
