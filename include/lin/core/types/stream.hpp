/** @file lin/core/types/stream.hpp
 *  @author Kyle Krol
 *  Defines the stream type which is a tensor read-only interface. */

// TODO : Add iostream support if available

#ifndef LIN_CORE_TYPES_STREAM_HPP_
#define LIN_CORE_TYPES_STREAM_HPP_

#ifdef LIN_DESKTOP
  #include <iostream>
#endif

#include "../config.hpp"
#include "../traits.hpp"

namespace lin {
namespace internal {

/** @class Stream
 *  Representation of a tensor presenting read-only access to it's elements.
 *  This class' main purpose is to facilitate lazy evaluation. */
template <class D>
class Stream {
  static_assert(has_valid_traits<D>::value, "Invalid traits detected.");

 public:
  /* Include traits information from the derived type. */
  typedef traits<D> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr Stream() = default;
  constexpr Stream(Stream<D> const &) = default;
  constexpr Stream(Stream<D> &&) = default;
  constexpr Stream<D> &operator=(Stream<D> const &) = default;
  constexpr Stream<D> &operator=(Stream<D> &&) = default;
  /* Element access/evaluation functions and size information. */
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr size_t size() const;
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;
  /* Force the evaluation of a stream to a value backed type. */
  constexpr typename Traits::Eval eval() const;

 protected:
  /* Cast the stream to it's D type. */
  constexpr D const &derived() const;
  constexpr D &derived();
};

#ifdef LIN_DESKTOP
template <class C>
std::ostream &operator<<(std::ostream &os, Stream<C> const &stream);
#endif

}  // namespace internal
}  // namespace lin

#include "inl/stream.inl"

#endif
