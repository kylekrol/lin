/** @file lin/math/functors.hpp
 *  @author Kyle Krol
 *  Defines functors to faciliate operations in the math module. */

#ifndef LIN_MATH_FUNCTORS_HPP_
#define LIN_MATH_FUNCTORS_HPP_

#include <cmath>
#include <utility>

#define LIN_MATH_GEN_UNARY_FUNCTOR(op) \
    struct op {\
      template <typename T>\
      using expression = decltype(std::op(std::declval<T &>()));\
      constexpr op() = default;\
      template <typename T>\
      inline constexpr auto operator()(T const &t) const { return std::op(t); }\
    }

#define LIN_MATH_GEN_BINARY_FUNCTOR(op) \
    struct op {\
       template <typename T, typename U>\
       using expression = decltype(std::op(std::declval<T &>(), std::declval<U &>()));\
       constexpr op() = default;\
       template <typename T, typename U>\
       inline constexpr auto operator()(T const &t, U const &u) const { return std::op(t, u); }\
    };\
    template <typename T>\
    struct op##_st {\
      template <typename U>\
      using expression = typename op::template expression<T, U>;\
      T const t;\
      constexpr op##_st() = default;\
      constexpr op##_st(T const &t) : t(t) { }\
      template <typename U>\
      inline constexpr auto operator()(U const &u) const { return std::op(t, u); }\
    };\
    template <typename T>\
    struct op##_ts {\
      template <typename U>\
      using expression = typename op::template expression<U, T>;\
      T const t;\
      constexpr op##_ts() = default;\
      constexpr op##_ts(T const &t) : t(t) { }\
      template <typename U>\
      inline constexpr auto operator()(U const &u) const { return std::op(u, t); }\
    }

namespace lin {
namespace internal {

/* Standard trigonometric functions. */
LIN_MATH_GEN_UNARY_FUNCTOR(sin);
LIN_MATH_GEN_UNARY_FUNCTOR(cos);
LIN_MATH_GEN_UNARY_FUNCTOR(tan);
LIN_MATH_GEN_UNARY_FUNCTOR(asin);
LIN_MATH_GEN_UNARY_FUNCTOR(acos);
LIN_MATH_GEN_UNARY_FUNCTOR(atan);
LIN_MATH_GEN_BINARY_FUNCTOR(atan2);

/* Query charactaristics. */
LIN_MATH_GEN_UNARY_FUNCTOR(isfinite);
LIN_MATH_GEN_UNARY_FUNCTOR(isinf);
LIN_MATH_GEN_UNARY_FUNCTOR(isnan);
LIN_MATH_GEN_UNARY_FUNCTOR(isnormal);

/* Exponential and logarithmic functions. */
LIN_MATH_GEN_UNARY_FUNCTOR(exp);
LIN_MATH_GEN_UNARY_FUNCTOR(log);
LIN_MATH_GEN_UNARY_FUNCTOR(log10);
LIN_MATH_GEN_UNARY_FUNCTOR(log2);

/* Power functions. */
LIN_MATH_GEN_UNARY_FUNCTOR(sqrt);
LIN_MATH_GEN_UNARY_FUNCTOR(cbrt);
LIN_MATH_GEN_BINARY_FUNCTOR(pow);

/* Others. */
LIN_MATH_GEN_UNARY_FUNCTOR(abs);

}  // namespace internal
}  // namespace lin

#endif
