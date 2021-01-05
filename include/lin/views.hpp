// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/views.hpp
 *  @author Kyle Krol
 */

/** @defgroup VIEWS Views
 * 
 *  @brief Allows arbitrary data buffers to be interpreted as value backed
 *         tensor types.
 * 
 *  ## Overview
 * 
 *  The views module serves one main purpose: to allows external buffers to be
 *  interpretted as tensor objects within lin.
 *
 *  This can be extremely helpful, say for example, if you'd like to treat an
 *  array from the STL as a three dimensional vector and perform some operations
 *  in a function to mutate it. All that's required is to use the lin::view
 *  function to create a vector view and then leverage the rest of the lin
 *  library.
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
 *    auto v = lin::view<lin::Vector3f>(array.data());
 *    lin::Matrix3x3f R = {
 *      std::cos(alpha), -std::sin(alpha), 0.0f,
 *      std::sin(alpha),  std::cos(alpha), 0.0f,
 *      0.0f,             0.0f,            1.0f
 *    };
 *    v = (R * v).eval();
 *  }
 *  ~~~
 *
 *  It's important to note that there are actually two types of views that can
 *  be returned by lin::view. The first is a standard view which allows read and
 *  write access to the underlying elements (this is seen in the example above).
 *  The second is known as a constant view and only allows read access to the
 *  underlying elements. This is done automatically if the buffer passed to
 *  lin::view points to const elements.
 */

#ifndef LIN_VIEWS_HPP_
#define LIN_VIEWS_HPP_

#include "views/const_matrix_view.hpp"
#include "views/const_tensor_view.hpp"
#include "views/const_vector_view.hpp"
#include "views/matrix_view.hpp"
#include "views/tensor_view.hpp"
#include "views/vector_view.hpp"
#include "views/view.hpp"

#endif
