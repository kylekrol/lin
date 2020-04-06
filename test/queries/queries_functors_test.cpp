/** @file test/queries/queries_functors_test.cpp
 *  @author Kyle Krol */

#include <lin/queries/functors.hpp>

#include <gtest/gtest.h>

#include <type_traits>

using namespace lin::internal;

static_assert(std::is_same<bool, equal_to::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, equal_to::template expression<float, float>>::value, "");

TEST(QueriesFunctors, EqualTo) {
  equal_to _equal;
  ASSERT_FALSE(_equal(-1.0, 0.0));
  ASSERT_TRUE(_equal(0.0, 0.0));
  ASSERT_FALSE(_equal(1.0, 0.0));
}

TEST(QueriesFunctors, EqualToST) {
  equal_to_st<double> _equal(0.0);
  ASSERT_FALSE(_equal(1.0));
  ASSERT_TRUE(_equal(0.0));
  ASSERT_FALSE(_equal(-1.0));
}

TEST(QueriesFunctors, EqualToTS) {
  equal_to_ts<double> _equal(0.0);
  ASSERT_FALSE(_equal(-1.0));
  ASSERT_TRUE(_equal(0.0));
  ASSERT_FALSE(_equal(1.0));
}

static_assert(std::is_same<bool, greater::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, greater::template expression<float, float>>::value, "");

TEST(QueriesFunctors, Greater) {
  greater _greater;
  ASSERT_FALSE(_greater(-1.0, 0.0));
  ASSERT_FALSE(_greater(0.0, 0.0));
  ASSERT_TRUE(_greater(1.0, 0.0));
}

TEST(QueriesFunctors, GreaterST) {
  greater_st<double> _greater(0.0);
  ASSERT_FALSE(_greater(1.0));
  ASSERT_FALSE(_greater(0.0));
  ASSERT_TRUE(_greater(-1.0));
}

TEST(QueriesFunctors, GreaterTS) {
  greater_ts<double> _greater(0.0);
  ASSERT_FALSE(_greater(-1.0));
  ASSERT_FALSE(_greater(0.0));
  ASSERT_TRUE(_greater(1.0));
}

static_assert(std::is_same<bool, greater_equal::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, greater_equal::template expression<float, float>>::value, "");

TEST(QueriesFunctors, GreaterEqual) {
  greater_equal _greater_equal;
  ASSERT_FALSE(_greater_equal(-1.0, 0.0));
  ASSERT_TRUE(_greater_equal(0.0, 0.0));
  ASSERT_TRUE(_greater_equal(1.0, 0.0));
}

TEST(QueriesFunctors, GreaterEqualST) {
  greater_equal_st<double> _greater_equal(0.0);
  ASSERT_FALSE(_greater_equal(1.0));
  ASSERT_TRUE(_greater_equal(0.0));
  ASSERT_TRUE(_greater_equal(-1.0));
}

TEST(QueriesFunctors, GreaterEqualTS) {
  greater_equal_ts<double> _greater_equal(0.0);
  ASSERT_FALSE(_greater_equal(-1.0));
  ASSERT_TRUE(_greater_equal(0.0));
  ASSERT_TRUE(_greater_equal(1.0));
}

static_assert(std::is_same<bool, less::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, less::template expression<float, float>>::value, "");

TEST(QueriesFunctors, Less) {
  less _less;
  ASSERT_TRUE(_less(-1.0, 0.0));
  ASSERT_FALSE(_less(0.0, 0.0));
  ASSERT_FALSE(_less(1.0, 0.0));
}

TEST(QueriesFunctors, LessST) {
  less_st<double> _less(0.0);
  ASSERT_TRUE(_less(1.0));
  ASSERT_FALSE(_less(0.0));
  ASSERT_FALSE(_less(-1.0));
}

TEST(QueriesFunctors, LessTS) {
  less_ts<double> _less(0.0);
  ASSERT_TRUE(_less(-1.0));
  ASSERT_FALSE(_less(0.0));
  ASSERT_FALSE(_less(1.0));
}

static_assert(std::is_same<bool, less_equal::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, less_equal::template expression<float, float>>::value, "");

TEST(QueriesFunctors, LessEqual) {
  less_equal _less_equal;
  ASSERT_TRUE(_less_equal(-1.0, 0.0));
  ASSERT_TRUE(_less_equal(0.0, 0.0));
  ASSERT_FALSE(_less_equal(1.0, 0.0));
}

