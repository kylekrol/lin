// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_VIEW_HPP_
#define LIN_VIEWS_VIEW_HPP_

#include "const_matrix_view.hpp"
#include "const_vector_view.hpp"
#include "matrix_view.hpp"
#include "vector_view.hpp"

#include "../core.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @brief Provides a specific tensor type's corresponding view type.
 *
 *  @tparam C %Tensor type.
 *
 *  @sa internal::const_view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = void>
struct view { };

template <class C>
using view_t = typename view<C>::type;

template <class C>
struct view<C, std::enable_if_t<is_matrix<C>::value>> {
  typedef MatrixView<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols> type;
};

template <class C>
struct view<C, std::enable_if_t<is_col_vector<C>::value>> {
  typedef VectorView<typename C::VectorTraits::elem_t, C::VectorTraits::length, C::VectorTraits::max_length> type;
};

template <class C>
struct view<C, std::enable_if_t<is_row_vector<C>::value>> {
  typedef RowVectorView<typename C::VectorTraits::elem_t, C::VectorTraits::length, C::VectorTraits::max_length> type;
};

/** @brief Provides a specific tensor type's corresponding constant view type.
 *
 *  @tparam C %Tensor type.
 *
 *  @sa internal::view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = void>
struct const_view { };

template <class C>
using const_view_t = typename const_view<C>::type;

template <class C>
struct const_view<C, std::enable_if_t<is_matrix<C>::value>> {
  typedef ConstMatrixView<typename C::Traits::elem_t, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols> type;
};

template <class C>
struct const_view<C, std::enable_if_t<is_col_vector<C>::value>> {
  typedef ConstVectorView<typename C::VectorTraits::elem_t, C::VectorTraits::length, C::VectorTraits::max_length> type;
};

template <class C>
struct const_view<C, std::enable_if_t<is_row_vector<C>::value>> {
  typedef ConstRowVectorView<typename C::VectorTraits::elem_t, C::VectorTraits::length, C::VectorTraits::max_length> type;
};
}  // namespace internal

/** @brief Creates a tensor view with default dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *
 *  @param elems Element backing array.
 *
 *  @return internal::MatrixView, internal::RowVectorView, or
 *          internal::VectorView.
 *
 *  If the view's traits support variable dimensions, the view is constructed
 *  with the largest allowable dimensions (i.e. default dimensions).
 *
 *  @sa internal::traits
 *  @sa internal::view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto view(typename C::Traits::elem_t *elems) {
  return internal::view_t<C>(elems);
}

/** @brief Creates a vector view with the provided length.
 *
 *  @tparam C %Vector type whose traits are replicated.
 *
 *  @param elems Element backing array.
 *
 *  @return internal::RowVectorView or internal::VectorView.
 *
 *  Lin assertion errors will be triggered if the requested length isn't
 *  possible given the vector view's traits.
 *
 *  @sa internal::traits
 *  @sa internal::view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = std::enable_if_t<internal::conjunction<
    internal::has_traits<C>, internal::is_vector<C>>::value>>
constexpr auto view(typename C::Traits::elem_t *elems, size_t n) {
  return internal::view_t<C>(elems, n);
}

/** @brief Creates a tensor view with the provided dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *
 *  @param elems Element backing array.
 *  @param r     Initial row dimension.
 *  @param c     Initial column dimension.
 *
 *  @return internal::MatrixView, internal::RowVectorView, or
 *          internal::VectorView.
 *
 *  Lin assertions errors will be triggered if the requested dimensions aren't
 *  possible given the view's traits.
 *
 *  @sa internal::traits
 *  @sa internal::view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto view(typename C::Traits::elem_t *elems, size_t r, size_t c) {
  return internal::view_t<C>(elems, r, c);
}

/** @brief Creates a constant tensor view with default dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *
 *  @param elems Constant element backing array.
 *
 *  @return internal::ConstMatrixView, internal::ConstRowVectorView, or
 *          internal::ConstVectorView.
 *
 *  If the view's traits support variable dimensions, the view is constructed
 *  with the largest allowable dimensions (i.e. default dimensions).
 *
 *  @sa internal::traits
 *  @sa internal::const_view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto view(typename C::Traits::elem_t const *elems) {
  return internal::const_view_t<C>(elems);
}

/** @brief Creates a constant vector view with the provided length.
 *
 *  @tparam C %Vector type whose traits are replicated.
 *
 *  @param elems Constant element backing array.
 *
 *  @return internal::ConstRowVectorView or internal::ConstVectorView.
 *
 *  Lin assertion errors will be triggered if the requested length isn't
 *  possible given the vector view's traits.
 *
 *  @sa internal::traits
 *  @sa internal::const_view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = std::enable_if_t<internal::conjunction<
    internal::has_traits<C>, internal::is_vector<C>>::value>>
constexpr auto view(typename C::Traits::elem_t const *elems, size_t n) {
  return internal::const_view_t<C>(elems, n);
}

/** @brief Creates a constant tensor view with the provided dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *
 *  @param elems Constant element backing array.
 *  @param r     Initial row dimension.
 *  @param c     Initial column dimension.
 *
 *  @return internal::ConstMatrixView, internal::ConstRowVectorView, or
 *          internal::ConstVectorView.
 *
 *  Lin assertions errors will be triggered if the requested dimensions aren't
 *  possible given the view's traits.
 *
 *  @sa internal::traits
 *  @sa internal::const_view
 *
 *  @ingroup VIEWS
 */
template <class C, typename = std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto view(typename C::Traits::elem_t const *elems, size_t r, size_t c) {
  return internal::const_view_t<C>(elems, r, c);
}
}  // namespace lin

#endif
