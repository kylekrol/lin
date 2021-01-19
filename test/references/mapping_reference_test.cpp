/** @file test/references/mapping_reference_test.cpp
 *  @author Kyle Krol
 */

#include <lin/core.hpp>
#include <lin/references.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(MappingReference, MatrixMappingReference) {
  lin::Matrix3x3f A = {
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f,
    6.0f, 7.0f, 8.0f
  };
  lin::Matrix2x2f B = {
    3.0f, 4.0f,
    6.0f, 7.0f
  };

  auto C = lin::ref<lin::Matrix2x2f>(A, 1, 0);
  static_assert(lin::internal::have_same_traits<decltype(C), lin::Matrix2x2f>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(B - C));
  ASSERT_EQ(2, C.rows());
  ASSERT_EQ(2, C.cols());

  lin::Matrixf<0, 0, 5, 5> D(2, 3);
  D = {
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f
  };
  lin::Matrixf<0, 0, 5, 5> E(2, 2);
  E = {
    1.0f, 2.0f,
    4.0f, 5.0f
  };

  auto F = lin::ref<lin::Matrixf<0, 0, 5, 5>>(D, 0, 1, 2, 2);
  static_assert(lin::internal::have_same_traits<decltype(F), lin::Matrixf<0, 0, 5, 5>>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(E - F));
  ASSERT_EQ(2, F.rows());
  ASSERT_EQ(2, F.cols());

  F(0, 0) = 10.0f;
  ASSERT_FLOAT_EQ(10.0f, D(0, 1));
}

TEST(MappingReference, VectorMappingReference) {
  lin::Matrix3x3f A = {
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f,
    6.0f, 7.0f, 8.0f
  };
  lin::Vector3f a = {
    1.0f,
    4.0f,
    7.0f
  };

  auto b = lin::ref<lin::Vector3f>(A, 0, 1);
  static_assert(lin::internal::have_same_traits<decltype(b), lin::Vector3f>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(a - b));
  ASSERT_EQ(3, b.rows());
  ASSERT_EQ(1, b.cols());

  lin::Vectorf<0, 3> c(2);
  c = {
    4.0f,
    7.0f
  };

  auto d = lin::ref<lin::Vectorf<0, 3>>(A, 1, 1, 2);
  static_assert(lin::internal::have_same_traits<decltype(d), lin::Vectorf<0, 3>>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(c - d));
  ASSERT_EQ(2, d.rows());
  ASSERT_EQ(1, d.cols());

  d(0) = 10.0f;
  ASSERT_FLOAT_EQ(10.0f, A(1, 1));
}

TEST(MappingReference, RowVectorMappingReference) {
  lin::Matrix3x3f A = {
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f,
    6.0f, 7.0f, 8.0f
  };
  lin::RowVector3f a = {
    3.0f, 4.0f, 5.0f
  };

  auto b = lin::ref<lin::RowVector3f>(A, 1, 0);
  static_assert(lin::internal::have_same_traits<decltype(b), lin::RowVector3f>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(a - b));
  ASSERT_EQ(1, b.rows());
  ASSERT_EQ(3, b.cols());

  lin::RowVectorf<0, 3> c(2);
  c = {
    7.0f, 8.0f
  };

  auto d = lin::ref<lin::RowVectorf<0, 3>>(A, 2, 1, 2);
  static_assert(lin::internal::have_same_traits<decltype(d), lin::RowVectorf<0, 3>>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(c - d));
  ASSERT_EQ(1, d.rows());
  ASSERT_EQ(2, d.cols());

  d(1) = 10.0f;
  ASSERT_FLOAT_EQ(10.0f, A(2, 2));
}

TEST(MappingReference, DiagonalMappingReference) {
  lin::Matrix3x3f A = {
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f,
    6.0f, 7.0f, 8.0f
  };
  lin::Vector3f a = {
    0.0f,
    4.0f,
    8.0f
  };

  auto b = lin::diag(A);
  static_assert(lin::internal::have_same_traits<decltype(b), lin::Vector3f>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(a - b));
  ASSERT_EQ(3, b.rows());
  ASSERT_EQ(1, b.cols());

  lin::Matrixf<0, 0, 5, 5> B(2, 2, {
    0.0f, 1.0f,
    2.0f, 3.0f
  });
  lin::Vectorf<0, 5> c(2, {
    0.0f,
    3.0f
  });

  auto d = lin::diag(B);
  static_assert(lin::internal::have_same_traits<decltype(d), lin::Vectorf<0, 5>>::value, "");
  ASSERT_FLOAT_EQ(0.0f, lin::fro(c - d));
  ASSERT_EQ(2, d.rows());
  ASSERT_EQ(1, d.cols());

  d(1) = 4.0f;
  ASSERT_FLOAT_EQ(4.0f, B(1, 1));
}
