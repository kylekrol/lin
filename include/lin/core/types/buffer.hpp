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

/** @file lin/core/types/buffer.hpp
 *  @author Kyle Krol
 */

#include "dimensions.hpp"
#include "mapping.hpp"

namespace lin {
namespace internal {

template <class D>
class Buffer : public Mapping<D>, public Dimensions<D> {
 public:
  using Mapping<D>::Traits;

 protected:
  using Mapping<D>::derived;

  constexpr Buffer() noexcept = default;
  constexpr Buffer(Buffer const &) noexcept = default;
  constexpr Buffer(Buffer &&) noexcept = default;
  constexpr Buffer &operator=(Buffer const &) noexcept = default;
  constexpr Buffer &operator=(Buffer &&) noexcept = default;

 public:
  using Mapping<D>::size;
  using Mapping<D>::operator=;

  using Dimensions<D>::rows;
  using Dimensions<D>::cols;
  using Dimensions<D>::resize;

  constexpr typename Traits::elem_t const *data() const
      noexcept(noexcept(derived().data())) {
    return derived().data();
  }

  constexpr typename Traits::elem_t *data()
      noexcept(noexcept(derived().data())) {
    return derived().data();
  }

  constexpr typename Traits::elem_t operator()(size_t i, size_t j) const
      noexcept(noexcept(data()[i * cols() + j])) {
    LIN_ASSERT(0 <= i && i < rows());
    LIN_ASSERT(0 <= j && j < cols());

    return data()[i * cols() + j];
  }

  constexpr typename Traits::elem_t &operator()(size_t i, size_t j)
      noexcept(noexcept(data()[i * cols() + j])) {
    LIN_ASSERT(0 <= i && i < rows());
    LIN_ASSERT(0 <= j && j < cols());

    return data()[i * cols() + j];
  }

  constexpr typename Traits::elem_t operator()(size_t i) const
      noexcept(noexcept(data()[i])) {
    LIN_ASSERT(0 <= i && i < size());

    return data()[i];
  }

  constexpr typename Traits::elem_t &operator()(size_t i)
      noexcept(noexcept(data()[i])) {
    LIN_ASSERT(0 <= i && i < size());

    return data()[i];
  }
};
}  // namespace internal
}  // namespace lin
