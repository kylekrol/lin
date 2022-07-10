// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/const_vector_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_CONST_VECTOR_VIEW_HPP_
#define LIN_VIEWS_CONST_VECTOR_VIEW_HPP_

#include "../core.hpp"
#include "const_tensor_view.hpp"

namespace lin {
namespace internal {

/** @brief Generic constant vector view.
 * 
 *  @tparam T  Constant vector view element type.
 *  @tparam N  Number of elements at compile time (i.e. number of rows).
 *  @tparam MN Maximum number of elements (i.e. maximum number of rows).
 * 
 *  The template parameters specify the vector views's traits. The traits must
 *  qualify this type as a column vector.
 * 
 *  @sa internal::traits
 *  @sa internal::is_col_vector
 * 
 *  @ingroup VIEWS
 */
template <typename T, size_t N, size_t MN = N>
class ConstVectorView : public ConstTensorView<ConstVectorView<T, N, MN>> {
  static_assert(is_col_vector<ConstVectorView<T, N, MN>>::value,
      "Invalid ConstVectorView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<ConstVectorView<T, N, MN>> Traits;

  /** @brief Vector traits information for this type.
   * 
   *  @sa internal::vector_traits
   */
  typedef vector_traits<ConstVectorView<T, N, MN>> VectorTraits;

 protected:
  using ConstTensorView<ConstVectorView<T, N, MN>>::derived;

 public:
  using ConstTensorView<ConstVectorView<T, N, MN>>::ConstTensorView;
  using ConstTensorView<ConstVectorView<T, N, MN>>::rows;
  using ConstTensorView<ConstVectorView<T, N, MN>>::cols;
  using ConstTensorView<ConstVectorView<T, N, MN>>::size;
  using ConstTensorView<ConstVectorView<T, N, MN>>::data;
  using ConstTensorView<ConstVectorView<T, N, MN>>::eval;
  using ConstTensorView<ConstVectorView<T, N, MN>>::resize;
  using ConstTensorView<ConstVectorView<T, N, MN>>::operator();

  constexpr ConstVectorView() = delete;
  constexpr ConstVectorView(ConstVectorView<T, N, MN> const &) = default;
  constexpr ConstVectorView(ConstVectorView<T, N, MN> &&) = default;
  constexpr ConstVectorView<T, N, MN> &operator=(ConstVectorView<T, N, MN> const &) = default;
  constexpr ConstVectorView<T, N, MN> &operator=(ConstVectorView<T, N, MN> &&) = default;

  /** @brief Constructs a constant vector view with the provided backing array
   *         and requested length.
   *
   *  @param elems Constant element backing array.
   *  @param n     Initial length.
   * 
   *  The backing array should be at least as large as the maximum length of the
   *  vector (see internal::traits information).
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the vector view's traits.
   * 
   *  @sa internal::has_fixed_rows
   *  @sa internal::has_strictly_bounded_rows
   */
  constexpr ConstVectorView(typename Traits::elem_t const *elems, size_t n)
  : ConstTensorView<ConstVectorView<T, N, MN>>(elems, n, 1) { }

  /** @brief Resizes the constant vector view's length.
   *  
   *  @param n Length.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the vector view's traits.
   * 
   *  @sa internal::has_fixed_rows
   *  @sa internal::has_strictly_bounded_rows
   */
  constexpr void resize(size_t n) {
    resize(n, 1);
  }
};

/** @brief Generic constant row vector view.
 * 
 *  @tparam T  Constant row vector view element type.
 *  @tparam N  Number of elements at compile time (i.e. number of rows).
 *  @tparam MN Maximum number of elements (i.e. maximum number of rows).
 * 
 *  The template parameters specify the row vector views's traits. The traits
 *  must qualify this type as a row vector.
 * 
 *  @sa internal::traits
 *  @sa internal::is_row_vector
 * 
 *  @ingroup VIEWS
 */
template <typename T, size_t N, size_t MN = N>
class ConstRowVectorView : public ConstTensorView<ConstRowVectorView<T, N, MN>> {
  static_assert(is_row_vector<ConstRowVectorView<T, N, MN>>::value,
      "Invalid ConstRowVectorView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<ConstRowVectorView<T, N, MN>> Traits;

  /** @brief Vector traits information for this type.
   * 
   *  @sa internal::vector_traits
   */
  typedef vector_traits<ConstRowVectorView<T, N, MN>> VectorTraits;

 protected:
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::derived;

 public:
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::ConstTensorView;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::rows;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::cols;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::size;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::data;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::eval;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::resize;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::operator=;
  using ConstTensorView<ConstRowVectorView<T, N, MN>>::operator();

  constexpr ConstRowVectorView() = default;
  constexpr ConstRowVectorView(ConstRowVectorView<T, N, MN> const &) = default;
  constexpr ConstRowVectorView(ConstRowVectorView<T, N, MN> &&) = default;
  constexpr ConstRowVectorView<T, N, MN> &operator=(ConstRowVectorView<T, N, MN> const &) = default;
  constexpr ConstRowVectorView<T, N, MN> &operator=(ConstRowVectorView<T, N, MN> &&) = default;

  /** @brief Constructs a vector view with the provided backing array and
   *         requested length.
   *
   *  @param elems Constant element backing array.
   *  @param n     Initial length.
   * 
   *  The backing array should be at least as large as the maximum length of the
   *  row vector (see internal::traits information).
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the row vector view's traits.
   * 
   *  @sa internal::has_fixed_cols
   *  @sa internal::has_strictly_bounded_cols
   */
  constexpr ConstRowVectorView(typename Traits::elem_t const *elems, size_t n)
  : ConstTensorView<ConstRowVectorView<T, N, MN>>(elems, 1, n) { }

  /** @brief Resizes the row vector view's length.
   *  
   *  @param n Length.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the row vector view's traits.
   * 
   *  @sa internal::has_fixed_cols
   *  @sa internal::has_strictly_bounded_cols
   */
  constexpr void resize(size_t n) {
    resize(1, n);
  }
};

template <typename T, size_t N, size_t MN>
struct _elem<ConstVectorView<T, N, MN>> {
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct _dims<ConstVectorView<T, N, MN>> {
  static constexpr size_t rows = N;
  static constexpr size_t cols = 1;
  static constexpr size_t max_rows = MN;
  static constexpr size_t max_cols = 1;
};

template <typename T, size_t N, size_t MN>
struct _elem<ConstRowVectorView<T, N, MN>> {
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct _dims<ConstRowVectorView<T, N, MN>> {
  static constexpr size_t rows = 1;
  static constexpr size_t cols = N;
  static constexpr size_t max_rows = 1;
  static constexpr size_t max_cols = MN;
};
}  // namespace internal
}  // namespace lin

#endif
