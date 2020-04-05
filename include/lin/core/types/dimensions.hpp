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

/** @class Dimension
 *  Keeps track of a single dimensions of a tensor object. */
template <size_t N, size_t MN>
class Dimension;

/** @class Dimensions
 *  Keeps track of both dimensions of a tensor object. */
template <class D>
class Dimensions {
 public:
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimensions() = default;
  constexpr Dimensions(Dimensions<D> const &) = default;
  constexpr Dimensions(Dimensions<D> &&) = default;
  constexpr Dimensions<D> &operator=(Dimensions<D> const &) = default;
  constexpr Dimensions<D> &operator=(Dimensions<D> &&) = default;
  /* Dimensions getters and resizing function. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr void resize(size_t r, size_t c);

 private:
  Dimension<traits<D>::Rows, traits<D>::MaxRows> row_dimension;
  Dimension<traits<D>::Cols, traits<D>::MaxCols> col_dimension;
};
}  // namespace internal
}  // namespace lin

#include "inl/dimensions.inl"

#endif
