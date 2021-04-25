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
// lin is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// lin. If not, see <https://www.gnu.org/licenses/>.
//

/** @file lin/core/config.hpp
 *  @author Kyle Krol
 */

#if (__cplusplus < 201402L)
  #error "C++14 support is required"
#endif

/** @def LIN_ASSERT(x)
 *
 *  @brief Asserts the condition x when assertions are enabled within lin.
 *
 *  To disable assertions, define the `LIN_NDEBUG` macro when building.
 *
 *  @ingroup core
 */
#if defined(LIN_NDEBUG) //|| defined(NDEBUG)
  #define LIN_ASSERT(x)
#else
  #include <cassert>
  #define LIN_ASSERT(x) assert(x)
#endif

namespace lin {

/** @brief Type tracking tensor dimensions and indices.
 *
 *  @ingroup core
 */
using size_t = int;

}  // namespace lin
