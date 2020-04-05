/** @file test/core/types_vector_test.cpp
 *  @author Kyle Krol */

// TODO : Test the stream constructor

#include <lin/core/types/vector.hpp>

#include <gtest/gtest.h>

// Check for constexpr vector dimensions and zero initialization
constexpr static lin::Vector3f u;
static_assert(u.rows() == 3, "");
static_assert(u.cols() == 1, "");
static_assert(u.size() == 3, "");
static_assert(u(0) == 0.0f, "");
static_assert(u(1) == 0.0f, "");
static_assert(u(2) == 0.0f, "");

// Check for constexpr row vector dimensions and zero initialization
constexpr static lin::RowVector3f v;
static_assert(v.rows() == 1, "");
static_assert(v.cols() == 3, "");
static_assert(v.size() == 3, "");
static_assert(v(0) == 0.0f, "");
static_assert(v(1) == 0.0f, "");
static_assert(v(2) == 0.0f, "");

TEST(CoreTypesVector, VectorDimensions) {
  lin::Vectorf<5> u;
  ASSERT_EQ(5, u.rows());
  ASSERT_EQ(1, u.cols());
  ASSERT_EQ(5, u.size());

  lin::Vectord<0, 9> v(7);
  ASSERT_EQ(7, v.rows());
  ASSERT_EQ(1, v.cols());
  ASSERT_EQ(7, v.size());
}

TEST(CoreTypesVector, RowVectorDimensions) {
  lin::RowVectord<8> u;
  ASSERT_EQ(1, u.rows());
  ASSERT_EQ(8, u.cols());
  ASSERT_EQ(8, u.size());

  lin::RowVectorf<0, 3> v(2);
  ASSERT_EQ(1, v.rows());
  ASSERT_EQ(2, v.cols());
  ASSERT_EQ(2, v.size());
}

TEST(CoreTypesVector, VectorResize) {
  lin::Vectorf<0, 5> u;
  ASSERT_EQ(5, u.rows());
  ASSERT_EQ(1, u.cols());
  ASSERT_EQ(5, u.size());

  u.resize(4);
  ASSERT_EQ(4, u.rows());
  ASSERT_EQ(1, u.cols());
  ASSERT_EQ(4, u.size());

  u.resize(3, 1);
  ASSERT_EQ(3, u.rows());
  ASSERT_EQ(1, u.cols());
  ASSERT_EQ(3, u.size());
}

TEST(CoreTypesVector, RowVectorResize) {
  lin::RowVectorf<0, 5> u;
  ASSERT_EQ(1, u.rows());
  ASSERT_EQ(5, u.cols());
  ASSERT_EQ(5, u.size());

  u.resize(4);
  ASSERT_EQ(1, u.rows());
  ASSERT_EQ(4, u.cols());
  ASSERT_EQ(4, u.size());

  u.resize(3);
  ASSERT_EQ(1, u.rows());
  ASSERT_EQ(3, u.cols());
  ASSERT_EQ(3, u.size());
}

TEST(CoreTypesVector, VectorResSizeConstructor) {
  lin::Vectorf<0, 5> u(4);
  ASSERT_EQ(4, u.rows());
  ASSERT_EQ(1, u.cols());
  ASSERT_EQ(4, u.size());
}

TEST(CoreTypesVector, RowVectorResizeConstructor) {
  lin::RowVectorf<0, 5> u(4);
  ASSERT_EQ(1, u.rows());
  ASSERT_EQ(4, u.cols());
  ASSERT_EQ(4, u.size());
}

TEST(CoreTypesVector, VectorListConstructor) {
  lin::Vector3f u({0.0f, 1.0f, 2.0f});
  ASSERT_FLOAT_EQ(0.0f, u(0));
  ASSERT_FLOAT_EQ(1.0f, u(1));
  ASSERT_FLOAT_EQ(2.0f, u(2));
}

TEST(CoreTypesVector, RowVectorListConstructor) {
  lin::RowVector4f u({0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(0.0f, u(0));
  ASSERT_FLOAT_EQ(1.0f, u(1));
  ASSERT_FLOAT_EQ(2.0f, u(2));
  ASSERT_FLOAT_EQ(3.0f, u(3));
}

TEST(CoreTypesVector, VectorResizeListConstructor) {
  lin::Vectorf<0, 5> u(2, {0.0f, 1.0f});
  ASSERT_EQ(2, u.rows());
  ASSERT_EQ(1, u.cols());
  ASSERT_EQ(2, u.size());
  ASSERT_FLOAT_EQ(0.0f, u(0));
  ASSERT_FLOAT_EQ(1.0f, u(1));
}

TEST(CoreTypesVector, RowVectorResizeListConstructor) {
  lin::RowVectorf<0, 5> u(2, {0.0f, 1.0f});
  ASSERT_EQ(1, u.rows());
  ASSERT_EQ(2, u.cols());
  ASSERT_EQ(2, u.size());
  ASSERT_FLOAT_EQ(0.0f, u(0));
  ASSERT_FLOAT_EQ(1.0f, u(1));
}
