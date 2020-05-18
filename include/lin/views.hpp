// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views.hpp
 *  @author Kyle Krol
 */

/** @defgroup VIEWS Views
 *
 *  @brief Defines the tensor view types which allow raw pointers to be
 *         interpretted as value backed tensor types.
 *
 *  ## Overview
 * 
 *  The views module serves one main purpose: to allows external buffers to be
 *  interpretted as tensor objects within lin.
 * 
 *  This may can be extremely helpful, say if you'd like to treat an array from
 *  the STL with length of three as a three dimensional lin vector. Once you
 *  create a lin::VectorView3f from it, it'll be compatible with all of lin
 *  operations and write changes directly back into the original array object.
 *
 *  See the following example which treats an array as a three dimensional
 *  vector and rotates it in place about the z-axis by an angle `alpha`:
 * 
 *  ~~~{.cpp}
 *  #include <lin/core.hpp>
 *  #include <lin/views.hpp>
 * 
 *  #include <array>
 *  #include <cmath>
 * 
 *  void rotate_z(std::array<float, 3> &array, float alpha) {
 *    lin::VectorView3f v(array.data());
 *    lin::Matrix3x3f R {
 *      std::cos(alpha), -std::sin(alpha), 0.0f,
 *      std::sin(alpha),  std::cos(alpha), 0.0f,
 *      0.0f,             0.0f,            1.0f
 *    };
 *    v = (R * v).eval();
 *  }
 *  ~~~
 */

#ifndef LIN_VIEWS_HPP_
#define LIN_VIEWS_HPP_

#include "views/matrix_view.hpp"
#include "views/tensor_view.hpp"
#include "views/vector_view.hpp"

#endif
