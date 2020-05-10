// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types/vector.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_TYPES_VECTOR_HPP_
#define LIN_CORE_TYPES_VECTOR_HPP_

#include "../config.hpp"
#include "../traits.hpp"
#include "tensor.hpp"

#include <type_traits>

namespace lin {

/** @brief Generic vector.
 * 
 *  @tparam T  %Vector element type.
 *  @tparam N  Number of elements at compile time (i.e. number of rows).
 *  @tparam MN Maximum number of elements (i.e. maximum number of rows).
 * 
 *  The template parameters specify the vector's traits. The traits must qualify
 *  this type as a column vector.
 * 
 *  @sa internal::traits
 *  @sa internal::is_col_vector
 * 
 *  @ingroup CORETYPES
 */
template <typename T, size_t N, size_t MN = N>
class Vector : public internal::Tensor<Vector<T, N, MN>> {
  static_assert(internal::is_col_vector<Vector<T, N, MN>>::value,
      "Invalid Vector<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef internal::traits<Vector<T, N, MN>> Traits;

  /** @brief Vector traits information for this type.
   * 
   *  @sa internal::vector_traits
   */
  typedef internal::vector_traits<Vector<T, N, MN>> VectorTraits;

 protected:
  using internal::Tensor<Vector<T, N, MN>>::derived;

 public:
  using internal::Tensor<Vector<T, N, MN>>::Tensor;
  using internal::Tensor<Vector<T, N, MN>>::rows;
  using internal::Tensor<Vector<T, N, MN>>::cols;
  using internal::Tensor<Vector<T, N, MN>>::size;
  using internal::Tensor<Vector<T, N, MN>>::data;
  using internal::Tensor<Vector<T, N, MN>>::eval;
  using internal::Tensor<Vector<T, N, MN>>::resize;
  using internal::Tensor<Vector<T, N, MN>>::operator=;
  using internal::Tensor<Vector<T, N, MN>>::operator();

  constexpr Vector() = default;
  constexpr Vector(Vector<T, N, MN> const &) = default;
  constexpr Vector(Vector<T, N, MN> &&) = default;
  constexpr Vector<T, N, MN> &operator=(Vector<T, N, MN> const &) = default;
  constexpr Vector<T, N, MN> &operator=(Vector<T, N, MN> &&) = default;

  /** @brief Constructs a vector with zero initialized elements are the requested
   *         length.
   * 
   *  @param n Initial length.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the vector's traits.
   * 
   *  @sa internal::has_fixed_rows
   *  @sa internal::has_strictly_bounded_rows
   */
  constexpr Vector(size_t n)
  : internal::Tensor<Vector<T, N, MN>>(n, 1) { }

  /** @brief Constructs a vector with elements initialized from an initializer
   *         list and the requested length.
   * 
   *  @param n    Initial length.
   *  @param list Initializer list.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the vector's traits.
   * 
   *  The initializer list must also be assignable to the vector.
   * 
   *  @sa internal::Mapping::operator=(std::initializer_list<T> const &)
   */
  template <typename U>
  constexpr Vector(size_t n, std::initializer_list<U> const &list)
  : internal::Tensor<Vector<T, N, MN>>(n, 1, list) { }

  /** @brief Resizes the vector's length.
   *  
   *  @param n Length.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the vector's traits.
   * 
   *  @sa internal::has_fixed_rows
   *  @sa internal::has_strictly_bounded_rows
   */
  constexpr void resize(size_t n) {
    resize(n, 1);
  }
};

/** @brief Generic row vector.
 * 
 *  @tparam T  Row vector element type.
 *  @tparam N  Number of elements at compile time (i.e. number of rows).
 *  @tparam MN Maximum number of elements (i.e. maximum number of rows).
 * 
 *  The template parameters specify the row vector's traits. The traits must
 *  qualify this type as a row vector.
 * 
 *  @sa internal::traits
 *  @sa internal::is_row_vector
 * 
 *  @ingroup CORETYPES
 */
template <typename T, size_t N, size_t MN = N>
class RowVector : public internal::Tensor<RowVector<T, N, MN>> {
  static_assert(internal::is_row_vector<RowVector<T, N, MN>>::value,
      "Invalid RowVector<...> parameters");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef internal::traits<RowVector<T, N, MN>> Traits;

  /** @brief Vector traits information for this type.
   * 
   *  @sa internal::vector_traits
   */
  typedef internal::vector_traits<RowVector<T, N, MN>> VectorTraits;

 protected:
  using internal::Tensor<RowVector<T, N, MN>>::derived;

 public:
  using internal::Tensor<RowVector<T, N, MN>>::Tensor;
  using internal::Tensor<RowVector<T, N, MN>>::rows;
  using internal::Tensor<RowVector<T, N, MN>>::cols;
  using internal::Tensor<RowVector<T, N, MN>>::size;
  using internal::Tensor<RowVector<T, N, MN>>::data;
  using internal::Tensor<RowVector<T, N, MN>>::eval;
  using internal::Tensor<RowVector<T, N, MN>>::resize;
  using internal::Tensor<RowVector<T, N, MN>>::operator=;
  using internal::Tensor<RowVector<T, N, MN>>::operator();

