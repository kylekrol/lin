/** @file test/substitution/backward_substitution_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/factorizations/qr.hpp>
#include <lin/generators/randoms.hpp>
#include <lin/substitutions/backward_substitution.hpp>

#include <gtest/gtest.h>

TEST(SubstitutionsBackwardSubstitution, FixedSizeBackwardSubstituion) {
  lin::internal::RandomsGenerator const rand;
  lin::Matrix4x4f M, Q, R;
  lin::Matrix4x3f X, Y;

  for (lin::size_t i = 0; i < 25; i++) {
    M = lin::rands<decltype(M)>(M.rows(), M.cols(), rand);
    Y = lin::rands<decltype(Y)>(Y.rows(), Y.cols(), rand);
    ASSERT_EQ(0, lin::qr(M, Q, R));
    ASSERT_EQ(0, lin::backward_sub(R, X, (lin::transpose(Q) * Y).eval()));
    ASSERT_NEAR(0.0f, lin::fro(M * X - Y), 1e-6 * Y.size());
  }
}

TEST(SubstitutionsBackwardSubstitution, StaticSizeBackwardSubstituion) {
  lin::internal::RandomsGenerator const rand;
  lin::Matrixf<0, 0, 9, 9> M, Q, R;
  lin::Matrixf<0, 0, 9, 6> X, Y;

  M.resize(8, 8);
  Y.resize(8, 5);
  for (lin::size_t i = 0; i < 25; i++) {
    M = lin::rands<decltype(M)>(M.rows(), M.cols(), rand);
    Y = lin::rands<decltype(Y)>(Y.rows(), Y.cols(), rand);
    ASSERT_EQ(0, lin::qr(M, Q, R));
    ASSERT_EQ(0, lin::backward_sub(R, X, (lin::transpose(Q) * Y).eval()));
    ASSERT_NEAR(0.0f, lin::fro(M * X - Y), 1e-6 * Y.size());
  }
}
