/** @file test/generators/randoms_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/generators/randoms.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(GeneratorsRandoms, RandomsGenerator) {
  lin::internal::RandomsGenerator const rand;
  for (lin::size_t i = 0; i < 10000; i++) {
    double x = rand.next();
    ASSERT_LE(x, 1.0);
    ASSERT_GT(x, 0.0);
  }
}

TEST(GeneratorsRandoms, Rands) {
  lin::internal::RandomsGenerator const rand;
  auto const A = lin::rands<lin::Matrixd<0, 3, 5, 3>>(4, 3, rand);
  static_assert(std::is_same<std::remove_cv_t<decltype(A)>, lin::Matrixd<0, 3, 5, 3>>::value, "");
  ASSERT_EQ( 4, A.rows());
  ASSERT_EQ( 3, A.cols());
  ASSERT_EQ(12, A.size());
}
