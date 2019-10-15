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

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr internal::StreamReference<R, C, MR, MC, _E>
reference(internal::Stream<_E> const &E, size_t i, size_t j, size_t r = MR, size_t c = MC);

template <size_t R, size_t C, class _E>
constexpr internal::StreamReference<R, C, R, C, _E>
reference(internal::Stream<_E> const &E, size_t i, size_t j);

}  // namespace lin

#include "inl/stream_reference.inl"

#endif
