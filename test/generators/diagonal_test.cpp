/** @file test/generators/diagonal_test.cpp
 *  @author Kyle Krol */

#include "lin/core.hpp"
#include "lin/generators/diagonal.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>

TEST(GeneratorsDiagonal, Diagonal) {
  lin::Vector2f a = {
    1.0f,
    2.0f
  };

  auto const A = lin::diag(a);
  static_assert(lin::internal::have_same_traits<std::remove_const_t<decltype(A)>, lin::Matrix2x2f>::value, "");
  ASSERT_FLOAT_EQ(1.0f, A(0, 0));
  ASSERT_FLOAT_EQ(0.0f, A(0, 1));
  ASSERT_FLOAT_EQ(0.0f, A(1, 0));
  ASSERT_FLOAT_EQ(2.0f, A(1, 1));
  ASSERT_EQ(2, A.rows());
  ASSERT_EQ(2, A.cols());

  lin::Vectorf<0, 3> b(2, {
    1.0f,
    2.0f
  });

  auto const B = lin::diag(b);
  static_assert(lin::internal::have_same_traits<std::remove_const_t<decltype(B)>, lin::Matrixf<0, 0, 3, 3>>::value, "");
  ASSERT_FLOAT_EQ(1.0f, B(0, 0));
  ASSERT_FLOAT_EQ(0.0f, B(0, 1));
  ASSERT_FLOAT_EQ(0.0f, B(1, 0));
  ASSERT_FLOAT_EQ(2.0f, B(1, 1));
  ASSERT_EQ(2, B.rows());
  ASSERT_EQ(2, B.cols());
}
