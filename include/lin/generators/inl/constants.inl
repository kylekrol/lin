/** @file lin/generators/inl/constants.inl
 *  @author Kyle Krol
 *  See %lin/generators/constants.hpp for more information. */

#include "../constants.hpp"

namespace lin {
namespace internal {

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
class StreamConstants : public Stream<StreamConstants<T, R, C, MR, MC>>,
    public Dimensions<StreamConstants<T, R, C, MR, MC>> {
  template <typename U, size_t S, size_t D, size_t MS, size_t MD>
  friend constexpr StreamConstants<U, S, D, MS, MD> lin::consts(U, size_t, size_t);

 public:
  /* Import elements from Stream<StreamConstants<T, R, C, MR, MC>>. */
  using Stream<StreamConstants<T, R, C, MR, MC>>::size;
  using Stream<StreamConstants<T, R, C, MR, MC>>::eval;
  /* Import elements from Dimensions<StreamConstants<T, R, C, MR, MC>> */
  using Dimensions<StreamConstants<T, R, C, MR, MC>>::rows;
  using Dimensions<StreamConstants<T, R, C, MR, MC>>::cols;
  /* Include traits information. */
  typedef traits<StreamConstants<T, R, C, MR, MC>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamConstants() = default;
  constexpr StreamConstants(StreamConstants<T, R, C, MR, MC> const &) = default;
  constexpr StreamConstants(StreamConstants<T, R, C, MR, MC> &&) = default;
  constexpr StreamConstants<T, R, C, MR, MC> &operator=(StreamConstants<T, R, C, MR, MC> const &) = default;
  constexpr StreamConstants<T, R, C, MR, MC> &operator=(StreamConstants<T, R, C, MR, MC> &&) = default;
  /* Element access/evaluation functions. */
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamConstants<T, R, C, MR, MC>>. */
  using Stream<StreamConstants<T, R, C, MR, MC>>::derived;

 private:
  T const t;
  /* Import elements from Dimensions<StreamConstants<T, R, C, MR, MC>>. */
  using Dimensions<StreamConstants<T, R, C, MR, MC>>::resize;
  /* StreamConstants constructor(s). */
  constexpr StreamConstants(T t, size_t r, size_t c);
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _traits<StreamConstants<T, R, C, MR, MC>> {
  typedef T Elem;
  constexpr static size_t
      Rows = R,
      Cols = C,
      MaxRows = MR,
      MaxCols = MC;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr traits_elem_t<StreamConstants<T, R, C, MR, MC>>
StreamConstants<T, R, C, MR, MC>::operator()(size_t i, size_t j) const {
  LIN_ASSERT(0 <= i && i <= rows() /* Invalid argument passed to StreamConstants<...>::operator() */);
  LIN_ASSERT(0 <= j && j <= cols() /* Invalid argument passed to StreamConstants<...>::operator() */);
  return t;
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr traits_elem_t<StreamConstants<T, R, C, MR, MC>>
StreamConstants<T, R, C, MR, MC>::operator()(size_t i) const {
  LIN_ASSERT(0 <= i && i <= size() /* Invalid argument passed to StreamConstants<...>::operator() */);
  return t;
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr StreamConstants<T, R, C, MR, MC>::StreamConstants(T t, size_t r, size_t c) : t(t) {
  resize(r, c);
}
}  // namespace internal

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr internal::StreamConstants<T, R, C, MR, MC> consts(T t, size_t r, size_t c) {
  return internal::StreamConstants<T, R, C, MR, MC>(t, r, c);
}

template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t>>
constexpr auto consts(typename C::Traits::Elem t, size_t r, size_t c) {
  return consts<
      internal::_traits_elem_t<C>,
      internal::_traits<C>::Rows,
      internal::_traits<C>::Cols,
      internal::_traits<C>::MaxRows,
      internal::_traits<C>::MaxCols
    >(t, r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr internal::StreamConstants<T, R, C, MR, MC> ones(size_t r, size_t c) {
  return consts<T, R, C, MR, MC>(static_cast<T>(1), r, c);
}

template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t>>
constexpr auto ones(size_t r, size_t c) {
  return consts<C>(static_cast<internal::traits_elem_t<C>>(1), r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr internal::StreamConstants<T, R, C, MR, MC> zeros(size_t r, size_t c) {
    return consts<T, R, C, MR, MC>(static_cast<T>(0), r, c);
}

template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t>>
constexpr auto zeros(size_t r, size_t c) {
  return consts<C>(static_cast<internal::traits_elem_t<C>>(0), r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC, std::enable_if_t<
    std::numeric_limits<T>::has_quiet_NaN, size_t>>
constexpr internal::StreamConstants<T, R, C, MR, MC> nans(size_t r, size_t c) {
  return consts<T, R, C, MR, MC>(std::numeric_limits<T>::quiet_NaN(), r, c);
}

template <class C, std::enable_if_t<(internal::has_traits<C>::value &&
    std::numeric_limits<typename C::Traits::Elem>::has_quiet_NaN), size_t>>
constexpr auto nans(size_t r, size_t c) {
  return consts<C>(std::numeric_limits<internal::traits_elem_t<C>>::quiet_NaN(), r, c);
}
}  // namespace lin
