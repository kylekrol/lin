/** @file lin/core/tensor/inl/operations.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/operations.hpp for more information. */

#include "../operations.hpp"

#include <type_traits> // TODO : Clean up this type_traits header here

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
  /* StreamTranspose constructor(s). */
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

template <class C>
class StreamSign : public Stream<StreamSign<C>> {
  template <class D>
  friend constexpr StreamSign<D> lin::sign(lin::internal::Stream<D> const &);

 public:
  /* Import elements from Stream<StreamSign<C>>. */
  using Stream<StreamSign<C>>::size;
  using Stream<StreamSign<C>>::eval;
  /* Include traits information. */
  typedef traits<StreamSign<C>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamSign() = delete;
  constexpr StreamSign(StreamSign<C> const &) = default;
  constexpr StreamSign(StreamSign<C> &&) = default;
  constexpr StreamSign<C> &operator=(StreamSign<C> const &) = default;
  constexpr StreamSign<C> &operator=(StreamSign<C> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamSign<D>>. */
  using Stream<StreamSign<C>>::derived;

 private:
  Stream<C> const &c;
  /* StreamSign constructor(s). */
  constexpr StreamSign(Stream<C> const &c);
};

template <class C>
struct _traits<StreamSign<C>> {
  typedef _traits_elem_t<C> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
};

// Adapted from
// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T>
inline constexpr T sign(T const &x) {
  if (std::is_signed<T>::value)
    return static_cast<T>((T(0) < x) - (x < T(0)));
  else
    return static_cast<T>(T(0) < x);
}

template <class C>
constexpr size_t StreamSign<C>::rows() const {
  return c.rows();
}

template <class C>
constexpr size_t StreamSign<C>::cols() const {
  return c.cols();
}

template <class C>
constexpr traits_elem_t<StreamSign<C>> StreamSign<C>::operator()(size_t i, size_t j) const {
  return sign(c(i, j));
}

template <class C>
constexpr traits_elem_t<StreamSign<C>> StreamSign<C>::operator()(size_t i) const {
  return sign(c(i));
}

template <class C>
constexpr StreamSign<C>::StreamSign(Stream<C> const &c) : c(c) { }

}  // namespace internal

template <class C>
constexpr bool all(internal::Stream<C> const &c, bool (*f)(typename C::Traits::Elem const &)) {
  for (size_t i = 0; i < c.size(); i++)
    if (!f(c(i))) return false;
  return true;
}

template <class C>
constexpr bool all_isfinite(internal::Stream<C> const &c) {
  return all(c, [](internal::traits_elem_t<C> const &e) -> bool {
    return std::isfinite(e);
  });
}

template <class C>
constexpr bool all_isinf(internal::Stream<C> const &c) {
  return all(c, [](internal::traits_elem_t<C> const &e) -> bool {
    return std::isinf(e);
  });
}

template <class C>
constexpr bool all_isnan(internal::Stream<C> const &c) {
  return all(c, [](internal::traits_elem_t<C> const &e) -> bool {
    return std::isnan(e);
  });
}

template <class C>
constexpr bool any(internal::Stream<C> const &c, bool (*f)(typename C::Traits::Elem const &)) {
  for (size_t i = 0; i < c.size(); i++)
    if (f(c(i))) return true;
  return false;
}

template <class C>
constexpr bool any_isfinite(internal::Stream<C> const &c) {
  return any(c, [](internal::traits_elem_t<C> const &e) -> bool {
    return std::isfinite(e);
  });
}

template <class C>
constexpr bool any_isinf(internal::Stream<C> const &c) {
  return any(c, [](internal::traits_elem_t<C> const &e) -> bool {
    return std::isinf(e);
  });
}

template <class C>
constexpr bool any_isnan(internal::Stream<C> const &c) {
  return any(c, [](internal::traits_elem_t<C> const &e) -> bool {
    return std::isnan(e);
  });
}

template <class C>
constexpr auto fro(internal::Stream<C> const &c) {
  internal::traits_elem_t<C> x = c(0) * c(0);
  for (size_t i = 1; i < c.size(); i++) x += c(i) * c(i);
  return x;
}

template <class C>
constexpr internal::StreamSign<C> sign(internal::Stream<C> const &c) {
  return internal::StreamSign<C>(c);
}

template <class C>
constexpr internal::StreamTranspose<C> transpose(internal::Stream<C> const &c) {
  return internal::StreamTranspose<C>(c);
}
}  // namespace lin
