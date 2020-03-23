/** @file lin/core/tensor/inl/operators.inl
 *  @author Kyle Krol
 *  See %lin/core/tensor/operators.hpp for more information. */

#include "../operators.hpp"

namespace lin {
namespace internal {

template <class C, class D, typename>
struct can_add : false_type { };

template <class C, class D>
struct can_add<C, D, enable_if_t<(
    is_detected<add_expr, _traits_elem_t<C>, _traits_elem_t<D>>::value &&
    have_same_dimensions<C, D>::value
  )>> : true_type { };

template <class C, class D>
class StreamAdd : public Stream<StreamAdd<C, D>> {
  template <class E, class F, enable_if_t<can_add<E, F>::value, size_t>>
  friend constexpr StreamAdd<E, F> lin::internal::operator+(
      lin::internal::Stream<E> const &, lin::internal::Stream<F> const &);

 public:
  /* Import elements from Stream<StreamAdd<C, D>>. */
  using Stream<StreamAdd<C, D>>::size;
  using Stream<StreamAdd<C, D>>::eval;
  /* Include traits information. */
  typedef traits<StreamAdd<C, D>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamAdd() = delete;
  constexpr StreamAdd(StreamAdd<C, D> const &) = default;
  constexpr StreamAdd(StreamAdd<C, D> &&) = default;
  constexpr StreamAdd<C, D> &operator=(StreamAdd<C, D> const &) = default;
  constexpr StreamAdd<C, D> &operator=(StreamAdd<C, D> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamAdd<C, D>>. */
  using Stream<StreamAdd<C, D>>::derived;

 private:
  Stream<C> const &c;
  Stream<D> const &d;
  /* StreamAdd constructor(s). */
  constexpr StreamAdd(Stream<C> const &c, Stream<D> const &d);
};

template <class C, class D>
struct _traits<StreamAdd<C, D>> {
  typedef add_expr<_traits_elem_t<C>, _traits_elem_t<D>> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
};

template <class C, class D>
constexpr size_t StreamAdd<C, D>::rows() const {
  return c.rows();
}

template <class C, class D>
constexpr size_t StreamAdd<C, D>::cols() const {
  return c.cols();
}

template <class C, class D>
constexpr traits_elem_t<StreamAdd<C, D>> StreamAdd<C, D>::operator()(size_t i, size_t j) const {
  return c(i, j) + d(i, j);
}

template <class C, class D>
constexpr traits_elem_t<StreamAdd<C, D>> StreamAdd<C, D>::operator()(size_t i) const {
  return c(i) + d(i);
}

template <class C, class D>
constexpr StreamAdd<C, D>::StreamAdd(Stream<C> const &c, Stream<D> const &d) : c(c), d(d) {
  LIN_ASSERT(c.rows() == d.rows() /* Invalid arguments passed to StreamAdd<...>::StreamAdd */);
  LIN_ASSERT(c.cols() == d.cols() /* Invalid arguments passed to StreamAdd<...>::StreamAdd */);
}

template <class C, class D, enable_if_t<can_add<C, D>::value, size_t>>
constexpr StreamAdd<C, D> operator+(Stream<C> const &c, Stream<D> const &d) {
  return StreamAdd<C, D>(c, d);
}

template <class C, class D, typename>
struct can_subtract : false_type { };

template <class C, class D>
struct can_subtract<C, D, enable_if_t<(
    is_detected<subtract_expr, _traits_elem_t<C>, _traits_elem_t<D>>::value &&
    have_same_dimensions<C, D>::value
  )>> : true_type { };

template <class C, class D>
class StreamSubtract : public Stream<StreamSubtract<C, D>> {
  template <class E, class F, enable_if_t<can_subtract<E, F>::value, size_t>>
  friend constexpr StreamSubtract<E, F> lin::internal::operator-(
      lin::internal::Stream<E> const &, lin::internal::Stream<F> const &);

