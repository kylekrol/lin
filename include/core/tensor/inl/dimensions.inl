// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../dimensions.hpp"

namespace lin
{
namespace internal
{

template <size_t N>
class Dimension<N, N>
{
 public:
  constexpr Dimension() = default;
  constexpr size_t get() const { return N; }
  constexpr void resize(size_t n) {
    assert(n == N /* Invalid resize in Dimension<_N, _N>::resize */);
  }
};

template <size_t MN>
class Dimension<0, MN>
{
 private:
  size_t n = MN;
 public:
  constexpr Dimension() = default;
  constexpr size_t get() const { return n; }
  constexpr void resize(size_t n) {
    assert(n <= MN /* Invalid resize in Dimension<0, MN>::resize */);
    this->n = n;
  }
};

template <class D>
constexpr size_t Dimensions<D>::rows() const
{
  return row_dimension.get();
}

template <class D>
constexpr size_t Dimensions<D>::cols() const
{
  return col_dimension.get();
}

template <class D>
constexpr void Dimensions<D>::resize(size_t r, size_t c)
{
  row_dimension.resize(r);
  col_dimension.resize(c);
}
}  // namespace internal
}  // namespace lin
