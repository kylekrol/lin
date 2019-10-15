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

  // TODO : Create reference_row and reference_col functions to make this more
  //        readable

  // Solve for the last rows
  // It's trivially the last row of Y divided by the bottom right element of U
  const int m = U.rows() - 1;
  reference<1, TY::cols, 1, TY::max_cols>(X, m, 0, 1, X.cols()) =
      reference<1, TY::cols, 1, TY::max_cols>(Y, m, 0, 1, Y.cols()) / U(m, m);

  // Solve for the other rows in descending order
  for (int n = m - 1; n >= 0; n--)
    reference<1, TY::cols, 1, TY::max_cols>(X, n, 0, 1, X.cols()) = (
          reference<1, TY::cols, 1, TY::max_cols>(Y, n, 0, 1, Y.cols()) - (
              reference<1, 0, 1, TU::max_rows>(U, n, n + 1, 1, m - n) * 
                reference<0, TY::cols, TY::max_rows, TY::max_cols>(X, n + 1, 0, m - n, X.cols())
            )
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
