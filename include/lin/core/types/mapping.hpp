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

/** @file lin/core/types/mapping.hpp
 *  @author Kyle Krol
 */

#include "../traits.hpp"
#include "stream.hpp"

namespace lin {

template <class C, class D, typename = void>
struct can_assign : false_type { };

namespace internal {

template <class D>
class Mapping : public Stream<D> {
 public:
  using Stream<D>::Traits;

 protected:
  using Stream<D>::derived;

  constexpr Mapping() noexcept = default;
  constexpr Mapping(Mapping const &) noexcept = default;
  constexpr Mapping(Mapping &&) noexcept = default;
  constexpr Mapping &operator=(Mapping const &) noexcept = default;
  constexpr Mapping &operator=(Mapping &&) noexcept = default;

 public:
  using Stream<D>::rows;
  using Stream<D>::cols;
  using Stream<D>::size;
  using Stream<D>::operator();

  constexpr typename Traits::elem_t &operator()(size_t i, size_t j)
      noexcept(noexcept(derived()(i, j))) {
    return derived()(i, j);
  }

  constexpr typename Traits::elem_t operator()(size_t i)
      noexcept(noexcept(derived()(i))) {
    return derived()(i);
  }
};
}  // namespace internal
}  // namespace lin
