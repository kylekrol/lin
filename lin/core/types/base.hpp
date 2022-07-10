// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/base.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_BASE_HPP_
#define LIN_CORE_TYPES_BASE_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "dimensions.hpp"
#include "mapping.hpp"

namespace lin {
namespace internal {

/** @brief Value backed tensor interface with resizing support.
 * 
 *  @tparam D Derived type.
 * 
 *  This is the third of the three main entry points on the lin inheritance tree
 *  after internal::Mapping.
 * 
 *  Here, direct tracking of runtime dimensions and the ability to resize is
 *  added. A getter to retrive a pointer to the element backing array is also
 *  included.
 * 
 *  The main purpose is to provide an interface that supports value backed types
 *  - i.e. those directly storing tensor elements in a member array or and a
 *  pointer.
 * 
 *  @sa internal::Stream
 *  @sa internal::Mapping
 *  @sa internal::Tensor
 * 
 *  @ingroup CORETYPES
 */
template <class D>
class Base : public Mapping<D>, public Dimensions<D> {
  static_assert(has_valid_traits<D>::value,
      "Derived types to Base<...> must have valid traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 protected:
  using Mapping<D>::derived;

 public:
  using Mapping<D>::size;
  using Mapping<D>::eval;
  using Mapping<D>::operator=;
  using Mapping<D>::operator();

  using Dimensions<D>::rows;
  using Dimensions<D>::cols;
  using Dimensions<D>::resize;

  constexpr Base() = default;
  constexpr Base(Base<D> const &) = default;
  constexpr Base(Base<D> &&) = default;
  constexpr Base<D> &operator=(Base<D> const &) = default;
  constexpr Base<D> &operator=(Base<D> &&) = default;

  /** @brief Retrives a pointer to the element backing array.
   * 
   *  @returns Pointer to the backing array.
   * 
   *  The elements of the tensor are layed out in row major order in the backing
   *  array. They are stored contiguously in memory.
   */
  inline constexpr typename Traits::elem_t *data() {
    return derived().data();
  }

  /** @brief Retrives a constant pointer to the element backing array.
   * 
   *  @returns Constant pointer to the backing array.
   * 
   *  The elements of the tensor are layed out in row major order in the backing
   *  array. They are stored contiguously in memory.
   */
  inline constexpr typename Traits::elem_t const *data() const {
    return const_cast<D &>(derived()).data();
  }

  /** @brief Provides read and write access to tensor elements.
   * 
   *  @param i Row index.
   *  @param j Column index.
   * 
   *  @return Reference to the tensor element.
   * 
   *  If the indices are out of bounds as defined by the tensor's current
   *  dimensions, lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t &operator()(size_t i, size_t j) {
    LIN_ASSERT(0 <= i && i < rows());
    LIN_ASSERT(0 <= j && j < cols());

    return data()[i * cols() + j];
  }

  /** @brief Provides read and write access to tensor elements.
   * 
   *  @param i Index
   * 
   *  @return Reference to the tensor element.
   * 
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   * 
   *  If the index is out of bounds as defined by the tensor's current size, lin
   *  lin assertion errors will be triggered.
   */
  constexpr typename Traits::elem_t &operator()(size_t i) {
    LIN_ASSERT(0 <= i && i < size());

    return data()[i];
  }
};
}  // namespace internal
}  // namespace lin

#endif
