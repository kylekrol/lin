/** @file lin/core/operations/inl/tensor_operators.inl
 *  @author Kyle Krol
 *  See %lin/core/operations/tensor_operators.hpp for more information. */

#include "../tensor_operators.hpp"

namespace lin {
namespace internal {

template <class C, class D, typename>
struct can_multiply : std::false_type { };

template <class C, class D>
struct can_multiply<C, D, std::enable_if_t<(
    matches_tensor_tensor<C, D>::value &&
    is_detected<multiply::template expression, _traits_elem_t<C>, _traits_elem_t<D>>::value &&
    (_traits<C>::Cols == _traits<D>::Rows) &&
    (_traits<C>::MaxCols == _traits<D>::MaxRows)
  )>> : std::true_type { };

template <class C, class D>
class StreamMultiply : public Stream<StreamMultiply<C, D>> {
 public:
  /* Import elements from Stream<StreamMultiply<C, D>>. */
  using Stream<StreamMultiply<C, D>>::size;
  using Stream<StreamMultiply<C, D>>::eval;
  /* Include traits information. */
  typedef traits<StreamMultiply<C, D>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamMultiply() = delete;
  constexpr StreamMultiply(StreamMultiply<C, D> const &) = default;
  constexpr StreamMultiply(StreamMultiply<C, D> &&) = default;
  constexpr StreamMultiply<C, D> &operator=(StreamMultiply<C, D> const &) = default;
  constexpr StreamMultiply<C, D> &operator=(StreamMultiply<C, D> &&) = default;
  /* StreamMultiply constructor(s). */
  constexpr StreamMultiply(Stream<C> const &c, Stream<D> const &d);
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamMultiply<C, D>>. */
  using Stream<StreamMultiply<C, D>>::derived;

 private:
  Stream<C> const &c;
  Stream<D> const &d;
};

template <class C, class D>
struct _traits<StreamMultiply<C, D>> {
  typedef typename multiply::template expression<_traits_elem_t<C>, _traits_elem_t<D>> Elem;
  constexpr static size_t
    Rows = _traits<C>::Rows,
    Cols = _traits<D>::Cols,
    MaxRows = _traits<C>::MaxRows,
    MaxCols = _traits<D>::MaxCols;
};

template <class C, class D>
constexpr StreamMultiply<C, D>::StreamMultiply(Stream<C> const &c,
    Stream<D> const &d) : c(c), d(d) { }

template <class C, class D>
constexpr size_t StreamMultiply<C, D>::rows() const {
  return c.rows();
}

template <class C, class D>
constexpr size_t StreamMultiply<C, D>::cols() const {
  return d.cols();
}

template <class C, class D>
constexpr traits_elem_t<StreamMultiply<C, D>> StreamMultiply<C, D>::operator()(
    size_t i, size_t j) const {
  traits_elem_t<StreamMultiply<C, D>> x = c(i, 0) * d(0, j);
  for (size_t k = 1; k < c.cols(); k++) x += c(i, k) * d(k, j);
  return x;
}

template <class C, class D>
constexpr traits_elem_t<StreamMultiply<C, D>> StreamMultiply<C, D>::operator()(size_t i) const {
  return (*this)(i / cols(), i % cols());
}
}  // namespace internal
}  // namespace lin
