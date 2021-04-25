#include "../test.hpp"

//
// MIT License
//
// Copyright (c) 2021 Kyle Krol (kylekrol)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

/** @file test_core/test_traits.cpp
 *  @author Kyle Krol
 */

#include "lin/core/traits.hpp"

#include <type_traits>
#include <utility>

using namespace lin;

#define T(...) static_assert((__VA_ARGS__), "");
#define F(...) static_assert(!(__VA_ARGS__), "");

using True = std::true_type;
using False = std::false_type;

void test_conjunction() {
  T(conjunction<>::value);
  T(conjunction<True>::value);
  F(conjunction<False>::value);
  T(conjunction<True, True>::value);
  F(conjunction<True, False>::value);
  F(conjunction<False, True>::value);
  F(conjunction<False, False>::value);
  T(conjunction<True, True, True>::value);
  F(conjunction<True, False, True>::value);
  F(conjunction<False, True, True>::value);
  F(conjunction<False, False, True>::value);
  F(conjunction<True, True, False>::value);
  F(conjunction<True, False, False>::value);
  F(conjunction<False, True, False>::value);
  F(conjunction<False, False, False>::value);
}

void test_disjunction() {
  F(disjunction<>::value);
  T(disjunction<True>::value);
  F(disjunction<False>::value);
  T(disjunction<True, True>::value);
  T(disjunction<True, False>::value);
  T(disjunction<False, True>::value);
  F(disjunction<False, False>::value);
  T(disjunction<True, True, True>::value);
  T(disjunction<True, False, True>::value);
  T(disjunction<False, True, True>::value);
  T(disjunction<False, False, True>::value);
  T(disjunction<True, True, False>::value);
  T(disjunction<True, False, False>::value);
  T(disjunction<False, True, False>::value);
  F(disjunction<False, False, False>::value);
}

void test_negation() {
  F(negation<True>::value);
  T(negation<False>::value);
}

template <typename U, typename V>
using assign_expression = decltype(std::declval<U &>() = std::declval<V &>());

void test_is_detected() {
  T(is_detected<assign_expression, float, float>::value);
  T(is_detected<assign_expression, float, double>::value);
  T(is_detected<assign_expression, double, float>::value);
  T(is_detected<assign_expression, double, double>::value);
  F(is_detected<assign_expression, void *, float>::value);
}

