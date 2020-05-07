/** @file lin/references/inl/mapping_reference.inl
 *  @author Kyle Krol
 *  See %lin/references/mapping_reference.hpp for more information. */

#include "../mapping_reference.hpp"

namespace lin {
namespace internal {

template <size_t R, size_t C, size_t MR, size_t MC, class D>
class MappingReference : public Mapping<MappingReference<R, C, MR, MC, D>>,
    public Dimensions<MappingReference<R, C, MR, MC, D>> {
  template <size_t S, size_t E, size_t MS, size_t ME, class F>
  friend constexpr MappingReference<S, E, MS, ME, F> lin::ref(lin::internal::Mapping<F> &,
      lin::size_t, lin::size_t, lin::size_t , lin::size_t);

 public:
  /* Import elements from Mapping<MappingReference<R, C, MR, MC, D>>. */
  using Mapping<MappingReference<R, C, MR, MC, D>>::size;
  using Mapping<MappingReference<R, C, MR, MC, D>>::eval;
  using Mapping<MappingReference<R, C, MR, MC, D>>::operator=;
  using Mapping<MappingReference<R, C, MR, MC, D>>::operator();
  /* Import elements from Dimensions<MappingReference<R, C, MR, MC, D>>. */
  using Dimensions<MappingReference<R, C, MR, MC, D>>::rows;
  using Dimensions<MappingReference<R, C, MR, MC, D>>::cols;
  /* Include traits information. */
  typedef traits<MappingReference<R, C, MR, MC, D>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr MappingReference() = default;
  constexpr MappingReference(MappingReference<R, C, MR, MC, D> const &) = default;
  constexpr MappingReference(MappingReference<R, C, MR, MC, D> &&) = default;
  constexpr MappingReference<R, C, MR, MC, D> &operator=(MappingReference<R, C, MR, MC, D> const &) = default;
  constexpr MappingReference<R, C, MR, MC, D> &operator=(MappingReference<R, C, MR, MC, D> &&) = default;
  /* Element access/evaluation functions. */
  constexpr typename Traits::elem_t &operator()(size_t i, size_t j);
  constexpr typename Traits::elem_t &operator()(size_t i);

 protected:
  /* Import elements from Mapping<MappingReference<R, C, MR, MC, D>>. */
  using Mapping<MappingReference<R, C, MR, MC, D>>::derived;

 private:
  Mapping<D> &d;
  size_t const i, j;
  /* Import elements from Dimensions<MappingReference<R, C, MR, MC, D>>. */
  using Dimensions<MappingReference<R, C, MR, MC, D>>::resize;
  /* MappingReference constructor(s). */
  constexpr MappingReference(Mapping<D> &d, size_t i, size_t j, size_t r, size_t c);
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
struct _elem<MappingReference<R, C, MR, MC, D>> {
  typedef _elem_t<D> type;
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
struct _dims<MappingReference<R, C, MR, MC, D>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr traits_elem_t<MappingReference<R, C, MR, MC, D>> &
MappingReference<R, C, MR, MC, D>::operator()(size_t i, size_t j) {
  LIN_ASSERT(i < rows() /* Invalid argument passed to MappingReference<...>::operator() */);
  LIN_ASSERT(j < cols() /* Invalid argument passed to MappingReference<...>::operator() */);
  return d(i + this->i, j + this->j);
}

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr traits_elem_t<MappingReference<R, C, MR, MC, D>> &
MappingReference<R, C, MR, MC, D>::operator()(size_t i) {
  return operator()(i / cols(), i % cols());
}

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr MappingReference<R, C, MR, MC, D>::MappingReference(Mapping<D> &d, size_t i, size_t j, size_t r, size_t c)
: d(d), i(i), j(j) {
  LIN_ASSERT(i + r <= d.rows() /* Invalid argument passed to MappingReference<...>::MappingReference */);
  LIN_ASSERT(j + c <= d.cols() /* Invalid argument passed to MappingReference<...>::MappingReference */);
  resize(r, c);
}
}  // namespace internal

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr internal::MappingReference<R, C, MR, MC, D> ref(internal::Mapping<D> &d,
    size_t i, size_t j, size_t r, size_t c) {
  return internal::MappingReference<R, C, MR, MC, D>(d, i, j, r, c);
}

template <size_t R, size_t C, class D>
constexpr internal::MappingReference<R, C, R, C, D> ref(internal::Mapping<D> &d,
    size_t i, size_t j) {
  return ref<R, C, R, C, D>(d, i, j);
}

template <class D>
constexpr auto ref_row(internal::Mapping<D> &d, size_t i) {
  return ref<1, D::Traits::cols, 1, D::Traits::max_cols>(d, i, 0, 1, d.cols());
}

template <class D>
constexpr auto ref_col(internal::Mapping<D> &d, size_t j) {
  return ref<D::Traits::rows, 1, D::Traits::max_rows, 1>(d, 0, j, d.rows(), 1);
}
}  // namespace lin
