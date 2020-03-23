/** @file test/generators/constants_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/generators/constants.hpp>

#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>

TEST(GeneratorsConstants, Consts) {
  auto const A = lin::consts<lin::Vector3f>(2.0f);
  static_assert(lin::internal::have_same_traits<typename std::remove_cv<decltype(A)>::type,
      lin::Vector3f>::value, "");
  ASSERT_EQ(3, A.rows());
  ASSERT_EQ(1, A.cols());
  ASSERT_EQ(3, A.size());
  for (size_t i = 0; i < 3; i++) ASSERT_FLOAT_EQ(2.0f, A(i));

  auto const B = lin::consts<float, 0, 5, 5, 5>(1.0f, 3, 5);
  static_assert(lin::internal::have_same_traits<typename std::remove_cv<decltype(B)>::type,
      lin::Matrixf<0, 5, 5, 5>>::value, "");
  ASSERT_EQ( 3, B.rows());
  ASSERT_EQ( 5, B.cols());
  ASSERT_EQ(15, B.size());
  for (size_t i = 0; i < A.rows(); i++)
    for (size_t j = 0; j < A.cols(); j++) ASSERT_FLOAT_EQ(1.0f, B(i, j));
}

TEST(GeneratorsConstants, Ones) {
  auto const A = lin::ones<double, 0, 0, 6, 6>();
  static_assert(lin::internal::have_same_traits<typename std::remove_cv<decltype(A)>::type,
      lin::Matrixd<0, 0, 6, 6>>::value, "");
  ASSERT_EQ( 6, A.rows());
  ASSERT_EQ( 6, A.cols());
  ASSERT_EQ(36, A.size());
  for (size_t i = 0; i < A.rows(); i++)
    for (size_t j = 0; j < A.cols(); j++) ASSERT_DOUBLE_EQ(1.0, A(i, j));
}

TEST(GeneratorsConstants, Zeros) {
  auto const A = lin::zeros<lin::Matrixd<5, 5>>();
  static_assert(lin::internal::have_same_traits<typename std::remove_cv<decltype(A)>::type,
      lin::Matrixd<5, 5>>::value, "");
  ASSERT_EQ( 5, A.rows());
  ASSERT_EQ( 5, A.cols());
  ASSERT_EQ(25, A.size());
  for (size_t i = 0; i < A.rows(); i++)
    for (size_t j = 0; j < A.cols(); j++) ASSERT_DOUBLE_EQ(0.0, A(i, j));
}

TEST(GeneratorsConstants, Nans) {
  auto const A = lin::nans<lin::Matrixd<5, 5>>();
  static_assert(lin::internal::have_same_traits<typename std::remove_cv<decltype(A)>::type,
      lin::Matrixd<5, 5>>::value, "");
  ASSERT_EQ( 5, A.rows());
  ASSERT_EQ( 5, A.cols());
  ASSERT_EQ(25, A.size());
  for (size_t i = 0; i < A.rows(); i++)
    for (size_t j = 0; j < A.cols(); j++) ASSERT_TRUE(std::isnan(A(i, j)));
}
