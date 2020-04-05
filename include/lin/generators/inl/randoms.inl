/** @file lin/generators/inl/randoms.inl
 *  @author Kyle Krol
 *  See %lin/generators/randoms.hpp for more information. */

#include "../randoms.hpp"

namespace lin {
namespace internal {

constexpr RandomsGenerator::RandomsGenerator(unsigned long long seed)
: seed(seed ^ 4101842887655102017LL) {
  next();
}

constexpr double RandomsGenerator::next() const {
  seed ^= (seed >> 21);
  seed ^= (seed << 35);
  seed ^= (seed >> 4);
  return 5.42101086242752217E-20 * (seed * 2685821657736338717ULL);
}
}  // namespace internal

template <class C, std::enable_if_t<internal::has_traits<C>::value, size_t>>
constexpr typename C::Traits::Eval rands(size_t r, size_t c, internal::RandomsGenerator const &rand) {
  internal::traits_eval_t<C> tensor(r, c);
  for (size_t i = 0; i < tensor.size(); i++) tensor(i) = rand.next();
  return tensor;
}
}  // namespace lin
