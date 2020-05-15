// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/tensor.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_TENSOR_HPP_
#define LIN_CORE_TYPES_TENSOR_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "base.hpp"

#include <initializer_list>

namespace lin {
namespace internal {

/** @brief Member array backed tensor.
 * 
 *  @tparam D Derived type.
 * 
 *  This is the most commonly used implementation of the internal::Base interface.
 *  %Tensor elements are stored contiguously in a member backing array in row
 *  major order.
 * 
 *  This type is directly derived by the user facing Matrix, RowVector, and Vector
 *  types.
 * 
 *  @sa internal::Base
 *  @sa Matrix
 *  @sa RowVector
 *  @sa Vector
 * 
 *  @ingroup CORETYPES
 */
template <class D>
class Tensor : public Base<D> {
  static_assert(has_valid_traits<D>::value,
      "Derived types to Tensor<...> must have valid traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 private:
  typename Traits::elem_t elems[Traits::max_size] = { typename Traits::elem_t(0) };

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

  constexpr Tensor(Tensor<D> const &) = default;
  constexpr Tensor(Tensor<D> &&) = default;
  constexpr Tensor<D> &operator=(Tensor<D> const &) = default;
  constexpr Tensor<D> &operator=(Tensor<D> &&) = default;

  /** @brief Constructs a new tensor with zeros initialized elements and the
   *         largest allowable dimensions.
   *  
   *  @sa internal::traits
   */
  constexpr Tensor() {
    resize(Traits::max_rows, Traits::max_cols);
  }

  /** @brief Constructs a tensor with zeros initialized elements and the
   *         requested dimensions.
   *
   *  @param r Initial row dimension.
   *  @param c Initial column dimesnion.
   *
   *  @sa internal::traits
   */
  constexpr Tensor(size_t r, size_t c) {
    resize(r, c);
  }

  /** @brief Constructs a tensor with elements initialized from an initializer
   *         list.
   * 
   *  @tparam T   Element type of the initializer list.
   *  @param list Initializer list.
   * 
   *  The tensor dimensions defaults to the largest allowable dimensions and the
   *  initializer list must be assignable to a tensor of this type.
   * 
   *  @sa internal::traits
   *  @sa internal::Mapping::operator=(std::initializer_list<T> const &)
   *  @sa internal::Tensor::Tensor(size_t, size_t, std::initializer_list<T> const &)
   */
  template <typename T>
  constexpr Tensor(std::initializer_list<T> const &list) {
    derived() = list;
  }

  /** @brief Constructs a tensor with elements initialized from an initializer
   *         list and the requested dimensions.
   * 
   *  @tparam T    Element type of the initializer list.
   *  @param  r    Initial row dimension.
   *  @param  c    Initial column dimensions.
   *  @param  list Initializer list.
   * 
   *  The initializer list must be assignable to a tensor of this type.
   * 
   *  @sa internal::traits
   *  @sa internal::Mapping::operator=(std::initializer_list<T> const &)
   *  @sa internal::Tensor::Tensor(std::initializer_list<T> const &)
   */
  template <typename T>
  constexpr Tensor(size_t r, size_t c, std::initializer_list<T> const &list) {
    resize(r, c);
    derived() = list;
  }

  /** @brief Constructs a tensor by copying in dimensions and elements from
   *         another tensor stream.
   * 
   *  @tparam C Other derived type.
   *  @param  s Other tensor stream.
   * 
   *  The tensor will automatically attempt to resize to the dimensions of the
   *  other tensor stream.
   * 
   *  The stream must be assignable to a tensor of this type.
   * 
   *  @sa internal::Mapping::operator=(Stream<C> const &)
   */
  template <class C>
  constexpr Tensor(Stream<C> const &s) {
    resize(s.rows(), s.cols());
    derived() = s;
  }

  /** @brief Retrives a pointer to the element backing array.
   * 
   *  @returns Pointer to the backing array.
   * 
   *  The elements of the tensor are layed out in row major order in the backing
   *  array. They are stored continguously in memory.
   */
  constexpr typename Traits::elem_t *data() {
    return elems;
  }
};
}  // namespace internal
}  // namespace lin

#endif
