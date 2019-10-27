// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../backward_sub.hpp"

namespace lin
{

template <class _U, class _X, class _Y,
    typename std::enable_if<internal::can_backward_sub<_U, _X, _Y>::value, size_t>::type>
constexpr int backward_sub(internal::Base<_U> const &U, internal::Base<_X> &X,
    internal::Base<_Y> const &Y)
{
  typedef internal::traits<_U> TU;
  typedef internal::traits<_Y> TY;

  assert(U.rows() == U.cols() /* U isn't square in backward_sub(...) */);
  assert(U.cols() == Y.rows() /* Y rows don't match in backward_sub(...) */);
  assert(Y.rows() == X.rows() /* X rows don't match in backward_sub(...) */);
  assert(Y.cols() == X.cols() /* X cols don't match in backward_sub(...) */);

  // Solve for the last rows
  // It's trivially the last row of Y divided by the bottom right element of U
  const size_t m = U.rows() - 1;
  ref_row(X, m) = ref_row(Y, m) / U(m, m);

  // Below for loop caused issues with size_t being unsigned
  // Solve for the other rows in descending order
  for (size_t n = m - 1; n >= 0; n--)
    ref_row(X, n) = (
            ref_row(Y, n) - (ref<1, 0, 1, TU::max_rows>(U, n, n + 1, 1, m - n) * 
                ref<0, TY::cols, TY::max_rows, TY::max_cols>(X, n + 1, 0, m - n, X.cols()))
        ) / U(n, n);

  return 0;  // TODO : Return an actual error code
}

template <class _U, class _X, class _Y,
    typename std::enable_if<internal::can_backward_sub<_U, _X, _Y>::value, size_t>::type>
constexpr int backward_sub(internal::Base<_U> const &U, internal::Tensor<_X> &X,
    internal::Base<_Y> const &Y)
{
  X.resize(Y.rows(), Y.cols());
  return backward_sub(U, static_cast<internal::Base<_X> &>(X), Y);
}
}  // namespace lin
