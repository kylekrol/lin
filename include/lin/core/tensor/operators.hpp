/** @file lin/core/tensor/operators.hpp
 *  @author Kyle Krol
 *  Defines operators that can be used across all tensor types. */

#ifndef LIN_CORE_TENSOR_OPERATORS_HPP_
#define LIN_CORE_TENSOR_OPERATORS_HPP_

#include "../config.hpp"
#include "../traits.hpp"

#include "stream.hpp"

namespace lin {
namespace internal {

/** @struct can_add
 *  Used to test if two tensor types can be added. */
template <class C, class D, typename = void>
struct can_add;

/** @class StreamAdd
 *  Represents a lazily evalutated addition operation. */
template <class C, class D>
class StreamAdd;

/** @fn operator+ */
template <class C, class D, enable_if_t<can_add<C, D>::value, size_t> = 0>
constexpr StreamAdd<C, D> operator+(Stream<C> const &c, Stream<D> const &d);

/** @struct can_subtract
 *  Used to test if two tensor types can be subtracted. */
template <class C, class D, typename = void>
struct can_subtract;

/** @class StreamSubtract
 *  Represents a lazily evaluated subtraction operation. */
template <class C, class D>
class StreamSubtract;

/** @fn operator- */
template <class C, class D, enable_if_t<can_subtract<C, D>::value, size_t> = 0>
constexpr StreamSubtract<C, D> operator-(Stream<C> const &c, Stream<D> const &d);

/** @struct can_scale
 *  Used to test if the tensor type can be scaled by the specified type. */
template <class C, typename T, typename = void>
struct can_scale;

/** @class StreamScale
 *  Represents a lazily evaluated element-wise multiplication. */
template <class C, typename T>
class StreamScale;

/** @fn operator* */
template <class C, typename T, enable_if_t<can_scale<C, T>::value, size_t> = 0>
constexpr StreamScale<C, T> operator*(Stream<C> const &c, T t);

/** @fn operator* */
template <class C, typename T, enable_if_t<can_scale<C, T>::value, size_t> = 0>
constexpr StreamScale<C, T> operator*(T t, Stream<C> const &c);

/** @struct can_divide
 *  Used to test if the tensor type can have it's elements divided by the
 *  specified type. */
template <class C, typename T, typename = void>
struct can_divide;

/** @class StreamDivide
 *  Represents a lazily evaluated element-wise division. */
template <class C, typename T>
class StreamDivide;

/** @fn operator/ */
template <class C, typename T, enable_if_t<can_divide<C, T>::value, size_t> = 0>
constexpr StreamDivide<C, T> operator/(Stream<C> const &c, T t);

/** @struct can_negate
 *  Used to test if a tensor can be element-wise negated. */
template <class C, typename = void>
struct can_negate;

/** @class StreamNegate
 *  Represents a lazily evaluated element-wise negation. */
template <class C>
class StreamNegate;

/** @fn operator- */
template <class C, enable_if_t<can_negate<C>::value, size_t> = 0>
constexpr StreamNegate<C> operator-(Stream<C> const &c);

/** @struct can_multiply
 *  Used to test if two tensor can be multiplied together. */
template <class C, class D, typename = void>
struct can_multiply;

/** @class StreamMultiply
 *  Represents a lazily evaluated tensor multiplication. */
template <class C, class D>
class StreamMultiply;

/** @fn operator* */
template <class C, class D, enable_if_t<can_multiply<C, D>::value, size_t> = 0>
constexpr StreamMultiply<C, D> operator*(Stream<C> const &c, Stream<D> const &d);

}  // namespace internal
}  // namespace lin

#include "inl/operators.inl"

#endif