 public:
  /* Import elements from Stream<StreamSubtract<C, D>>. */
  using Stream<StreamSubtract<C, D>>::size;
  using Stream<StreamSubtract<C, D>>::eval;
  /* Include traits information. */
  typedef traits<StreamSubtract<C, D>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamSubtract() = delete;
  constexpr StreamSubtract(StreamSubtract<C, D> const &) = default;
  constexpr StreamSubtract(StreamSubtract<C, D> &&) = default;
  constexpr StreamSubtract<C, D> &operator=(StreamSubtract<C, D> const &) = default;
  constexpr StreamSubtract<C, D> &operator=(StreamSubtract<C, D> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamSubtract<C, D>>. */
  using Stream<StreamSubtract<C, D>>::derived;

 private:
  Stream<C> const &c;
  Stream<D> const &d;
  /* StreamSubtract constructor(s). */
  constexpr StreamSubtract(Stream<C> const &c, Stream<D> const &d);
};

template <class C, class D>
struct _traits<StreamSubtract<C, D>> {
  typedef subtract_expr<_traits_elem_t<C>, _traits_elem_t<D>> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
};

template <class C, class D>
constexpr size_t StreamSubtract<C, D>::rows() const {
  return c.rows();
}

template <class C, class D>
constexpr size_t StreamSubtract<C, D>::cols() const {
  return c.cols();
}

template <class C, class D>
constexpr traits_elem_t<StreamSubtract<C, D>> StreamSubtract<C, D>::operator()(size_t i, size_t j) const {
  return c(i, j) - d(i, j);
}

template <class C, class D>
constexpr traits_elem_t<StreamSubtract<C, D>> StreamSubtract<C, D>::operator()(size_t i) const {
  return c(i) - d(i);
}

template <class C, class D>
constexpr StreamSubtract<C, D>::StreamSubtract(Stream<C> const &c, Stream<D> const &d) : c(c), d(d) {
  LIN_ASSERT(c.rows() == d.rows() /* Invalid arguments passed to StreamSubtract<...>::StreamSubtract */);
  LIN_ASSERT(c.cols() == d.cols() /* Invalid arguments passed to StreamSubtract<...>::StreamSubtract */);
}

template <class C, class D, enable_if_t<can_subtract<C, D>::value, size_t>>
constexpr StreamSubtract<C, D> operator-(Stream<C> const &c, Stream<D> const &d) {
  return StreamSubtract<C, D>(c, d);
}

template <class C, typename T, typename>
struct can_scale : false_type { };

template <class C, typename T>
struct can_scale<C, T, enable_if_t<(
    is_detected<multiply_expr, _traits_elem_t<C>, T>::value &&
    !has_traits<T>::value
  )>> : true_type { };

template <class C, typename T>
class StreamScale : public Stream<StreamScale<C, T>> {
  template <class D, typename U, enable_if_t<can_scale<D, U>::value, size_t>>
  friend constexpr StreamScale<D, U> lin::internal::operator*(lin::internal::Stream<D> const &, U);
  template <class D, typename U, enable_if_t<can_scale<D, U>::value, size_t>>
  friend constexpr StreamScale<D, U> lin::internal::operator*(U, lin::internal::Stream<D> const &);

