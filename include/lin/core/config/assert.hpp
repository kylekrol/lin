/** @file lin/core/config/assert.hpp
 *  @author Kyle Krol
 *  Defines assertion behavior within the lin package. */

#ifndef LIN_CORE_CONFIG_ASSERT_HPP_
#define LIN_CORE_CONFIG_ASSERT_HPP_

#ifndef LIN_NO_CASSERT
  #include <cassert>
  #define LIN_ASSERT(x) assert(x)
#else
  #define LIN_ASSERT(x)
#endif

#endif
