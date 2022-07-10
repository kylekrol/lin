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

/** @file lin/references.hpp
 *  @author Kyle Krol
 */

/** @defgroup REFERENCES References
 *
 *  @brief Allows interpretting portions of larger tensor as other tensor types.
 *
 *  This can be extremely helpful if, for example, you'd like to normalize all
 *  the columns of a matrix without copying elements in and out of the matrix
 *  itself. We'll use this an example demonstrating how to use the refernces
 *  module.
 *
 *  First, be sure to include the appropriate headers (that being the
 *  `%lin/core.hpp` and `%lin/references.hpp` headers). From there, we can
 *  implement the following function which will normalize the columns in a three
 *  by three matrix:
 *
 *  ~~~{.cpp}
 *  #include <lin/core.hpp>
 *  #include <lin/references.hpp>
 *
 *  template <typename T>
 *  void normalize(lin::Matrix<T, 3, 3> &M) {
 *    for (lin::size_t j = 0; j < M.cols(); j++) {
 *      auto m = lin::ref<lin::Vector<T, 3>>(M, 0, j);
 *      m = m / lin::norm(m);
 *    }
 *  }
 *  ~~~
 *
 *  where line of interest here is clearly the call to
 *  `%lin::ref<%lin::Vector<T, 3>>` which essentially asks for a reference to be
 *  created that acts like a `%lin::Vector<T, 3>` and whose first element
 *  matches up with `M(0, j)`.
 *
 *  There are a couple things to note here:
 *
 *   - The reference itself is invalid when the backing object (in this case
 *     `M`) goes out of scope.
 *   - This particular reference serves as a read and write interface. However,
 *     read only references can also be generated in the same fashion if the
 *     underlying type is `const` or read only.
 *
 *  Lastly, there are also convenience functions `lin::col`, `lin::row`, and
 *  `lin::diag` to more easily reference the entire column, row, or diagonal of
 *  a tensor. In fact, if you don't mind using the `lin::internal` namespace a
 *  little, a simple function normalizing the columns of any matrix can be
 *  implemented as shown below:
 *
 *  ~~~{.cpp}
 *  #include <lin/core.hpp>
 *  #include <lin/references.hpp>
 *
 *  #include <type_traits>
 *
 *  template <class D, typename = std::enable_if_t<lin::internal::disjunction<
 *      lin::internal::is_matrix<D>, lin::internal::is_col_vector<D>>::value>>
 *  void normalize(lin::internal::Mapping<D> &M) {
 *    for (lin::size_t j = 0; j < M.cols(); j++) {
 *      auto m = lin::col(M, j);
 *      m = m / lin::norm(m);
 *    }
 *  }
 *  ~~~
 */

#ifndef LIN_REFERENCES_HPP_
#define LIN_REFERENCES_HPP_

#include "core.hpp"
#include "references/diagonal_mapping_reference.hpp"
#include "references/diagonal_stream_reference.hpp"
#include "references/matrix_mapping_reference.hpp"
#include "references/matrix_stream_reference.hpp"
#include "references/vector_mapping_reference.hpp"
#include "references/vector_stream_reference.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @internal
 *
 *  @brief Provides a specific tensor type's corresponding mapping reference
 *         type.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @sa internal::stream_reference
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename = void>
struct mapping_reference;

template <class C, class D>
using mapping_reference_t = typename mapping_reference<C, D>::type;

template <class C, class D>
struct mapping_reference<C, D, std::enable_if_t<conjunction<
    is_matrix<C>, have_same_elements<C, D>>::value>> {
  typedef MatrixMappingReference<D, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols> type;
};

template <class C, class D>
struct mapping_reference<C, D, std::enable_if_t<conjunction<
    is_col_vector<C>, have_same_elements<C, D>>::value>> {
  typedef VectorMappingReference<D, C::VectorTraits::length, C::VectorTraits::max_length> type;
};

template <class C, class D>
struct mapping_reference<C, D, std::enable_if_t<conjunction<
    is_row_vector<C>, have_same_elements<C, D>>::value>> {
  typedef RowVectorMappingReference<D, C::VectorTraits::length, C::VectorTraits::max_length> type;
};

