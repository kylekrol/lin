// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_GENERATORS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_GENERATORS_HPP_

#include "dimensions.hpp"
#include "stream.hpp"
#include "traits.hpp"

#include <cassert>

#if defined(LIN_DESKTOP) && !defined(LIN_RANDOM_SEED)
#include <ctime>
#endif

namespace lin
{
namespace internal
{

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
class Constants : public Stream<Constants<T, R, C, MR, MC>>,
    public Dimensions<Constants<T, R, C, MR, MC>>
{
 public:
  typedef traits<Constants<T, R, C, MR, MC>> Traits;
  using Dimensions<Constants<T, R, C, MR, MC>>::rows;
  using Dimensions<Constants<T, R, C, MR, MC>>::cols;
  using Stream<Constants<T, R, C, MR, MC>>::size;
  constexpr Constants() = delete;
  constexpr Constants(T t, size_t r, size_t c);
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  using Dimensions<Constants<T, R, C, MR, MC>>::resize;
  using Stream<Constants<T, R, C, MR, MC>>::derived;
  T const t;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct elem<Constants<T, R, C, MR, MC>>
{
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct dims<Constants<T, R, C, MR, MC>>
{
  enum {
    rows = R,
    cols = C,
    max_rows = MR,
    max_cols = MC,
  };
};

class RandomsGenerator {
private:
  mutable long long seed;

public:
  constexpr RandomsGenerator() = delete;
  constexpr RandomsGenerator(unsigned long long seed);
  constexpr double next();
};

#if defined(LIN_DESKTOP) && !defined(LIN_RANDOM_SEED)
static RandomsGenerator rand(time(nullptr));
#else
static RandomsGenerator rand(LIN_RANDOM_SEED);
#endif

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
class Randoms : public Stream<Randoms<T, R, C, MR, MC>>,
    public Dimensions<Randoms<T, R, C, MR, MC>>
{
 public:
  typedef traits<Randoms<T, R, C, MR, MC>> Traits;
  using Dimensions<Randoms<T, R, C, MR, MC>>::rows;
  using Dimensions<Randoms<T, R, C, MR, MC>>::cols;
  using Stream<Randoms<T, R, C, MR, MC>>::size;
  constexpr Randoms() = delete;
  constexpr Randoms(size_t r, size_t c, RandomsGenerator &rand);
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  using Dimensions<Randoms<T, R, C, MR, MC>>::resize;
  using Stream<Randoms<T, R, C, MR, MC>>::derived;
  RandomsGenerator &rand;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct elem<Randoms<T, R, C, MR, MC>>
{
  typedef T type;
};

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
struct dims<Randoms<T, R, C, MR, MC>>
{
  enum {
    rows = R,
    cols = C,
    max_rows = MR,
    max_cols = MC,
  };
};
}  // namespace internal

template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr internal::Constants<T, R, C, MR, MC>
consts(T t, size_t r = MR, size_t c = MC);

template <class _A>
constexpr auto consts(typename internal::elem<_A>::type t, size_t r = internal::dims<_A>::max_rows,
    size_t c = internal::dims<_A>::max_cols);

template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr internal::Constants<T, R, C, MR, MC>
zeroes(size_t r = MR, size_t c = MC);

template <class _A>
constexpr auto zeroes(size_t r = internal::dims<_A>::max_rows,
    size_t c = internal::dims<_A>::max_cols);

template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr internal::Constants<T, R, C, MR, MC>
ones(size_t r = MR, size_t c = MC);

template <class _A>
constexpr auto ones(size_t r = internal::dims<_A>::max_rows,
    size_t c = internal::dims<_A>::max_cols);

// Evaluation here is forced because internal::Randoms won't produce the same
// values every time.
template <typename T, size_t R, size_t C, size_t MR = R, size_t MC = C>
constexpr typename internal::Randoms<T, R, C, MR, MC>::Traits::eval
rands(size_t r = MR, size_t c = MC, internal::RandomsGenerator &rand = internal::rand);

template <class _A>
constexpr auto rands(size_t r = internal::dims<_A>::max_rows,
    size_t c = internal::dims<_A>::max_cols, internal::RandomsGenerator &rand = internal::rand);

}  // namespace lin

#include "inl/generators.inl"

#endif
