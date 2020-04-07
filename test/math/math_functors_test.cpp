/** @file test/math/math_functors_test.cpp
 *  @author Kyle Krol */

/* We should only need to test a few functors here because they are generated
 * with macros. */

#include <lin/math/functors.hpp>

#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>

static_assert(std::is_same<double,
    typename lin::internal::abs::template expression<double>>::value, "");
static_assert(std::is_same<float,
    typename lin::internal::abs::template expression<float>>::value, "");

TEST(MathFunctors, UnaryFunctors) {
  lin::internal::abs _abs;
  ASSERT_FLOAT_EQ(1.0f, _abs(1.0f));
  ASSERT_FLOAT_EQ(1.0f, _abs(-1.0f));

  lin::internal::sin _sin;
  ASSERT_DOUBLE_EQ(std::sin(5.0), _sin(5.0));
  ASSERT_DOUBLE_EQ(std::sin(5.2), _sin(5.2));
}

static_assert(std::is_same<double,
    typename lin::internal::pow::template expression<double, double>>::value, "");
static_assert(std::is_same<double,
    typename lin::internal::pow_st<double>::template expression<double>>::value, "");
static_assert(std::is_same<float,
    typename lin::internal::pow_ts<float>::template expression<float>>::value, "");

TEST(MathFunctors, BinaryFunctors) {
  lin::internal::pow _pow;
  ASSERT_FLOAT_EQ(std::pow(2.0f, 5.0f), _pow(2.0f, 5.0f));
  lin::internal::pow_st<float> _pow_st(2.0f);
  ASSERT_FLOAT_EQ(std::pow(2.0f, 5.0f), _pow_st(5.0f));
  lin::internal::pow_ts<float> _pow_ts(5.0f);
  ASSERT_FLOAT_EQ(std::pow(2.0f, 5.0f), _pow_ts(2.0f));
}
