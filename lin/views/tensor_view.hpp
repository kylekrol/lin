// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/tensor_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_TENSOR_VIEW_HPP_
#define LIN_VIEWS_TENSOR_VIEW_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Member pointer backed tensor.
 * 
 *  @tparam D Derived type.
 * 
 *  This allows users to interpret arbitrary buffers as tensor objects. The user
 *  specified buffer is assumed to be at least as large as the tensor's maximum
 *  size and elements are read and written to the buffer in row major order.
 *
 *  @sa internal::Base
 *  @sa internal::MatrixView
 *  @sa internal::RowVectorView
 *  @sa internal::VectorView
 * 
 *  @ingroup VIEWS
 */
template <class D>
class TensorView : public Base<D> {
  static_assert(has_valid_traits<D>::value,
      "Derived types to Tensor<...> must have valid traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 private:
  typename Traits::elem_t *const elems;

 protected:
  using Base<D>::derived;

 public:
  using Base<D>::rows;
  using Base<D>::cols;
  using Base<D>::resize;
  using Base<D>::size;
  using Base<D>::operator=;
  using Base<D>::operator();
  using Base<D>::data;
  using Base<D>::eval;

  constexpr TensorView() = delete;
  constexpr TensorView(TensorView<D> const &) = default;
  constexpr TensorView(TensorView<D> &&) = default;
  constexpr TensorView<D> &operator=(TensorView<D> const &) = default;
  constexpr TensorView<D> &operator=(TensorView<D> &&) = default;

  /** @brief Constructs a new tensor tensor view with the provided backing
   *         array.
   * 
   *  @param elems Element backing array.
   * 
   *  The element backing array is a assumed to be in row major order. Elements
   *  of the tensor initially hold whatever values were left in the backing
   *  array.
   * 
   *  The backing array should be at least as large as the maximum size of the
   *  tensor (see internal::traits information).
   * 
   *  The size of the tensor defaults to the maximum allowed size.
   */
  constexpr TensorView(typename Traits::elem_t *elems)
  : elems(elems) {
    resize(Traits::max_rows, Traits::max_cols);
  }

  /** @brief Constructs a new tensor tensor view with the provided backing
   *         array and requested dimensions.
   *
   *  @param elems Element backing array.
   *  @param r     Initial row dimension.
   *  @param c     Initial column dimension.
   *
   *  The element backing array is a assumed to be in row major order. Elements
   *  of the tensor initially hold whatever values were left in the backing
   *  array.
   * 
   *  The backing array should be at least as large as the maximum size of the
   *  tensor (see internal::traits information).
   *
   *  Lin assertions errors will be triggered if the requested dimensions aren't
   *  possible given the tensor's traits.
   *
   *  @sa internal::traits
   */
  constexpr TensorView(typename Traits::elem_t *elems, size_t r, size_t c)
  : elems(elems) {
    resize(r, c);
  }

  /** @brief Retrives a pointer to the element backing array.
   * 
   *  @returns Pointer to the backing array.
   * 
   *  This is the same buffer the tensor view was constructed with.
   */
  constexpr typename Traits::elem_t *data() {
    return elems;
  }
};
}  // namespace internal
}  // namespace lin

#endif
