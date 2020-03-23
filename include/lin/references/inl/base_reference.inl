/** @file lin/references/inl/base_reference.inl
 *  @author Kyle Krol
 *  See %lin/references/base_reference.hpp for more information. */

#include "../base_reference.hpp"

namespace lin {
namespace internal {

template <size_t R, size_t C, size_t MR, size_t MC, class D>
class BaseReference : public Base<BaseReference<R, C, MR, MC, D>>,
    public Dimensions<BaseReference<R, C, MR, MC, D>> {
  template <size_t S, size_t E, size_t MS, size_t ME, class F>
  friend constexpr BaseReference<S, E, MS, ME, F> lin::ref(lin::internal::Base<F> &,
      lin::size_t, lin::size_t, lin::size_t , lin::size_t);

 public:
  /* Import elements from Base<BaseReference<R, C, MR, MC, D>>. */
  using Base<BaseReference<R, C, MR, MC, D>>::size;
  using Base<BaseReference<R, C, MR, MC, D>>::eval;
  using Base<BaseReference<R, C, MR, MC, D>>::operator=;
  using Base<BaseReference<R, C, MR, MC, D>>::operator();
  /* Import elements from Dimensions<BaseReference<R, C, MR, MC, D>>. */
  using Dimensions<BaseReference<R, C, MR, MC, D>>::rows;
  using Dimensions<BaseReference<R, C, MR, MC, D>>::cols;
  /* Include traits information. */
  typedef traits<BaseReference<R, C, MR, MC, D>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr BaseReference() = default;
  constexpr BaseReference(BaseReference<R, C, MR, MC, D> const &) = default;
  constexpr BaseReference(BaseReference<R, C, MR, MC, D> &&) = default;
  constexpr BaseReference<R, C, MR, MC, D> &operator=(BaseReference<R, C, MR, MC, D> const &) = default;
  constexpr BaseReference<R, C, MR, MC, D> &operator=(BaseReference<R, C, MR, MC, D> &&) = default;
  /* Element access/evaluation functions. */
  constexpr typename Traits::Elem &operator()(size_t i, size_t j);
  constexpr typename Traits::Elem &operator()(size_t i);

 protected:
  /* Import elements from Base<BaseReference<R, C, MR, MC, D>>. */
  using Base<BaseReference<R, C, MR, MC, D>>::derived;

 private:
  Base<D> &d;
  size_t const i, j;
  /* Import elements from Dimensions<BaseReference<R, C, MR, MC, D>>. */
  using Dimensions<BaseReference<R, C, MR, MC, D>>::resize;
  /* BaseReference constructor(s). */
  constexpr BaseReference(Base<D> &d, size_t i, size_t j, size_t r, size_t c);
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
struct _traits<BaseReference<R, C, MR, MC, D>> {
  typedef _traits_elem_t<D> Elem;
  constexpr static size_t Rows = R;
  constexpr static size_t Cols = C;
  constexpr static size_t MaxRows = MR;
  constexpr static size_t MaxCols = MC;
};

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr traits_elem_t<BaseReference<R, C, MR, MC, D>> &
BaseReference<R, C, MR, MC, D>::operator()(size_t i, size_t j) {
  LIN_ASSERT(i < rows() /* Invalid argument passed to BaseReference<...>::operator() */);
  LIN_ASSERT(j < cols() /* Invalid argument passed to BaseReference<...>::operator() */);
  return d(i + this->i, j + this->j);
}

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr traits_elem_t<BaseReference<R, C, MR, MC, D>> &
BaseReference<R, C, MR, MC, D>::operator()(size_t i) {
  return operator()(i / cols(), i % cols());
}

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr BaseReference<R, C, MR, MC, D>::BaseReference(Base<D> &d, size_t i, size_t j, size_t r, size_t c)
: d(d), i(i), j(j) {
  LIN_ASSERT(i + r <= d.rows() /* Invalid argument passed to BaseReference<...>::BaseReference */);
  LIN_ASSERT(j + c <= d.cols() /* Invalid argument passed to BaseReference<...>::BaseReference */);
  resize(r, c);
}
}  // namespace internal

template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr internal::BaseReference<R, C, MR, MC, D> ref(internal::Base<D> &d,
    size_t i, size_t j, size_t r, size_t c) {
  return internal::BaseReference<R, C, MR, MC, D>(d, i, j, r, c);
}

template <size_t R, size_t C, class D>
constexpr internal::BaseReference<R, C, R, C, D> ref(internal::Base<D> &d,
    size_t i, size_t j) {
  return ref<R, C, R, C, D>(d, i, j);
}

template <class D>
constexpr auto ref_row(internal::Base<D> &d, size_t i) {
  return ref<1, D::Traits::Cols, 1, D::Traits::MaxCols>(d, i, 0, 1, d.cols());
}

template <class D>
constexpr auto ref_col(internal::Base<D> &d, size_t j) {
  return ref<D::Traits::Rows, 1, D::Traits::MaxRows, 1>(d, 0, j, d.rows(), 1);
}
}  // namespace lin
