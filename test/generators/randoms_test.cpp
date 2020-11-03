/** @file test/generators/randoms_test.cpp
 *  @author Kyle Krol */
#define LIN_DESKTOP
#include <lin/core.hpp>
#include <lin/generators/randoms.hpp>

#include <gtest/gtest.h>

#include <type_traits>
#include <iostream>

TEST(GeneratorsRandoms, RandomsGenerator) {
  lin::internal::RandomsGenerator rand;
  for (lin::size_t i = 0; i < 10000; i++) {
    double x = rand.next();
    ASSERT_LE(x, 1.0);
    ASSERT_GT(x, 0.0);
  }
}

TEST(GeneratorsRandoms, GaussianRandomsGenerator) {
  lin::internal::RandomsGenerator rand;
  double mean = 0.0L;
  double std = 0.0L;
  uint N = 10000000;
  for (lin::size_t i = 0; i < N; i++) {
    double x = rand.gaussian();
    mean += x;
    std += x*x;
  }
  std = sqrt(std/N);
  mean = mean/N;

  ASSERT_LE(mean,0.01);
  ASSERT_GT(mean,-0.01);

  ASSERT_LE(std,1.01);
  ASSERT_GT(std,0.99);
}

TEST(GeneratorsRandoms, Rands) {
  lin::internal::RandomsGenerator rand;
  auto const A = lin::rands<lin::Matrixd<0, 3, 5, 3>>(rand, 4, 3);
  static_assert(std::is_same<std::remove_cv_t<decltype(A)>, lin::Matrixd<0, 3, 5, 3>>::value, "");
  ASSERT_EQ( 4, A.rows());
  ASSERT_EQ( 3, A.cols());
  ASSERT_EQ(12, A.size());
}

TEST(GeneratorRandoms, GaussianRandsShape){
  lin::internal::RandomsGenerator rand;
  auto const A = lin::gaussian_rands<lin::Matrixd<0, 3, 5, 3>>(rand, 4, 3);
  static_assert(std::is_same<std::remove_cv_t<decltype(A)>, lin::Matrixd<0, 3, 5, 3>>::value, "");
  ASSERT_EQ( 4, A.rows());
  ASSERT_EQ( 3, A.cols());
  ASSERT_EQ(12, A.size());
}

TEST(GeneratorsRandoms, GaussianRands){
  lin::internal::RandomsGenerator rand;
  double mean = 0.0;
  double std = 0.0;
  uint L = 100000;
  uint N = L*15;
  for(uint j = 0; j<L;j++){
    auto const A = lin::gaussian_rands<lin::Matrixd<3,5>>(rand, 3, 5);
    // std::cout << A;
    for(lin::size_t i = 0; i < A.size(); i++){
      mean += A(i);
      std += A(i)*A(i);
    }
  }

  std = sqrt(std/N);
  mean = mean/N;

  ASSERT_LE(mean,0.01);
  ASSERT_GT(mean,-0.01);

  ASSERT_LE(std,1.01);
  ASSERT_GT(std,0.99);
}