  constexpr RowVector() = default;
  constexpr RowVector(RowVector<T, N, MN> const &) = default;
  constexpr RowVector(RowVector<T, N, MN> &&) = default;
  constexpr RowVector<T, N, MN> &operator=(RowVector<T, N, MN> const &) = default;
  constexpr RowVector<T, N, MN> &operator=(RowVector<T, N, MN> &&) = default;

  /** @brief Constructs a row vector with zero initialized elements are the
   *         requested length.
   * 
   *  @param n Initial length.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the row vector's traits.
   * 
   *  @sa internal::has_fixed_rows
   *  @sa internal::has_strictly_bounded_rows
   */
  constexpr RowVector(size_t n)
  : internal::Tensor<RowVector<T, N, MN>>(1, n) { }

  /** @brief Constructs a row vector with elements initialized from an initializer
   *         list and the requested length.
   * 
   *  @param n    Initial length.
   *  @param list Initializer list.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the row vector's traits.
   * 
   *  The initializer list must also be assignable to the row vector.
   * 
   *  @sa internal::Mapping::operator=(std::initializer_list<T> const &)
   */
  template <typename U>
  constexpr RowVector(size_t n, std::initializer_list<U> const &list)
  : internal::Tensor<RowVector<T, N, MN>>(1, n, list) { }

  /** @brief Resizes the row vector's length.
   *  
   *  @param n Length.
   * 
   *  Lin assertion errors will be triggered if the requested length isn't
   *  possible given the row vector's traits.
   * 
   *  @sa internal::has_fixed_cols
   *  @sa internal::has_strictly_bounded_cols
   */
  constexpr void resize(size_t n) {
    resize(1, n);
  }
};

/** @weakgroup CORETYPES
 *  @{
 */

/** @brief Generic float vector.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa Vector
 */
template <size_t N, size_t MN = N>
using Vectorf = Vector<float, N, MN>;

typedef Vectorf<2> Vector2f; ///< Two dimensional float vector.
typedef Vectorf<3> Vector3f; ///< Three dimensional float vector.
typedef Vectorf<4> Vector4f; ///< Four dimensional float vector.

/** @brief Generic double vector.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa Vector
 */
template <size_t N, size_t MN = N>
using Vectord = Vector<double, N, MN>;

typedef Vectord<2> Vector2d; ///< Two dimensional double vector.
typedef Vectord<3> Vector3d; ///< Three dimensional double vector.
typedef Vectord<4> Vector4d; ///< Four dimensional double vector.

/** @brief Generic float row vector.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa RowVector
 */
template <size_t N, size_t MN = N>
using RowVectorf = RowVector<float, N, MN>;

typedef RowVectorf<2> RowVector2f; ///< Two dimensional float row vector.
typedef RowVectorf<3> RowVector3f; ///< Three dimensional float row vector.
typedef RowVectorf<4> RowVector4f; ///< Four dimensional float row vector.

/** @brief Generic double row vector.
 * 
 *  @tparam N  Length at compile time
 *  @tparam MN Max length.
 * 
 *  @sa internal::traits
 *  @sa RowVector
 */
template <size_t N, size_t MN = N>
using RowVectord = RowVector<double, N, MN>;

typedef RowVectord<2> RowVector2d; ///< Two dimensional double row vector.
typedef RowVectord<3> RowVector3d; ///< Three dimensional double row vector.
typedef RowVectord<4> RowVector4d; ///< Four dimensional double row vector.

/** @}
 */

namespace internal {

template <typename T, size_t N, size_t MN>
struct _elem<Vector<T, N, MN>> {
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct _dims<Vector<T, N, MN>> {
  static constexpr size_t rows = N;
  static constexpr size_t cols = 1;
  static constexpr size_t max_rows = MN;
  static constexpr size_t max_cols = 1;
};

template <class C>
struct _eval<C, std::enable_if_t<is_col_vector<C>::value>> {
  typedef Vector<
      _elem_t<C>,
      _dims<C>::rows,
      _dims<C>::max_rows
    > type;
};

template <typename T, size_t N, size_t MN>
struct _elem<RowVector<T, N, MN>> {
  typedef T type;
};

template <typename T, size_t N, size_t MN>
struct _dims<RowVector<T, N, MN>> {
  static constexpr size_t rows = 1;
  static constexpr size_t cols = N;
  static constexpr size_t max_rows = 1;
  static constexpr size_t max_cols = MN;
};

template <class C>
struct _eval<C, std::enable_if_t<is_row_vector<C>::value>> {
  typedef RowVector<
      _elem_t<C>,
      _dims<C>::cols,
      _dims<C>::max_cols
    > type;
};
}  // namespace internal
}  // namespace lin

#endif
