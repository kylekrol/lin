// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../qr.hpp"

namespace lin
{

template <class _M, class _Q, class _R,
    typename std::enable_if<internal::can_qr<_M, _Q, _R>::value, size_t>::type>
constexpr int qr(internal::Stream<_M> const &M, internal::Base<_Q> &Q, internal::Base<_R> &R)
{
  typedef internal::traits<_M> TM;

  assert(M.rows() >= M.cols() /* M isn't 'tall' in qr(...) */);
  assert(M.rows() == Q.rows() /* Q rows doesn't match in qr(...) */);
  assert(M.cols() == Q.cols() /* Q cols doesn't match in qr(...) */);
  assert(M.cols() == R.rows() /* R rows doesn't match in qr(...) */);
  assert(M.cols() == R.cols() /* R cols doesn't match in qr(...) */);

  // Initialize R and Q
  R = zeroes<_R>(R.rows(), R.cols());
  Q = M;

  for (int j = 0; j < M.cols(); j++) {
    auto Qj = reference<TM::rows, 1, TM::max_rows, 1>(Q, 0, j, Q.rows(), 1);

    // Normalize this column
    R(j, j) = norm(Qj);
    Qj = Qj / R(j, j);

    // Remove parallel components from subsequent columns
    for (int k = j + 1; k < M.cols(); k++) {
      auto Qk = reference<TM::rows, 1, TM::max_rows, 1>(Q, 0, k, Q.rows(), 1);
      R(j, k) = dot(Qj, Qk);
      Qk = Qk - Qj * R(j, k);
    }
  }

  return 0;  // TODO : Return an actual status code
}

template <class _M, class _Q, class _R,
    typename std::enable_if<internal::can_qr<_M, _Q, _R>::value, size_t>::type>
constexpr int qr(internal::Stream<_M> const &M, internal::Tensor<_Q> &Q, internal::Tensor<_R> &R)
{
  // Resize while Q and R and stil Tensor types
  Q.resize(M.rows(), M.cols());
  R.resize(M.cols(), M.cols());
  // Calculate the qr factorization
  return qr(M, static_cast<internal::Base<_Q> &>(Q), static_cast<internal::Base<_R> &>(R));
}
}  // namespace lin
