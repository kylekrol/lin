/** @file test/core/types_matrix_test.cpp
 *  @author Kyle Krol */

// TODO : Test the stream constructor

#include <lin/core/types/matrix.hpp>

#include <gtest/gtest.h>

static_assert(lin::internal::can_assign_types<float, float>::value, "shit my pants");

// Check for constexpr matrix dimensions and zero initialization
constexpr static lin::Matrix2x2f A;
static_assert(A.rows() == 2, "");
static_assert(A.cols() == 2, "");
static_assert(A.size() == 4, "");
static_assert(A(0, 0) == 0.0f, "");
static_assert(A(0, 1) == 0.0f, "");
static_assert(A(1, 0) == 0.0f, "");
static_assert(A(1, 1) == 0.0f, "");

TEST(CoreTypesMatrix, MatrixDimensions) {
  lin::Matrixf<3, 5> A;
  ASSERT_EQ(3,  A.rows());
  ASSERT_EQ(5,  A.cols());
  ASSERT_EQ(15, A.size());

  lin::Matrixf<0, 2, 3, 2> B;
  ASSERT_EQ(3, B.rows());
  ASSERT_EQ(2, B.cols());
  ASSERT_EQ(6, B.size());
}

TEST(CoreTypesMatrix, MatrixResize) {
  lin::Matrixf<0, 0, 4, 4> A;
  ASSERT_EQ(4,  A.rows());
  ASSERT_EQ(4,  A.cols());
  ASSERT_EQ(16, A.size());

  A.resize(3, 3);
  ASSERT_EQ(3, A.rows());
  ASSERT_EQ(3, A.cols());
  ASSERT_EQ(9, A.size());

  A.resize(2, 3);
  ASSERT_EQ(2, A.rows());
  ASSERT_EQ(3, A.cols());
  ASSERT_EQ(6, A.size());
}

TEST(CoreTypesMatrix, MatrixResizeConstructor) {
  lin::Matrixf<0, 0, 4, 4> A(2, 3);
  ASSERT_EQ(2, A.rows());
  ASSERT_EQ(3, A.cols());
  ASSERT_EQ(6, A.size());
}

TEST(CoreTypesMatrix, MatrixListConstructor) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(0.0f, A(0, 0));
  ASSERT_FLOAT_EQ(1.0f, A(0, 1));
  ASSERT_FLOAT_EQ(2.0f, A(1, 0));
  ASSERT_FLOAT_EQ(3.0f, A(1, 1));
}

TEST(CoreTypesMatrix, MatrixResizeListConstructor) {
  lin::Matrixf<0, 0, 4, 4> A(2, 2, {0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(0.0f, A(0, 0));
  ASSERT_FLOAT_EQ(1.0f, A(0, 1));
  ASSERT_FLOAT_EQ(2.0f, A(1, 0));
  ASSERT_FLOAT_EQ(3.0f, A(1, 1));
}
