// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/const_tensor_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_CONST_TENSOR_VIEW_HPP_
#define LIN_VIEWS_CONST_TENSOR_VIEW_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Member pointer backed constant tensor.
 * 
 *  @tparam D Derived type.
 * 
 *  This allows users to interpret arbitrary buffers as tensor objects. The user
 *  specified buffer is assumed to be at least as large as the tensor's maximum
 *  size and elements are read and written to the buffer in row major order.
 *
 *  @sa internal::ConstBase
 *  @sa internal::ConstMatrixView
 *  @sa internal::ConstRowVectorView
 *  @sa internal::ConstVectorView
 * 
 *  @ingroup VIEWS
 */
template <class D>
class ConstTensorView : public ConstBase<D> {
  static_assert(has_valid_traits<D>::value,
      "Derived types to ConstTensor<...> must have valid traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 private:
  typename Traits::elem_t const *const elems;

 protected:
  using ConstBase<D>::derived;

 public:
  using ConstBase<D>::rows;
  using ConstBase<D>::cols;
  using ConstBase<D>::resize;
  using ConstBase<D>::size;
  using ConstBase<D>::operator();
  using ConstBase<D>::eval;

  constexpr ConstTensorView() = delete;
  constexpr ConstTensorView(ConstTensorView<D> const &) = default;
  constexpr ConstTensorView(ConstTensorView<D> &&) = default;
  constexpr ConstTensorView<D> &operator=(ConstTensorView<D> const &) = default;
  constexpr ConstTensorView<D> &operator=(ConstTensorView<D> &&) = default;

  /** @brief Constructs a new constant tensor tensor view with the provided
   *         backing array.
   * 
   *  @param elems Constant element backing array.
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
  constexpr ConstTensorView(typename Traits::elem_t const *elems)
  : elems(elems) {
    resize(Traits::max_rows, Traits::max_cols);
  }

  /** @brief Constructs a new constant tensor tensor view with the provided
   *         backing array and requested dimensions.
   *
   *  @param elems Constant element backing array.
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
  constexpr ConstTensorView(typename Traits::elem_t const *elems, size_t r, size_t c)
  : elems(elems) {
    resize(r, c);
  }

  /** @brief Retrives a constant pointer to the element backing array.
   * 
   *  @returns Constant pointer to the backing array.
   * 
   *  This is the same buffer the tensor view was constructed with.
   */
  constexpr typename Traits::elem_t const *data() const {
    return elems;
  }
};
}  // namespace internal
}  // namespace lin

#endif
