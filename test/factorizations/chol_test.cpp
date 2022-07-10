/** @file test/factorizations/chol_test.cpp
 *  @author Kyle Krol */

#include "lin/core.hpp"
#include "lin/factorizations/chol.hpp"
#include "lin/generators/randoms.hpp"

#include <gtest/gtest.h>

template <typename T, lin::size_t N, lin::size_t MN>
static void zero_above_diagonal(lin::Matrix<T, N, N, MN, MN> &M) {
  ASSERT_EQ(M.rows(), M.cols());
  for (lin::size_t i = 0; i < M.rows(); i++)
    for (lin::size_t j = i + 1; j < M.cols(); j++) M(i, j) = 0;
}

TEST(FactorizationsChol, FixedSizeChol) {
  lin::internal::RandomsGenerator rand;
  lin::Matrix4x4f M, L;

  for (size_t i = 0; i < 20; i++) {
    M = lin::rands<lin::Matrix4x4f>(rand, 4, 4);
    zero_above_diagonal(M);
    L = M * lin::transpose(M);
    lin::chol(L);
    ASSERT_NEAR(0.0f, lin::fro(M - L), M.size() * 1e-5);
  }
}

TEST(FactorizationsChol, VariableSizeChol) {
  lin::internal::RandomsGenerator rand;
  lin::Matrixf<0, 0, 7, 7> M(6, 6), L(6, 6);

  for (size_t i = 0; i < 20; i++) {
    M = lin::rands<decltype(M)>(rand, 6, 6);
    zero_above_diagonal(M);
    L = M * lin::transpose(M);
    lin::chol(L);
    ASSERT_NEAR(0.0f, lin::fro(M - L), M.size() * 1e-5);
  }
}
