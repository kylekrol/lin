// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views/vector_view.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_VIEWS_VECTOR_VIEW_HPP_
#define LIN_VIEWS_VECTOR_VIEW_HPP_

#include "../core.hpp"
#include "tensor_view.hpp"

namespace lin {

/** @brief Generic vector view.
 * 
 *  @tparam T  %Vector view element type.
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
class VectorView : public internal::TensorView<VectorView<T, N, MN>> {
  static_assert(internal::is_col_vector<VectorView<T, N, MN>>::value,
      "Invalid VectorView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef internal::traits<VectorView<T, N, MN>> Traits;

  /** @brief Vector traits information for this type.
   * 
   *  @sa internal::vector_traits
   */
  typedef internal::vector_traits<VectorView<T, N, MN>> VectorTraits;

 protected:
  using internal::TensorView<VectorView<T, N, MN>>::derived;

 public:
  using internal::TensorView<VectorView<T, N, MN>>::TensorView;
  using internal::TensorView<VectorView<T, N, MN>>::rows;
  using internal::TensorView<VectorView<T, N, MN>>::cols;
  using internal::TensorView<VectorView<T, N, MN>>::size;
  using internal::TensorView<VectorView<T, N, MN>>::data;
  using internal::TensorView<VectorView<T, N, MN>>::eval;
  using internal::TensorView<VectorView<T, N, MN>>::resize;
  using internal::TensorView<VectorView<T, N, MN>>::operator=;
  using internal::TensorView<VectorView<T, N, MN>>::operator();

  constexpr VectorView() = default;
  constexpr VectorView(VectorView<T, N, MN> const &) = default;
  constexpr VectorView(VectorView<T, N, MN> &&) = default;
  constexpr VectorView<T, N, MN> &operator=(VectorView<T, N, MN> const &) = default;
  constexpr VectorView<T, N, MN> &operator=(VectorView<T, N, MN> &&) = default;

  /** @brief Constructs a vector view with the provided backing array and
   *         requested length.
   *
   *  @param elems Element backing array.
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
  constexpr VectorView(typename Traits::elem_t *elems, size_t n)
  : internal::TensorView<VectorView<T, N, MN>>(elems, n, 1) { }

  /** @brief Resizes the vector view's length.
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

/** @brief Generic row vector view.
 * 
 *  @tparam T  Row vector element type.
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
class RowVectorView : public internal::TensorView<RowVectorView<T, N, MN>> {
  static_assert(internal::is_row_vector<RowVectorView<T, N, MN>>::value,
      "Invalid RowVectorView<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef internal::traits<RowVectorView<T, N, MN>> Traits;

  /** @brief Vector traits information for this type.
   * 
   *  @sa internal::vector_traits
   */
  typedef internal::vector_traits<RowVectorView<T, N, MN>> VectorTraits;

 protected:
  using internal::TensorView<RowVectorView<T, N, MN>>::derived;

 public:
  using internal::TensorView<RowVectorView<T, N, MN>>::TensorView;
  using internal::TensorView<RowVectorView<T, N, MN>>::rows;
  using internal::TensorView<RowVectorView<T, N, MN>>::cols;
  using internal::TensorView<RowVectorView<T, N, MN>>::size;
  using internal::TensorView<RowVectorView<T, N, MN>>::data;
  using internal::TensorView<RowVectorView<T, N, MN>>::eval;
  using internal::TensorView<RowVectorView<T, N, MN>>::resize;
  using internal::TensorView<RowVectorView<T, N, MN>>::operator=;
  using internal::TensorView<RowVectorView<T, N, MN>>::operator();

  constexpr RowVectorView() = default;
  constexpr RowVectorView(RowVectorView<T, N, MN> const &) = default;
  constexpr RowVectorView(RowVectorView<T, N, MN> &&) = default;
  constexpr RowVectorView<T, N, MN> &operator=(RowVectorView<T, N, MN> const &) = default;
  constexpr RowVectorView<T, N, MN> &operator=(RowVectorView<T, N, MN> &&) = default;

  /** @brief Constructs a vector view with the provided backing array and
   *         requested length.
   *
   *  @param elems Element backing array.
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
  constexpr RowVectorView(typename Traits::elem_t *elems, size_t n)
  : internal::TensorView<RowVectorView<T, N, MN>>(elems, 1, n) { }

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

/** @weakgroup VIEWS
 *  @{
 */


/** @brief Generic float vector view.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa VectorView
 */
template <size_t N, size_t MN = N>
using VectorViewf = VectorView<float, N, MN>;

typedef VectorViewf<2> VectorView2f; ///< Two dimensional float vector view.
typedef VectorViewf<3> VectorView3f; ///< Three dimensional float vector view.
typedef VectorViewf<4> VectorView4f; ///< Four dimensional float vector view.

/** @brief Generic double vector view.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa VectorView
 */
template <size_t N, size_t MN = N>
using VectorViewd = VectorView<double, N, MN>;

typedef VectorViewd<2> VectorView2d; ///< Two dimensional double vector view.
typedef VectorViewd<3> VectorView3d; ///< Three dimensional double vector view.
typedef VectorViewd<4> VectorView4d; ///< Four dimensional double vector view.

/** @brief Generic float row vector view.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa RowVectorView
 */
template <size_t N, size_t MN = N>
using RowVectorViewf = RowVectorView<float, N, MN>;

typedef RowVectorViewf<2> RowVectorView2f; ///< Two dimensional float row vector view.
typedef RowVectorViewf<3> RowVectorView3f; ///< Three dimensional float row vector view.
typedef RowVectorViewf<4> RowVectorView4f; ///< Four dimensional float row vector view.

/** @brief Generic double row vector view.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa RowVectorView
 */
template <size_t N, size_t MN = N>
using RowVectorViewd = RowVectorView<double, N, MN>;

typedef RowVectorViewd<2> RowVectorView2d; ///< Two dimensional double row vector view.
typedef RowVectorViewd<3> RowVectorView3d; ///< Three dimensional double row vector view.
typedef RowVectorViewd<4> RowVectorView4d; ///< Four dimensional double row vector view.

/** @}
 */

namespace internal {

template <typename T, size_t N, size_t MN>
struct _elem<VectorView<T, N, MN>> {
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct _dims<VectorView<T, N, MN>> {
  static constexpr size_t rows = N;
  static constexpr size_t cols = 1;
  static constexpr size_t max_rows = MN;
  static constexpr size_t max_cols = 1;
};

template <typename T, size_t N, size_t MN>
struct _elem<RowVectorView<T, N, MN>> {
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct _dims<RowVectorView<T, N, MN>> {
  static constexpr size_t rows = 1;
  static constexpr size_t cols = N;
  static constexpr size_t max_rows = 1;
  static constexpr size_t max_cols = MN;
};
}  // namespace internal
}  // namespace lin

#endif
