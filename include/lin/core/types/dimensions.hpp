/** @file lin/core/types/dimensions.hpp
 *  @author Kyle Krol
 *  Defines the dimensions type to allow simple resizing and dimensions
 *  tracking. */

#ifndef LIN_CORE_TYPES_DIMENSIONS_HPP_
#define LIN_CORE_TYPES_DIMENSIONS_HPP_

#include "../config.hpp"
#include "../traits.hpp"

namespace lin {
namespace internal {

/** @class Dimensions
 *  Keeps track of the size of a tensor object. */
template <class D, typename = void>
class Dimensions;

/* Fixed row and fixed column count. */
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
  constexpr size_t rows() const { return D::Traits::Rows; }
  constexpr size_t cols() const { return D::Traits::Cols; }
  constexpr void resize(size_t r, size_t c) {
    LIN_ASSERT(r == D::Traits::Rows /* Invalid argument passed to Dimensions<...>::resize */);
    LIN_ASSERT(c == D::Traits::Cols /* Invalid argument passed to Dimensions<...>::resize */);
  }
};

/* Variable row and fixed column count. */
template <class D>
class Dimensions<D, std::enable_if_t<conjunction<
    negation<has_fixed_cols<D>>, has_bounded_cols<D>, has_fixed_rows<D>>::value>> {
 private:
  size_t _cols;

 public:
  typedef Dimensions<D, std::enable_if_t<conjunction<
      negation<has_fixed_cols<D>>, has_bounded_cols<D>, has_fixed_rows<D>>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() : _cols(D::Traits::MaxCols) { }
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  constexpr size_t rows() const { return D::Traits::Rows; }
  constexpr size_t cols() const { return _cols; }
  constexpr void resize(size_t r, size_t c) {
    LIN_ASSERT(r == D::Traits::Rows /* Invalid argument passed to Dimensions<...>::resize */);
    LIN_ASSERT(c > 0 && c <= D::Traits::MaxCols /* Invalid argument passed to Dimensions<...>::resize */);
    _cols = c;
  }
};

/* Variable row and fixed column count. */
template <class D>
class Dimensions<D, std::enable_if_t<conjunction<
    has_fixed_cols<D>, negation<has_fixed_rows<D>>, has_bounded_rows<D>>::value>> {
 private:
  size_t _rows;

 public:
  typedef Dimensions<D, std::enable_if_t<conjunction<
      has_fixed_cols<D>, negation<has_fixed_rows<D>>, has_bounded_rows<D>>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() : _rows(D::Traits::MaxRows) { }
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  constexpr size_t rows() const { return _rows; }
  constexpr size_t cols() const { return D::Traits::Cols; }
  constexpr void resize(size_t r, size_t c) {
    LIN_ASSERT(r > 0 && r <= D::Traits::MaxRows /* Invalid argument passed to Dimensions<...>::resize */);
    LIN_ASSERT(c == D::Traits::Cols /* Invalid argument passed to Dimensions<...>::resize */);
    _rows = r;
  }
};

/* Variable rows and variable column count. */
template <class D>
class Dimensions<D, std::enable_if_t<conjunction<
    negation<has_fixed_cols<D>>, has_bounded_cols<D>, negation<has_fixed_rows<D>>, has_bounded_rows<D>>::value>> {
 private:
  size_t _rows, _cols;

 public:
  typedef Dimensions<D, std::enable_if_t<conjunction<
      negation<has_fixed_cols<D>>, has_bounded_cols<D>, negation<has_fixed_rows<D>>, has_bounded_rows<D>>::value>> This;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() : _rows(D::Traits::MaxRows), _cols(D::Traits::MaxCols) { }
  constexpr Dimensions(This const &) = default;
  constexpr Dimensions(This &&) = default;
  constexpr This &operator=(This const &) = default;
  constexpr This &operator=(This &&) = default;
  /* Getters and setters for tensor size. */
  constexpr size_t rows() const { return _rows; }
  constexpr size_t cols() const { return _cols; }
  constexpr void resize(size_t r, size_t c) {
    LIN_ASSERT(r > 0 && r <= D::Traits::MaxRows /* Invalid argument passed to Dimensions<...>::resize */);
    LIN_ASSERT(c > 0 && c <= D::Traits::MaxCols /* Invalid argument passed to Dimensions<...>::resize */);
    _rows = r;
    _cols = c;
  }
};
}  // namespace internal
}  // namespace lin

#endif
