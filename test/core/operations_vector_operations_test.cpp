/** @file test/core/operations/vector_operations_test.cpp
 *  @author Kyle Krol */

#include <lin/core/operations/vector_operations.hpp>
#include <lin/core/types/vector.hpp>

#include <gtest/gtest.h>

TEST(CoreOperationsVectorOperations, Cross) {
  lin::Vector3f u({1.0f, 2.0f, 3.0f}), v({2.0f, 1.0f, 3.0f}), w = lin::cross(u, v);
  ASSERT_FLOAT_EQ( 3.0f, w(0));
  ASSERT_FLOAT_EQ( 3.0f, w(1));
  ASSERT_FLOAT_EQ(-3.0f, w(2));

  u = {1.0f, 3.0f, 1.0f};
  v = {2.0f, 1.0f, 3.0f};
  w = lin::cross(u, v);
  ASSERT_FLOAT_EQ( 8.0f, w(0));
  ASSERT_FLOAT_EQ(-1.0f, w(1));
  ASSERT_FLOAT_EQ(-5.0f, w(2));
}

TEST(CoreOperationsVectorOperations, Dot) {
  lin::Vector3f u({1.0f, 2.0f, 3.0f}), v({2.0f, 1.0f, 3.0f});
  ASSERT_FLOAT_EQ(13.0f, lin::dot(u, v));

  u = {1.0f, 3.0f, 1.0f};
  v = {2.0f, 1.0f, 3.0f};
  ASSERT_FLOAT_EQ(8.0f, lin::dot(u, v));
}

TEST(CoreOperationsVectorOperations, Norm) {
  lin::Vector3f u({1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(3.741657f, lin::norm(u));
}
