/** @file test/math/math_operations_test.cpp
 *  @author Kyle Krol */

/* We should only need to test a few operations here because they are generated
 * with macros. */

#include <lin/core.hpp>
#include <lin/math/operations.hpp>

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

constexpr static float _nan = std::numeric_limits<float>::quiet_NaN();
constexpr static float _inf = std::numeric_limits<float>::infinity();

#define LIN_MATH_GEN_UNARY_OPERATION_TEST(title, op, val0, val1, val2) \
    TEST(MathOperations, title) {\
      lin::Vector2f a { val0, val1 };\
      lin::Vector2f b = lin::op(a);\
      ASSERT_FLOAT_EQ(std::op(val0), b(0));\
      ASSERT_FLOAT_EQ(std::op(val1), b(1));\
      ASSERT_FLOAT_EQ(std::op(val2), lin::op(val2));\
    }\
    static_assert(true, "")

LIN_MATH_GEN_UNARY_OPERATION_TEST(Sin, sin, 0.1f, 0.2f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Cos, cos, 0.1f, 0.2f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Tan, tan, 0.1f, 0.2f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Asin, asin, 0.1f, 0.2f, -0.1f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Acos, acos, 0.1f, 0.2f, -0.1f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Atan, atan, 0.1f, 0.2f, -0.1f);

TEST(MathOperations, Atan2) {
  lin::Vector2f a {1.0f,  2.0f};
  lin::Vector2f b {0.0f, -1.0f};

  lin::Vector2f c = lin::atan2(a, b);
  ASSERT_FLOAT_EQ(std::atan2(1.0f,  0.0f), c(0));
  ASSERT_FLOAT_EQ(std::atan2(2.0f, -1.0f), c(1));

  lin::Vector2f d = lin::atan2(a, 3.0f);
  ASSERT_FLOAT_EQ(std::atan2(1.0f, 3.0f), d(0));
  ASSERT_FLOAT_EQ(std::atan2(2.0f, 3.0f), d(1));

  lin::Vector2f e = lin::atan2(-2.0f, a);
  ASSERT_FLOAT_EQ(std::atan2(-2.0f, 1.0f), e(0));
  ASSERT_FLOAT_EQ(std::atan2(-2.0f, 2.0f), e(1));

  ASSERT_FLOAT_EQ(std::atan2(5.0f, -4.0f), lin::atan2(5.0f, -4.0f));
}

TEST(MathOperations, IsFinite) {
  ASSERT_TRUE(lin::isfinite(0.0f));
  ASSERT_FALSE(lin::isfinite(_inf));
  ASSERT_FALSE(lin::isfinite(_nan));
}

TEST(MathOperations, IsInf) {
  ASSERT_FALSE(lin::isinf(0.0f));
  ASSERT_TRUE(lin::isinf(_inf));
  ASSERT_FALSE(lin::isinf(_nan));
}

TEST(MathOperations, IsNan) {
  ASSERT_FALSE(lin::isnan(0.0f));
  ASSERT_FALSE(lin::isnan(_inf));
  ASSERT_TRUE(lin::isnan(_nan));
}

TEST(MathOperations, IsNormal) {
  ASSERT_FALSE(lin::isnormal(0.0f));
  ASSERT_FALSE(lin::isnormal(_inf));
  ASSERT_FALSE(lin::isnormal(_nan));
}

LIN_MATH_GEN_UNARY_OPERATION_TEST(Exp, exp, 1.0f, 2.0f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Log, log, 1.0f, 2.0f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Log10, log10, 1.0f, 2.0f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Log2, log2, 1.0f, 2.0f, 3.0f);

LIN_MATH_GEN_UNARY_OPERATION_TEST(Sqrt, sqrt, 1.0f, 2.0f, 3.0f);
LIN_MATH_GEN_UNARY_OPERATION_TEST(Cbrt, cbrt, 1.0f, 2.0f, 3.0f);


TEST(MathOperations, Pow) {
  lin::Vector2f a {3.0f, 2.0f};
  lin::Vector2f b = lin::pow(2.0f, a);
  ASSERT_FLOAT_EQ(8.0f, b(0));
  ASSERT_FLOAT_EQ(4.0f, b(1));
}

LIN_MATH_GEN_UNARY_OPERATION_TEST(Abs, abs, 1.0f, -2.0f, 3.0f);
