// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

#include <lin/core.hpp>
#include <lin/views.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(MatrixViews, FixedSizeMatrixView) {
  float buf[9] = {
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  };

  auto A = lin::view<lin::Matrix3x3f>(buf);
  static_assert(std::is_same<decltype(A), lin::internal::MatrixView<float, 3, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(A), lin::Matrix3x3f>::value, "");

  ASSERT_EQ(A.rows(), 3);
  ASSERT_EQ(A.cols(), 3);

  ASSERT_FLOAT_EQ(A(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(A(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(A(0, 2), 3.0f);
  ASSERT_FLOAT_EQ(A(1, 0), 4.0f);
  ASSERT_FLOAT_EQ(A(1, 1), 5.0f);
  ASSERT_FLOAT_EQ(A(1, 2), 6.0f);
  ASSERT_FLOAT_EQ(A(2, 0), 7.0f);
  ASSERT_FLOAT_EQ(A(2, 1), 8.0f);
  ASSERT_FLOAT_EQ(A(2, 2), 9.0f);

  A(1, 1) = 10.0f;
  ASSERT_FLOAT_EQ(buf[4], 10.0f);

  ASSERT_EQ(A.data(), buf);
}

TEST(MatrixViews, FixedSizeConstMatrixView) {
  float const buf[9] = {
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  };

  auto A = lin::view<lin::Matrix3x3f>(buf);
  static_assert(std::is_same<decltype(A), lin::internal::ConstMatrixView<float, 3, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(A), lin::Matrix3x3f>::value, "");

  ASSERT_EQ(A.rows(), 3);
  ASSERT_EQ(A.cols(), 3);

  ASSERT_FLOAT_EQ(A(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(A(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(A(0, 2), 3.0f);
  ASSERT_FLOAT_EQ(A(1, 0), 4.0f);
  ASSERT_FLOAT_EQ(A(1, 1), 5.0f);
  ASSERT_FLOAT_EQ(A(1, 2), 6.0f);
  ASSERT_FLOAT_EQ(A(2, 0), 7.0f);
  ASSERT_FLOAT_EQ(A(2, 1), 8.0f);
  ASSERT_FLOAT_EQ(A(2, 2), 9.0f);

  // Test the correct buffer is returned
  ASSERT_EQ(A.data(), buf);
}

TEST(MatrixViews, VariableSizeMatrixView) {
  float buf[9] = {
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  };

  auto A = lin::view<lin::Matrixf<0, 0, 3, 3>>(buf, 2, 2);
  static_assert(std::is_same<decltype(A), lin::internal::MatrixView<float, 0, 0, 3, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(A), lin::Matrixf<0, 0, 3, 3>>::value, "");

  ASSERT_EQ(A.rows(), 2);
  ASSERT_EQ(A.cols(), 2);

  ASSERT_FLOAT_EQ(A(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(A(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(A(1, 0), 3.0f);
  ASSERT_FLOAT_EQ(A(1, 1), 4.0f);

  A(1, 1) = 10.0f;
  ASSERT_FLOAT_EQ(buf[3], 10.0f);

  A.resize(3, 2);
  ASSERT_EQ(A.rows(), 3);
  ASSERT_EQ(A.cols(), 2);

  A(2, 1) = 20.0f;
  ASSERT_FLOAT_EQ(buf[5], 20.0f);

  ASSERT_EQ(A.data(), buf);
}

TEST(MatrixViews, VariableSizeConstMatrixView) {
  float const buf[9] = {
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  };

  auto A = lin::view<lin::Matrixf<0, 0, 3, 3>>(buf, 2, 2);
  static_assert(std::is_same<decltype(A), lin::internal::ConstMatrixView<float, 0, 0, 3, 3>>::value, "");
  static_assert(lin::internal::have_same_traits<decltype(A), lin::Matrixf<0, 0, 3, 3>>::value, "");

  ASSERT_EQ(A.rows(), 2);
  ASSERT_EQ(A.cols(), 2);

  ASSERT_FLOAT_EQ(A(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(A(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(A(1, 0), 3.0f);
  ASSERT_FLOAT_EQ(A(1, 1), 4.0f);

  A.resize(3, 2);
  ASSERT_EQ(A.rows(), 3);
  ASSERT_EQ(A.cols(), 2);

  ASSERT_FLOAT_EQ(A(0, 0), 1.0f);
  ASSERT_FLOAT_EQ(A(0, 1), 2.0f);
  ASSERT_FLOAT_EQ(A(1, 0), 3.0f);
  ASSERT_FLOAT_EQ(A(1, 1), 4.0f);
  ASSERT_FLOAT_EQ(A(2, 0), 5.0f);
  ASSERT_FLOAT_EQ(A(2, 1), 6.0f);

  // Test the correct buffer is returned
  ASSERT_EQ(A.data(), buf);
}
