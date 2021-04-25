#pragma once

//
// MIT License
//
// Copyright (c) 2021 Kyle Krol (kylekrol)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

/** @file lin/core/types/stream.hpp
 *  @author Kyle Krol
 */

#include "../config.hpp"
#include "../traits.hpp"

namespace lin {
namespace internal {

template <class D>
class Stream {
  static_assert(has_traits<D>::value,
      "Derived types of internal::Stream<...> must have traits");

 public:
  using Traits = traits<D>;

 protected:
  constexpr D const &derived() const
      noexcept(noexcept(static_cast<D const &>(*this)) {
    return static_cast<D const &>(*this);
  }

  constexpr D &derived()
      noexcept(noexcept(static_cast<D &>(*this))) {
    return static_cast<D &>(*this);
  }

 public:
  constexpr size_t rows() const
      noexcept(noexcept(derived().rows())) {
    return derived().rows();
  }

  constexpr size_t cols() const
      noexcept(noexcept(derived().cols())) {
    return derived().cols();
  }

  constexpr size_t size() const
      noexcept(noexcept(rows() * cols())) {
    return rows() * cols();
  }

  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const
      noexcept(noexcept(derived()(i, j))) {
    return derived()(i, j);
  }

  constexpr typename Traits::elem_t operator()(size_t i) const
      noexcept(noexcept(derived()(i))) {
    return derived()(i);
  }
};
}  // namespace internal
}  // namespace lin
