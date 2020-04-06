/** @file test/queries/queries_operators_test.cpp
 *  @author Kyle Krol */

#include <lin/queries/operators.hpp>
#include <lin/queries/types.hpp>

#include <gtest/gtest.h>

TEST(QueriesOperators, EqualTo) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = (a == b);
  ASSERT_FALSE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_FALSE(c(2));

  lin::Vector3b d = (a == 0.0f);
  ASSERT_FALSE(d(0));
  ASSERT_TRUE(d(1));
  ASSERT_FALSE(d(2));

  lin::Vector3b e = (0.0f == a);
  ASSERT_FALSE(e(0));
  ASSERT_TRUE(e(1));
  ASSERT_FALSE(e(2));
}

TEST(QueriesOperators, Greater) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = (a > b);
  ASSERT_FALSE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_TRUE(c(2));

  lin::Vector3b d = (a > 0.0f);
  ASSERT_FALSE(d(0));
  ASSERT_FALSE(d(1));
  ASSERT_TRUE(d(2));

  lin::Vector3b e = (0.0f > a);
  ASSERT_TRUE(e(0));
  ASSERT_FALSE(e(1));
  ASSERT_FALSE(e(2));
}

TEST(QueriesOperators, GreaterEqual) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = (a >= b);
  ASSERT_FALSE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_TRUE(c(2));

  lin::Vector3b d = (a >= 0.0f);
  ASSERT_FALSE(d(0));
  ASSERT_TRUE(d(1));
  ASSERT_TRUE(d(2));

  lin::Vector3b e = (0.0f >= a);
  ASSERT_TRUE(e(0));
  ASSERT_TRUE(e(1));
  ASSERT_FALSE(e(2));
}

TEST(QueriesOperators, Less) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = (a < b);
  ASSERT_TRUE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_FALSE(c(2));

  lin::Vector3b d = (a < 0.0f);
  ASSERT_TRUE(d(0));
  ASSERT_FALSE(d(1));
  ASSERT_FALSE(d(2));

  lin::Vector3b e = (0.0f < a);
  ASSERT_FALSE(e(0));
  ASSERT_FALSE(e(1));
  ASSERT_TRUE(e(2));
}

TEST(QueriesOperators, LessEqual) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = (a <= b);
  ASSERT_TRUE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_FALSE(c(2));

  lin::Vector3b d = (a <= 0.0f);
  ASSERT_TRUE(d(0));
  ASSERT_TRUE(d(1));
  ASSERT_FALSE(d(2));

  lin::Vector3b e = (0.0f <= a);
  ASSERT_FALSE(e(0));
  ASSERT_TRUE(e(1));
  ASSERT_TRUE(e(2));
}

TEST(QueriesOperators, LogicalAnd) {
  lin::Vector4b a {true, true, false, false};
  lin::Vector4b b {true, false, true, false};

  lin::Vector4b c = (a && b);
  ASSERT_TRUE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_FALSE(c(2));
  ASSERT_FALSE(c(3));

  lin::Vector4b d = (true && a);
  ASSERT_TRUE(d(0));
  ASSERT_FALSE(d(2));

  lin::Vector4b e = (a && false);
  ASSERT_FALSE(e(0));
  ASSERT_FALSE(e(2));
}

TEST(QueriesOperators, LogicalNot) {
  lin::Vector2b a {true, false};

  lin::Vector2b b = (!a);
  ASSERT_FALSE(b(0));
  ASSERT_TRUE(b(1));
}

TEST(QueriesOperators, LogicalOr) {
  lin::Vector4b a {true, true, false, false};
  lin::Vector4b b {true, false, true, false};

  lin::Vector4b c = (a || b);
  ASSERT_TRUE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_TRUE(c(2));
  ASSERT_FALSE(c(3));

  lin::Vector4b d = (true || a);
  ASSERT_TRUE(d(0));
  ASSERT_TRUE(d(2));

  lin::Vector4b e = (a || false);
  ASSERT_TRUE(e(0));
  ASSERT_FALSE(e(2));
}

TEST(QueriesOperators, NotEqualTo) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = (a != b);
  ASSERT_TRUE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_TRUE(c(2));

  lin::Vector3b d = (a != 0.0f);
  ASSERT_TRUE(d(0));
  ASSERT_FALSE(d(1));
  ASSERT_TRUE(d(2));

  lin::Vector3b e = (0.0f != a);
  ASSERT_TRUE(e(0));
  ASSERT_FALSE(e(1));
  ASSERT_TRUE(e(2));
}
