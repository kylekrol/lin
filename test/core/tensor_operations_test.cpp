/** @file test/core/tensor_operations_test.cpp
 *  @author Kyle Krol */

#include <lin/core/matrix/matrix.hpp>
#include <lin/core/tensor/operations.hpp>

#include <gtest/gtest.h>

TEST(CoreTensorOperations, TransposeDimensions) {
  lin::Matrix2x4f A;
  auto const transpose_A = lin::transpose(A);
  ASSERT_EQ(4, transpose_A.rows());
  ASSERT_EQ(2, transpose_A.cols());
  ASSERT_EQ(8, transpose_A.size());

  lin::Matrixf<0, 0, 4, 4> B(3, 2);
  auto const transpose_B = lin::transpose(B);
  ASSERT_EQ(2, transpose_B.rows());
  ASSERT_EQ(3, transpose_B.cols());
  ASSERT_EQ(6, transpose_B.size());
}

TEST(CoreTensorOperations, TransposeElements) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  auto const transpose_A = lin::transpose(A);
  ASSERT_FLOAT_EQ(0.0f, transpose_A(0, 0));
  ASSERT_FLOAT_EQ(2.0f, transpose_A(0, 1));
  ASSERT_FLOAT_EQ(1.0f, transpose_A(1, 0));
  ASSERT_FLOAT_EQ(3.0f, transpose_A(1, 1));
}

TEST(CoreTensorOperations, Frobenius) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(14.0f, lin::fro(A));

  lin::Matrixf<0, 0, 4, 4> B(3, 2, {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
  ASSERT_FLOAT_EQ(55.0f, lin::fro(B));
}
