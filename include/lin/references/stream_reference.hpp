/** @file lin/references/stream_reference.hpp
 *  @author Kyle Krol
 *  Defines the stream reference type which is a read-only reference interface.
 *  */

// TODO : Documenation for this whole file

#ifndef LIN_REFERENCE_STREAM_REFERENCE_HPP_
#define LIN_REFERENCE_STREAM_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @class StreamReference */
template <size_t R, size_t C, size_t MR, size_t MC, class D>
class StreamReference;

}  // namespace internal

/** @fn ref */
template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr internal::StreamReference<R, C, MR, MC, D> ref(internal::Stream<D> const &d,
    size_t i, size_t j, size_t r = MR, size_t c = MC);

/** @fn ref */
template <size_t R, size_t C, class D>
constexpr internal::StreamReference<R, C, R, C, D> ref(internal::Stream<D> const &d,
    size_t i, size_t j);

/** @fn ref_row */
template <class D>
constexpr auto ref_row(internal::Stream<D> const &d, size_t i);

/** @fn ref_col */
template <class D>
constexpr auto ref_col(internal::Stream<D> const &d, size_t j);

}  // namespace lin

#include "inl/stream_reference.inl"

#endif