TEST(QueriesFunctors, LessEqualST) {
  less_equal_st<double> _less_equal(0.0);
  ASSERT_TRUE(_less_equal(1.0));
  ASSERT_TRUE(_less_equal(0.0));
  ASSERT_FALSE(_less_equal(-1.0));
}

TEST(QueriesFunctors, LessEqualTS) {
  less_equal_ts<double> _less_equal(0.0);
  ASSERT_TRUE(_less_equal(-1.0));
  ASSERT_TRUE(_less_equal(0.0));
  ASSERT_FALSE(_less_equal(1.0));
}

static_assert(std::is_same<bool, logical_and::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, logical_and::template expression<bool, bool>>::value, "");

TEST(QueriesFunctors, LogicalAnd) {
  logical_and _and;
  ASSERT_TRUE(_and(true, true));
  ASSERT_FALSE(_and(true, false));
  ASSERT_FALSE(_and(false, true));
  ASSERT_FALSE(_and(false, false));
}

TEST(QueriesFunctors, LogicalAndST) {
  logical_and_st<bool> _and_t(true);
  ASSERT_TRUE(_and_t(true));
  ASSERT_FALSE(_and_t(false));

  logical_and_st<bool> _and_f(false);
  ASSERT_FALSE(_and_f(true));
  ASSERT_FALSE(_and_f(false));
}

TEST(QueriesFunctors, LogicalAndTS) {
  logical_and_ts<bool> _and_t(true);
  ASSERT_TRUE(_and_t(true));
  ASSERT_FALSE(_and_t(false));

  logical_and_ts<bool> _and_f(false);
  ASSERT_FALSE(_and_f(true));
  ASSERT_FALSE(_and_f(false));
}

static_assert(std::is_same<bool, logical_not::template expression<float>>::value, "");
static_assert(std::is_same<bool, logical_not::template expression<bool>>::value, "");

TEST(QueriesFunctors, LogicalNot) {
  logical_not _not_;
  ASSERT_TRUE(_not_(0.0f));
  ASSERT_FALSE(_not_(true));
}

static_assert(std::is_same<bool, logical_or::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, logical_or::template expression<bool, bool>>::value, "");

TEST(QueriesFunctors, LogicalOr) {
  logical_or _or;
  ASSERT_TRUE(_or(true, true));
  ASSERT_TRUE(_or(true, false));
  ASSERT_TRUE(_or(false, true));
  ASSERT_FALSE(_or(false, false));
}

TEST(QueriesFunctors, LogicalOrST) {
  logical_or_st<bool> _or_t(true);
  ASSERT_TRUE(_or_t(true));
  ASSERT_TRUE(_or_t(false));

  logical_or_st<bool> _or_f(false);
  ASSERT_TRUE(_or_f(true));
  ASSERT_FALSE(_or_f(false));
}

TEST(QueriesFunctors, LogicalOrTS) {
  logical_or_ts<bool> _or_t(true);
  ASSERT_TRUE(_or_t(true));
  ASSERT_TRUE(_or_t(false));

  logical_or_ts<bool> _or_f(false);
  ASSERT_TRUE(_or_f(true));
  ASSERT_FALSE(_or_f(false));
}

static_assert(std::is_same<bool, not_equal_to::template expression<float, double>>::value, "");
static_assert(std::is_same<bool, not_equal_to::template expression<float, float>>::value, "");

TEST(QueriesFunctors, NotEqualTo) {
  not_equal_to _not_equal;
  ASSERT_TRUE(_not_equal(-1.0, 0.0));
  ASSERT_FALSE(_not_equal(0.0, 0.0));
  ASSERT_TRUE(_not_equal(1.0, 0.0));
}

TEST(QueriesFunctors, NotEqualToST) {
  not_equal_to_st<double> _not_equal(0.0);
  ASSERT_TRUE(_not_equal(1.0));
  ASSERT_FALSE(_not_equal(0.0));
  ASSERT_TRUE(_not_equal(-1.0));
}

TEST(QueriesFunctors, NotEqualToTS) {
  not_equal_to_ts<double> _not_equal(0.0);
  ASSERT_TRUE(_not_equal(-1.0));
  ASSERT_FALSE(_not_equal(0.0));
  ASSERT_TRUE(_not_equal(1.0));
}