/** @internal
 *
 *  @brief Provides a specific tensor type's corresponding stream reference
 *         type.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @sa internal::mapping_reference
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename = void>
struct stream_reference;

template <class C, class D>
using stream_reference_t = typename stream_reference<C, D>::type;

template <class C, class D>
struct stream_reference<C, D, std::enable_if_t<conjunction<
    is_matrix<C>, have_same_elements<C, D>>::value>> {
  typedef MatrixStreamReference<D, C::Traits::rows, C::Traits::cols, C::Traits::max_rows, C::Traits::max_cols> type;
};

template <class C, class D>
struct stream_reference<C, D, std::enable_if_t<conjunction<
    is_col_vector<C>, have_same_elements<C, D>>::value>> {
  typedef VectorStreamReference<D, C::VectorTraits::length, C::VectorTraits::max_length> type;
};

template <class C, class D>
struct stream_reference<C, D, std::enable_if_t<conjunction<
    is_row_vector<C>, have_same_elements<C, D>>::value>> {
  typedef RowVectorStreamReference<D, C::VectorTraits::length, C::VectorTraits::max_length> type;
};
}  // namespace internal

/** @brief Creates a mapping reference with default dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @param mapping Underlying mapping.
 *  @param i       Anchor point row index.
 *  @param j       Anchor point column index.
 *
 *  @return Instace of an internal::MatrixMappingReference,
 *          internal::RowVectorMappingReference, or
 *          internal::VectorMappingReference
 *
 *  This serves essentially as a wrapper around the reference constructors
 *  using default dimensions.
 *
 *  The anchor points specifies where the top left corner of the reference maps
 *  to in the underlying mapping.
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename =
    std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto ref(internal::Mapping<D> &mapping, size_t i, size_t j) {
  return internal::mapping_reference_t<C, D>(mapping, i, j);
}

/** @brief Creates a vector mapping reference with the provided length.
 *
 *  @tparam C %Vector type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @param mapping Underlying mapping.
 *  @param i       Anchor point row index.
 *  @param j       Anchor point column index.
 *  @param n       Provided length.
 *
 *  @return Instance of an internal::RowVectorMappingReference or
 *          internal::VectorMappingReference
 *
 *  This serves essentially as a wrapper around the vector reference
 *  constructors requesting a length.
 *
 *  The anchor points specifies where the top left corner of the reference maps
 *  to in the underlying mapping.
 *
 *  Lin assertions errors will be triggered if the requested dimensions aren't
 *  possible given the reference's traits.
 *
 *  @sa internal::traits
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename = std::enable_if_t<internal::conjunction<
    internal::has_traits<C>, internal::is_vector<C>>::value>>
constexpr auto ref(internal::Mapping<D> &mapping, size_t i, size_t j, size_t n) {
  return internal::mapping_reference_t<C, D>(mapping, i, j, n);
}

/** @brief Creates a mapping reference with the provided dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @param mapping Underlying mapping.
 *  @param i       Anchor point row index.
 *  @param j       Anchor point column index.
 *  @param r       Provided row dimension.
 *  @param c       Provided column dimension.
 *
 *  @return Instance of an internal::MatrixMappingReference,
 *          internal::RowVectorMappingReference, or
 *          internal::VectorMappingReference
 *
 *  This serves essentially as a wrapper around the reference constructors
 *  using default dimensions.
 *
 *  The anchor points specifies where the top left corner of the reference maps
 *  to in the underlying mapping.
 *
 *  Lin assertions errors will be triggered if the requested dimensions aren't
 *  possible given the reference's traits.
 *
 *  @sa internal::traits
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename =
    std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto ref(internal::Mapping<D> &mapping, size_t i, size_t j, size_t r, size_t c) {
  return internal::mapping_reference_t<C, D>(mapping, i, j, r, c);
}

/** @brief Creates a mapping reference of a particular column of a given tensor.
 *
 *  @tparam D Underlying referened type.
 *
 *  @param mapping Underlying mapping.
 *  @param j       Index of the referenced column.
 *
 *  @return Instance of an internal::VectorMappingReference or
 *          internal::MatrixMappingReference
 *
 *  This is a convenience function and the same result can be obtained with a
 *  call to another reference function.
 *
 *  The dimensions of a variably sized column are set depending on the provided
 *  mapping's row dimension at run time.
 *
 *  If calling this function on a mapping representing a row vector, a one by
 *  one matrix reference is returned.
 *
 *  @ingroup REFERENCES
 */
