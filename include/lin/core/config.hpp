// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/config.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_CONFIG_HPP_
#define LIN_CORE_CONFIG_HPP_

#include <cstddef>

/** @def LIN_ASSERT(x)
 *  @brief Asserts the condition x when assertions are enabled within lin.
 *
 *  To disable assertions, define the `LIN_NO_CASSERT` macro when building.
 *
 *  @ingroup CORE
 */

#ifndef LIN_NO_CASSERT
  #include <cassert>
  #define LIN_ASSERT(x) assert(x)
#else
  #define LIN_ASSERT(x)
#endif

namespace lin {

/** @brief Type tracking tensor dimensions and sizing.
 *
 *  @ingroup CORE
 */
typedef std::size_t size_t;

}  // namespace lin

#endif
