// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../matrix.hpp"

namespace lin
{

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr Matrix<T, R, C, MR, MC>::Matrix(size_t r, size_t c)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(r, c) { }

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr Matrix<T, R, C, MR, MC>::Matrix(std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(l) { }

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr Matrix<T, R, C, MR, MC>::Matrix(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(r, c, l) { }

template <typename T, size_t R, size_t C, size_t MR, size_t MC> template <class _E>
constexpr Matrix<T, R, C, MR, MC>::Matrix(internal::Stream<_E> const &E)
: internal::Tensor<Matrix<T, R, C, MR, MC>>(E) { }

}  // namespace lin