template <class D>
constexpr auto col(internal::Mapping<D> &mapping, size_t j) {
  typedef typename D::Traits::elem_t Elem;
  constexpr size_t Rows = D::Traits::rows;
  constexpr size_t MaxRows = D::Traits::max_rows;
  typedef std::conditional_t<internal::is_row_vector<D>::value, Matrix<Elem, 1, 1>, Vector<Elem, Rows, MaxRows>> T;

  return ref<T>(mapping, 0, j, mapping.rows(), 1);
}

/** @brief Creates a mapping reference of a particular row of a given tensor.
 *
 *  @tparam D Underlying referened type.
 *
 *  @param mapping Underlying mapping.
 *  @param j       Index of the referenced row.
 *
 *  @return Instance of an internal::RowVectorMappingReference or
 *          internal::MatrixMappingReference.
 *
 *  This is a convenience function and the same result can be obtained with a
 *  call to another reference function.
 *
 *  The dimensions of a variably sized row are set depending on the provided
 *  mapping's column dimension at run time.
 *
 *  If calling this function on a mapping representing a column vector, a one by
 *  one matrix reference is returned.
 *
 *  @ingroup REFERENCES
 */
template <class D>
constexpr auto row(internal::Mapping<D> &mapping, size_t i) {
  typedef typename D::Traits::elem_t Elem;
  constexpr size_t Cols = D::Traits::cols;
  constexpr size_t MaxCols = D::Traits::max_cols;
  typedef std::conditional_t<internal::is_col_vector<D>::value, Matrix<Elem, 1, 1>, RowVector<Elem, Cols, MaxCols>> T;

  return ref<T>(mapping, i, 0, 1, mapping.cols());
}

/** @brief Creates a diagonal mapping reference from the given mapping.
 *
 *  @tparam D Underlying referenced type.
 *
 *  @param mapping Underlying mapping.
 *
 *  @return Instance of an internal::DiagonalMappingReference.
 *
 *  The underlying mapping must have the traits of a square matrix and lin
 *  assertion errors will be thrown if the underlying mapping isn't square at
 *  runtime.
 *
 *  @sa internal::is_matrix
 *  @sa internal::is_square
 *  @sa internal::traits
 *
 *  @ingroup REFERENCES
 */
template <class D, typename = std::enable_if_t<internal::conjunction<
    internal::is_matrix<D>, internal::is_square<D>>::value>>
constexpr auto diag(internal::Mapping<D> &mapping) {
  return internal::DiagonalMappingReference<D>(mapping);
}

/** @brief Creates a mapping stream with default dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @param stream Underlying stream.
 *  @param i      Anchor point row index.
 *  @param j      Anchor point column index.
 *
 *  @return Instace of an internal::MatrixStreamReference,
 *          internal::RowVectorStreamReference, or
 *          internal::VectorStreamReference
 *
 *  This serves essentially as a wrapper around the reference constructors
 *  using default dimensions.
 *
 *  The anchor points specifies where the top left corner of the reference maps
 *  to in the underlying stream.
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename =
    std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto ref(internal::Stream<D> const &stream, size_t i, size_t j) {
  return internal::stream_reference_t<C, D>(stream, i, j);
}

/** @brief Creates a vector stream reference with the provided length.
 *
 *  @tparam C %Vector type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @param stream Underlying stream.
 *  @param i      Anchor point row index.
 *  @param j      Anchor point column index.
 *  @param n      Provided length.
 *
 *  @return Instance of an internal::RowVectorStreamReference or
 *          internal::VectorStreamReference
 *
 *  This serves essentially as a wrapper around the vector reference
 *  constructors requesting a length.
 *
 *  The anchor points specifies where the top left corner of the reference maps
 *  to in the underlying stream.
 *
 *  Lin assertions errors will be triggered if the requested dimensions aren't
 *  possible given the reference's traits.
 *
 *  @sa internal::traits
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename = std::enable_if_t<internal::conjunction<
    internal::has_traits<C>, internal::is_vector<C>>::value>>
constexpr auto ref(internal::Stream<D> const &stream, size_t i, size_t j, size_t n) {
  return internal::stream_reference_t<C, D>(stream, i, j, n);
}

/** @brief Creates a stream reference with the provided dimensions.
 *
 *  @tparam C %Tensor type whose traits are replicated.
 *  @tparam D Underlying referenced type.
 *
 *  @param stream Underlying stream.
 *  @param i      Anchor point row index.
 *  @param j      Anchor point column index.
 *  @param r      Provided row dimension.
 *  @param c      Provided column dimension.
 *
 *  @return Instance of an internal::MatrixStreamReference,
 *          internal::RowVectorStreamReference, or
 *          internal::VectorStreamReference
 *
 *  This serves essentially as a wrapper around the reference constructors
 *  using default dimensions.
 *
 *  The anchor points specifies where the top left corner of the reference maps
 *  to in the underlying mapping.
 *
 *  Lin assertions errors will be triggered if the requested dimensions aren't
 *  possible given the reference's traits.
 *
 *  @sa internal::traits
 *
 *  @ingroup REFERENCES
 */
