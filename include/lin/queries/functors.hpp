/** @file lin/queries/functors.hpp
 *  @author Kyle Krol
 *  Defines functors to faciliate operations in the queries module. */

// TODO : Documentation for this entire file

#ifndef LIN_QUERIES_FUNCTORS_HPP_
#define LIN_QUERIES_FUNCTORS_HPP_

#include <utility>

namespace lin {
namespace internal {

/** @struct equal_to */
struct equal_to {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() == std::declval<U &>());

  constexpr equal_to() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t == u; }
};

/** @struct equal_to_st */
template <typename T>
struct equal_to_st {
  template <typename U>
  using expression = typename equal_to::template expression<T, U>;

  T const t;
  constexpr equal_to_st() = default;
  constexpr equal_to_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return equal_to()(t, u); }
};

/** @typedef equal_to_ts */
template <typename T>
using equal_to_ts = equal_to_st<T>;

/** @struct greater */
struct greater {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() > std::declval<U &>());

  constexpr greater() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t > u; }
};

/** @struct greater_st */
template <typename T>
struct greater_st {
  template <typename U>
  using expression = typename greater::template expression<T, U>;

  T const t;
  constexpr greater_st() = default;
  constexpr greater_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return greater()(t, u); }
};

/** @struct greater_ts */
template <typename T>
struct greater_ts {
  template <typename U>
  using expression = typename greater::template expression<U, T>;

  T const t;
  constexpr greater_ts() = default;
  constexpr greater_ts(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return greater()(u, t); }
};

/** @struct greater_equal */
struct greater_equal {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() >= std::declval<U &>());

  constexpr greater_equal() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t >= u; }
};

/** @struct greater_equal_st */
template <typename T>
struct greater_equal_st {
  template <typename U>
  using expression = typename greater_equal::template expression<T, U>;

  T const t;
  constexpr greater_equal_st() = default;
  constexpr greater_equal_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return greater_equal()(t, u); }
};

/** @struct greater_equal_ts */
template <typename T>
struct greater_equal_ts {
  template <typename U>
  using expression = typename greater_equal::template expression<U, T>;

  T const t;
  constexpr greater_equal_ts() = default;
  constexpr greater_equal_ts(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return greater_equal()(u, t); }
};

/** @struct less */
struct less {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() < std::declval<U &>());

  constexpr less() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t < u; }
};

/** @struct less_st */
template <typename T>
struct less_st {
  template <typename U>
  using expression = typename less::template expression<T, U>;

  T const t;
  constexpr less_st() = default;
  constexpr less_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return less()(t, u); }
};

/** @struct less_ts */
template <typename T>
struct less_ts {
  template <typename U>
  using expression = typename less::template expression<U, T>;

  T const t;
  constexpr less_ts() = default;
  constexpr less_ts(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return less()(u, t); }
};

/** @struct less_equal */
struct less_equal {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() <= std::declval<U &>());

  constexpr less_equal() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t <= u; }
};

/** @struct less_equal_st */
template <typename T>
struct less_equal_st {
  template <typename U>
  using expression = typename less_equal::template expression<T, U>;

  T const t;
  constexpr less_equal_st() = default;
  constexpr less_equal_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return less_equal()(t, u); }
};

/** @struct less_equal_ts */
template <typename T>
struct less_equal_ts {
  template <typename U>
  using expression = typename less_equal::template expression<U, T>;

  T const t;
  constexpr less_equal_ts() = default;
  constexpr less_equal_ts(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return less_equal()(u, t); }
};

/** @struct logical_and */
struct logical_and {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() && std::declval<U &>());

  constexpr logical_and() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t && u; }
};

/** @struct logical_and_st */
template <typename T>
struct logical_and_st {
  template <typename U>
  using expression = typename logical_and::template expression<T, U>;

  T const t;
  constexpr logical_and_st() = default;
  constexpr logical_and_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return logical_and()(t, u); }
};

/** @typedef logical_and_ts */
template <typename T>
using logical_and_ts = logical_and_st<T>;

/** @struct logical_not */
struct logical_not {
  template <typename T>
  using expression = decltype(!std::declval<T &>());

  constexpr logical_not() = default;
  template <typename T>
  inline constexpr auto operator()(T const &t) const { return !t; }
};

/** @struct logical_or */
struct logical_or {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() || std::declval<U &>());

  constexpr logical_or() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t || u; }
};

/** @struct logical_or_st */
template <typename T>
struct logical_or_st {
  template <typename U>
  using expression = typename logical_or::template expression<T, U>;

  T const t;
  constexpr logical_or_st() = default;
  constexpr logical_or_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return logical_or()(t, u); }
};

/** @typedef logical_or_ts */
template <typename T>
using logical_or_ts = logical_or_st<T>;

/** @struct not_equal_to */
struct not_equal_to {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() != std::declval<U &>());

  constexpr not_equal_to() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t != u; }
};

/** @struct not_equal_to_st */
template <typename T>
struct not_equal_to_st {
  template <typename U>
  using expression = typename not_equal_to::template expression<T, U>;

  T const t;
  constexpr not_equal_to_st() = default;
  constexpr not_equal_to_st(T const &t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return not_equal_to()(t, u); }
};

/** @typedef not_equal_to_ts */
template <typename T>
using not_equal_to_ts = not_equal_to_st<T>;

}  // namespace internal
}  // namespace lin

#endif
