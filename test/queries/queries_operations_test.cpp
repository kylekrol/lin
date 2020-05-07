/** @file test/queries/queries_operations_test.cpp
 *  @author Kyle Krol */

#include <lin/queries/operations.hpp>
#include <lin/queries/types.hpp>

#include <gtest/gtest.h>

TEST(QueriesOperations, All) {
  lin::Vector3b a {true, true, false};
  lin::Vector3b b {true, true, true };
  ASSERT_FALSE(lin::all(a));
  ASSERT_TRUE(lin::all(b));

  ASSERT_TRUE(lin::any(1));
  ASSERT_FALSE(lin::any(0u));
  ASSERT_FALSE(lin::any(false));
}

TEST(QueriesOperations, Any) {
  lin::Vector3b a {true, true, false};
  lin::Vector3b b {true, true, true };
  ASSERT_TRUE(lin::any(lin::logical_not(a)));
  ASSERT_FALSE(lin::any(lin::logical_not(b)));

  ASSERT_TRUE(lin::any(1));
  ASSERT_FALSE(lin::any(0u));
  ASSERT_FALSE(lin::any(false));
}

TEST(QueriesOperations, EqualTo) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = lin::equal_to(a, b);
  ASSERT_FALSE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_FALSE(c(2));

  lin::Vector3b d = lin::equal_to(a, 0.0f);
  ASSERT_FALSE(d(0));
  ASSERT_TRUE(d(1));
  ASSERT_FALSE(d(2));

  lin::Vector3b e = lin::equal_to(0.0f, a);
  ASSERT_FALSE(e(0));
  ASSERT_TRUE(e(1));
  ASSERT_FALSE(e(2));

  ASSERT_FALSE(lin::equal_to(-1.0f, 0.0f));
  ASSERT_TRUE(lin::equal_to(0.0f, 0.0f));
  ASSERT_FALSE(lin::equal_to(1.0f, 0.0f));
}

TEST(QueriesOperations, Greater) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = lin::greater(a, b);
  ASSERT_FALSE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_TRUE(c(2));

  lin::Vector3b d = lin::greater(a, 0.0f);
  ASSERT_FALSE(d(0));
  ASSERT_FALSE(d(1));
  ASSERT_TRUE(d(2));

  lin::Vector3b e = lin::greater(0.0f, a);
  ASSERT_TRUE(e(0));
  ASSERT_FALSE(e(1));
  ASSERT_FALSE(e(2));

  ASSERT_FALSE(lin::greater(-1.0f, 0.0f));
  ASSERT_FALSE(lin::greater(0.0f, 0.0f));
  ASSERT_TRUE(lin::greater(1.0f, 0.0f));
}

TEST(QueriesOperations, GreaterEqual) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = lin::greater_equal(a, b);
  ASSERT_FALSE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_TRUE(c(2));

  lin::Vector3b d = lin::greater_equal(a, 0.0f);
  ASSERT_FALSE(d(0));
  ASSERT_TRUE(d(1));
  ASSERT_TRUE(d(2));

  lin::Vector3b e = lin::greater_equal(0.0f, a);
  ASSERT_TRUE(e(0));
  ASSERT_TRUE(e(1));
  ASSERT_FALSE(e(2));

  ASSERT_FALSE(lin::greater_equal(-1.0f, 0.0f));
  ASSERT_TRUE(lin::greater_equal(0.0f, 0.0f));
  ASSERT_TRUE(lin::greater_equal(1.0f, 0.0f));
}

TEST(QueriesOperations, Less) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = lin::less(a, b);
  ASSERT_TRUE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_FALSE(c(2));

  lin::Vector3b d = lin::less(a, 0.0f);
  ASSERT_TRUE(d(0));
  ASSERT_FALSE(d(1));
  ASSERT_FALSE(d(2));

  lin::Vector3b e = lin::less(0.0f, a);
  ASSERT_FALSE(e(0));
  ASSERT_FALSE(e(1));
  ASSERT_TRUE(e(2));

  ASSERT_TRUE(lin::less(-1.0f, 0.0f));
  ASSERT_FALSE(lin::less(0.0f, 0.0f));
  ASSERT_FALSE(lin::less(1.0f, 0.0f));
}

