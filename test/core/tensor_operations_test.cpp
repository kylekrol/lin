/** @file test/core/tensor_operations_test.cpp
 *  @author Kyle Krol */

#include <lin/core/matrix/matrix.hpp>
#include <lin/core/tensor/operations.hpp>

#include <gtest/gtest.h>

#include <cmath>

TEST(CoreTensorOperations, All) {
  lin::Matrix2x2f A({0.0f, 0.0f, 0.0f, 0.0f});
  ASSERT_TRUE(lin::all(A, [](float const &f) { return f == 0.0f; }));
  lin::Matrix2x2f B({0.0f, 0.0f, 1.0f, 0.0f});
  ASSERT_FALSE(lin::all(B, [](float const &f) { return f == 0.0f; }));
}

TEST(CoreTensorOperations, Any) {
  lin::Matrix2x2f A({0.0f, 0.0f, 0.0f, 0.0f});
  ASSERT_FALSE(lin::any(A, [](float const &f) -> bool { return f != 0.0f; }));
  lin::Matrix2x2f B({0.0f, 0.0f, 1.0f, 0.0f});
  ASSERT_TRUE(lin::any(B, [](float const &f) -> bool { return f != 0.0f; }));
}

TEST(CoreTensorOperations, Frobenius) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(14.0f, lin::fro(A));

  lin::Matrixf<0, 0, 4, 4> B(3, 2, {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
  ASSERT_FLOAT_EQ(55.0f, lin::fro(B));
}

TEST(CoreTensorOperations, Sign) {
  lin::Matrix2x3f A({
    0.0f, 0.2f, -100.0f,
    3.0f, -1.0f, -20.0f
  });
  auto sign_A = lin::sign(A);
  static_assert(lin::internal::have_same_traits<decltype(A), decltype(sign_A)>::value, "");
  ASSERT_EQ(2, sign_A.rows());
  ASSERT_EQ(3, sign_A.cols());
  ASSERT_EQ(6, sign_A.size());
  ASSERT_FLOAT_EQ( 0.0f, sign_A(0, 0));
  ASSERT_FLOAT_EQ( 1.0f, sign_A(0, 1));
  ASSERT_FLOAT_EQ(-1.0f, sign_A(0, 2));
  ASSERT_FLOAT_EQ( 1.0f, sign_A(1, 0));
  ASSERT_FLOAT_EQ(-1.0f, sign_A(1, 1));
  ASSERT_FLOAT_EQ(-1.0f, sign_A(1, 2));
}

TEST(CoreTensorOperations, Transpose) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  auto const transpose_A = lin::transpose(A);
  ASSERT_FLOAT_EQ(0.0f, transpose_A(0, 0));
  ASSERT_FLOAT_EQ(2.0f, transpose_A(0, 1));
  ASSERT_FLOAT_EQ(1.0f, transpose_A(1, 0));
  ASSERT_FLOAT_EQ(3.0f, transpose_A(1, 1));

  lin::Matrixf<0, 0, 4, 4> B(3, 2);
  auto const transpose_B = lin::transpose(B);
  ASSERT_EQ(2, transpose_B.rows());
  ASSERT_EQ(3, transpose_B.cols());
  ASSERT_EQ(6, transpose_B.size());

  lin::Matrix2x4f C;
  auto const transpose_C = lin::transpose(C);
  ASSERT_EQ(4, transpose_C.rows());
  ASSERT_EQ(2, transpose_C.cols());
  ASSERT_EQ(8, transpose_C.size());
}
