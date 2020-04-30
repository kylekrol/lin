/** @file test/core/operations_tensor_operations_test.cpp
 *  @author Kyle Krol */

#include <lin/core/types.hpp>
#include <lin/core/operations/tensor_operations.hpp>

#include <gtest/gtest.h>

/* START: From matrix operations */
#include <lin/core/operations/matrix_operations.hpp>

TEST(CoreOperationsMatrixOperations, Trace) {
  lin::Matrix3x3f A {
    2.0f,  5.0f, 6.0f,
    1.0f,  4.0f, 3.0f,
    0.0f, -7.0f, -1.0f
  };
  ASSERT_FLOAT_EQ(5.0f, lin::trace(A));
}
/* END: From amtrix operations */

TEST(CoreOperationsTensorOperations, Add) {
  lin::Vector2f a {1.0f, 2.0f};
  lin::Vector2f b {1.0f, 3.0f};

  lin::Vector2f c = lin::add(a, b);
  ASSERT_FLOAT_EQ(2.0f, c(0));
  ASSERT_FLOAT_EQ(5.0f, c(1));

  lin::Vector2f d = lin::add(a, 1.0f);
  ASSERT_FLOAT_EQ(2.0f, d(0));
  ASSERT_FLOAT_EQ(3.0f, d(1));

  lin::Vector2d e = lin::add(-2.0, b);
  ASSERT_DOUBLE_EQ(-1.0, e(0));
  ASSERT_DOUBLE_EQ( 1.0, e(1));

  ASSERT_DOUBLE_EQ(5.0, lin::add(2.0, 3.0));
}

TEST(CoreOperationsTensorOperations, Cast) {
  lin::Vector2f a {1.0f, 2.0f};
  static_assert(std::is_same<double, decltype(lin::cast<double>(a)(0))>::value, "");
  ASSERT_DOUBLE_EQ(1.0, lin::cast<double>(a)(0));
  ASSERT_DOUBLE_EQ(2.0, lin::cast<double>(a)(1));

  double b = 2.0;
  static_assert(std::is_same<float, decltype(lin::cast<float>(b))>::value, "");
  ASSERT_FLOAT_EQ(2.0f, lin::cast<float>(b));
}

TEST(CoreOperationsTensorOperations, Divide) {
  lin::Vectorf<0, 3> a(2, {12.0f, 9.0f});
  lin::Vectorf<0, 3> b(2, { 2.0f, 3.0f});

  lin::Vectorf<0, 3> c(2); c = lin::divide(a, b);
  ASSERT_FLOAT_EQ(6.0f, c(0));
  ASSERT_FLOAT_EQ(3.0f, c(1));

  lin::Vectorf<0, 3> d(2); d = lin::divide(a, 6.0f);
  ASSERT_FLOAT_EQ(2.0f, d(0));
  ASSERT_FLOAT_EQ(1.5f, d(1));

  lin::Vectord<0, 3> e(2); e = lin::divide(6.0, b);
  ASSERT_DOUBLE_EQ(3.0, e(0));
  ASSERT_DOUBLE_EQ(2.0, e(1));

  ASSERT_DOUBLE_EQ(5.0, lin::divide(25.0, 5.0));
}

TEST(CoreOperationsTensorOperations, Fro) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(14.0f, lin::fro(A));

  lin::Matrixf<0, 0, 4, 4> B(3, 2, {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
  ASSERT_FLOAT_EQ(55.0f, lin::fro(B));
}

TEST(CoreOperationsTensorOperations, Multiply) {
  lin::Vector2f a {1.0f, 2.0f};
  lin::Vector2f b {1.0f, 3.0f};

  lin::Vector2f c = lin::multiply(a, b);
  ASSERT_FLOAT_EQ(1.0f, c(0));
  ASSERT_FLOAT_EQ(6.0f, c(1));

  lin::Vector2f d = lin::multiply(a, 2.0f);
  ASSERT_FLOAT_EQ(2.0f, d(0));
  ASSERT_FLOAT_EQ(4.0f, d(1));

  lin::Vector2d e = lin::multiply(-2.0, b);
  ASSERT_DOUBLE_EQ(-2.0, e(0));
  ASSERT_DOUBLE_EQ(-6.0, e(1));

  ASSERT_DOUBLE_EQ(6.0, lin::multiply(2.0, 3.0));
}

TEST(CoreOperationsTensorOperations, Negate) {
  lin::Matrixf<0, 0, 3, 3> A(2, 2, {
    1.0f, 2.0f,
    -1.0f, 3.0f
  });
  lin::Matrixf<0, 0, 3, 3> B(2, 2); B = lin::negate(A);
  ASSERT_FLOAT_EQ(-1.0f, B(0, 0));
  ASSERT_FLOAT_EQ(-2.0f, B(0, 1));
  ASSERT_FLOAT_EQ( 1.0f, B(1, 0));
  ASSERT_FLOAT_EQ(-3.0f, B(1, 1));

  ASSERT_DOUBLE_EQ(-1.0, lin::negate(1.0));
}

TEST(CoreOperationsTensorOperations, Sign) {
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

  ASSERT_DOUBLE_EQ(1.0, lin::sign(0.1));
  ASSERT_DOUBLE_EQ(0.0, lin::sign(0.0));
}

TEST(CoreOperationsTensorOperations, Square) {
  lin::Matrix2x3f A({
    0.0f, 0.2f, -100.0f,
    3.0f, -1.0f, -20.0f
  });
  auto sign_A = lin::square(A);
  static_assert(lin::internal::have_same_traits<decltype(A), decltype(sign_A)>::value, "");
  ASSERT_EQ(2, sign_A.rows());
  ASSERT_EQ(3, sign_A.cols());
  ASSERT_EQ(6, sign_A.size());
  ASSERT_FLOAT_EQ(    0.0f, sign_A(0, 0));
  ASSERT_FLOAT_EQ(   0.04f, sign_A(0, 1));
  ASSERT_FLOAT_EQ(10000.0f, sign_A(0, 2));
  ASSERT_FLOAT_EQ(    9.0f, sign_A(1, 0));
  ASSERT_FLOAT_EQ(    1.0f, sign_A(1, 1));
  ASSERT_FLOAT_EQ(  400.0f, sign_A(1, 2));

  ASSERT_DOUBLE_EQ(0.01, lin::square(0.1));
  ASSERT_DOUBLE_EQ( 0.0, lin::square(0.0));
}

TEST(CoreOperationsTensorOperations, Subtract) {
  lin::Vector2f a {1.0f, 2.0f};
  lin::Vector2f b {1.0f, 3.0f};

  lin::Vector2f c = lin::subtract(a, b);
  ASSERT_FLOAT_EQ( 0.0f, c(0));
  ASSERT_FLOAT_EQ(-1.0f, c(1));

  lin::Vector2f d = lin::subtract(a, 2.0f);
  ASSERT_FLOAT_EQ(-1.0f, d(0));
  ASSERT_FLOAT_EQ( 0.0f, d(1));

  lin::Vector2d e = lin::subtract(-2.0, b);
  ASSERT_DOUBLE_EQ(-3.0, e(0));
  ASSERT_DOUBLE_EQ(-5.0, e(1));

  ASSERT_DOUBLE_EQ(-1.0, lin::subtract(2.0, 3.0));
}

TEST(CoreOperationsTensorOperations, Sum) {
  lin::Matrix2x2f A {
     1.0f, 2.0f,
    -1.0f, 0.0f
  };
  ASSERT_FLOAT_EQ(2.0f, lin::sum(A));
}

TEST(CoreOperationsTensorOperations, Transpose) {
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