 public:
  /* Import elements from Stream<StreamScale<C, T>>. */
  using Stream<StreamScale<C, T>>::size;
  using Stream<StreamScale<C, T>>::eval;
  /* Include traits information. */
  typedef traits<StreamScale<C, T>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamScale() = delete;
  constexpr StreamScale(StreamScale<C, T> const &) = default;
  constexpr StreamScale(StreamScale<C, T> &&) = default;
  constexpr StreamScale<C, T> &operator=(StreamScale<C, T> const &) = default;
  constexpr StreamScale<C, T> &operator=(StreamScale<C, T> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamScale<C, T>>. */
  using Stream<StreamScale<C, T>>::derived;

 private:
  Stream<C> const &c;
  T const t;
  /* StreamScale constructor(s). */
  constexpr StreamScale(Stream<C> const &c, T t);
};

template <class C, typename T>
struct _traits<StreamScale<C, T>> {
  typedef multiply_expr<_traits_elem_t<C>, T> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
};

template <class C, typename T>
constexpr size_t StreamScale<C, T>::rows() const {
  return c.rows();
}

template <class C, typename T>
constexpr size_t StreamScale<C, T>::cols() const {
  return c.cols();
}

template <class C, typename T>
constexpr traits_elem_t<StreamScale<C, T>> StreamScale<C, T>::operator()(size_t i, size_t j) const {
  return t * c(i, j);
}

template <class C, typename T>
constexpr traits_elem_t<StreamScale<C, T>> StreamScale<C, T>::operator()(size_t i) const {
  return t * c(i);
}

template <class C, typename T>
constexpr StreamScale<C, T>::StreamScale(Stream<C> const &c, T t) : c(c), t(t) { }

template <class C, typename T, enable_if_t<can_scale<C, T>::value, size_t>>
constexpr StreamScale<C, T> operator*(Stream<C> const &c, T t) {
  return StreamScale<C, T>(c, t);
}

template <class C, typename T, enable_if_t<can_scale<C, T>::value, size_t>>
constexpr StreamScale<C, T> operator*(T t, Stream<C> const &c) {
  return c * t;
}

template <class C, typename T, typename>
struct can_divide : false_type { };

template <class C, typename T>
struct can_divide<C, T, enable_if_t<(
    is_detected<divide_expr, _traits_elem_t<C>, T>::value &&
    !has_traits<T>::value
  )>> : true_type { };

template <class C, typename T>
class StreamDivide : public Stream<StreamDivide<C, T>> {
  template <class D, typename U, enable_if_t<can_divide<D, U>::value, size_t>>
  friend constexpr StreamDivide<D, U> operator/(Stream<D> const &, U);

 public:
  /* Import elements from Stream<StreamDivide<C, T>>. */
  using Stream<StreamDivide<C, T>>::size;
  using Stream<StreamDivide<C, T>>::eval;
  /* Include traits information. */
  typedef traits<StreamDivide<C, T>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamDivide() = delete;
  constexpr StreamDivide(StreamDivide<C, T> const &) = default;
  constexpr StreamDivide(StreamDivide<C, T> &&) = default;
  constexpr StreamDivide<C, T> &operator=(StreamDivide<C, T> const &) = default;
  constexpr StreamDivide<C, T> &operator=(StreamDivide<C, T> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamScale<C, T>>. */
  using Stream<StreamDivide<C, T>>::derived;

 private:
  Stream<C> const &c;
  T const t;
  /* StreamDivide constructor(s). */
  constexpr StreamDivide(Stream<C> const &c, T t);
};

template <class C, typename T>
struct _traits<StreamDivide<C, T>> {
  typedef divide_expr<_traits_elem_t<C>, T> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
};

template <class C, typename T>
constexpr size_t StreamDivide<C, T>::rows() const {
  return c.rows();
}

template <class C, typename T>
constexpr size_t StreamDivide<C, T>::cols() const {
  return c.cols();
}

template <class C, typename T>
constexpr traits_elem_t<StreamDivide<C, T>> StreamDivide<C, T>::operator()(size_t i, size_t j) const {
  return c(i, j) / t;
}

template <class C, typename T>
constexpr traits_elem_t<StreamDivide<C, T>> StreamDivide<C, T>::operator()(size_t i) const {
  return c(i) / t;
}

template <class C, typename T>
constexpr StreamDivide<C, T>::StreamDivide(Stream<C> const &c, T t) : c(c), t(t) { }

template <class C, typename T, enable_if_t<can_divide<C, T>::value, size_t>>
constexpr StreamDivide<C, T> operator/(Stream<C> const &c, T t) {
  return StreamDivide<C, T>(c, t);
}

template <class C, typename>
struct can_negate : is_detected<negate_expr, _traits_elem_t<C>> { };

template <class C>
class StreamNegate : public Stream<StreamNegate<C>> {
  template <class D, enable_if_t<can_negate<D>::value, size_t>>
  friend constexpr StreamNegate<D> lin::internal::operator-(lin::internal::Stream<D> const &);

