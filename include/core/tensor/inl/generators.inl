// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../generators.hpp"

namespace lin
{

/******************************************************************************/
// Constants

namespace internal
{

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr Constants<T, R, C, MR, MC>::Constants(T t, size_t r, size_t c)
: t(t)
{
  resize(r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr typename Constants<T, R, C, MR, MC>::Traits::elem
Constants<T, R, C, MR, MC>::operator()(size_t i, size_t j) const
{
  assert(i < rows() /* Invalid row index in Constants<...>::operator() */);
  assert(j < cols() /* Invalid col index in Constants<...>::operator() */);
  return t;
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr typename Constants<T, R, C, MR, MC>::Traits::elem
Constants<T, R, C, MR, MC>::operator()(size_t i) const
{
  assert(i < size() /* Invalid size index in Constants<...>::operator() */);
  return t;
}

constexpr RandomsGenerator::RandomsGenerator(unsigned long long seed)
: seed(seed ^ 4101842887655102017LL)
{
  next();
}

constexpr double RandomsGenerator::next()
{
  seed ^= (seed >> 21);
  seed ^= (seed << 35);
  seed ^= (seed >> 4);
  return 5.42101086242752217E-20 * (seed * 2685821657736338717ULL);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr Randoms<T, R, C, MR, MC>::Randoms(size_t r, size_t c, RandomsGenerator &rand)
: rand(rand)
{
  resize(r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr typename Randoms<T, R, C, MR, MC>::Traits::elem
Randoms<T, R, C, MR, MC>::operator()(size_t i, size_t j) const
{
  assert(i < rows() /* Invalid row index in Constants<...>::operator() */);
  assert(j < cols() /* Invalid col index in Constants<...>::operator() */);
  return rand.next();
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr typename Randoms<T, R, C, MR, MC>::Traits::elem
Randoms<T, R, C, MR, MC>::operator()(size_t i) const
{
  assert(i < size() /* Invalid size index in Constants<...>::operator() */);
  return rand.next();
}
}  // namespace internal

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr internal::Constants<T, R, C, MR, MC>
consts(T t, size_t r, size_t c)
{
  return internal::Constants<T, R, C, MR, MC>(t, r, c);
}

template <class _A>
constexpr auto consts(typename internal::elem<_A>::type t, size_t r, size_t c)
{
  typedef internal::traits<_A> Traits;
  return consts<typename Traits::elem, Traits::rows, Traits::cols,
      Traits::max_rows, Traits::max_cols>(t, r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr internal::Constants<T, R, C, MR, MC>
zeroes(size_t r, size_t c)
{
  return consts<T, R, C, MR, MC>(static_cast<T>(0.0), r, c);
}

template <class _A>
constexpr auto zeroes(size_t r, size_t c)
{
  typedef internal::traits<_A> Traits;
  return zeroes<typename Traits::elem, Traits::rows, Traits::cols,
      Traits::max_rows, Traits::max_cols>(r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr internal::Constants<T, R, C, MR, MC>
ones(size_t r, size_t c)
{
  return consts<T, R, C, MR, MC>(static_cast<T>(1.0), r, c);
}

template <class _A>
constexpr auto ones(size_t r, size_t c)
{
  typedef internal::traits<_A> Traits;
  return ones<typename Traits::elem, Traits::rows, Traits::cols,
      Traits::max_rows, Traits::max_cols>(r, c);
}

template <typename T, size_t R, size_t C, size_t MR, size_t MC>
constexpr typename internal::Randoms<T, R, C, MR, MC>::Traits::eval
rands(size_t r, size_t c, internal::RandomsGenerator &rand)
{
  return internal::Randoms<T, R, C, MR, MC>(r, c, rand).evaluate();
}

template <class _A>
constexpr auto rands(size_t r, size_t c, internal::RandomsGenerator &rand)
{
  typedef internal::traits<_A> Traits;
  return rands<typename Traits::elem, Traits::rows, Traits::cols,
      Traits::max_rows, Traits::max_cols>(r, c, rand);
}
}  // namespace lin
