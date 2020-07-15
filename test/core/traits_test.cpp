// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

#include <lin/core/config.hpp>
#include <lin/core/traits.hpp>

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

TEST(CoreTraits, All) {
  ASSERT_TRUE(true);
}

template <typename U, typename V>
using assign_expr = decltype(std::declval<U &>() = std::declval<V &>());

namespace lin {
namespace internal {

template <typename T, lin::size_t R, lin::size_t C, lin::size_t MR, lin::size_t MC>
class Traits { };

template <typename T, lin::size_t R, lin::size_t C, lin::size_t MR, lin::size_t MC>
struct _elem<Traits<T, R, C, MR, MC>> {
  typedef T type;
};

template <typename T, lin::size_t R, lin::size_t C, lin::size_t MR, lin::size_t MC>
struct _dims<Traits<T, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

using F = std::false_type;
using T = std::true_type;

using namespace lin::internal;


// Test traits/utilities.hpp

static_assert( is_detected<assign_expr, double, float>(), "");
static_assert(!is_detected<assign_expr, void *, float>(), "");

static_assert( conjunction<>(), "");
static_assert( conjunction<T>(), "");
static_assert(!conjunction<F>(), "");
static_assert(!conjunction<F, F>(), "");
static_assert(!conjunction<T, F>(), "");
static_assert(!conjunction<F, T>(), "");
static_assert( conjunction<T, T>(), "");
static_assert( conjunction<T, T, T>(), "");
static_assert(!conjunction<T, T, F>(), "");

static_assert(!disjunction<>(), "");
static_assert( disjunction<T>(), "");
static_assert(!disjunction<F>(), "");
static_assert(!disjunction<F, F>(), "");
static_assert( disjunction<T, F>(), "");
static_assert( disjunction<F, T>(), "");
static_assert( disjunction<T, T>(), "");
static_assert(!disjunction<F, F, F>(), "");
static_assert( disjunction<F, F, T>(), "");

static_assert( negation<F>(), "");
static_assert(!negation<T>(), "");


// Test traits/tensor.hpp

using TraitsFFf = Traits<float, 3, 4, 3, 4>;
using TraitsFBf = Traits<float, 3, 0, 3, 4>;
using TraitsBFf = Traits<float, 0, 4, 3, 4>;
using TraitsBBf = Traits<float, 0, 0, 3, 4>;
using TraitsXFf = Traits<float, 0, 4, 0, 4>;
using TraitsXXf = Traits<float, 0, 0, 0, 0>;

using TraitsFFd = Traits<double, 3, 4, 3, 4>;
using TraitsFBd = Traits<double, 3, 0, 3, 4>;
using TraitsBFd = Traits<double, 0, 4, 3, 4>;
using TraitsBBd = Traits<double, 0, 0, 3, 4>;

using TraitsFFi = Traits<int, 3, 4, 3, 4>;
using TraitsFBi = Traits<int, 3, 0, 3, 4>;
using TraitsBFi = Traits<int, 0, 4, 3, 4>;
using TraitsBBi = Traits<int, 0, 0, 3, 4>;

static_assert( has_fixed_rows<TraitsFFf>(), "");
static_assert( has_fixed_rows<TraitsFBf>(), "");
static_assert(!has_fixed_rows<TraitsBFf>(), "");
static_assert(!has_fixed_rows<TraitsBBf>(), "");
static_assert(!has_fixed_rows<TraitsXXf>(), "");

static_assert( has_fixed_cols<TraitsFFf>(), "");
static_assert(!has_fixed_cols<TraitsFBf>(), "");
static_assert( has_fixed_cols<TraitsBFf>(), "");
static_assert(!has_fixed_cols<TraitsBBf>(), "");
static_assert(!has_fixed_cols<TraitsXXf>(), "");

static_assert( has_fixed_dimensions<TraitsFFf>(), "");
static_assert(!has_fixed_dimensions<TraitsFBf>(), "");
static_assert(!has_fixed_dimensions<TraitsBFf>(), "");
static_assert(!has_fixed_dimensions<TraitsBBf>(), "");
static_assert(!has_fixed_dimensions<TraitsXXf>(), "");

static_assert(!has_strictly_bounded_rows<TraitsFFf>(), "");
static_assert(!has_strictly_bounded_rows<TraitsFBf>(), "");
static_assert( has_strictly_bounded_rows<TraitsBFf>(), "");
static_assert( has_strictly_bounded_rows<TraitsBBf>(), "");
static_assert(!has_strictly_bounded_rows<TraitsXXf>(), "");

static_assert(!has_strictly_bounded_cols<TraitsFFf>(), "");
static_assert( has_strictly_bounded_cols<TraitsFBf>(), "");
static_assert(!has_strictly_bounded_cols<TraitsBFf>(), "");
static_assert( has_strictly_bounded_cols<TraitsBBf>(), "");
static_assert(!has_strictly_bounded_cols<TraitsXXf>(), "");

static_assert(!has_strictly_bounded_dimensions<TraitsFFf>(), "");
static_assert(!has_strictly_bounded_dimensions<TraitsFBf>(), "");
static_assert(!has_strictly_bounded_dimensions<TraitsBFf>(), "");
static_assert( has_strictly_bounded_dimensions<TraitsBBf>(), "");
static_assert(!has_strictly_bounded_dimensions<TraitsXXf>(), "");

static_assert( has_bounded_rows<TraitsFFf>(), "");
static_assert( has_bounded_rows<TraitsFBf>(), "");
static_assert( has_bounded_rows<TraitsBFf>(), "");
static_assert( has_bounded_rows<TraitsBBf>(), "");
static_assert(!has_bounded_rows<TraitsXXf>(), "");

static_assert( has_bounded_cols<TraitsFFf>(), "");
static_assert( has_bounded_cols<TraitsFBf>(), "");
static_assert( has_bounded_cols<TraitsBFf>(), "");
static_assert( has_bounded_cols<TraitsBBf>(), "");
static_assert(!has_bounded_cols<TraitsXXf>(), "");

static_assert( has_bounded_dimensions<TraitsFFf>(), "");
static_assert( has_bounded_dimensions<TraitsFBf>(), "");
static_assert( has_bounded_dimensions<TraitsBFf>(), "");
static_assert( has_bounded_dimensions<TraitsBBf>(), "");
static_assert(!has_bounded_dimensions<TraitsXFf>(), "");
static_assert(!has_bounded_dimensions<TraitsXXf>(), "");

static_assert( has_valid_traits<TraitsFFf>(), "");
static_assert( has_valid_traits<TraitsFBf>(), "");
static_assert( has_valid_traits<TraitsBFf>(), "");
static_assert( has_valid_traits<TraitsBBf>(), "");
static_assert(!has_valid_traits<TraitsXFf>(), "");
static_assert(!has_valid_traits<TraitsXXf>(), "");
static_assert(!has_valid_traits<Traits<void, 5, 1, 5, 1>>(), "");

static_assert( is_tall<Traits<float, 5, 5, 5, 5>>(), "");
static_assert( is_tall<Traits<float, 6, 5, 6, 5>>(), "");
static_assert(!is_tall<Traits<float, 5, 6, 5, 6>>(), "");

static_assert( is_short<Traits<float, 5, 5, 5, 5>>(), "");
static_assert(!is_short<Traits<float, 6, 5, 6, 5>>(), "");
static_assert( is_short<Traits<float, 5, 6, 5, 6>>(), "");

static_assert( is_square<Traits<float, 5, 5, 5, 5>>(), "");
static_assert(!is_square<Traits<float, 6, 5, 6, 5>>(), "");
static_assert(!is_square<Traits<float, 5, 6, 5, 6>>(), "");

static_assert( have_same_elements<>(), "");
static_assert( have_same_elements<TraitsFFf>(), "");
static_assert( have_same_elements<TraitsFFf, TraitsBFf>(), "");
static_assert(!have_same_elements<TraitsFFf, TraitsFFd>(), "");
static_assert( have_same_elements<TraitsFFf, TraitsFBf, TraitsBFf>(), "");
static_assert(!have_same_elements<TraitsFFf, TraitsFBd, TraitsBFf>(), "");

static_assert( have_floating_point_elements<>(), "");
static_assert( have_floating_point_elements<TraitsFFf>(), "");
static_assert( have_floating_point_elements<TraitsFBd, TraitsFFf>(), "");
static_assert(!have_floating_point_elements<TraitsFBd, TraitsFFi>(), "");

static_assert( have_integral_elements<>(), "");
static_assert(!have_integral_elements<TraitsFFf>(), "");
static_assert(!have_integral_elements<TraitsFBi, TraitsFFf>(), "");
static_assert( have_integral_elements<TraitsFBi, TraitsFFi>(), "");

static_assert( have_same_rows<>(), "");
static_assert( have_same_rows<TraitsFFf>(), "");
static_assert( have_same_rows<TraitsFFf, TraitsFFd>(), "");
static_assert(!have_same_rows<TraitsFFf, TraitsBFd>(), "");
static_assert( have_same_rows<TraitsFFf, TraitsFBd>(), "");

static_assert( have_same_cols<>(), "");
static_assert( have_same_cols<TraitsFFf>(), "");
static_assert( have_same_cols<TraitsFFf, TraitsFFd>(), "");
static_assert( have_same_cols<TraitsFFf, TraitsBFd>(), "");
static_assert(!have_same_cols<TraitsFFf, TraitsFBd>(), "");

static_assert( have_same_dimensions<>(), "");
static_assert( have_same_dimensions<TraitsFFf>(), "");
static_assert( have_same_dimensions<TraitsFFf, TraitsFFd>(), "");
static_assert(!have_same_dimensions<TraitsFFf, TraitsBFd>(), "");
static_assert(!have_same_dimensions<TraitsFFf, TraitsFBd>(), "");

static_assert( have_same_traits<>(), "");
static_assert( have_same_traits<TraitsFFf>(), "");
static_assert(!have_same_traits<TraitsFFf, TraitsFFd>(), "");
static_assert(!have_same_traits<TraitsFFf, TraitsBFf>(), "");
static_assert( have_same_traits<TraitsFFf, TraitsFFf>(), "");

// Test traits/vector.hpp

using TraitsVFf = Traits<float, 5, 1, 5, 1>;
using TraitsVBf = Traits<float, 0, 1, 5, 1>;
using TraitsRFf = Traits<float, 1, 5, 1, 5>;
using TraitsRBf = Traits<float, 1, 0, 1, 5>;

using TraitsVFd = Traits<double, 5, 1, 5, 1>;
using TraitsVBd = Traits<double, 0, 1, 5, 1>;
using TraitsRFd = Traits<double, 1, 5, 1, 5>;
using TraitsRBd = Traits<double, 1, 0, 1, 5>;

static_assert(!is_row_vector<TraitsVFf>(), "");
static_assert(!is_row_vector<TraitsVBf>(), "");
static_assert( is_row_vector<TraitsRFf>(), "");
static_assert( is_row_vector<TraitsRBf>(), "");
static_assert(!is_row_vector<TraitsFFf>(), "");

static_assert( is_col_vector<TraitsVFf>(), "");
static_assert( is_col_vector<TraitsVBf>(), "");
static_assert(!is_col_vector<TraitsRFf>(), "");
static_assert(!is_col_vector<TraitsRBf>(), "");
static_assert(!is_col_vector<TraitsFFf>(), "");

static_assert( is_vector<TraitsVFf>(), "");
static_assert( is_vector<TraitsVBf>(), "");
static_assert( is_vector<TraitsRFf>(), "");
static_assert( is_vector<TraitsRBf>(), "");
static_assert(!is_vector<TraitsFFf>(), "");

static_assert(_vector_dims<TraitsVFf>::length     == 5, "");
static_assert(_vector_dims<TraitsVFf>::max_length == 5, "");
static_assert(_vector_dims<TraitsVBf>::length     == 0, "");
static_assert(_vector_dims<TraitsVBf>::max_length == 5, "");
static_assert(_vector_dims<TraitsRBf>::length     == 0, "");
static_assert(_vector_dims<TraitsRBf>::max_length == 5, "");

static_assert( have_same_vector_dimensions<>(), "");
static_assert( have_same_vector_dimensions<TraitsVBf>(), "");
static_assert(!have_same_vector_dimensions<TraitsVBf, TraitsVFd>(), "");
static_assert( have_same_vector_dimensions<TraitsVBf, TraitsVBd>(), "");
static_assert( have_same_vector_dimensions<TraitsRFf, TraitsVFd>(), "");
static_assert(!have_same_vector_dimensions<TraitsRFf, TraitsVFd, TraitsVBd>(), "");

static_assert( have_same_vector_traits<>(), "");
static_assert( have_same_vector_traits<TraitsVBf>(), "");
static_assert(!have_same_vector_traits<TraitsVBf, TraitsVFd>(), "");
static_assert(!have_same_vector_traits<TraitsVBf, TraitsVBd>(), "");
static_assert( have_same_vector_traits<TraitsRFf, TraitsVFf>(), "");
static_assert(!have_same_vector_traits<TraitsRFf, TraitsVFd>(), "");
static_assert(!have_same_vector_traits<TraitsRFf, TraitsVFd, TraitsVBd>(), "");

// Test traits/matrix.hpp

static_assert(!is_matrix<TraitsVFf>(), "");
static_assert(!is_matrix<TraitsRBd>(), "");
static_assert( is_matrix<TraitsBFf>(), "");
