/** @file lin/core/tensor/inl/dimensions.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/dimensions.hpp for more information. */

#include "../dimensions.hpp"

namespace lin {
namespace internal {

template <size_t N>
class Dimension<N, N> {
 public:
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimension() = default;
  constexpr Dimension(Dimension<N, N> const &) = default;
  constexpr Dimension(Dimension<N, N> &&) = default;
  constexpr Dimension<N, N> &operator=(Dimension<N, N> const &) = default;
  constexpr Dimension<N, N> &operator=(Dimension<N, N> &&) = default;
  /* Simple, single dimensions resize and getter functions. */
  constexpr size_t get() const { return N; }
  constexpr void resize(size_t n) {
    LIN_ASSERT(n == N /* Invalid argument passed to Dimension<...>::resize */);
  }
};

template <size_t MN>
class Dimension<0, MN> {
 private:
  size_t n = MN;
 public:
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Dimension() = default;
  constexpr Dimension(Dimension<0, MN> const &) = default;
  constexpr Dimension(Dimension<0, MN> &&) = default;
  constexpr Dimension<0, MN> &operator=(Dimension<0, MN> const &) = default;
  constexpr Dimension<0, MN> &operator=(Dimension<0, MN> &&) = default;
  /* Simple, single dimensions resize and getter functions. */
  constexpr size_t get() const { return n; }
  constexpr void resize(size_t n) {
    LIN_ASSERT(n <= MN /* Invalid argument passed to Dimension<...>::resize */);
    this->n = n;
  }
};

template <class D>
constexpr size_t Dimensions<D>::rows() const {
  return this->row_dimension.get();
}

template <class D>
constexpr size_t Dimensions<D>::cols() const {
  return this->col_dimension.get();
}

template <class D>
constexpr void Dimensions<D>::resize(size_t r, size_t c) {
  this->row_dimension.resize(r);
  this->col_dimension.resize(c);
}
}  // namespace internal
}  // namespace lin
