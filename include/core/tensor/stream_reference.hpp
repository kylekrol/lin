// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_STREAM_REFERENCE_HPP_
#define LIN_INCLUDE_CORE_TENSOR_STREAM_REFERENCE_HPP_

#include "dimensions.hpp"
#include "stream.hpp"
#include "traits.hpp"

#include <cassert>

namespace lin
{
namespace internal
{

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
class StreamReference : public Stream<StreamReference<R, C, MR, MC, _E>>,
    public Dimensions<StreamReference<R, C, MR, MC, _E>>
{
 public:
  typedef traits<StreamReference<R, C, MR, MC, _E>> Traits;
  using Dimensions<StreamReference<R, C, MR, MC, _E>>::rows;
  using Dimensions<StreamReference<R, C, MR, MC, _E>>::cols;
  using Stream<StreamReference<R, C, MR, MC, _E>>::size;
  constexpr StreamReference() = delete;
  constexpr StreamReference(Stream<_E> const &E, size_t i, size_t j, size_t r, size_t c);
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  using Dimensions<StreamReference<R, C, MR, MC, _E>>::resize;
  using Stream<StreamReference<R, C, MR, MC, _E>>::derived;
  Stream<_E> const &E;
  size_t const i;
  size_t const j;
};

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
struct elem<StreamReference<R, C, MR, MC, _E>> : public elem<_E> { };

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
struct dims<StreamReference<R, C, MR, MC, _E>>
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
 *  Generates a statically sized, read only reference to the provided backing
 *  stream. If you are looking to reference a full row/column of a tensor, see
 *  the row and column reference functions. */
template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr internal::StreamReference<R, C, MR, MC, _E> const
ref(internal::Stream<_E> const &E, size_t i, size_t j, size_t r = MR, size_t c = MC);

/** @fn ref
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row offset of the reference in the backing stream.
 *  @param[in] j Column offset of the reference in in the backing stream.
 *  
 *  Generates a fixed sized, read only reference to the provided backing stream.
 *  If you are looking to reference a full row/column of a tensor, see the row
 *  and column reference functions. */
template <size_t R, size_t C, class _E>
constexpr internal::StreamReference<R, C, R, C, _E> const
ref(internal::Stream<_E> const &E, size_t i, size_t j);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row index to be referenced.
 * 
 *  Generates a read only reference to the i'th row of the provided stream as a
 *  row vector. This function is a small wrapper around the standard ref
 *  function using the traits of _E and E's dimensions at runtime. */
template <class _E>
constexpr auto const ref_row(internal::Stream<_E> const &E, size_t i);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Column index to be referenced.
 * 
 *  Generates a read only reference to the j'th column of the provided stream as
 *  a column vector. This function is a small wrapper around the standard ref
 *  function using the traits of _E and E's dimensions at runtime. */
template <class _E>
constexpr auto const ref_col(internal::Stream<_E> const &E, size_t j);

}  // namespace lin

#include "inl/stream_reference.inl"

#endif
