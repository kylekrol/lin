/** @file lin/core/types/inl/matrix.inl
 *  @author Kyle Krol
 *  See %lin/core/types/matrix.hpp for more information. */

#include "../matrix.hpp"

namespace lin {
namespace internal {

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _traits<Matrix<T, R, C, MR, MC>> {
  typedef T Elem;
  constexpr static size_t
    Rows = R,
    Cols = C,
    MaxRows = MR,
    MaxCols = MC;
};

template <class C>
struct _evaluates_to<C, std::enable_if_t<is_matrix<C>::value>> {
  typedef Matrix<
      _traits_elem_t<C>,
      _traits<C>::Rows,
      _traits<C>::Cols,
      _traits<C>::MaxRows,
      _traits<C>::MaxCols
    > Eval;
};
}  // namespace internal

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr Matrix<T, R, C, MR, MC>::Matrix(size_t r, size_t c)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(r, c) { }

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
template <typename U>
constexpr Matrix<T, R, C, MR, MC>::Matrix(std::initializer_list<U> const &list)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(list) { }

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
template <typename U>
constexpr Matrix<T, R, C, MR, MC>::Matrix(size_t r, size_t c, std::initializer_list<U> const &list)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(r, c, list) { }

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
template <typename D>
constexpr Matrix<T, R, C, MR, MC>::Matrix(internal::Stream<D> const &stream)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(stream) { }

}  // namespace lin
