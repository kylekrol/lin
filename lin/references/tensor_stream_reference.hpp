// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/tensor_stream_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_TENSOR_STREAM_REFERENCE_HPP_
#define LIN_REFERENCES_TENSOR_STREAM_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Generic tensor reference with read only access.
 *
 *  @tparam D Derived type.
 *  @tparam E Underlying referenced type.
 *
 *  This allows users to interpret a portion of a larger internal::Stream as an
 *  independent tensor type with user specified traits. A common use may be to
 *  treat block diagonal elements of a larger matrix independently or perform
 *  vector operations on the columns of a matrix.
 *
 *  It's important to note, if the underlying stream goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::Stream
 *  @sa internal::MatrixStreamReference
 *  @sa internal::VectorStreamReference
 *  @sa internal::RowVectorStreamReference
 *
 *  @ingroup REFERENCES
 */
template <class D, class E>
class TensorStreamReference : public Stream<D>, public Dimensions<D> {
 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 private:
  Stream<E> const &_stream;
  size_t const _i;
  size_t const _j;

 protected:
  using Stream<D>::derived;

  using Dimensions<D>::resize;

 public:
  using Stream<D>::size;
  using Stream<D>::eval;

  using Dimensions<D>::rows;
  using Dimensions<D>::cols;

  constexpr TensorStreamReference() = delete;
  constexpr TensorStreamReference(TensorStreamReference<D, E> const &) = default;
  constexpr TensorStreamReference(TensorStreamReference<D, E> &&) = default;
  constexpr TensorStreamReference<D, E> &operator=(TensorStreamReference<D, E> const &) = default;
  constexpr TensorStreamReference<D, E> &operator=(TensorStreamReference<D, E> &&) = default;

  /** @brief Constructs a new reference with the provided stream and anchor
   *         point.
   *
   *  @param stream Underlying stream.
   *  @param i      Anchor point row index.
   *  @param j      Anchor point column index.
   *
   *  The reference's dimensions are defaulted to the largest allowable size and
   *  the anchor point maps the top left corner of the reference to an element
   *  in the underlying stream.
   *
   *  The reference traits must define a type that fits within the provided
   *  mapping given the anchor point. If this is not the case, lin assertion
   *  errors will be triggered.
   *
   *  The anchor points specifies where the top left corner of the reference
   *  maps to in the underlying stream.
   *
   *  @sa internal::traits
   */
  constexpr TensorStreamReference(Stream<E> const &stream, size_t i, size_t j)
  : _stream(stream), _i(i), _j(j) {
    LIN_ASSERT((i >= 0) && (i + Traits::max_rows <= stream.rows()));
    LIN_ASSERT((j >= 0) && (j + Traits::max_cols <= stream.cols()));

    resize(Traits::max_rows, Traits::max_cols);
  }

  /** @brief Constructs a new reference with the provided mapping, anchor point,
   *         and dimensions.
   *
   *  @param mapping Underlying stream.
   *  @param i       Anchor point row index.
   *  @param j       Anchor point column index.
   *  @param r       Reference row dimension.
   *  @param c       Reference column dimension.
   *
   *  The anchor point maps the top left corner of the reference to an element
   *  in the underlying stream.
   *
   *  The reference traits must define a type that fits within the provided
   *  mapping given the anchor point. If this is not the case, lin assertion
   *  errors will be triggered.
   *
   *  The anchor points specifies where the top left corner of the reference
   *  maps to in the underlying stream.
   *
   *  Lin assertions errors will be triggered if the requested dimensions aren't
   *  possible given the reference's traits.
   *
   *  @sa internal::traits
   */
  constexpr TensorStreamReference(Stream<E> const &stream, size_t i, size_t j, size_t r, size_t c)
  : _stream(stream), _i(i), _j(j) {
    LIN_ASSERT((i >= 0) && (i + r <= stream.rows()));
    LIN_ASSERT((j >= 0) && (j + c <= stream.cols()));

    resize(r, c);
  }

  /** @brief Provides read only access to tensor elements.
   *
   *  @param i Row index.
   *  @param j Column index.
   *
   *  @return Value of the tensor element.
   *
   *  If the indices are out of bounds as defined by the reference's current
   *  dimensions, lin assertion errors will be triggered.
   *
   *  If accessing data from a lazily evaluation tensor operation, you may want
   *  to consider for the creation of a value backed type to reduce overhead.
   *
   *  @sa internal::Stream::eval
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT((i >= 0) && (i < rows()));
    LIN_ASSERT((j >= 0) && (j < cols()));

    return _stream(_i + i, _j + j);
  }

  /** @brief Provides read only access to tensor elements.
   *
   *  @param i Index.
   *
   *  @return Reference to the tensor element.
   *
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   *
   *  If the index is out of bounds as defined by the tensor's current size, lin
   *  assertion errors will be triggered.
   *
   *  If accessing data from a lazily evaluation tensor operation, you may want
   *  to consider for the creation of a value backed type to reduce overhead.
   *
   *  @sa internal::Stream::eval
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    LIN_ASSERT((i >= 0) && (i < size()));

    return operator()(i / cols(), i % cols());
  }
};
}  // namespace internal
}  // namespace lin

#endif
