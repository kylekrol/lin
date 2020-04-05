/** @file lin/core/operations/functors.hpp
 *  @author Kyle Krol
 *  Defines functors to facilitate element wise operations. */

// TODO : Documentation for this entire file

#ifndef LIN_CORE_OPERATIONS_FUNCTORS_HPP_
#define LIN_CORE_OPERATIONS_FUNCTORS_HPP_

#include <cmath>
#include <type_traits>
#include <utility>

namespace lin {
namespace internal {

/** @struct add */
struct add {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() + std::declval<U &>());

  constexpr add() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t + u; }
};

/** @struct add_st */
template <typename T>
struct add_st {
  template <typename U>
  using expression = typename add::expression<T, U>;

  T const t;
  constexpr add_st() = default;
  constexpr add_st(T t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return add()(t, u); }
};

/** @typedef add_ts */
template <typename T>
using add_ts = add_st<T>;

/** @struct divide */
struct divide {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() / std::declval<U &>());

  constexpr divide() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t / u; }
};

/** @struct divide_st */
template <typename T>
struct divide_st {
  template <typename U>
  using expression = typename divide::expression<T, U>;

  T const t;
  constexpr divide_st() = default;
  constexpr divide_st(T t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const u) const { return divide()(t, u); }
};

/** @struct divide_ts */
template <typename T>
struct divide_ts {
  template <typename U>
  using expression = typename divide::expression<U, T>;

  T const t;
  constexpr divide_ts() = default;
  constexpr divide_ts(T t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return divide()(u, t); }
};

/** @struct multiply */
struct multiply {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() * std::declval<U &>());

  constexpr multiply() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t * u; }
};

/** @struct multiply_st */
template <typename T>
struct multiply_st {
  template <typename U>
  using expression = typename multiply::expression<T, U>;

  T const t;
  constexpr multiply_st() = default;
  constexpr multiply_st(T t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return multiply()(t, u); }
};

/** @typedef multiply_ts */
template <typename T>
using multiply_ts = multiply_st<T>;

/** @struct negate */
struct negate {
  template <typename T>
  using expression = decltype(-std::declval<T &>());

  constexpr negate() = default;
  template <typename T>
  inline constexpr auto operator()(T const &t) const { return -t; }
};

/** @struct sign */
struct sign {
  template <typename T>
  inline constexpr static T _sign(T const &t) {
    if (std::is_signed<T>::value) return T((T(0) < t) - (t < T(0)));
    else return T(T(0) < t);
  }

  template <typename T>
  using expression = decltype(_sign(std::declval<T &>()));

  constexpr sign() = default;
  template <typename T>
  inline constexpr auto operator()(T const &t) const { return _sign(t); }
};

/** @struct subtract */
struct subtract {
  template <typename T, typename U>
  using expression = decltype(std::declval<T &>() - std::declval<U &>());

  constexpr subtract() = default;
  template <typename T, typename U>
  inline constexpr auto operator()(T const &t, U const &u) const { return t - u; }
};

/** @struct subtract_st */
template <typename T>
struct subtract_st {
  template <typename U>
  using expression = typename subtract::expression<T, U>;

  T const t;
  constexpr subtract_st() = default;
  constexpr subtract_st(T t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return subtract()(t, u); }
};

/** @struct subtract_ts */
template <typename T>
struct subtract_ts {
  template <typename U>
  using expression = typename subtract::expression<U, T>;

  T const t;
  constexpr subtract_ts() = default;
  constexpr subtract_ts(T t) : t(t) { }
  template <typename U>
  inline constexpr auto operator()(U const &u) const { return subtract()(u, t); }
};
}  // namespace internal
}  // namespace lin

#endif