 public:
  /* Import elements from Stream<StreamDivide<C, T>>. */
  using Stream<StreamNegate<C>>::size;
  using Stream<StreamNegate<C>>::eval;
  /* Include traits information. */
  typedef traits<StreamNegate<C>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamNegate() = delete;
  constexpr StreamNegate(StreamNegate<C> const &) = default;
  constexpr StreamNegate(StreamNegate<C> &&) = default;
  constexpr StreamNegate<C> &operator=(StreamNegate<C> const &) = default;
  constexpr StreamNegate<C> &operator=(StreamNegate<C> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamScale<C, T>>. */
  using Stream<StreamNegate<C>>::derived;

 private:
  Stream<C> const &c;
  /* StreamNegate constructor(s). */
  constexpr StreamNegate(Stream<C> const &c);
};

template <class C>
struct _traits<StreamNegate<C>> {
  typedef negate_expr<_traits_elem_t<C>> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<C>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<C>::MaxCols;
};

template <class C>
constexpr size_t StreamNegate<C>::rows() const {
  return c.rows();
}

template <class C>
constexpr size_t StreamNegate<C>::cols() const {
  return c.cols();
}

template <class C>
constexpr traits_elem_t<StreamNegate<C>> StreamNegate<C>::operator()(size_t i, size_t j) const {
  return -c(i, j);
}

template <class C>
constexpr traits_elem_t<StreamNegate<C>> StreamNegate<C>::operator()(size_t i) const {
  return -c(i);
}

template <class C>
constexpr StreamNegate<C>::StreamNegate(Stream<C> const &c) : c(c) { }

template <class C, enable_if_t<can_negate<C>::value, size_t>>
constexpr StreamNegate<C> operator-(Stream<C> const &c) {
  return StreamNegate<C>(c);
}

template <class C, class D, typename>
struct can_multiply : false_type { };

template <class C, class D>
struct can_multiply<C, D, enable_if_t<(
    is_detected<multiply_expr, _traits_elem_t<C>, _traits_elem_t<D>>::value &&
    (_traits<C>::Cols == _traits<D>::Rows) &&
    (_traits<C>::MaxCols == _traits<D>::MaxRows)
  )>> : true_type { };

template <class C, class D>
class StreamMultiply : public Stream<StreamMultiply<C, D>> {
  template <class E, class F, enable_if_t<can_multiply<E, F>::value, size_t>>
  friend constexpr StreamMultiply<E, F> lin::internal::operator*(
      lin::internal::Stream<E> const &, lin::internal::Stream<F> const &);

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
  /* StreamMultiply constructor(s). */
  constexpr StreamMultiply(Stream<C> const &c, Stream<D> const &d);
};

template <class C, class D>
struct _traits<StreamMultiply<C, D>> {
  typedef multiply_expr<_traits_elem_t<C>, _traits_elem_t<D>> Elem;
  constexpr static size_t Rows = _traits<C>::Rows;
  constexpr static size_t Cols = _traits<D>::Cols;
  constexpr static size_t MaxRows = _traits<C>::MaxRows;
  constexpr static size_t MaxCols = _traits<D>::MaxCols;
};

template <class C, class D>
constexpr size_t StreamMultiply<C, D>::rows() const {
  return c.rows();
}

template <class C, class D>
constexpr size_t StreamMultiply<C, D>::cols() const {
  return d.cols();
}

template <class C, class D>
constexpr traits_elem_t<StreamMultiply<C, D>> StreamMultiply<C, D>::operator()(size_t i, size_t j) const {
  traits_elem_t<StreamMultiply<C, D>> x = c(i, 0) * d(0, j);
  for (size_t k = 1; k < c.cols(); k++) x += c(i, k) * d(k, j);
  return x;
}

template <class C, class D>
constexpr traits_elem_t<StreamMultiply<C, D>> StreamMultiply<C, D>::operator()(size_t i) const {
  return (*this)(i / cols(), i % cols());
}

template <class C, class D>
constexpr StreamMultiply<C, D>::StreamMultiply(Stream<C> const &c, Stream<D> const &d) : c(c), d(d) {
  LIN_ASSERT(c.cols() == d.rows() /* Invalid arguments passed to StreamMultiply<...>::StreamMultiply */);
}

template <class C, class D, enable_if_t<can_multiply<C, D>::value, size_t>>
constexpr StreamMultiply<C, D> operator*(Stream<C> const &c, Stream<D> const &d) {
  return StreamMultiply<C, D>(c, d);
}
}  // namespace internal
}  // namespace lin
