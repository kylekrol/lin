// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

#include <lin/core.hpp>
#include <lin/views/matrix_view.hpp>

#include <gtest/gtest.h>

TEST(MatrixViews, FixedSizeMatrixView) {
  float buf[9] = {
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  };

  lin::MatrixView3x3f A(buf);
  static_assert(lin::internal::have_same_traits<lin::MatrixView3x3f, lin::Matrix3x3f>::value, "");

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

TEST(MatrixViews, VariableSizeMatrixView) {
  float buf[9] = {
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  };

  lin::MatrixViewf<0, 0, 3, 3> A(buf, 2, 2);
  static_assert(lin::internal::have_same_traits<lin::Matrixf<0, 0, 3, 3>, lin::MatrixViewf<0, 0, 3, 3>>::value, "");

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
