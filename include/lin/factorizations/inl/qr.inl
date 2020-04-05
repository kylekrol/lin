/** @file lin/factorizations/inl/qr.inl
 *  @author Kyle Krol
 *  See %lin/factorizations/qr.hpp for more information. */

#include "../qr.hpp"

namespace lin {

template <class C, class D, class E, std::enable_if_t<internal::can_qr<C, D, E>::value, size_t>>
constexpr int qr(internal::Stream<C> const &M, internal::Base<D> &Q, internal::Base<E> &R) {
  LIN_ASSERT(M.rows() >= M.cols() /* M isn't 'tall' in qr(...) */);
  LIN_ASSERT(M.rows() == Q.rows() /* Q rows doesn't match in qr(...) */);
  LIN_ASSERT(M.cols() == Q.cols() /* Q cols doesn't match in qr(...) */);
  LIN_ASSERT(M.cols() == R.rows() /* R rows doesn't match in qr(...) */);
  LIN_ASSERT(M.cols() == R.cols() /* R cols doesn't match in qr(...) */);

  // Initialize R and Q
  R = zeros<E>(R.rows(), R.cols());
  Q = M;

  for (size_t j = 0; j < M.cols(); j++) {
    auto qj = ref_col(Q, j);

    // Normalize this column
    R(j, j) = norm(qj);
    qj = qj / R(j, j);

    // Remove parallel components from subsequent columns
    for (size_t k = j + 1; k < M.cols(); k++) {
      auto qk = ref_col(Q, k);
      R(j, k) = dot(qj, qk);
      qk = qk - qj * R(j, k);
    }
  }

  return 0;  // TODO : Return an actual status code
}

template <class C, class D, class E, std::enable_if_t<internal::can_qr<C, D, E>::value, size_t>>
constexpr int qr(internal::Stream<C> const &M, internal::Tensor<D> &Q, internal::Tensor<E> &R) {
  Q.resize(M.rows(), M.cols());
  R.resize(M.cols(), M.cols());
  return qr(M, static_cast<internal::Base<D> &>(Q), static_cast<internal::Base<E> &>(R));
}
}  // namespace lin
