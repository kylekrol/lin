/** @file test/core/operations_tensor_operations_test.cpp
 *  @author Kyle Krol */

#include <lin/core/types/matrix.hpp>
#include <lin/core/operations/tensor_operations.hpp>

#include <gtest/gtest.h>

// #include <cmath>
// #include <limits>

// constexpr static double _nan = std::numeric_limits<double>::quiet_NaN();
// constexpr static double _inf = std::numeric_limits<double>::infinity();

// TEST(CoreOperationsTensorOperations, All) {
//   lin::Matrix2x2f A({0.0f, 0.0f, 0.0f, 0.0f});
//   ASSERT_TRUE(lin::all(A, [](float const &f) { return f == 0.0f; }));
//   lin::Matrix2x2f B({0.0f, 0.0f, 1.0f, 0.0f});
//   ASSERT_FALSE(lin::all(B, [](float const &f) { return f == 0.0f; }));
// }

// TEST(CoreOperationsTensorOperations, AllIsFinite) {
//   lin::Matrix2x2d A { 0.0, _nan, 0.0, 0.0 };
//   ASSERT_FALSE(lin::all_isfinite(A));
//   lin::Matrix2x2d B { 0.0, _inf, 0.0, 0.0 };
//   ASSERT_FALSE(lin::all_isfinite(B));
//   lin::Matrix2x2d C; // Zero initialized
//   ASSERT_TRUE(lin::all_isfinite(C));
// }

// TEST(CoreOperationsTensorOperations, AllIsInfinite) {
//   lin::Matrix2x2f A ({ _inf, _inf, _inf, _inf });
//   ASSERT_TRUE(lin::all_isinf(A));
//   lin::Matrix2x2f B { _inf, _inf, _nan, _inf };
//   ASSERT_FALSE(lin::all_isinf(B));
//   lin::Matrix2x2f C { _inf, _inf, 0.0, _inf };
//   ASSERT_FALSE(lin::all_isinf(C));
// }

// TEST(CoreOperationsTensorOperations, AllIsNan) {
//   lin::Matrix2x2f A { _nan, _nan, _nan, _nan };
//   ASSERT_TRUE(lin::all_isnan(A));
//   lin::Matrix2x2f B { _nan, _nan, _nan, _inf };
//   ASSERT_FALSE(lin::all_isnan(B));
//   lin::Matrix2x2f C { _nan, _nan, 0.0, _nan };
//   ASSERT_FALSE(lin::all_isnan(C));
// }

// TEST(CoreOperationsTensorOperations, Any) {
//   lin::Matrix2x2f A({0.0f, 0.0f, 0.0f, 0.0f});
//   ASSERT_FALSE(lin::any(A, [](float const &f) -> bool { return f != 0.0f; }));
//   lin::Matrix2x2f B({0.0f, 0.0f, 1.0f, 0.0f});
//   ASSERT_TRUE(lin::any(B, [](float const &f) -> bool { return f != 0.0f; }));
// }

// TEST(CoreOperationsTensorOperations, AnyIsFinite) {
//   lin::Matrix2x2f A { _nan, _nan, _nan, _nan };
//   ASSERT_FALSE(lin::any_isfinite(A));
//   lin::Matrix2x2f B { _nan, _nan, _nan, _inf };
//   ASSERT_FALSE(lin::any_isfinite(B));
//   lin::Matrix2x2f C { _nan, _inf, 0.0, _inf };
//   ASSERT_TRUE(lin::any_isfinite(C));
// }

// TEST(CoreOperationsTensorOperations, AnyIsInfinite) {
//   lin::Matrix2x2f A { _nan, _nan, _nan, _nan };
//   ASSERT_FALSE(lin::any_isinf(A));
//   lin::Matrix2x2f B { _nan, _nan, _nan, 0.0 };
//   ASSERT_FALSE(lin::any_isinf(B));
//   lin::Matrix2x2f C { _nan, _inf, 0.0, _inf };
//   ASSERT_TRUE(lin::any_isinf(C));
// }

// TEST(CoreOperationsTensorOperations, AnyIsNan) {
//     lin::Matrix2x2f A ({ _inf, _inf, _inf, _inf });
//   ASSERT_FALSE(lin::any_isnan(A));
//   lin::Matrix2x2f B { _inf, _inf, _nan, _inf };
//   ASSERT_TRUE(lin::any_isnan(B));
//   lin::Matrix2x2f C { _inf, _inf, 0.0, _inf };
//   ASSERT_FALSE(lin::any_isnan(C));
// }

TEST(CoreOperationsTensorOperations, Frobenius) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  ASSERT_FLOAT_EQ(14.0f, lin::fro(A));

  lin::Matrixf<0, 0, 4, 4> B(3, 2, {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f});
  ASSERT_FLOAT_EQ(55.0f, lin::fro(B));
}

TEST(CoreOperationsTensorOperations, Sign) {
  lin::Matrix2x3f A({
    0.0f, 0.2f, -100.0f,
    3.0f, -1.0f, -20.0f
  });
  auto sign_A = lin::sign(A);
  static_assert(lin::internal::have_same_traits<decltype(A), decltype(sign_A)>::value, "");
  ASSERT_EQ(2, sign_A.rows());
  ASSERT_EQ(3, sign_A.cols());
  ASSERT_EQ(6, sign_A.size());
  ASSERT_FLOAT_EQ( 0.0f, sign_A(0, 0));
  ASSERT_FLOAT_EQ( 1.0f, sign_A(0, 1));
  ASSERT_FLOAT_EQ(-1.0f, sign_A(0, 2));
  ASSERT_FLOAT_EQ( 1.0f, sign_A(1, 0));
  ASSERT_FLOAT_EQ(-1.0f, sign_A(1, 1));
  ASSERT_FLOAT_EQ(-1.0f, sign_A(1, 2));
}

TEST(CoreOperationsTensorOperations, Transpose) {
  lin::Matrix2x2f A({0.0f, 1.0f, 2.0f, 3.0f});
  auto const transpose_A = lin::transpose(A);
  ASSERT_FLOAT_EQ(0.0f, transpose_A(0, 0));
  ASSERT_FLOAT_EQ(2.0f, transpose_A(0, 1));
  ASSERT_FLOAT_EQ(1.0f, transpose_A(1, 0));
  ASSERT_FLOAT_EQ(3.0f, transpose_A(1, 1));

  lin::Matrixf<0, 0, 4, 4> B(3, 2);
  auto const transpose_B = lin::transpose(B);
  ASSERT_EQ(2, transpose_B.rows());
  ASSERT_EQ(3, transpose_B.cols());
  ASSERT_EQ(6, transpose_B.size());

  lin::Matrix2x4f C;
  auto const transpose_C = lin::transpose(C);
  ASSERT_EQ(4, transpose_C.rows());
  ASSERT_EQ(2, transpose_C.cols());
  ASSERT_EQ(8, transpose_C.size());
}
