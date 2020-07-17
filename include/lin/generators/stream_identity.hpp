// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/stream_constants.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_STREAM_IDENTITY_HPP_
#define LIN_GENERATORS_STREAM_IDENTITY_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Tensor stream where all element accesses specify an identity matrix.
 *
 *  @tparam T  %Stream element type.
 *  @tparam R  Rows at compile time.
 *  @tparam C  Columns at compile time.
 *  @tparam MR Maximum rows at compile time.
 *  @tparam MC Maximum columns at compile time.
 *
 *  This is most commonly use to implement the identity generator function. The
 *  tensor parameters specified must be considered a square matrix.
 *
 *  @sa identity
 *  @sa internal::is_matrix
 *  @sa internal::is_square
 *
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR, size_t MC>
class StreamIdentity : public Stream<StreamIdentity<T, R, C, MR, MC>>,
    public Dimensions<StreamIdentity<T, R, C, MR, MC>> {
  static_assert(is_square<StreamIdentity<T, R, C, MR, MC>>::value,
      "StreamIdentity<...> must have square traits");

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamIdentity<T, R, C, MR, MC>> Traits;

 protected:
  using Stream<StreamIdentity<T, R, C, MR, MC>>::derived;
  using Dimensions<StreamIdentity<T, R, C, MR, MC>>::resize;

 public:
  using Stream<StreamIdentity<T, R, C, MR, MC>>::size;
  using Stream<StreamIdentity<T, R, C, MR, MC>>::eval;
  using Dimensions<StreamIdentity<T, R, C, MR, MC>>::rows;
  using Dimensions<StreamIdentity<T, R, C, MR, MC>>::cols;

  constexpr StreamIdentity() = delete;
  constexpr StreamIdentity(StreamIdentity<T, R, C, MR, MC> const &) = default;
  constexpr StreamIdentity(StreamIdentity<T, R, C, MR, MC> &&) = default;
  constexpr StreamIdentity<T, R, C, MR, MC> &operator=(StreamIdentity<T, R, C, MR, MC> const &) = default;
  constexpr StreamIdentity<T, R, C, MR, MC> &operator=(StreamIdentity<T, R, C, MR, MC> &&) = default;

  /** @brief Constructs a tensor stream that specifies the identity matrix.
   *
   *  @param[in] r Row count.
   *  @param[in] c Column count.
   */
  constexpr StreamIdentity(size_t r, size_t c) {
    LIN_ASSERT(r == c);

    resize(r, c);
  }

  /** @brief Retrieves the requested tensor elements value, which, in this case
   *         is one when on the diagonal and zero otherwise.
   *
   *  @param i Row index.
   *  @param j Column index.
   *
   *  @return Value of the tensor element.
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT(0 <= i && i <= rows());
    LIN_ASSERT(0 <= j && j <= cols());

    return typename Traits::elem_t(i == j);
  }

  /** @brief Retrieves the requested tensor elements value, which, in this case
   *         is one when on the diagonal and zero otherwise.
   *
   *  @param i Index.
   *
   *  @return Value of the tensor element.
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    LIN_ASSERT(0 <= i && i <= size());

    return (*this)(i / cols(), i % cols());
  }
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _elem<StreamIdentity<T, R, C, MR, MC>> {
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _dims<StreamIdentity<T, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

#endif
