// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/stream.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_STREAM_HPP_
#define LIN_CORE_TYPES_STREAM_HPP_

#ifdef LIN_DESKTOP
  #include <iostream>
#endif

#include "../config.hpp"
#include "../traits.hpp"

namespace lin {
namespace internal {

/** @brief %Tensor interface providing read only access to elements.
 * 
 *  @tparam D Derived type.
 * 
 *  This is the first of the three main entry points on the lin inheritance tree
 *  and is therefore the parent class for all other tensor types.
 *  
 *  All that is provided at this level is read only access to tensor elements and
 *  dimension information. It also adds the ability to force the evaluation of any
 *  tensor stream to a value backed object.
 * 
 *  This class, and the entire inheritance tree, employs the curiosly recurring
 *  template patter (CRTP). As such, derived types are required to implement most
 *  of the methods listed in this class.
 *
 *  It's main purpose is to provide an interface the supports lazy evaluation.
 *
 *  @sa internal::Mapping
 *  @sa internal::Base
 *
 *  @ingroup CORETYPES
 */
template <class D>
class Stream {
  static_assert(has_valid_traits<D>::value,
      "Derived types to Stream<...> must have valid traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 protected:
  /** @return Reference to the derived object.
   */
  inline constexpr D &derived() {
    return static_cast<D &>(*this);
  }

  /** @return Constant reference to the derived object.
   */
  inline constexpr D const &derived() const {
    return static_cast<D const &>(*this);
  }

 public:
  constexpr Stream() = default;
  constexpr Stream(Stream<D> const &) = default;
  constexpr Stream(Stream<D> &&) = default;
  constexpr Stream<D> &operator=(Stream<D> const &) = default;
  constexpr Stream<D> &operator=(Stream<D> &&) = default;

  /** @return Number of rows in the tensor.
   */
  inline constexpr size_t rows() const {
    return derived().rows();
  }

  /** @return Number of columns in the tensor.
   */
  inline constexpr size_t cols() const {
    return derived().cols();
  }

  /** @return Number of elements in the tensor.
   * 
   *  This is always the number of rows times the number of columns in the tensor.
   */
  inline constexpr size_t size() const {
    return rows() * cols();
  }

  /** @brief Provides read only access to tensor elements.
   * 
   *  @param i Row index.
   *  @param j Column index.
   * 
   *  @return Value of the tensor element.
   * 
   *  If accessing data from a lazily evaluation tensor operation, you may want to
   *  consider for the creation of a value backed type to reduce overhead.
   * 
   *  @sa internal::Stream::eval
   */
  inline constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    return derived()(i, j);
  }

  /** @brief Provides read only access to tensor elements.
   * 
   *  @param i Index.
   * 
   *  @return Value of the tensor elements.
   * 
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   * 
   *  If accessing data from a lazily evaluation tensor operation, you may want to
   *  consider for the creation of a value backed type to reduce overhead.
   * 
   *  @sa internal::Stream::eval
   */
  inline constexpr typename Traits::elem_t operator()(size_t i) const {
    return derived()(i);
  }

  /** @brief Forces evaluation of this stream to a value backed type.
   * 
   *  @returns Resulting value.
   *
   *  This is especially useful when working with a proxy to a lazily evaluated
   *  expression.
   * 
   *  The return type is dependant on the evaluation type stored in its traits.
   *  
   *  @sa internal::traits
   */
  inline constexpr typename Traits::eval_t eval() const {
    return typename Traits::eval_t(derived());
  }
};

#ifdef LIN_DESKTOP
template <class C>
std::ostream &operator<<(std::ostream &os, Stream<C> const &s) {
  for (size_t i = 0; i < s.rows() - 1; i++) {
    for (size_t j = 0; j < s.cols() - 1; j++)
      os << s(i, j) << " ";
    os << s(i, s.cols() - 1) << "\n";
  }
  for (size_t j = 0; j < s.cols() - 1; j++)
    os << s(s.rows() - 1, j) << " ";
  os << s(s.rows() - 1, s.cols() - 1) << "\n";
  return os;
}
#endif

}  // namespace internal
}  // namespace lin

#endif
