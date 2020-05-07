/** @file test/core/operations_functors_test.cpp
 *  @author Kyle Krol */

#include <lin/core/operations/functors.hpp>

#include <gtest/gtest.h>

#include <type_traits>

using namespace lin::internal;

static_assert(std::is_same<double,
    typename add::template expression<double, float>>::value, "");
static_assert(std::is_same<float,
    typename add::template expression<float, float>>::value, "");

TEST(CoreOperationsFunctors, Add) {
  add _add;
  ASSERT_FLOAT_EQ(3.0f, _add(1.0f, 2.0f));
  ASSERT_DOUBLE_EQ(2.0, _add(-1.0, 3.0f));
}

TEST(CoreOperationsFunctors, AddST) {
  add_st<float> _add(1.0f);
  ASSERT_FLOAT_EQ(-1.0f, _add(-2.0f));
  ASSERT_DOUBLE_EQ(0.0, _add(-1.0));
}

TEST(CoreOperationsFunctors, AddTS) {
  add_ts<double> _add(3.0);
  ASSERT_DOUBLE_EQ(4.0, _add(1.0));
}

TEST(CoreOperationsFunctors, Cast) {
  cast<double> _cast;
  static_assert(std::is_same<double, decltype(_cast(2.0f))>::value, "");

  ASSERT_DOUBLE_EQ(2.0, _cast(2.0f));
}

static_assert(std::is_same<double,
    typename divide::template expression<double, float>>::value, "");
static_assert(std::is_same<float,
    typename divide::template expression<float, float>>::value, "");

TEST(CoreOperationsFunctors, Divide) {
  divide _divide;
  ASSERT_FLOAT_EQ(0.5f, _divide(1.0f, 2.0f));
  ASSERT_DOUBLE_EQ(-0.25, _divide(-1.0, 4.0f));
}

TEST(CoreOperationsFunctors, DivideST) {
  divide_st<float> _divide(1.0f);
  ASSERT_FLOAT_EQ(-0.5f, _divide(-2.0f));
}

TEST(CoreOperationsFunctors, DivideTS) {
  divide_ts<double> _divide(5.0);
  ASSERT_DOUBLE_EQ(0.2, _divide(1.0));
}

static_assert(std::is_same<double,
    typename multiply::template expression<double, float>>::value, "");
static_assert(std::is_same<float,
    typename multiply::template expression<float, float>>::value, "");

TEST(CoreOperationsFunctors, Multiply) {
  multiply _multiply;
  ASSERT_FLOAT_EQ(2.0f, _multiply(1.0f, 2.0f));
  ASSERT_DOUBLE_EQ(-4.0, _multiply(-1.0, 4.0f));
}

TEST(CoreOperationsFunctors, MultiplyST) {
  multiply_st<float> _multiply(1.0f);
  ASSERT_FLOAT_EQ(-2.0f, _multiply(-2.0f));
}

TEST(CoreOperationsFunctors, MultiplyTS) {
  multiply_ts<double> _multiply(5.0);
  ASSERT_DOUBLE_EQ(5.0, _multiply(1.0));
}

static_assert(std::is_same<double,
    typename negate::template expression<double>>::value, "");
static_assert(std::is_same<float,
    typename negate::template expression<float>>::value, "");

TEST(CoreOperationsFunctors, Negate) {
  negate _negate;
  ASSERT_FLOAT_EQ(-1.0f, _negate(1.0f));
}

static_assert(std::is_same<double,
    typename sign::template expression<double>>::value, "");
static_assert(std::is_same<float,
    typename sign::template expression<float>>::value, "");

TEST(CoreOperationsFunctors, Sign) {
  sign _sign;
  ASSERT_FLOAT_EQ(-1.0f, _sign(-2.0f));
  ASSERT_FLOAT_EQ(0.0f, _sign(0.0f));
  ASSERT_FLOAT_EQ(1.0f, _sign(0.1f));
  ASSERT_EQ(1, _sign(20));
  ASSERT_EQ(0, _sign(0));
  ASSERT_EQ(1u, _sign(20u));
}

static_assert(std::is_same<double,
    typename square::template expression<double>>::value, "");
  static_assert(std::is_same<float,
    typename square::template expression<float>>::value, "");

TEST(CoreOperationsFunctors, Square) {
  square _square;
  ASSERT_FLOAT_EQ(4.0f, _square(-2.0f));
  ASSERT_FLOAT_EQ(0.0f, _square(0.0f));
  ASSERT_FLOAT_EQ(0.01f, _square(0.1f));
  ASSERT_EQ(400, _square(20));
  ASSERT_EQ(0, _square(0));
  ASSERT_EQ(400u, _square(20u));
}

static_assert(std::is_same<double,
    typename subtract::template expression<double, float>>::value, "");
static_assert(std::is_same<float,
    typename subtract::template expression<float, float>>::value, "");

TEST(CoreOperationsFunctors, Subtract) {
  subtract _subtract;
  ASSERT_FLOAT_EQ(2.0f, _subtract(5.0f, 3.0f));
  ASSERT_FLOAT_EQ(-2.0f, _subtract(3.0f, 5.0f));
}

TEST(CoreOperationsFunctors, SubtractST) {
  subtract_st<float> _subtract(4.0f);
  ASSERT_FLOAT_EQ(0.0f, _subtract(4.0f));
  ASSERT_FLOAT_EQ(2.0f, _subtract(2.0f));
}

TEST(CoreOperationsFunctors, SubtractTS) {
  subtract_ts<float> _subtract(4.0f);
  ASSERT_FLOAT_EQ(0.0f, _subtract(4.0f));
  ASSERT_FLOAT_EQ(-2.0f, _subtract(2.0f));
}