template <class C, class D, typename =
    std::enable_if_t<internal::has_traits<C>::value>>
constexpr auto ref(internal::Stream<D> const &stream, size_t i, size_t j, size_t r, size_t c) {
  return internal::stream_reference_t<C, D>(stream, i, j, r, c);
}

/** @brief Creates a stream reference of a particular column of a given tensor.
 *
 *  @tparam D Underlying referened type.
 *
 *  @param stream Underlying stream.
 *  @param j      Index of the referenced column.
 *
 *  @return Instance of an internal::VectorStreamReference or
 *          internal::MatrixStreamReference.
 *
 *  This is a convenience function and the same result can be obtained with a
 *  call to another reference function.
 *
 *  The dimensions of a variably sized column are set depending on the provided
 *  mapping's row dimension at run time.
 *
 *  If calling this function on a stream representing a row vector, a one by one
 *  matrix reference is returned.
 *
 *  @ingroup REFERENCES
 */
template <class D>
constexpr auto col(internal::Stream<D> const &stream, size_t j) {
  typedef typename D::Traits::elem_t Elem;
  constexpr size_t Rows = D::Traits::rows;
  constexpr size_t MaxRows = D::Traits::max_rows;
  typedef std::conditional_t<internal::is_row_vector<D>::value, Matrix<Elem, 1, 1>, Vector<Elem, Rows, MaxRows>> T;

  return ref<T>(stream, 0, j, stream.rows(), 1);
}

/** @brief Creates a stream reference of a particular row of a given tensor.
 *
 *  @tparam D Underlying referened type.
 *
 *  @param stream Underlying stream.
 *  @param j      Index of the referenced row.
 *
 *  @return Instance of an internal::RowVectorStreamReference or
 *          internal::MatrixStreamReference.
 *
 *  This is a convenience function and the same result can be obtained with a
 *  call to another reference function.
 *
 *  The dimensions of a variably sized row are set depending on the provided
 *  mapping's column dimension at run time.
 *
 *  If calling this function on a stream representing a column vector, a one by
 *  one matrix reference is returned.
 *
 *  @ingroup REFERENCES
 */
template <class D>
constexpr auto row(internal::Stream<D> const &stream, size_t i) {
  typedef typename D::Traits::elem_t Elem;
  constexpr size_t Cols = D::Traits::cols;
  constexpr size_t MaxCols = D::Traits::max_cols;
  typedef std::conditional_t<internal::is_col_vector<D>::value, Matrix<Elem, 1, 1>, RowVector<Elem, Cols, MaxCols>> T;

  return ref<T>(stream, i, 0, 1, stream.cols());
}

/** @brief Creates a diagonal stream reference from the given stream.
 *
 *  @tparam D Underlying referenced type.
 *
 *  @param stream Underlying stream.
 *
 *  @return Instance of an internal::DiagonalMappingReference.
 *
 *  The underlying mapping must have the traits of a square matrix and lin
 *  assertion errors will be thrown if the underlying mapping isn't square at
 *  runtime.
 *
 *  @sa internal::is_matrix
 *  @sa internal::is_square
 *  @sa internal::traits
 *
 *  @ingroup REFERENCES
 */
template <class D, typename = std::enable_if_t<internal::conjunction<
    internal::is_matrix<D>, internal::is_square<D>>::value>>
constexpr auto diag(internal::Stream<D> const &stream) {
  return internal::DiagonalStreamReference<D>(stream);
}
}  // namespace lin

#endif
