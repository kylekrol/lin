// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_BASE_REFERENCE_HPP_
#define LIN_INCLUDE_CORE_TENSOR_BASE_REFERENCE_HPP_

#include "base.hpp"
#include "dimensions.hpp"

#include <cassert>

namespace lin
{
namespace internal
{

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
class BaseReference : public Base<BaseReference<R, C, MR, MC, _E>>,
    public Dimensions<BaseReference<R, C, MR, MC, _E>>
{
 public:
  typedef traits<BaseReference<R, C, MR, MC, _E>> Traits;
  using Dimensions<BaseReference<R, C, MR, MC, _E>>::rows;
  using Dimensions<BaseReference<R, C, MR, MC, _E>>::cols;
  using Base<BaseReference<R, C, MR, MC, _E>>::size;
  using Base<BaseReference<R, C, MR, MC, _E>>::operator=;
  using Base<BaseReference<R, C, MR, MC, _E>>::operator();
  constexpr BaseReference() = delete;
  constexpr BaseReference(Base<_E> &E, size_t i, size_t j, size_t r, size_t c);
  constexpr typename Traits::elem &operator()(size_t i, size_t j);
  constexpr typename Traits::elem &operator()(size_t i);

 private:
  using Dimensions<BaseReference<R, C, MR, MC, _E>>::resize;
  using Base<BaseReference<R, C, MR, MC, _E>>::derived;
  Base<_E> &E;
  size_t const i;
  size_t const j;
};

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
struct elem<BaseReference<R, C, MR, MC, _E>> : public elem<_E> { };

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
struct dims<BaseReference<R, C, MR, MC, _E>>
{
  enum {
    rows = R,
    cols = C,
    max_rows = MR,
    max_cols = MC
  };
};
}  // namespace internal

/** @fn ref
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row offset of the reference in the backing stream.
 *  @param[in] j Column offset of the reference in in the backing stream.
 *  @param[in] r Resizes the references row count.
 *  @param[in] c Resizes the references column count.
 *  
 *  Generates a statically sized, read/write reference to the provided backing
 *  stream. If you are looking to reference a full row/column of a tensor, see
 *  the row and column reference functions. */
template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr internal::BaseReference<R, C, MR, MC, _E>
ref(internal::Base<_E> &E, size_t i, size_t j, size_t r = MR, size_t c = MC);

/** @fn ref
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row offset of the reference in the backing stream.
 *  @param[in] j Column offset of the reference in in the backing stream.
 *  
 *  Generates a fixed sized, read/write reference to the provided backing
 *  stream. If you are looking to reference a full row/column of a tensor, see
 *  the row and column reference functions. */
template <size_t R, size_t C, class _E>
constexpr internal::BaseReference<R, C, R, C, _E>
ref(internal::Base<_E> &E, size_t i, size_t j);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row index to be referenced.
 * 
 *  Generates a read/write reference to the i'th row of the provided stream as a
 *  row vector. This function is a small wrapper around the standard ref
 *  function using the traits of _E and E's dimensions at runtime. */
template <class _E>
constexpr auto ref_row(internal::Base<_E> &E, size_t i);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Column index to be referenced.
 * 
 *  Generates a read/writee only reference to the j'th column of the provided
 *  stream as a column vector. This function is a small wrapper around the
 *  standard ref function using the traits of _E and E's dimensions at runtime.
 *  */
template <class _E>
constexpr auto ref_col(internal::Base<_E> &E, size_t j);

}  // namespace lin

#include "inl/base_reference.inl"

#endif
