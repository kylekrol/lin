// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/generators/randoms.hpp
 *  @author Kyle Krol
 *  @author Shihao Cao
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

  /**
   * @brief Value of a cached standard normal gassauisan random.
   * 
   */
  double cached_rand;

  /**
   * @brief has_cached is true if there's a cached standard normal available.
   * 
   */
  bool has_cached;

 public:
  constexpr RandomsGenerator(RandomsGenerator const &) = default;
  constexpr RandomsGenerator(RandomsGenerator &&) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator const &) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator &&) = default;

  /** @brief Creates a random number generator based on the specified seed.
   *
   *  @param[in] seed
   */
  constexpr RandomsGenerator(unsigned long long seed = 0) : 
    seed(seed ^ 4101842887655102017LL), 
    cached_rand(0.0),
    has_cached(false) { }

  /** @brief Generates a uniform random number in the range zero to one.
   * 
   *  @return Random number between zero and one.
   */
  constexpr double rand() {
    seed ^= (seed >> 21);
    seed ^= (seed << 35);
    seed ^= (seed >> 4);

    return 5.42101086242752217E-20 * (seed * 2685821657736338717ULL);
  }

  /**
   * @brief Return a gaussian random number with mean 0 and std 1.
   * Uses Box-Mueller transform with caching.
   * 
   * @return constexpr double 
   */
  constexpr double gaussian() {
    if(has_cached) {
      has_cached = false;
      return cached_rand;
    }
    else{
      double R = std::sqrt(-2.0*std::log(rand()));
      double T = 2.0*M_PI*rand();
      cached_rand = R*std::sin(T);
      has_cached = true;
      return R*std::cos(T);
    }
  }
};
}  // namespace internal

/** @brief Generates a Matrix or Vector populated with uniform random values between 0 and 1
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
  for (lin::size_t i = 0; i < t.size(); i++) t(i) = typename C::Traits::elem_t(rand.rand());
  return t;
}

/** @brief Generates a Matrix or Vector populated with independent gaussian random variables 
 *  with a mean of 0 and standard deviation of 1. Uses Box–Muller transform.
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
constexpr auto gaussians(internal::RandomsGenerator &rand, size_t r = C::Traits::max_rows, size_t c = C::Traits::max_cols) {
  typename C::Traits::eval_t t(r, c);
  for (lin::size_t i = 0; i < t.size(); i++) t(i) = typename C::Traits::elem_t(rand.gaussian());
  return t;
}
}  // namespace lin

#endif
