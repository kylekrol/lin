// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/traits.hpp
 *  @author Kyle Krol
 */

/** @defgroup CORETRAITS Traits
 *
 *  @ingroup CORE
 *  @brief Set of template metaprogramming constructs to examine compile time
 *         information about tensor types.
 * 
 *  ## Overview
 *
 *  The traits module serves two main purposes:
 *
 *  1. Provide a mechanism for the leaves of the lin inheritance tree communicate
 *     their compile time traits to their parents classes.
 *  2. Give a set of structs to help query properties about these traits.
 *
 *  All of this allows incredibly flexible implementations of tensor operators.
 *  They can, for example, detect at compile time whether or not a given operation
 *  "makes sense" with two arbitrary tensor types.
 * 
 *  ### Providing Traits Information
 * 
 *  Every type in lin has traits information associated with it (see @link
 *  internal::traits @endlink). All leaves of the lin inheritance tree must
 *  provide traits information by define a template specialization for @link
 *  internal::_elem @endlink and @link internal::_dims @endlink.
 * 
 *  For example, the @link Vector @endlink class specifies it's traits like so:
 * 
 *  ~~~{.cpp}
 *  namespace lin {
 * 
 *  template <typename T, size_t N, size_t MN = N>
 *  class Vector : ... { ... };
 * 
 *  namespace internal {
 * 
 *  template <typename T, size_t N, size_t MN>
 *  struct _elem<Vector<T, N, MN>> {
 *    typedef T type;
 *  };
 * 
 *  template <typename T, size_t N, size_t MN>
 *  struct _dims<Vector<T, N, MN>> {
 *    static constexpr size_t rows = N;
 *    static constexpr size_t cols = 1;
 *    static constexpr size_t max_rows = MN;
 *    static constexpr size_t max_cols = 1;
 *  };
 *  }  // namespace internal
 *  }  // namespace lin
 *  ~~~
 * 
 *  Those struct defintions along with @link internal::_eval @endlink (which we
 *  won't get into here) are then used by @link internal::traits @endlink to
 *  complete each types trait's set.
 *
 *  ### Using Traits Information
 * 
 *  As previously mentioned, the template metaprogramming constructs provided by
 *  the traits module are commonly used in
 *  <a href="http://www.cplusplus.com/reference/type_traits/enable_if/">std::enable_if</a>
 *  guards for tensor operations.// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/types.hpp
 *  @author Kyle Krol
 */

/** @defgroup CORETYPES Types
 *
 *  @ingroup CORE
 *  @brief Set of core tensor types and interfaces used throughout lin.
 * 
 *  More details to come...
 */

#ifndef LIN_CORE_TYPES_HPP_
#define LIN_CORE_TYPES_HPP_

#include "types/base.hpp"
#include "types/dimensions.hpp"
#include "types/mapping.hpp"
#include "types/matrix.hpp"
#include "types/stream.hpp"
#include "types/vector.hpp"

#endif
 to add together.
 *  2. The tensor's should have the same dimensions traits.
 * 
 *  As such, we would define an enable if guard similiar to the following:
 * 
 *  ~~~{.cpp}
 *  namespace lin {
 *  namespace internal {
 * 
 *  template <typename T, typename U>
 *  using add_expr = decltype(std::declval<T &>() + std::declval<U &>());
 * 
 *  template <class C, class D>
 *  struct can_add
 *      : conjunction<is_dectected<add_expr, _elem_t<C>, _elem_t<D>>, have_same_dimensions<C, D>> { };
 * 
 *  template <class C, class D, std::enable_if_t<can_add<C, D>::value, size_t> = 0>
 *  constexpr auto operator+(Stream<C> const &, Stream<D> const &) { ... }
 * 
 *  }  // namespace internal
 *  }  // namespace lin
 *  ~~~
 * 
 *  This can be extended to matrix factorizations and more complex operations. See
 *  the list of structs above for more ideas!
 */

#ifndef LIN_CORE_TRAITS_HPP_
#define LIN_CORE_TRAITS_HPP_

#include "traits/matrix.hpp"
#include "traits/tensor.hpp"
#include "traits/utilities.hpp"
#include "traits/vector.hpp"

#endif
