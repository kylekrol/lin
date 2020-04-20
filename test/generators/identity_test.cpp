/** @file test/generators/identity_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/generators/identity.hpp>

#include <gtest/gtest.h>

TEST(GeneratorsIdentity, Identity) {
  lin::Matrix3x3f A {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };
  ASSERT_FLOAT_EQ(0.0f, lin::fro(A - lin::identity<float, 3>()));
  ASSERT_FLOAT_EQ(0.0f, lin::fro(A - lin::identity<lin::Matrix3x3f>()));

  lin::Matrixf<0, 0, 5, 5> B(2, 2);
  B = lin::identity<lin::Matrixf<0, 0, 5, 5>>(2); // 2x2 output
  ASSERT_FLOAT_EQ(1.0f, B(0, 0));
  ASSERT_FLOAT_EQ(0.0f, B(0, 1));
  ASSERT_FLOAT_EQ(0.0f, B(1, 0));
  ASSERT_FLOAT_EQ(1.0f, B(1, 1));
}
