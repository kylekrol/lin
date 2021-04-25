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

/** @file lin/core/types/dimensions.hpp
 *  @author Kyle Krol
 */

#include "../config.hpp"
#include "../traits.hpp"

namespace lin {
namespace internal {

template <class D, typename = void>
class Dimensions;

template <class D>
class Dimensions<D, enable_if_t<has_fixed_size<D>::value>> {
 protected:
  constexpr Dimensions() noexcept = default;
  constexpr Dimensions(Dimensions const &) noexcept = default;
  constexpr Dimensions(Dimensions &&) noexcept = default;
  constexpr Dimensions &operator=(Dimensions const &) noexcept = default;
  constexpr Dimensions &operator=(Dimensions &&) noexcept = default;

 public:
  constexpr size_t rows() const noexcept {
    return D::Traits::rows;
  }

  constexpr size_t cols() const noexcept {
    return D::Traits::cols;
  }

  constexpr void resize(size_t r, size_t c) noexcept {
    LIN_ASSERT(r == rows());
    LIN_ASSERT(c == cols());
  }
};

template <class D>
class Dimensions<D,
    enable_if_t<conjunction<has_fixed_rows<D>, has_variable_cols<D>>::value>> {
 private:
  size_t _c {D::Traits::max_cols};

 protected:
  constexpr Dimensions() noexcept = default;
  constexpr Dimensions(Dimensions const &) noexcept = default;
  constexpr Dimensions(Dimensions &&) noexcept = default;
  constexpr Dimensions &operator=(Dimensions const &) noexcept = default;
  constexpr Dimensions &operator=(Dimensions &&) noexcept = default;

 public:
  constexpr size_t rows() const noexcept {
    return D::Traits::rows;
  }

  constexpr size_t cols() const noexcept {
    return _c;
  }

  constexpr void resize(size_t r, size_t c) noexcept {
    LIN_ASSERT(r == rows());
    LIN_ASSERT(0 < c && c <= C::Traits::max_cols);

    _c = c;
  }
};

template <class D>
class Dimensions<D,
    enable_if_t<conjunction<has_variable_rows<D>, has_fixed_cols<D>>::value>> {
 private:
  size_t _r {D::Traits::max_rows};

 protected:
  constexpr Dimensions() noexcept = default;
  constexpr Dimensions(Dimensions const &) noexcept = default;
  constexpr Dimensions(Dimensions &&) noexcept = default;
  constexpr Dimensions &operator=(Dimensions const &) noexcept = default;
  constexpr Dimensions &operator=(Dimensions &&) noexcept = default;

 public:
  constexpr size_t rows() const noexcept {
    return _r;
  }

  constexpr size_t cols() const noexcept {
    return D::Traits::cols;
  }

  constexpr size_t resize(size_t r, size_t c) noexcept {
    LIN_ASSERT(0 < r && r <= D::Traits::max_rows);
    LIN_ASSERT(c == cols());

    _r = r;
  }
};

template <class D>
class Dimensions<D, enable_if_t<
      conjunction<has_variable_rows<D>, has_variable_cols<D>>::value>> {
 private:
  size_t _r {D::Traits::max_rows};
  size_t _c {D::Traits::max_cols};

 protected:
  constexpr Dimensions() noexcept = default;
  constexpr Dimensions(Dimensions const &) noexcept = default;
  constexpr Dimensions(Dimensions &&) noexcept = default;
  constexpr Dimensions &operator=(Dimensions const &) noexcept = default;
  constexpr Dimensions &operator=(Dimensions &&) noexcept = default;

 public:
  constexpr size_t rows() const noexcept {
    return _r;
  }

  constexpr size_t cols() const noexcept {
    return _c;
  }

  constexpr void resize(size_t r, size_t c) noexcept {
    LIN_ASSERT(0 < r && r <= D::Traits::max_rows);
    LIN_ASSERT(0 < c && c <= D::Traits::max_cols);

    _r = r;
    _c = c;
  }
};
}  // namespace internal
}  // namespace lin