namespace lin {

template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
class TraitsContainer {
 public:
  using Traits = traits<TraitsContainer<T, R, C, MR, MC>>;
};

namespace internal {

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _traits<TraitsContainer<T, R, C, MR, MC>> {
  using elem_t = T;
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

void test_traits() {
  using LocalTraits = traits<TraitsContainer<float, 3, 0, 3, 5>>;

  static_assert(std::is_same<typename LocalTraits::elem_t, float>::value, "");
  static_assert(LocalTraits::rows == 3, "");
  static_assert(LocalTraits::cols == 0, "");
  static_assert(LocalTraits::size == 0, "");
  static_assert(LocalTraits::max_rows == 3, "");
  static_assert(LocalTraits::max_cols == 5, "");
  static_assert(LocalTraits::max_size == 15, "");
}

void test_has_traits() {
  T(has_traits<TraitsContainer<float, 2, 2>>::value);
  F(has_traits<void>::value);
}

void test_have_traits() {
  using LocalTraitsContainer = TraitsContainer<float, 2, 2>;

  T(have_traits<>::value);
  T(have_traits<LocalTraitsContainer>::value);
  T(have_traits<LocalTraitsContainer, LocalTraitsContainer>::value);
  F(have_traits<LocalTraitsContainer, void>::value);
  F(have_traits<void, LocalTraitsContainer>::value);
  F(have_traits<void, void>::value);
}

void test_have_same_elements() {
  using FloatTraitsContainer = TraitsContainer<float, 2, 3>;
  using DoubleTraitsContainer = TraitsContainer<double, 3, 2>;

  T(have_same_elements<>::value);
  T(have_same_elements<FloatTraitsContainer>::value);
  T(have_same_elements<FloatTraitsContainer, FloatTraitsContainer>::value);
  F(have_same_elements<FloatTraitsContainer, DoubleTraitsContainer>::value);
  F(have_same_elements<DoubleTraitsContainer, FloatTraitsContainer>::value);
  T(have_same_elements<DoubleTraitsContainer, DoubleTraitsContainer>::value);
  T(have_same_elements<FloatTraitsContainer, FloatTraitsContainer, FloatTraitsContainer>::value);
  F(have_same_elements<FloatTraitsContainer, DoubleTraitsContainer, FloatTraitsContainer>::value);
  F(have_same_elements<DoubleTraitsContainer, FloatTraitsContainer, FloatTraitsContainer>::value);
  F(have_same_elements<DoubleTraitsContainer, DoubleTraitsContainer, FloatTraitsContainer>::value);
  F(have_same_elements<FloatTraitsContainer, FloatTraitsContainer, DoubleTraitsContainer>::value);
  F(have_same_elements<FloatTraitsContainer, DoubleTraitsContainer, DoubleTraitsContainer>::value);
  F(have_same_elements<DoubleTraitsContainer, FloatTraitsContainer, DoubleTraitsContainer>::value);
  T(have_same_elements<DoubleTraitsContainer, DoubleTraitsContainer, DoubleTraitsContainer>::value);
}

void test_has_floating_point_elements() {
  using FloatTraitsContainer = TraitsContainer<float, 2, 2>;
  using IntTraitsContainer = TraitsContainer<int, 2, 2>;

  T(has_floating_point_elements<FloatTraitsContainer>::value);
  F(has_floating_point_elements<IntTraitsContainer>::value);
}

void test_have_floating_point_elements() {
  typedef TraitsContainer<float, 2, 2> FloatTraitsContainer;
  typedef TraitsContainer<int, 2, 2> IntTraitsContainer;

  T(have_floating_point_elements<>::value);
  T(have_floating_point_elements<FloatTraitsContainer>::value);
  F(have_floating_point_elements<IntTraitsContainer>::value);
  T(have_floating_point_elements<FloatTraitsContainer, FloatTraitsContainer>::value);
  F(have_floating_point_elements<IntTraitsContainer, FloatTraitsContainer>::value);
  F(have_floating_point_elements<FloatTraitsContainer, IntTraitsContainer>::value);
  F(have_floating_point_elements<IntTraitsContainer, IntTraitsContainer>::value);
}

void test_has_integral_elements() {
  typedef TraitsContainer<float, 2, 2> FloatTraitsContainer;
  typedef TraitsContainer<int, 2, 2> IntTraitsContainer;

  F(has_integral_elements<FloatTraitsContainer>::value);
  T(has_integral_elements<IntTraitsContainer>::value);
}

void test_have_integral_elements() {
  using FloatTraitsContainer = TraitsContainer<float, 2, 2>;
  using IntTraitsContainer = TraitsContainer<int, 2, 2>;

  T(have_integral_elements<>::value);
  F(have_integral_elements<FloatTraitsContainer>::value);
  T(have_integral_elements<IntTraitsContainer>::value);
  F(have_integral_elements<FloatTraitsContainer, FloatTraitsContainer>::value);
  F(have_integral_elements<IntTraitsContainer, FloatTraitsContainer>::value);
  F(have_integral_elements<FloatTraitsContainer, IntTraitsContainer>::value);
  T(have_integral_elements<IntTraitsContainer, IntTraitsContainer>::value);
}

void test_has_fixed_rows() {
  using FixedRowsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableRowsTraitsContainer = TraitsContainer<float, 0, 2, 2, 2>;

  T(has_fixed_rows<FixedRowsTraitsContainer>::value);
  F(has_fixed_rows<VariableRowsTraitsContainer>::value);
}

void test_have_fixed_rows() {
  using FixedRowsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableRowsTraitsContainer = TraitsContainer<float, 0, 2, 2, 2>;

  T(have_fixed_rows<>::value);
  T(have_fixed_rows<FixedRowsTraitsContainer>::value);
  F(have_fixed_rows<VariableRowsTraitsContainer>::value);
  T(have_fixed_rows<FixedRowsTraitsContainer, FixedRowsTraitsContainer>::value);
  F(have_fixed_rows<VariableRowsTraitsContainer, FixedRowsTraitsContainer>::value);
  F(have_fixed_rows<FixedRowsTraitsContainer, VariableRowsTraitsContainer>::value);
  F(have_fixed_rows<VariableRowsTraitsContainer, VariableRowsTraitsContainer>::value);
}

void test_has_fixed_cols() {
  using FixedColsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableColsTraitsContainer = TraitsContainer<float, 2, 0, 2, 2>;

  T(has_fixed_cols<FixedColsTraitsContainer>::value);
  F(has_fixed_cols<VariableColsTraitsContainer>::value);
}

void test_have_fixed_cols() {
  using FixedColsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableColsTraitsContainer = TraitsContainer<float, 2, 0, 2, 2>;

  T(have_fixed_cols<>::value);
  T(have_fixed_cols<FixedColsTraitsContainer>::value);
  F(have_fixed_cols<VariableColsTraitsContainer>::value);
  T(have_fixed_cols<FixedColsTraitsContainer, FixedColsTraitsContainer>::value);
  F(have_fixed_cols<VariableColsTraitsContainer, FixedColsTraitsContainer>::value);
  F(have_fixed_cols<FixedColsTraitsContainer, VariableColsTraitsContainer>::value);
  F(have_fixed_cols<VariableColsTraitsContainer, VariableColsTraitsContainer>::value);
}

void test_has_fixed_size() {
  using FixedTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableRowsTraitsContainer = TraitsContainer<float, 0, 2, 2, 2>;
  using VariableColsTraitsContainer = TraitsContainer<float, 2, 0, 2, 2>;
  using VariableTraitsContainer = TraitsContainer<float, 0, 0, 2, 2>;

  T(has_fixed_size<FixedTraitsContainer>::value);
  F(has_fixed_size<VariableRowsTraitsContainer>::value);
  F(has_fixed_size<VariableColsTraitsContainer>::value);
  F(has_fixed_size<VariableTraitsContainer>::value);
}

void test_have_fixed_size() {
  using FixedTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableTraitsContainer = TraitsContainer<float, 0, 0, 2, 2>;

  T(have_fixed_size<>::value);
  T(have_fixed_size<FixedTraitsContainer>::value);
  F(have_fixed_size<VariableTraitsContainer>::value);
  T(have_fixed_size<FixedTraitsContainer, FixedTraitsContainer>::value);
  F(have_fixed_size<VariableTraitsContainer, FixedTraitsContainer>::value);
  F(have_fixed_size<FixedTraitsContainer, VariableTraitsContainer>::value);
  F(have_fixed_size<VariableTraitsContainer, VariableTraitsContainer>::value);
}

void test_has_variable_rows() {
  using FixedRowsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableRowsTraitsContainer = TraitsContainer<float, 0, 2, 2, 2>;

  F(has_variable_rows<FixedRowsTraitsContainer>::value);
  T(has_variable_rows<VariableRowsTraitsContainer>::value);
}

void test_have_variable_rows() {
  using FixedRowsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableRowsTraitsContainer = TraitsContainer<float, 0, 2, 2, 2>;

  T(have_variable_rows<>::value);
  F(have_variable_rows<FixedRowsTraitsContainer>::value);
  T(have_variable_rows<VariableRowsTraitsContainer>::value);
  F(have_variable_rows<FixedRowsTraitsContainer, FixedRowsTraitsContainer>::value);
  F(have_variable_rows<VariableRowsTraitsContainer, FixedRowsTraitsContainer>::value);
  F(have_variable_rows<FixedRowsTraitsContainer, VariableRowsTraitsContainer>::value);
  T(have_variable_rows<VariableRowsTraitsContainer, VariableRowsTraitsContainer>::value);
}

void test_has_variable_cols() {
  using FixedColsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableColsTraitsContainer = TraitsContainer<float, 2, 0, 2, 2>;

  F(has_variable_cols<FixedColsTraitsContainer>::value);
  T(has_variable_cols<VariableColsTraitsContainer>::value);
}

void test_have_variable_cols() {
  using FixedColsTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableColsTraitsContainer = TraitsContainer<float, 2, 0, 2, 2>;

  T(have_variable_cols<>::value);
  F(have_variable_cols<FixedColsTraitsContainer>::value);
  T(have_variable_cols<VariableColsTraitsContainer>::value);
  F(have_variable_cols<FixedColsTraitsContainer, FixedColsTraitsContainer>::value);
  F(have_variable_cols<VariableColsTraitsContainer, FixedColsTraitsContainer>::value);
  F(have_variable_cols<FixedColsTraitsContainer, VariableColsTraitsContainer>::value);
  T(have_variable_cols<VariableColsTraitsContainer, VariableColsTraitsContainer>::value);
}

void test_has_variable_size() {
  using FixedTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableRowsTraitsContainer = TraitsContainer<float, 0, 2, 2, 2>;
  using VariableColsTraitsContainer = TraitsContainer<float, 2, 0, 2, 2>;
  using VariableTraitsContainer = TraitsContainer<float, 0, 0, 2, 2>;

  F(has_variable_size<FixedTraitsContainer>::value);
  T(has_variable_size<VariableRowsTraitsContainer>::value);
  T(has_variable_size<VariableColsTraitsContainer>::value);
  T(has_variable_size<VariableTraitsContainer>::value);
}

void test_have_variable_size() {
  using FixedTraitsContainer = TraitsContainer<float, 2, 2>;
  using VariableTraitsContainer = TraitsContainer<float, 0, 0, 2, 2>;

  T(have_variable_size<>::value);
  F(have_variable_size<FixedTraitsContainer>::value);
  T(have_variable_size<VariableTraitsContainer>::value);
  F(have_variable_size<FixedTraitsContainer, FixedTraitsContainer>::value);
  F(have_variable_size<VariableTraitsContainer, FixedTraitsContainer>::value);
  F(have_variable_size<FixedTraitsContainer, VariableTraitsContainer>::value);
  T(have_variable_size<VariableTraitsContainer, VariableTraitsContainer>::value);
}

void test_have_same_rows() {
  using FixedTraitsContainer2x3 = TraitsContainer<float, 2, 3>;
  using VariableTraitsContainer2x5 = TraitsContainer<float, 2, 0, 2, 5>;
  using VariableTraitsContainer4x5 = TraitsContainer<float, 0, 0, 4, 5>;
  using VariableTraitsContainer4x3 = TraitsContainer<float, 0, 3, 4, 3>;

  T(have_same_rows<>::value);
  T(have_same_rows<FixedTraitsContainer2x3>::value);
  T(have_same_rows<FixedTraitsContainer2x3, VariableTraitsContainer2x5>::value);
  F(have_same_rows<VariableTraitsContainer2x5, VariableTraitsContainer4x5>::value);
  T(have_same_rows<VariableTraitsContainer4x3, VariableTraitsContainer4x5>::value);
  T(have_same_rows<FixedTraitsContainer2x3, VariableTraitsContainer2x5, VariableTraitsContainer2x5>::value);
  F(have_same_rows<VariableTraitsContainer2x5, VariableTraitsContainer4x5, VariableTraitsContainer2x5>::value);
  F(have_same_rows<VariableTraitsContainer4x3, VariableTraitsContainer4x5, VariableTraitsContainer2x5>::value);
  F(have_same_rows<FixedTraitsContainer2x3, VariableTraitsContainer2x5, VariableTraitsContainer4x5>::value);
  F(have_same_rows<VariableTraitsContainer2x5, VariableTraitsContainer4x5, VariableTraitsContainer4x5>::value);
  T(have_same_rows<VariableTraitsContainer4x3, VariableTraitsContainer4x5, VariableTraitsContainer4x5>::value);
}

void test_have_same_cols() {
//  using FixedTraitsContainer2x3 = TraitsContainer<float, 2, 3>;
//  using VariableTraitsContainer2x5 = TraitsContainer<float, 2, 0, 2, 5>;
//  using VariableTraitsContainer4x5 = TraitsContainer<float, 0, 0, 4, 5>;
//  using VariableTraitsContainer4x3 = TraitsContainer<float, 0, 3, 4, 3>;

  T(have_same_cols<>::value);
}

int test() {
  UNITY_BEGIN();
  RUN_TEST(test_conjunction);
  RUN_TEST(test_disjunction);
  RUN_TEST(test_negation);
  RUN_TEST(test_is_detected);
  RUN_TEST(test_traits);
  RUN_TEST(test_has_traits);
  RUN_TEST(test_have_traits);
  RUN_TEST(test_have_same_elements);
  RUN_TEST(test_has_floating_point_elements);
  RUN_TEST(test_have_floating_point_elements);
  RUN_TEST(test_has_integral_elements);
  RUN_TEST(test_have_integral_elements);
  RUN_TEST(test_has_fixed_rows);
  RUN_TEST(test_have_fixed_rows);
  RUN_TEST(test_has_fixed_cols);
  RUN_TEST(test_have_fixed_cols);
  RUN_TEST(test_has_fixed_size);
  RUN_TEST(test_have_fixed_size);
  RUN_TEST(test_has_variable_rows);
  RUN_TEST(test_have_variable_rows);
  RUN_TEST(test_has_variable_cols);
  RUN_TEST(test_have_variable_cols);
  RUN_TEST(test_has_variable_size);
  RUN_TEST(test_have_variable_size);
  RUN_TEST(test_have_same_cols);
  return UNITY_END();
}
