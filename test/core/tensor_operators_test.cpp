/** @file test/core/tensor_operators_test.cpp
 *  @author Kyle Krol */

#include <lin/core/matrix/matrix.hpp>
#include <lin/core/tensor/operators.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(CoreTensorOperators, Add) {
  lin::Matrix2x2f A({1.0f, 2.0f, 3.0f, 4.0f}), B({5.0f, 6.0f, 7.0f, 8.0f});
  auto const C = A + B;
  ASSERT_FLOAT_EQ( 6.0f, C(0, 0));
  ASSERT_FLOAT_EQ( 8.0f, C(0, 1));
  ASSERT_FLOAT_EQ(10.0f, C(1, 0));
  ASSERT_FLOAT_EQ(12.0f, C(1, 1));
  ASSERT_EQ(2, C.rows());
  ASSERT_EQ(2, C.cols());
  ASSERT_EQ(4, C.size());

  lin::Matrixd<0, 0, 5, 5> D(2, 3, {
    1.0, 2.0, 3.0,
    4.0, 5.0, 6.0
  });
  lin::Matrixf<0, 0, 5, 5> E(2, 3, {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
  });
  lin::Matrixd<0, 0, 5, 5> F(D + E);
  static_assert(std::is_same<typename decltype(D + E)::Traits::Elem, double>::value, "");
  ASSERT_DOUBLE_EQ(2.0f, F(0, 0));
  ASSERT_DOUBLE_EQ(3.0f, F(0, 1));
  ASSERT_DOUBLE_EQ(4.0f, F(0, 2));
  ASSERT_DOUBLE_EQ(5.0f, F(1, 0));
  ASSERT_DOUBLE_EQ(6.0f, F(1, 1));
  ASSERT_DOUBLE_EQ(7.0f, F(1, 2));
  ASSERT_EQ(2, F.rows());
  ASSERT_EQ(3, F.cols());
  ASSERT_EQ(6, F.size());
}

TEST(CoreTensorOperators, Subtract) {
  lin::Matrix2x2f A({1.0f, 1.0f, 5.0f, 2.0f}), B({5.0f, 6.0f, 7.0f, 8.0f});
  auto const C = A - B;
  ASSERT_FLOAT_EQ(-4.0f, C(0, 0));
  ASSERT_FLOAT_EQ(-5.0f, C(0, 1));
  ASSERT_FLOAT_EQ(-2.0f, C(1, 0));
  ASSERT_FLOAT_EQ(-6.0f, C(1, 1));
  ASSERT_EQ(2, C.rows());
  ASSERT_EQ(2, C.cols());
  ASSERT_EQ(4, C.size());

  lin::Matrixd<0, 0, 5, 5> D(2, 3, {
    1.0, 2.0, 3.0,
    4.0, 5.0, 6.0
  });
  lin::Matrixf<0, 0, 5, 5> E(2, 3, {
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
  });
  lin::Matrixd<0, 0, 5, 5> F(D - E);
  static_assert(std::is_same<typename decltype(D - E)::Traits::Elem, double>::value, "");
  ASSERT_DOUBLE_EQ(0.0, F(0, 0));
  ASSERT_DOUBLE_EQ(1.0, F(0, 1));
  ASSERT_DOUBLE_EQ(2.0, F(0, 2));
  ASSERT_DOUBLE_EQ(3.0, F(1, 0));
  ASSERT_DOUBLE_EQ(4.0, F(1, 1));
  ASSERT_DOUBLE_EQ(5.0, F(1, 2));
  ASSERT_EQ(2, F.rows());
  ASSERT_EQ(3, F.cols());
  ASSERT_EQ(6, F.size());
}

TEST(CoreTensorOperators, Scale) {
  lin::Matrixd<0, 3, 5, 3> A(2, 3, {
    1.0, 3.0, 2.0,
    0.5, 1.0, 2.5
  });
  auto const B = A * 2.0f;
  static_assert(std::is_same<typename decltype(B)::Traits::Elem, double>::value, "");
  ASSERT_DOUBLE_EQ(2.0, B(0, 0));
  ASSERT_DOUBLE_EQ(6.0, B(0, 1));
  ASSERT_DOUBLE_EQ(4.0, B(0, 2));
  ASSERT_DOUBLE_EQ(1.0, B(1, 0));
  ASSERT_DOUBLE_EQ(2.0, B(1, 1));
  ASSERT_DOUBLE_EQ(5.0, B(1, 2));
  ASSERT_EQ(2, B.rows());
  ASSERT_EQ(3, B.cols());
  ASSERT_EQ(6, B.size());
}

TEST(CoreTensorOperators, Divide) {
  lin::Matrixd<0, 3, 5, 3> A(2, 3, {
    2.0, 6.0, 4.0,
    1.0, 9.0, 8.0
  });
  auto const B = A / 2.0f;
  static_assert(std::is_same<typename decltype(B)::Traits::Elem, double>::value, "");
  ASSERT_DOUBLE_EQ(1.0, B(0, 0));
  ASSERT_DOUBLE_EQ(3.0, B(0, 1));
  ASSERT_DOUBLE_EQ(2.0, B(0, 2));
  ASSERT_DOUBLE_EQ(0.5, B(1, 0));
  ASSERT_DOUBLE_EQ(4.5, B(1, 1));
  ASSERT_DOUBLE_EQ(4.0, B(1, 2));
  ASSERT_EQ(2, B.rows());
  ASSERT_EQ(3, B.cols());
  ASSERT_EQ(6, B.size());
}

TEST(CoreTensorOperators, Negate) {
  lin::Matrix2x2f A({
    1.0f, -1.0f,
    -1.0f, 1.0f
  });
  auto const B = -A;
  ASSERT_FLOAT_EQ(-1.0f, B(0, 0));
  ASSERT_FLOAT_EQ( 1.0f, B(0, 1));
  ASSERT_FLOAT_EQ( 1.0f, B(1, 0));
  ASSERT_FLOAT_EQ(-1.0f, B(1, 1));
  ASSERT_EQ(2, B.rows());
  ASSERT_EQ(2, B.cols());
  ASSERT_EQ(4, B.size());
}

TEST(CoreTensorOperators, Multiply) {
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
}
