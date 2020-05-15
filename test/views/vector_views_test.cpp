// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

#include <lin/core.hpp>
#include <lin/views/vector_view.hpp>

#include <gtest/gtest.h>

TEST(VectorViews, FixedSizeVectorView) {
  float buf[3];

  buf[0] = 1.0f;
  buf[1] = 2.0f;
  buf[2] = 3.0f;
  lin::VectorView3f a(buf);

  // Check traits are correct
  static_assert(lin::internal::have_same_traits<lin::Vector3f, lin::VectorView3f>::value, "");

  // Check dimesnions
  ASSERT_EQ(a.rows(), 3);
  ASSERT_EQ(a.cols(), 1);

  // Check elements are correct
  ASSERT_FLOAT_EQ(a(0), 1.0f);
  ASSERT_FLOAT_EQ(a(1), 2.0f);
  ASSERT_FLOAT_EQ(a(2), 3.0f);

  // Test changes are reflected in the original buffer
  a(1) = 4.0f;
  ASSERT_FLOAT_EQ(buf[1], 4.0f);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}

TEST(VectorViews, FixedSizeRowVectorView) {
  float buf[3];

  buf[0] = 1.0f;
  buf[1] = 2.0f;
  buf[2] = 3.0f;
  lin::RowVectorView3f a(buf);

  // Check traits are correct
  static_assert(lin::internal::have_same_traits<lin::RowVector3f, lin::RowVectorView3f>::value, "");

  // Check dimesnions
  ASSERT_EQ(a.rows(), 1);
  ASSERT_EQ(a.cols(), 3);

  // Check elements are correct
  ASSERT_FLOAT_EQ(a(0), 1.0f);
  ASSERT_FLOAT_EQ(a(1), 2.0f);
  ASSERT_FLOAT_EQ(a(2), 3.0f);

  // Test changes are reflected in the original buffer
  a(1) = 4.0f;
  ASSERT_FLOAT_EQ(buf[1], 4.0f);
}

TEST(VectorViews, VariableSizeVectorView) {
  double buf[6];

  buf[0] = 1.0;
  buf[1] = 2.0;
  buf[2] = 3.0;
  buf[3] = 4.0;
  lin::VectorViewd<0, 6> a(buf, 4);

  // Check traits are correct
  static_assert(lin::internal::have_same_traits<lin::Vectord<0, 6>, lin::VectorViewd<0, 6>>::value, "");

  // Check dimesnions
  ASSERT_EQ(a.rows(), 4);
  ASSERT_EQ(a.cols(), 1);

  // Check elements are correct
  ASSERT_DOUBLE_EQ(a(0), 1.0);
  ASSERT_DOUBLE_EQ(a(1), 2.0);
  ASSERT_DOUBLE_EQ(a(2), 3.0);
  ASSERT_DOUBLE_EQ(a(3), 4.0);

  // Test changes are reflected in the original buffer
  a(1) = 4.0;
  ASSERT_DOUBLE_EQ(buf[1], 4.0);

  // Test resize
  a.resize(6);
  a(5) = 10.0;
  ASSERT_EQ(a.rows(), 6);
  ASSERT_DOUBLE_EQ(buf[5], 10.0);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}

TEST(VectorViews, VariableSizeRowVectorView) {
  double buf[6];

  buf[0] = 1.0;
  buf[1] = 2.0;
  lin::RowVectorViewd<0, 6> a(buf, 2);

  // Check traits are correct
  static_assert(lin::internal::have_same_traits<lin::RowVectord<0, 6>, lin::RowVectorViewd<0, 6>>::value, "");

  // Check dimesnions
  ASSERT_EQ(a.rows(), 1);
  ASSERT_EQ(a.cols(), 2);

  // Check elements are correct
  ASSERT_DOUBLE_EQ(a(0), 1.0);
  ASSERT_DOUBLE_EQ(a(1), 2.0);

  // Test changes are reflected in the original buffer
  a(1) = 4.0;
  ASSERT_DOUBLE_EQ(buf[1], 4.0);

  // Test resize
  a.resize(5);
  a(4) = 10.0;
  ASSERT_EQ(a.cols(), 5);
  ASSERT_DOUBLE_EQ(buf[4], 10.0);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}
