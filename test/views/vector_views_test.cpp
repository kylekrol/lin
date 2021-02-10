// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

#include <lin/core.hpp>
#include <lin/views.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(VectorViews, FixedSizeVectorView) {
  float buf[3] = {1.0f, 2.0f, 3.0f};

  auto a = lin::view<lin::Vector3f>(buf);
  static_assert(std::is_same<decltype(a), lin::internal::VectorView<float, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::Vector3f>::value, "");

  // Check dimensions
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

TEST(VectorViews, FixedSizeConstVectorView) {
  float const buf[3] = {1.0f, 2.0f, 3.0f};

  auto a = lin::view<lin::Vector3f>(buf);
  static_assert(std::is_same<decltype(a), lin::internal::ConstVectorView<float, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::Vector3f>::value, "");

  // Check dimensions
  ASSERT_EQ(a.rows(), 3);
  ASSERT_EQ(a.cols(), 1);

  // Check elements are correct
  ASSERT_FLOAT_EQ(a(0), 1.0f);
  ASSERT_FLOAT_EQ(a(1), 2.0f);
  ASSERT_FLOAT_EQ(a(2), 3.0f);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}

TEST(VectorViews, FixedSizeRowVectorView) {
  float buf[3] = {1.0f, 2.0f, 3.0f};

  auto a = lin::view<lin::RowVector3f>(buf);
  static_assert(std::is_same<decltype(a), lin::internal::RowVectorView<float, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::RowVector3f>::value, "");

  // Check dimensions
  ASSERT_EQ(a.rows(), 1);
  ASSERT_EQ(a.cols(), 3);

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

TEST(VectorViews, FixedSizeConstRowVectorView) {
  float const buf[3] = {1.0f, 2.0f, 3.0f};

  auto a = lin::view<lin::RowVector3f>(buf);
  static_assert(std::is_same<decltype(a), lin::internal::ConstRowVectorView<float, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::RowVector3f>::value, "");

  // Check dimensions
  ASSERT_EQ(a.rows(), 1);
  ASSERT_EQ(a.cols(), 3);

  // Check elements are correct
  ASSERT_FLOAT_EQ(a(0), 1.0f);
  ASSERT_FLOAT_EQ(a(1), 2.0f);
  ASSERT_FLOAT_EQ(a(2), 3.0f);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}

TEST(VectorViews, VariableSizeVectorView) {
  double buf[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  auto a = lin::view<lin::Vectord<0, 6>>(buf, 4);
  static_assert(std::is_same<decltype(a), lin::internal::VectorView<double, 0, 6>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::Vectord<0, 6>>::value, "");

  // Check dimensions
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

TEST(VectorViews, VariableSizeConstVectorView) {
  double const buf[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  auto a = lin::view<lin::Vectord<0, 6>>(buf, 4);
  static_assert(std::is_same<decltype(a), lin::internal::ConstVectorView<double, 0, 6>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::Vectord<0, 6>>::value, "");

  // Check dimensions
  ASSERT_EQ(a.rows(), 4);
  ASSERT_EQ(a.cols(), 1);

  // Check elements are correct
  ASSERT_DOUBLE_EQ(a(0), 1.0);
  ASSERT_DOUBLE_EQ(a(1), 2.0);
  ASSERT_DOUBLE_EQ(a(2), 3.0);
  ASSERT_DOUBLE_EQ(a(3), 4.0);

  // Test resize
  a.resize(6);
  ASSERT_EQ(a.rows(), 6);
  ASSERT_DOUBLE_EQ(buf[5], 6.0);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}

TEST(VectorViews, VariableSizeRowVectorView) {
  double buf[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  auto a = lin::view<lin::RowVectord<0, 6>>(buf, 2);
  static_assert(std::is_same<decltype(a), lin::internal::RowVectorView<double, 0, 6>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::RowVectord<0, 6>>::value, "");

  // Check dimensions
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

TEST(VectorViews, VariableSizeConstRowVectorView) {
  double const buf[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  auto a = lin::view<lin::RowVectord<0, 6>>(buf, 2);
  static_assert(std::is_same<decltype(a), lin::internal::ConstRowVectorView<double, 0, 6>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(a), lin::RowVectord<0, 6>>::value, "");

  // Check dimensions
  ASSERT_EQ(a.rows(), 1);
  ASSERT_EQ(a.cols(), 2);

  // Check elements are correct
  ASSERT_DOUBLE_EQ(a(0), 1.0);
  ASSERT_DOUBLE_EQ(a(1), 2.0);

  // Test resize
  a.resize(5);
  ASSERT_EQ(a.cols(), 5);
  ASSERT_DOUBLE_EQ(buf[4], 5.0);

  // Test the correct buffer is returned
  ASSERT_EQ(a.data(), buf);
}
