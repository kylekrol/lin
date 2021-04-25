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

/** @file lin/core/types/tensor.hpp
 *  @author Kyle Krol
 */

#include "buffer.hpp"

namespace lin {
namespace internal {

template <class D>
class Tensor : public Buffer<D> {
 public:
  using Buffer<D>::Traits;

 private:
  typename Traits::elem_t _elements[Traits::max_size] {typename Traits::elem_t {0}};

 protected:
  using Buffer<D>::derived;

  constexpr Tensor() = default;
  constexpr Tensor(Tensor const &) = default;
  constexpr Tensor(Tensor &&) = default;
  constexpr Tensor &operator=(Tensor const &) = default;
  constexpr Tensor &operator=(Tensor &&) = default;

  constexpr Tensor(size_t r, size_t c) {
    resize(r, c);
  }

 public:
  using Buffer<D>::rows;
  using Buffer<D>::cols;
  using Buffer<D>::size;
  using Buffer<D>::resize;
  using Buffer<D>::operator=;

  constexpr auto data() const -> typename Traits::elem_t const * {
    return _elemets;
  }

  constexpr auto data() const -> typename Traits::elem_t * {
    return _elements;
  }
};
}  // namespace internal
}  // namespace lin