TEST(QueriesOperations, LessEqual) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = lin::less_equal(a, b);
  ASSERT_TRUE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_FALSE(c(2));

  lin::Vector3b d = lin::less_equal(a, 0.0f);
  ASSERT_TRUE(d(0));
  ASSERT_TRUE(d(1));
  ASSERT_FALSE(d(2));

  lin::Vector3b e = lin::less_equal(0.0f, a);
  ASSERT_FALSE(e(0));
  ASSERT_TRUE(e(1));
  ASSERT_TRUE(e(2));

  ASSERT_TRUE(lin::less_equal(-1.0f, 0.0f));
  ASSERT_TRUE(lin::less_equal(0.0f, 0.0f));
  ASSERT_FALSE(lin::less_equal(1.0f, 0.0f));
}

TEST(QueriesOperations, LogicalAnd) {
  lin::Vector4b a {true, true, false, false};
  lin::Vector4b b {true, false, true, false};

  lin::Vector4b c = lin::logical_and(a, b);
  ASSERT_TRUE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_FALSE(c(2));
  ASSERT_FALSE(c(3));

  lin::Vector4b d = lin::logical_and(true, a);
  ASSERT_TRUE(d(0));
  ASSERT_FALSE(d(2));

  lin::Vector4b e = lin::logical_and(a, false);
  ASSERT_FALSE(e(0));
  ASSERT_FALSE(e(2));

  ASSERT_TRUE(lin::logical_and(true, true));
  ASSERT_FALSE(lin::logical_and(true, false));
}

TEST(QueriesOperations, LogicalNot) {
  lin::Vector2b a {true, false};

  lin::Vector2b b = lin::logical_not(a);
  ASSERT_FALSE(b(0));
  ASSERT_TRUE(b(1));

  ASSERT_TRUE(lin::logical_not(false));
  ASSERT_FALSE(lin::logical_not(true));
}

TEST(QueriesOperations, LogicalOr) {
  lin::Vector4b a {true, true, false, false};
  lin::Vector4b b {true, false, true, false};

  lin::Vector4b c = lin::logical_or(a, b);
  ASSERT_TRUE(c(0));
  ASSERT_TRUE(c(1));
  ASSERT_TRUE(c(2));
  ASSERT_FALSE(c(3));

  lin::Vector4b d = lin::logical_or(true, a);
  ASSERT_TRUE(d(0));
  ASSERT_TRUE(d(2));

  lin::Vector4b e = lin::logical_or(a, false);
  ASSERT_TRUE(e(0));
  ASSERT_FALSE(e(2));

  ASSERT_TRUE(lin::logical_or(false, true));
  ASSERT_FALSE(lin::logical_or(false, false));
}

TEST(QueriesOperations, NotEqualTo) {
  lin::Vector3f a {-1.0f, 0.0f, 1.0f};
  lin::Vector3f b { 0.0f, 0.0f, 0.0f};

  lin::Vector3b c = lin::not_equal_to(a, b);
  ASSERT_TRUE(c(0));
  ASSERT_FALSE(c(1));
  ASSERT_TRUE(c(2));

  lin::Vector3b d = lin::not_equal_to(a, 0.0f);
  ASSERT_TRUE(d(0));
  ASSERT_FALSE(d(1));
  ASSERT_TRUE(d(2));

  lin::Vector3b e = lin::not_equal_to(0.0f, a);
  ASSERT_TRUE(e(0));
  ASSERT_FALSE(e(1));
  ASSERT_TRUE(e(2));

  ASSERT_TRUE(lin::not_equal_to(-1.0f, 0.0f));
  ASSERT_FALSE(lin::not_equal_to(0.0f, 0.0f));
  ASSERT_TRUE(lin::not_equal_to(1.0f, 0.0f));
}
