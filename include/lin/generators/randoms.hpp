// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/randoms.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_GENERATORS_RANDOMS_HPP_
#define LIN_GENERATORS_RANDOMS_HPP_

#include "../core.hpp"

#include <cstdint>
#include <type_traits>

namespace lin {
namespace internal {

/** @brief
 *
 *  @ingroup GENERATORS
 */
class RandomsGenerator {
 private:
  /** @brief
   */
  unsigned long long seed;

 public:
  constexpr RandomsGenerator(RandomsGenerator const &) = default;
  constexpr RandomsGenerator(RandomsGenerator &&) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator const &) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator &&) = default;

  /** @brief
   */
  constexpr RandomsGenerator(unsigned long long seed = 0) : seed(seed ^ 4101842887655102017LL) { }

  /** @brief
   * 
   *  @return
   */
  constexpr double next() {
    seed ^= (seed >> 21);
    seed ^= (seed << 35);
    seed ^= (seed >> 4);

    return 5.42101086242752217E-20 * (seed * 2685821657736338717ULL);
  }
};
}  // namespace internal

/** @brief
 * 
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto rands(internal::RandomsGenerator &rand, size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  typename C::Traits::eval_t t(r, c);
  for (lin::size_t i = 0; i < t.size(); i++) t(i) = typename C::Traits::elem_t(rand.next());
  return t;
}
}  // namespace lin

#endif
