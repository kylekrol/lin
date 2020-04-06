/** @file test/core/operations_tensor_operators_test.cpp
 *  @author Kyle Krol */

#include <lin/core/types.hpp>
#include <lin/core/operations/tensor_operators.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(CoreOperationsTensorOperators, Add) {
  lin::Vector2f a {1.0f, 2.0f};
  lin::Vector2f b {1.0f, 3.0f};

  lin::Vector2f c = a + b;
  ASSERT_FLOAT_EQ(2.0f, c(0));
  ASSERT_FLOAT_EQ(5.0f, c(1));

  lin::Vector2f d = a + 1.0f;
  ASSERT_FLOAT_EQ(2.0f, d(0));
  ASSERT_FLOAT_EQ(3.0f, d(1));

  lin::Vector2d e = -2.0 + b;
  ASSERT_DOUBLE_EQ(-1.0, e(0));
  ASSERT_DOUBLE_EQ( 1.0, e(1));
}

TEST(CoreOperationsTensorOperators, Divide) {
  lin::Vectorf<0, 3> a(2, {12.0f, 9.0f});
  lin::Vectorf<0, 3> b(2, { 2.0f, 3.0f});

  lin::Vectorf<0, 3> c(2); c = a / b;
  ASSERT_FLOAT_EQ(6.0f, c(0));
  ASSERT_FLOAT_EQ(3.0f, c(1));

  lin::Vectorf<0, 3> d(2); d = a / 6.0f;
  ASSERT_FLOAT_EQ(2.0f, d(0));
  ASSERT_FLOAT_EQ(1.5f, d(1));

  lin::Vectord<0, 3> e(2); e = 6.0 / b;
  ASSERT_DOUBLE_EQ(3.0, e(0));
  ASSERT_DOUBLE_EQ(2.0, e(1));
}

TEST(CoreOperationsTensorOperators, Multiply) {
  lin::Matrix2x2f A({1.0f, 2.0f, 3.0f, 4.0f}), B({5.0f, 6.0f, 7.0f, 8.0f});
  auto const C = A * B;
  ASSERT_FLOAT_EQ(19.0f, C(0, 0));
  ASSERT_FLOAT_EQ(22.0f, C(0, 1));
  ASSERT_FLOAT_EQ(43.0f, C(1, 0));
  ASSERT_FLOAT_EQ(50.0f, C(1, 1));
  ASSERT_EQ(2, C.rows());
  ASSERT_EQ(2, C.cols());
  ASSERT_EQ(4, C.size());

  lin::Matrixd<0, 0, 5, 5> D(2, 3, {
    1.0, 2.0, 3.0,
    4.0, 5.0, 6.0
  });
  lin::Matrixf<0, 0, 5, 5> E(3, 2, {
    1.0f, 2.0f,
    1.0f, 2.0f,
    1.0f, 1.0f
  });
  static_assert(std::is_same<typename decltype(D * E)::Traits::Elem, double>::value, "");
  lin::Matrixd<0, 0, 5, 5> F(D * E);
  ASSERT_FLOAT_EQ( 6.0f, F(0, 0));
  ASSERT_FLOAT_EQ( 9.0f, F(0, 1));
  ASSERT_FLOAT_EQ(15.0f, F(1, 0));
  ASSERT_FLOAT_EQ(24.0f, F(1, 1));
  ASSERT_EQ(2, F.rows());
  ASSERT_EQ(2, F.cols());
  ASSERT_EQ(4, F.size());

  lin::Vector2f a {1.0f, 2.0f};
  lin::Vector2f b {1.0f, 3.0f};

  lin::Vector2f d = a * 2.0f;
  ASSERT_FLOAT_EQ(2.0f, d(0));
  ASSERT_FLOAT_EQ(4.0f, d(1));

  lin::Vector2d e = -2.0 * b;
  ASSERT_DOUBLE_EQ(-2.0, e(0));
  ASSERT_DOUBLE_EQ(-6.0, e(1));
}

TEST(CoreOperationsTensorOperators, Negate) {
  lin::Matrixf<0, 0, 3, 3> A(2, 2, {
    1.0f, 2.0f,
    -1.0f, 3.0f
  });
  lin::Matrixf<0, 0, 3, 3> B(2, 2); B = -A;
  ASSERT_FLOAT_EQ(-1.0f, B(0, 0));
  ASSERT_FLOAT_EQ(-2.0f, B(0, 1));
  ASSERT_FLOAT_EQ( 1.0f, B(1, 0));
  ASSERT_FLOAT_EQ(-3.0f, B(1, 1));
}

TEST(CoreOperationsTensorOperators, Subtract) {
  lin::Vector2f a {1.0f, 2.0f};
  lin::Vector2f b {1.0f, 3.0f};

  lin::Vector2f c = a - b;
  ASSERT_FLOAT_EQ( 0.0f, c(0));
  ASSERT_FLOAT_EQ(-1.0f, c(1));

  lin::Vector2f d = a - 2.0f;
  ASSERT_FLOAT_EQ(-1.0f, d(0));
  ASSERT_FLOAT_EQ( 0.0f, d(1));

  lin::Vector2d e = -2.0 - b;
  ASSERT_DOUBLE_EQ(-3.0, e(0));
  ASSERT_DOUBLE_EQ(-5.0, e(1));
}
