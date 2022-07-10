/** @file test/factorizations/qr_test.cpp
 *  @author Kyle Krol */

#include "lin/core.hpp"
#include "lin/factorizations/qr.hpp"
#include "lin/generators/randoms.hpp"

#include <gtest/gtest.h>

TEST(FactorizationsQr, FixedSizeQr) {
  lin::internal::RandomsGenerator rand;
  lin::Matrix4x3f M, Q;
  lin::Matrix3x3f R;

  for (lin::size_t i = 0; i < 25; i++) {
    M = lin::rands<decltype(M)>(rand, M.rows(), M.cols());
    ASSERT_EQ(0, lin::qr(M, Q, R));
    ASSERT_NEAR(0.0f, lin::fro(M - Q * R), 1e-6 * M.size());
  }
}

TEST(Factorizations, StaticSizeQr) {
  lin::internal::RandomsGenerator rand;
  lin::Matrixf<0, 0, 9, 8> M, Q;
  lin::Matrixf<0, 0, 8, 8> R;

  M.resize(8, 6);
  for (lin::size_t i = 0; i < 25; i++) {
    M = lin::rands<decltype(M)>(rand, M.rows(), M.cols());
    ASSERT_EQ(0, lin::qr(M, Q, R));
    ASSERT_NEAR(0.0f, lin::fro(M - Q * R), 1e-6 * M.size());
  }
}
