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

/** @file lin/views.hpp
 *  @author Kyle Krol
 */

/** @defgroup VIEWS Views
 * 
 *  @brief Allows arbitrary data buffers to be interpreted as value backed
 *         tensor types.
 * 
 *  ## Overview
 * 
 *  The views module serves one main purpose: to allows external buffers to be
 *  interpretted as tensor objects within lin.
 *
 *  This can be extremely helpful, say for example, if you'd like to treat an
 *  array from the STL as a three dimensional vector and perform some operations
 *  in a function to mutate it. All that's required is to use the lin::view
 *  function to create a vector view and then leverage the rest of the lin
 *  library.
 * 
 *  See the following example which treats an array as a three dimensional
 *  vector and rotates it in place about the z-axis by an angle `alpha`:
 * 
 *  ~~~{.cpp}
 *  #include <lin/core.hpp>
 *  #include <lin/views.hpp>
 * 
 *  #include <array>
 *  #include <cmath>
 * 
 *  void rotate_z(std::array<float, 3> &array, float alpha) {
 *    auto v = lin::view<lin::Vector3f>(array.data());
 *    lin::Matrix3x3f R = {
 *      std::cos(alpha), -std::sin(alpha), 0.0f,
 *      std::sin(alpha),  std::cos(alpha), 0.0f,
 *      0.0f,             0.0f,            1.0f
 *    };
 *    v = (R * v).eval();
 *  }
 *  ~~~
 *
 *  It's important to note that there are actually two types of views that can
 *  be returned by lin::view. The first is a standard view which allows read and
 *  write access to the underlying elements (this is seen in the example above).
 *  The second is known as a constant view and only allows read access to the
 *  underlying elements. This is done automatically if the buffer passed to
 *  lin::view points to const elements.
 */

#ifndef LIN_VIEWS_HPP_
#define LIN_VIEWS_HPP_

#include "core.hpp"
#include "views/const_matrix_view.hpp"
#include "views/const_vector_view.hpp"
#include "views/matrix_view.hpp"
#include "views/vector_view.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @internal
 *
 *  @brief Provides a specific tensor type's corresponding view type.
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

/** @internal
 *
 *  @brief Provides a specific tensor type's corresponding constant view type.
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
 *  @param n     Initial length.
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
 *  @param n     Initial length.
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
