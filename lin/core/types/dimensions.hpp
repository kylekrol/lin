// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/dimensions.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_DIMENSIONS_HPP_
#define LIN_CORE_TYPES_DIMENSIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"

#include <type_traits>

namespace lin {
namespace internal {

/** @brief Tracks the runtime dimensions of a tensor object.
 * 
 *  @tparam D Derived type.
 * 
 *  This functionality is broken out as a separate object so we only include
 *  member variables for tensor dimensions that aren't of a fixed size. There is
 *  a template specialization of this class for each of the following cases:
 *
 *   - Fixed rows and columns.
 *   - Fixed rows and strictly bounded columns.
 *   - Strictly bounded rows and fixed columns.
 *   - Strictly bounded rows and columns.
 * 
 *  The specialization for fixed rows and columns, for example, has no
 *  additional member variables while the the specialization for fixed rows and
 *  stricly bounded columns requires one additional member variables to track
 *  the number of columns at runtime.
 *
 *  @sa internal::Base
 *  @sa internal::has_fixed_rows
 *  @sa internal::has_fixed_cols
 *  @sa internal::has_strictly_bounded_rows
 *  @sa internal::has_strictly_bounded_cols
 *
 *  @ingroup CORETYPES
 */
template <class D, typename = void>
class Dimensions
#ifdef IN_DOXYGEN
{
 public:
  constexpr Dimensions() = default;
  constexpr Dimensions(Dimensions<D> const &) = default;
  constexpr Dimensions(Dimensions<D> &&) = default;
  constexpr Dimensions<D> &operator=(Dimensions<D> const &) = default;
  constexpr Dimensions<D> &operator=(Dimensions<D> &&) = default;
  /** @return Number of rows.
   */
  constexpr size_t rows() const { return 0; }

  /** @return Number of columns.
   */
  constexpr size_t cols() const { return 0; }

  /** @brief Resizes a tensor's dimensions.
   * 
   *  @param r Number of rows.
   *  @param c Number of columns.
   * 
   *  Lin assertions errors will be triggered if the requested dimensions aren't
   *  possible given the tensor's traits.
   *
   *  @sa internal::has_fixed_rows
   *  @sa internal::has_fixed_cols
   *  @sa internal::has_strictly_bounded_rows
   *  @sa internal::has_strictly_bounded_cols
   */
  constexpr void resize(size_t r, size_t c) { }
}
#endif
;

template <class D>
class Dimensions<D, std::enable_if_t<has_fixed_dimensions<D>::value>> {
 public:
  typedef Dimensions<D, std::enable_if_t<has_fixed_dimensions<D>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() = default;
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  inline constexpr size_t rows() const { return D::Traits::rows; }
  inline constexpr size_t cols() const { return D::Traits::cols; }
  constexpr void resize([[maybe_unused]] size_t r, [[maybe_unused]] size_t c) {
    LIN_ASSERT(r == D::Traits::rows);
    LIN_ASSERT(c == D::Traits::cols);
  }
};

template <class D>
class Dimensions<D, std::enable_if_t<
    conjunction<has_fixed_rows<D>, has_strictly_bounded_cols<D>>::value>> {
 private:
  size_t _cols;

 public:
  typedef Dimensions<D, std::enable_if_t<
    conjunction<has_fixed_rows<D>, has_strictly_bounded_cols<D>>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() : _cols(D::Traits::max_cols) { }
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  inline constexpr size_t rows() const { return D::Traits::rows; }
  inline constexpr size_t cols() const { return _cols; }
  constexpr void resize([[maybe_unused]] size_t r, size_t c) {
    LIN_ASSERT(r == D::Traits::rows);
    LIN_ASSERT(c > 0 && c <= D::Traits::max_cols);
    _cols = c;
  }
};

template <class D>
class Dimensions<D, std::enable_if_t<
    conjunction<has_strictly_bounded_rows<D>, has_fixed_cols<D>>::value>> {
 private:
  size_t _rows;

 public:
  typedef Dimensions<D, std::enable_if_t<
    conjunction<has_strictly_bounded_rows<D>, has_fixed_cols<D>>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() : _rows(D::Traits::max_rows) { }
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  inline constexpr size_t rows() const { return _rows; }
  inline constexpr size_t cols() const { return D::Traits::cols; }
  constexpr void resize(size_t r, [[maybe_unused]] size_t c) {
    LIN_ASSERT(r > 0 && r <= D::Traits::max_rows);
    LIN_ASSERT(c == D::Traits::cols);
    _rows = r;
  }
};

template <class D>
class Dimensions<D, std::enable_if_t<has_strictly_bounded_dimensions<D>::value>> {
 private:
  size_t _rows, _cols;

 public:
  typedef Dimensions<D, std::enable_if_t<has_strictly_bounded_dimensions<D>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() : _rows(D::Traits::max_rows), _cols(D::Traits::max_cols) { }
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  inline constexpr size_t rows() const { return _rows; }
  inline constexpr size_t cols() const { return _cols; }
  constexpr void resize(size_t r, size_t c) {
    LIN_ASSERT(r > 0 && r <= D::Traits::max_rows);
    LIN_ASSERT(c > 0 && c <= D::Traits::max_cols);
    _rows = r;
    _cols = c;
  }
};
}  // namespace internal
}  // namespace lin

#endif
