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

/** @brief Random number generator.
 *
 *  Produces random values in the range zero to one. It's used by the rands
 *  generator function.
 *
 *  @ingroup GENERATORS
 */
class RandomsGenerator {
 private:
  /** @brief Seed for the random number generator.
   */
  unsigned long long seed;

 public:
  constexpr RandomsGenerator(RandomsGenerator const &) = default;
  constexpr RandomsGenerator(RandomsGenerator &&) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator const &) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator &&) = default;

  /** @brief Creates a random number generator based on the specified seed.
   *
   *  @param[in] seed
   */
  constexpr RandomsGenerator(unsigned long long seed = 0) : seed(seed ^ 4101842887655102017LL) { }

  /** @brief Generates a random number in the range zero to one.
   * 
   *  @return Random number between zero and one.
   */
  constexpr double next() {
    seed ^= (seed >> 21);
    seed ^= (seed << 35);
    seed ^= (seed >> 4);

    return 5.42101086242752217E-20 * (seed * 2685821657736338717ULL);
  }

  /**
   * @brief Return a gaussian random number with mean 0 and std 1
   * 
   * @return constexpr double 
   */
  constexpr double gaussian() {
    double R = sqrt(-2.0L*log(next()));
    double T = 2.0L*M_PI*next();
    return R*cos(T);
  }
};
}  // namespace internal

/** @brief Generates a Matrix or Vector populated with random values between 0 and 1
 *
 *  @tparam C Tensor type whose traits the returned stream will mimic.
 *
 *  @param[inout] rand Random number generator.
 *  @param[in]    r    Row count.
 *  @param[in]    c    Column count.
 *
 *  @return Tensor with randomly populated values.
 *
 *  @sa internal::RandomsGenerator
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto rands(internal::RandomsGenerator &rand, size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  typename C::Traits::eval_t t(r, c);
  for (lin::size_t i = 0; i < t.size(); i++) t(i) = typename C::Traits::elem_t(rand.next());
  return t;
}

/** @brief Generates a Matrix or Vector populated with independent gaussian random variables 
 *  with a mean of 0 and standard deviation of 1
 *
 *  @tparam C Tensor type whose traits the returned stream will mimic.
 *
 *  @param[inout] rand Random number generator.
 *  @param[in]    r    Row count.
 *  @param[in]    c    Column count.
 *
 *  @return Tensor with randomly populated values.
 *
 *  @sa internal::RandomsGenerator
 *
 *  @ingroup GENERATORS
 */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr auto gaussian_rands(internal::RandomsGenerator &rand, size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  typename C::Traits::eval_t t(r, c);
  for (lin::size_t i = 0; i < t.size()-1; i+=2) {
    double R = sqrt(-2.0L*log(rand.next()));
    double T = 2.0L*M_PI*rand.next();
    t(i) = typename C::Traits::elem_t(R*cos(T));
    t(i+1) = typename C::Traits::elem_t(R*sin(T));
  }
  if(t.size()/2 == 1){
    t(t.size() - 1) = typename C::Traits::elem_t(rand.gaussian());
  }
  return t;
}
}  // namespace lin

#endif
