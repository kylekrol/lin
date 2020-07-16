// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/stream_constants.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_STREAM_CONSTANTS_HPP_
#define LIN_GENERATORS_STREAM_CONSTANTS_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @brief Tensor stream where all elements are the same constant value.
 *
 *  @sa consts
 *  @sa nans
 *  @sa ones
 *  @sa zeros
 *
 *  @ingroup GENERATORS
 */
template <typename T, size_t R, size_t C, size_t MR, size_t MC>
class StreamConstants : public Stream<StreamConstants<T, R, C, MR, MC>>,
    public Dimensions<StreamConstants<T, R, C, MR, MC>> {
 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<StreamConstants<T, R, C, MR, MC>> Traits;

 private:
  /** @brief Constant value returned by element accesses.
   */
  typename Traits::elem_t const t;

 protected:
  using Stream<StreamConstants<T, R, C, MR, MC>>::derived;
  using Dimensions<StreamConstants<T, R, C, MR, MC>>::resize;

 public:
  using Stream<StreamConstants<T, R, C, MR, MC>>::size;
  using Stream<StreamConstants<T, R, C, MR, MC>>::eval;
  using Dimensions<StreamConstants<T, R, C, MR, MC>>::rows;
  using Dimensions<StreamConstants<T, R, C, MR, MC>>::cols;

  constexpr StreamConstants() = delete;
  constexpr StreamConstants(StreamConstants<T, R, C, MR, MC> const &) = default;
  constexpr StreamConstants(StreamConstants<T, R, C, MR, MC> &&) = default;
  constexpr StreamConstants<T, R, C, MR, MC> &operator=(StreamConstants<T, R, C, MR, MC> const &) = default;
  constexpr StreamConstants<T, R, C, MR, MC> &operator=(StreamConstants<T, R, C, MR, MC> &&) = default;

  /** @brief
   */
  constexpr StreamConstants(T t, size_t r, size_t c) : t(t) {
    resize(r, c);
  }

  /** @brief
   */
  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const {
    LIN_ASSERT(0 <= i && i <= rows());
    LIN_ASSERT(0 <= j && j <= cols());

    return t;
  }

  /** @brief
   */
  constexpr typename Traits::elem_t operator()(size_t i) const {
    LIN_ASSERT(0 <= i && i <= size());

    return t;
  }
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _elem<StreamConstants<T, R, C, MR, MC>> {
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct _dims<StreamConstants<T, R, C, MR, MC>> {
  static constexpr size_t rows = R;
  static constexpr size_t cols = C;
  static constexpr size_t max_rows = MR;
  static constexpr size_t max_cols = MC;
};
}  // namespace internal
}  // namespace lin

#endif
