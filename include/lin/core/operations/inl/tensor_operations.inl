/** @file lin/core/operations/inl/tensor_operations.inl
 *  @author Kyle Krol
 *  See %lin/core/operations/tensor_operations.hpp for more information. */

#include "../tensor_operations.hpp"

namespace lin {
namespace internal {

template <class C>
class StreamTranspose : public Stream<StreamTranspose<C>> {
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
  /* StreamTranspose constructor(s). */
  constexpr StreamTranspose(Stream<C> const &c);
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
};

template <class C>
struct _traits<StreamTranspose<C>> : _traits<C> {
  constexpr static size_t
    Rows = _traits<C>::Cols,
    Cols = _traits<C>::Rows,
    MaxRows = _traits<C>::MaxCols,
    MaxCols = _traits<C>::MaxRows;
};

template <class C>
constexpr StreamTranspose<C>::StreamTranspose(Stream<C> const &c) : c(c) { }

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
}  // namespace internal

template <class C, std::enable_if_t<
    internal::matches_tensor<C>::value, size_t>>
constexpr typename C::Traits::Elem fro(internal::Stream<C> const &c) {
  typename C::Traits::Elem f = c(0) * c(0);
  for (size_t i = 1; i < c.size(); i++) f += c(i) * c(i);
  return f;
}
}  // namespace lin
