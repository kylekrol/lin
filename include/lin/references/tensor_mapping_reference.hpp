// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/references/tensor_mapping_reference.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_REFERENCES_TENSOR_MAPPING_REFERENCE_HPP_
#define LIN_REFERENCES_TENSOR_MAPPING_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Generic tensor reference with read and write access.
 *
 *  @tparam D Derived type.
 *  @tparam E Underlying referenced type.
 *
 *  This allows users to interpret a portion of a larger internal::Mapping as an
 *  independent tensor type with user specified traits. A common use may be to
 *  treat block diagonal elements of a larger matrix independently or perform
 *  vector operations on the columns of a matrix.
 *
 *  It's important to note, if the underlying mapping goes out of scope the
 *  reference is invalidated.
 *
 *  @sa internal::Mapping
 *  @sa internal::MatrixMappingReference
 *  @sa internal::VectorMappingReference
 *  @sa internal::RowVectorMappingReference
 *
 *  @ingroup REFERENCES
 */
template <class D, class E>
class TensorMappingReference : public Mapping<D>, public Dimensions<D> {
 public:
  /** @brief Traits information for this type.
   *
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 private:
  Mapping<E> &_mapping;
  size_t const _i;
  size_t const _j;

 protected:
  using Mapping<D>::derived;

  using Dimensions<D>::resize;

 public:
  using Mapping<D>::size;
  using Mapping<D>::operator=;
  using Mapping<D>::operator();
  using Mapping<D>::eval;

  using Dimensions<D>::rows;
  using Dimensions<D>::cols;

  constexpr TensorMappingReference() = delete;
  constexpr TensorMappingReference(TensorMappingReference<D, E> const &) = default;
  constexpr TensorMappingReference(TensorMappingReference<D, E> &&) = default;
  constexpr TensorMappingReference<D, E> &operator=(TensorMappingReference<D, E> const &) = default;
  constexpr TensorMappingReference<D, E> &operator=(TensorMappingReference<D, E> &&) = default;

  /** @brief Constructs a new reference with the provided mapping and anchor
   *         point.
   *
   *  @param mapping Underlying mapping.
   *  @param i       Anchor point row index.
   *  @param j       Anchor point column index.
   *
   *  The reference's dimensions are defaulted to the largest allowable size and
   *  the anchor point maps the tops left corner of the reference to an element
   *  in the underlying mapping.
   *
   *  The reference traits must define a type that fits within the provided
   *  mapping given the anchor point. If this is not the case, lin assertion
   *  errors will be triggered.
   *
   *  The anchor points specifies where the top left corner of the reference
   *  maps to in the underlying mapping.
   *
   *  @sa internal::traits
   */
  constexpr TensorMappingReference(Mapping<E> &mapping, size_t i, size_t j)
  : _mapping(mapping), _i(i), _j(j) {
    LIN_ASSERT((i >= 0) && (i + Traits::max_rows <= mapping.rows()));
    LIN_ASSERT((j >= 0) && (j + Traits::max_cols <= mapping.cols()));

    resize(Traits::max_rows, Traits::max_cols);
  }

  /** @brief Constructs a new reference with the provided mapping, anchor point,
   *         and dimensions.
   *
   *  @param mapping Underlying mapping.
   *  @param i       Anchor point row index.
   *  @param j       Anchor point column index.
   *  @param r       Reference row dimension.
   *  @param c       Reference column dimension.
   *
   *  The anchor point maps the tops left corner of the reference to an element
   *  in the underlying mapping.
   *
   *  The reference traits must define a type that fits within the provided
   *  mapping given the anchor point. If this is not the case, lin assertion
   *  errors will be triggered.
   *
   *  The anchor points specifies where the top left corner of the reference
   *  maps to in the underlying mapping.
   *
   *  Lin assertions errors will be triggered if the requested dimensions aren't
   *  possible given the reference's traits.
   *
   *  @sa internal::traits
   */
  constexpr TensorMappingReference(Mapping<E> &mapping, size_t i, size_t j, size_t r, size_t c)
  : _mapping(mapping), _i(i), _j(j) {
    LIN_ASSERT((i >= 0) && (i + r <= mapping.rows()));
    LIN_ASSERT((j >= 0) && (j + c <= mapping.cols()));

    resize(r, c);
  }

  /** @brief Provides read and write access to tensor elements.
   *
   *  @param i Row index.
   *  @param j Column index.
   *
   *  @return Reference to the tensor element.
   *
   *  If the indices are out of bounds as defined by the reference's current
   *  dimensions, lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t &operator()(size_t i, size_t j) {
    LIN_ASSERT((i >= 0) && (i < rows()));
    LIN_ASSERT((j >= 0) && (j < cols()));

    return _mapping(_i + i, _j + j);
  }

  /** @brief Provides read and write access to tensor elements.
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
   */
  constexpr typename Traits::elem_t &operator()(size_t i) {
    LIN_ASSERT((i >= 0) && (i < size()));

    return operator()(i / cols(), i % cols());
  }
};
}  // namespace internal
}  // namespace lin

#endif
