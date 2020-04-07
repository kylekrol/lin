/** @file test/factorizations/chol_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/factorizations/chol.hpp>
#include <lin/generators/randoms.hpp>

#include <gtest/gtest.h>

template <typename T, size_t N, size_t MN>
static void make_L(lin::Matrix<T, N, N, MN, MN> &L) {
  ASSERT_EQ(L.rows(), L.cols());
  for (size_t i = 0; i < L.rows(); i++)
    for (size_t j = i + 1; j < L.cols(); j++)
      L(i, j) = 0;
}

TEST(FactorizationsChol, FixedSizeChol) {
  lin::internal::RandomsGenerator const rand;
  lin::Matrix4x4f A, L, M;
  for (size_t i = 0; i < 20; i++) {
    M = lin::rands<lin::Matrix4x4f>(4, 4, rand);
    make_L(M);
    A = M * lin::transpose(M);
    lin::chol(A, L);
    ASSERT_NEAR(0.0f, lin::fro(M - L), M.size() * 1e-5);
  }
}
