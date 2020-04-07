/** @file lin/math/functors.hpp
 *  @author Kyle Krol
 *  Defines all operations included in the math module. */

/* Note that most math functions within the cmath header are not constexpr so
 * neither are these operations. */

#ifndef LIN_MATH_OPERATIONS_HPP_
#define LIN_MATH_OPERATIONS_HPP_

#include "../core.hpp"
#include "functors.hpp"

#include <type_traits>

#define LIN_MATH_GEN_UNARY_OPERATION(op) \
    template <class C, std::enable_if_t<\
        internal::matches_tensor<C>::value, size_t> = 0>\
    inline constexpr auto op(internal::Stream<C> const &c) {\
      return internal::StreamElementWiseOperator<internal::op, C>(c);\
    }\
    template <typename T, std::enable_if_t<\
        internal::matches_scalar<T>::value, size_t> = 0>\
    inline constexpr auto op(T const &t) {\
      return internal::op()(t);\
    }\
    static_assert(true, "")

#define LIN_MATH_GEN_BINARY_OPERATION(op) \
    template <class C, class D, std::enable_if_t<\
        internal::matches_tensor_tensor<C, D>::value, size_t> = 0>\
    inline constexpr auto op(internal::Stream<C> const &c, internal::Stream<D> const &d) {\
      return internal::StreamElementWiseOperator<internal::op, C, D>(c, d);\
    }\
    template <typename T, class C, std::enable_if_t<\
        internal::matches_scalar_tensor<T, C>::value, size_t> = 0>\
    inline constexpr auto op(T const &t, internal::Stream<C> const &c) {\
      return internal::StreamElementWiseOperator<internal::op##_st<T>, C>(c, t);\
    }\
    template <class C, typename T, std::enable_if_t<\
        internal::matches_tensor_scalar<C, T>::value, size_t> = 0>\
    inline constexpr auto op(internal::Stream<C> const &c, T const &t) {\
      return internal::StreamElementWiseOperator<internal::op##_ts<T>, C>(c, t);\
    }\
    template <typename T, typename U, std::enable_if_t<\
        internal::matches_scalar_scalar<T, U>::value, size_t> = 0>\
    inline constexpr auto op(T const &t, U const &u) {\
      return internal::op()(t, u);\
    }\
    static_assert(true, "")

namespace lin {

/* Standard trigonometric functions. */
LIN_MATH_GEN_UNARY_OPERATION(sin);
LIN_MATH_GEN_UNARY_OPERATION(cos);
LIN_MATH_GEN_UNARY_OPERATION(tan);
LIN_MATH_GEN_UNARY_OPERATION(asin);
LIN_MATH_GEN_UNARY_OPERATION(acos);
LIN_MATH_GEN_UNARY_OPERATION(atan);
LIN_MATH_GEN_BINARY_OPERATION(atan2);

/* Query charactaristics. */
LIN_MATH_GEN_UNARY_OPERATION(isfinite);
LIN_MATH_GEN_UNARY_OPERATION(isinf);
LIN_MATH_GEN_UNARY_OPERATION(isnan);
LIN_MATH_GEN_UNARY_OPERATION(isnormal);

/* Exponential and logarithmic functions. */
LIN_MATH_GEN_UNARY_OPERATION(exp);
LIN_MATH_GEN_UNARY_OPERATION(log);
LIN_MATH_GEN_UNARY_OPERATION(log10);
LIN_MATH_GEN_UNARY_OPERATION(log2);

/* Power functions. */
LIN_MATH_GEN_UNARY_OPERATION(sqrt);
LIN_MATH_GEN_UNARY_OPERATION(cbrt);
LIN_MATH_GEN_BINARY_OPERATION(pow);

/* Others. */
LIN_MATH_GEN_UNARY_OPERATION(abs);

}  // namespace lin

#endif
