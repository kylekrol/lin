/** @file test/generators/randoms_test.cpp
 *  @author Kyle Krol */

#include <lin/core.hpp>
#include <lin/references/stream_reference.hpp>

#include <gtest/gtest.h>

#include <type_traits>

TEST(ReferencesStreamReference, Reference) {
  lin::Matrixf<3, 3> A({
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f,
    6.0f, 7.0f, 8.0f
  });
  lin::Matrixf<2, 2> B({
    3.0f, 4.0f,
    6.0f, 7.0f
  });
  auto const C = lin::ref<2, 2>(A, 1, 0);
  ASSERT_FLOAT_EQ(0.0f, lin::fro(B - C));
  ASSERT_EQ(2, C.rows());
  ASSERT_EQ(2, C.cols());
  ASSERT_EQ(4, C.size());

  lin::Matrixf<0, 0, 5, 5> D(2, 3, {
    0.0f, 1.0f, 2.0f,
    3.0f, 4.0f, 5.0f
  });
  lin::Matrixf<0, 0, 5, 5> E(2, 2, {
    1.0f, 2.0f,
    4.0f, 5.0f
  });
  auto const F = lin::ref<0, 0, 5, 5>(D, 0, 1, 2, 2);
  ASSERT_FLOAT_EQ(0.0f, lin::fro(E - F));
  ASSERT_EQ(2, F.rows());
  ASSERT_EQ(2, F.cols());
  ASSERT_EQ(4, F.size());
}

TEST(ReferencesStreamReference, ReferenceRow) {
  lin::Matrixf<0, 0, 4, 4> A(3, 2, {
    0.0f, 1.0f,
    2.0f, 3.0f,
    4.0f, 5.0f
  });
  auto const a = lin::ref_row(A, 1);
  ASSERT_FLOAT_EQ(0.0f, lin::fro(a - lin::RowVectorf<0, 4>(2, {2.0f, 3.0f})));
  ASSERT_EQ(1, a.rows());
  ASSERT_EQ(2, a.cols());
  ASSERT_EQ(2, a.size());
}

TEST(ReferencesStreamReference, ReferenceColumn) {
  lin::Matrixf<0, 0, 4, 4> A(3, 2, {
    0.0f, 1.0f,
    2.0f, 3.0f,
    4.0f, 5.0f
  });
  auto const a = lin::ref_col(A, 1);
  ASSERT_FLOAT_EQ(0.0f, lin::fro(a - lin::Vectorf<0, 4>(3, {1.0f, 3.0f, 5.0f})));
  ASSERT_EQ(3, a.rows());
  ASSERT_EQ(1, a.cols());
  ASSERT_EQ(3, a.size());
}
