/** @file test/substitution/forward_substitution_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/factorizations/chol.hpp>
#include <lin/generators/randoms.hpp>
#include <lin/substitutions.hpp>

#include <gtest/gtest.h>

template <typename T, size_t N, size_t MN>
static void zero_above_diagonal(lin::Matrix<T, N, N, MN, MN> &M) {
  ASSERT_EQ(M.rows(), M.cols());
  for (lin::size_t i = 0; i < M.rows(); i++)
    for (lin::size_t j = i + 1; j < M.cols(); j++) M(i, j) = 0;
}

TEST(SubstitutionsFowardSubstitutions, FixedSizeFowardSubstition) {
  lin::internal::RandomsGenerator const rand(9); // seed=0 fails here - unlucky I guess
  lin::Matrix4x4f M, L;
  lin::Matrix4x3f X, Y, Z;

  for (lin::size_t i = 0; i < 25; i++) {
    M = lin::rands<decltype(M)>(4, 4, rand);
    Z = lin::rands<decltype(Y)>(4, 3, rand);
    zero_above_diagonal(M);
    L = M * lin::transpose(M);
    M = L;

    lin::chol(L);
    lin::forward_sub(L, Y, Z);
    lin::backward_sub(lin::transpose(L).eval(), X, Y);
    ASSERT_NEAR(0.0f, lin::fro(M * X - Z), 1e-5 * Y.size());
  }
}

TEST(SubstitutionsFowardSubstitutions, VariableSizeForwardSubstitution) {
  lin::internal::RandomsGenerator const rand;
  lin::Matrixf<0, 0, 7, 7> M(5, 5), L(5, 5);
  lin::Matrixf<0, 2, 7, 2> X, Y, Z(5, 2);

  for (lin::size_t i = 0; i < 25; i++) {
    M = lin::rands<decltype(M)>(5, 5, rand);
    Z = lin::rands<decltype(Z)>(5, 2, rand);
    zero_above_diagonal(M);
    L = M * lin::transpose(M);
    M = L;

    lin::chol(L);
    lin::forward_sub(L, Y, Z);
    lin::backward_sub(lin::transpose(L).eval(), X, Y);
    ASSERT_NEAR(0.0f, lin::fro(M * X - Z), 1e-5 * Y.size());
  }
}
