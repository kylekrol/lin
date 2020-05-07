/** @file lin/references/mapping_reference.hpp
 *  @author Kyle Krol
 *  Defines the base reference type which is a read-write reference interface.
 */

// TODO : Documenation for this whole file

#ifndef LIN_REFERENCE_MAPPING_REFERENCE_HPP_
#define LIN_REFERENCE_MAPPING_REFERENCE_HPP_

#include "../core.hpp"

namespace lin {
namespace internal {

/** @class MappingReference */
template <size_t R, size_t C, size_t MR, size_t MC, class D>
class MappingReference;

}  // namespace internal

/** @fn ref */
template <size_t R, size_t C, size_t MR, size_t MC, class D>
constexpr internal::MappingReference<R, C, MR, MC, D> ref(internal::Mapping<D> &d, size_t i, size_t j,
    size_t r = MR, size_t c = MC);

/** @fn ref */
template <size_t R, size_t C, class D>
constexpr internal::MappingReference<R, C, R, C, D> ref(internal::Mapping<D> &d, size_t i, size_t j);

/** @fn ref_row */
template <class D>
constexpr auto ref_row(internal::Mapping<D> &d, size_t i);

/** @fn ref_col */
template <class D>
constexpr auto ref_col(internal::Mapping<D> &d, size_t j);

}  // namespace lin

#include "inl/mapping_reference.inl"

#endif
