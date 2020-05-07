// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/mapping.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_MAPPING_HPP_
#define LIN_CORE_TYPES_MAPPING_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "stream.hpp"

#include <initializer_list>
#include <type_traits>
#include <utility>

namespace lin {
namespace internal {

/** @brief %Tensor interface providing read and write access to elements.
 * 
 *  @tparam D Derived type.
 * 
 *  This is the second of the three main entry points on the lin inheritance tree
 *  after internal::Stream.
 * 
 *  Here, read and write element access is provided and the most frequently used
 *  assignment operators are defined.
 * 
 *  The main purpose is to provide an interface that supporst block references.
 *
 *  @sa internal::Stream
 *  @sa internal::Base
 *
 *  @ingroup CORETYPES
 */
template <class D>
class Mapping : public Stream<D> {
  static_assert(has_valid_traits<D>::value,
      "Derived types to Mapping<...> must have valid traits");

 private:
  template <typename T, typename U>
  using assign_expr = decltype(std::declval<T &>() = std::declval<U &>());

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<D> Traits;

 protected:
  using Stream<D>::derived;

 public:
  using Stream<D>::rows;
  using Stream<D>::cols;
  using Stream<D>::size;
  using Stream<D>::eval;

  constexpr Mapping() = default;
  constexpr Mapping(Mapping<D> const &) = default;
  constexpr Mapping(Mapping<D> &&) = default;
  constexpr Mapping<D> &operator=(Mapping<D> const &) = default;
  constexpr Mapping<D> &operator=(Mapping<D> &&) = default;

  /** @brief Provides read and write access to tensor elements.
   * 
   *  @param i Row index.
   *  @param j Column index.
   * 
   *  @return Reference to the tensor element.
   */
  inline constexpr typename Traits::elem_t &operator()(size_t i, size_t j) {
    return derived()(i, j);
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
    return const_cast<D &>(derived())(i, j);
  }

  /** @brief Provides read and write access to tensor elements.
   * 
   *  @param i Index
   * 
   *  @return Reference to the tensor element.
   * 
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   */
  inline constexpr typename Traits::elem_t &operator()(size_t i) {
    return derived()(i);
  }

  /** @brief Provides read only access to tensor elements.
   * 
   *  @param i Index.
   * 
   *  @return Value of the tensor elements.
   * 
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   */
  inline constexpr typename Traits::elem_t operator()(size_t i) const {
    return const_cast<D &>(derived())(i);
  }

  /** @brief Copy an initializer list's elements into the tensor's elements.
   * 
   *  @param list Initializer list.
   * 
   *  @return Reference to the derived object.
   * 
   *  The elements in the initializer need to be specified in row major order.
   * 
   *  If the length of the initializer list doesn't match the current size of the
   *  tensor, a lin assertion error will be triggered.
   */
  template <typename T, std::enable_if_t<
      is_detected<assign_expr, typename Traits::elem_t, T>::value, size_t> = 0>
  constexpr D &operator=(std::initializer_list<T> const &list) {
    LIN_ASSERT(size() == list.size());

    size_t i = 0;
    for (T const &l : list) (*this)(i++) = l;
    return derived();
  }

  /** @brief Copy another tensor's elements into this tenosr's elements.
   * 
   *  @param s Other tensor stream.
   * 
   *  @return Reference to the derived object.
   * 
   *  This function is only enable if both tensor have the same compile time
   *  dimensions and the other element's type can be assinged to this tensor's
   *  element type.
   * 
   *  If the dimensions of the tensor don't match at runtime, a lin assertion
   *  error will be triggered.
   * 
   *  @sa internal::have_same_dimensions
   */
  template <class C, std::enable_if_t<conjunction<
      have_same_dimensions<D, C>,
      is_detected<assign_expr, typename Traits::elem_t, traits_elem_t<C>>
    >::value, size_t> = 0>
  constexpr D &operator=(Stream<C> const &s) {
    LIN_ASSERT(rows() == s.rows());
    LIN_ASSERT(cols() == s.cols());

    for (size_t i = 0; i < size(); i++) (*this)(i) = s(i);
    return derived();
  }
};
}  // namespace internal
}  // namespace lin

#endif
