/** @file lin/generators/randoms.hpp
 *  @author Kyle Krol
 *  Defines a generator to create matrices and vectors populated with random
 *  values. */

// TODO : Documentation for this entire file

#ifndef LIN_GENERATORS_RANDOMS_HPP_
#define LIN_GENERATORS_RANDOMS_HPP_

#include "../core.hpp"

#include <type_traits>

#ifdef LIN_RANDOM_WITH_CTIME
  #ifdef LIN_RANDOM_SEED
    #undef LIN_RANDOM_SEED
  #endif
  #include <ctime>
  #define LIN_RANDOM_SEED time(nullptr)
#else
  #ifndef LIN_RANDOM_SEED
    #define LIN_RANDOM_SEED 0
  #endif
#endif

namespace lin {
namespace internal {

/** @class RandomsGenerator */
class RandomsGenerator {
 private:
  mutable unsigned long long seed;

 public:
  constexpr RandomsGenerator(RandomsGenerator const &) = default;
  constexpr RandomsGenerator(RandomsGenerator &&) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator const &) = default;
  constexpr RandomsGenerator &operator=(RandomsGenerator &&) = default;
  constexpr RandomsGenerator(unsigned long long seed = 0);
  constexpr double next() const;
};

/** @var RandomsGenerator rands */
extern RandomsGenerator const rand;

}  // namespace internal

/** @fn rands */
template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t> = 0>
constexpr typename C::Traits::Eval rands(size_t r = C::Traits::MaxRows,
    size_t c = C::Traits::MaxCols, internal::RandomsGenerator const &rand = internal::rand);

}  // namespace lin

#include "inl/randoms.inl"

#endif
