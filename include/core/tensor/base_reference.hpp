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

template <size_t R, size_t C, size_t MR, size_t MC, class _E>
constexpr internal::BaseReference<R, C, MR, MC, _E>
reference(internal::Base<_E> &E, size_t i, size_t j, size_t r = MR, size_t c = MC);

template <size_t R, size_t C, class _E>
constexpr internal::BaseReference<R, C, R, C, _E>
reference(internal::Base<_E> &E, size_t i, size_t j);

}  // namespace lin

#include "inl/base_reference.inl"

#endif
