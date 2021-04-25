#pragma once

//
// Copyright (c) 2021 Kyle Krol (kylekrol)
//
// This file is part of lin.
//
// lin is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// lin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with lin. If not, see <https://www.gnu.org/licenses/>.
//

/** @file lin/core/traits/utilities.hpp
 *  @author Kyle Krol
 */

#include "../config.hpp"
#include "utilities.hpp"

namespace lin {

template <class C, typename = void>
struct _traits;

template <class C, typename = void>
struct _evals_to;

template <class C>
struct traits {
  using elem_t = typename _traits<C>::elem_t;
  static constexpr size_t rows = _traits<C>::rows;
  static constexpr size_t cols = _traits<C>::cols;
  static constexpr size_t size = _traits<C>::size;
  static constexpr size_t max_rows = _traits<C>::max_rows;
  static constexpr size_t max_cols = _traits<C>::max_cols;
};

}  // namespace lin
