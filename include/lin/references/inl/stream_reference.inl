/** @file lin/references/inl/stream_reference.inl
 *  @author Kyle Krol
 *  See %lin/references/stream_reference.hpp for more information. */

#include "../stream_reference.hpp"

namespace lin {
namespace internal {

template <size_t R, size_t C, size_t MR, size_t MC, class D>
class StreamReference : public Stream<StreamReference<R, C, MR, MC, D>>,
    public Dimensions<StreamReference<R, C, MR, MC, D>> {
  template <size_t S, size_t E, size_t MS, size_t ME, class F>
  friend constexpr StreamReference<S, E, MS, ME, F> lin::ref(lin::internal::Stream<F> const &,
      lin::size_t, lin::size_t, lin::size_t , lin::size_t);

 public:
  /* Import elements from Stream<StreamReference<R, C, MR, MC, D>>. */
  using Stream<StreamReference<R, C, MR, MC, D>>::size;
  using Stream<StreamReference<R, C, MR, MC, D>>::eval;
  /* Import elements from Dimensions<StreamReference<R, C, MR, MC, D>>. */
  using Dimensions<StreamReference<R, C, MR, MC, D>>::rows;
  using Dimensions<StreamReference<R, C, MR, MC, D>>::cols;
  /* Include traits information. */
  typedef traits<StreamReference<R, C, MR, MC, D>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamReference() = default;
  constexpr StreamReference(StreamReference<R, C, MR, MC, D> const &) = default;
  constexpr StreamReference(StreamReference<R, C, MR, MC, D> &&) = default;
  constexpr StreamReference<R, C, MR, MC, D> &operator=(StreamReference<R, C, MR, MC, D> const &) = default;
  constexpr StreamReference<R, C, MR, MC, D> &operator=(StreamReference<R, C, MR, MC, D> &&) = default;
  /* Element access/evaluation functions. */
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamReference<R, C, MR, MC, D>>. */
  using Stream<StreamReference<R, C, MR, MC, D>>::derived;

 private:
  Stream<D> const &d;
  size_t const i, j;
  /* Import elements from Dimensions<StreamReference<R, C, MR, MC, D>>. */
  using Dimensions<StreamReference<R, C, MR, MC, D>>::resize;
  /* StreamReference constructor(s). */
  constexpr StreamReference(Stream<D> const &d, size_t i, size_t j, size_t r, size_t c);
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
struct _traits<StreamReference<R, C, MR, MC, D>> {
  typedef _traits_elem_t<D> Elem;
  constexpr static size_t Rows = R;
  constexpr static size_t Cols = C;
  constexpr static size_t MaxRows = MR;
  constexpr static size_t MaxCols = MC;
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr traits_elem_t<StreamReference<R, C, MR, MC, D>>
StreamReference<R, C, MR, MC, D>::operator()(size_t i, size_t j) const {
  LIN_ASSERT(i < rows() /* Invalid argument passed to StreamReference<...>::operator() */);
  LIN_ASSERT(j < cols() /* Invalid argument passed to StreamReference<...>::operator() */);
  return d(i + this->i, j + this->j);
}

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr traits_elem_t<StreamReference<R, C, MR, MC, D>>
StreamReference<R, C, MR, MC, D>::operator()(size_t i) const {
  return operator()(i / cols(), i % cols());
}

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr StreamReference<R, C, MR, MC, D>::StreamReference(Stream<D> const &d, size_t i, size_t j, size_t r, size_t c)
: d(d), i(i), j(j) {
  LIN_ASSERT(i + r <= d.rows() /* Invalid argument passed to StreamReference<...>::StreamReference */);
  LIN_ASSERT(j + c <= d.cols() /* Invalid argument passed to StreamReference<...>::StreamReference */);
  resize(r, c);
}
}  // namespace internal

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr internal::StreamReference<R, C, MR, MC, D> ref(internal::Stream<D> const &d,
    size_t i, size_t j, size_t r, size_t c) {
  return internal::StreamReference<R, C, MR, MC, D>(d, i, j, r, c);
}

template <size_t R, size_t C, class D>
constexpr internal::StreamReference<R, C, R, C, D> ref(internal::Stream<D> const &d,
    size_t i, size_t j) {
  return ref<R, C, R, C, D>(d, i, j);
}

template <class D>
constexpr auto ref_row(internal::Stream<D> const &d, size_t i) {
  return ref<1, D::Traits::Cols, 1, D::Traits::MaxCols>(d, i, 0, 1, d.cols());
}

template <class D>
constexpr auto ref_col(internal::Stream<D> const &d, size_t j) {
  return ref<D::Traits::Rows, 1, D::Traits::MaxRows, 1>(d, 0, j, d.rows(), 1);
}
}  // namespace lin
