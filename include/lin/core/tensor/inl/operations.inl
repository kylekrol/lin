/** @file lin/core/tensor/inl/operations.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/operations.hpp for more information. */

#include "../operations.hpp"

namespace lin {
namespace internal {

template <class C>
class StreamTranspose : public Stream<StreamTranspose<C>> {
  template <class D>
  friend constexpr StreamTranspose<D> lin::transpose(lin::internal::Stream<D> const &);

 public:
  /* Import elements from Stream<StreamTranspose<C>>. */
  using Stream<StreamTranspose<C>>::size;
  using Stream<StreamTranspose<C>>::eval;
  /* Include traits information. */
  typedef traits<StreamTranspose<C>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamTranspose() = delete;
  constexpr StreamTranspose(StreamTranspose<C> const &) = default;
  constexpr StreamTranspose(StreamTranspose<C> &&) = default;
  constexpr StreamTranspose<C> &operator=(StreamTranspose<C> const &) = default;
  constexpr StreamTranspose<C> &operator=(StreamTranspose<C> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamTranspose<D>>. */
  using Stream<StreamTranspose<C>>::derived;

 private:
  Stream<C> const &c;
  /* StreamAdd constructor(s). */
  constexpr StreamTranspose(Stream<C> const &c);
};

template <class C>
struct _traits<StreamTranspose<C>> {
  typedef _traits_elem_t<C> Elem;
  constexpr static size_t Rows = _traits<C>::Cols;
  constexpr static size_t Cols = _traits<C>::Rows;
  constexpr static size_t MaxRows = _traits<C>::MaxCols;
  constexpr static size_t MaxCols = _traits<C>::MaxRows;
};

template <class C>
constexpr size_t StreamTranspose<C>::rows() const {
  return c.cols();
}

template <class C>
constexpr size_t StreamTranspose<C>::cols() const {
  return c.rows();
}

template <class C>
constexpr traits_elem_t<StreamTranspose<C>> StreamTranspose<C>::operator()(size_t i, size_t j) const {
  return c(j, i);
}

template <class C>
constexpr traits_elem_t<StreamTranspose<C>> StreamTranspose<C>::operator()(size_t i) const {
  return (*this)(i / cols(), i % cols());
}

template <class C>
constexpr StreamTranspose<C>::StreamTranspose(Stream<C> const &c) : c(c) { }

}  // namespace internal

template <class C>
constexpr internal::StreamTranspose<C> transpose(internal::Stream<C> const &c) {
  return internal::StreamTranspose<C>(c);
}

template <class C>
constexpr auto fro(internal::Stream<C> const &c) {
  internal::traits_elem_t<C> x = c(0) * c(0);
  for (size_t i = 1; i < c.size(); i++) x += c(i) * c(i);
  return x;
}
}  // namespace lin
