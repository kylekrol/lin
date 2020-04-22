/** @file lin/generators/inl/identity.inl
 *  @author Kyle Krol
 *  See % lin/generators/identity.hpp for more information. */

#include "../identity.hpp"

namespace lin {
namespace internal {

template <typename T, size_t N, size_t MN>
class StreamIdentity : public Stream<StreamIdentity<T, N, MN>>,
    public Dimensions<StreamIdentity<T, N, MN>> {
 public:
  /* Import elements from Stream<StreamIdentity<T, N, MN>>. */
  using Stream<StreamIdentity<T, N, MN>>::size;
  using Stream<StreamIdentity<T, N, MN>>::eval;
  /* Import elements from Dimensions<StreamIdentity<T, N, MN>> */
  using Dimensions<StreamIdentity<T, N, MN>>::rows;
  using Dimensions<StreamIdentity<T, N, MN>>::cols;
  /* Include traits information. */
  typedef traits<StreamIdentity<T, N, MN>> Traits;
  /* Defaulted/deleted constructors and assignment operators. */
  constexpr StreamIdentity() = default;
  constexpr StreamIdentity(StreamIdentity<T, N, MN> const &) = default;
  constexpr StreamIdentity(StreamIdentity<T, N, MN> &&) = default;
  constexpr StreamIdentity<T, N, MN> &operator=(StreamIdentity<T, N, MN> const &) = default;
  constexpr StreamIdentity<T, N, MN> &operator=(StreamIdentity<T, N, MN> &&) = default;
  /* StreamConstants constructor(s). */
  constexpr StreamIdentity(size_t n);
  /* Element access/evaluation functions. */
  constexpr typename Traits::Elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::Elem operator()(size_t i) const;

 protected:
  /* Import elements from Stream<StreamConstants<T, R, C, MR, MC>>. */
  using Stream<StreamIdentity<T, N, MN>>::derived;

 private:
  /* Import elements from Dimensions<StreamConstants<T, R, C, MR, MC>>. */
  using Dimensions<StreamIdentity<T, N, MN>>::resize;
};

template <typename T, size_t N, size_t MN>
struct _traits<StreamIdentity<T, N, MN>> {
  typedef T Elem;
  constexpr static size_t
      Rows = N,
      Cols = N,
      MaxRows = MN,
      MaxCols = MN;
};

template <typename T, size_t N, size_t MN>
constexpr StreamIdentity<T, N, MN>::StreamIdentity(size_t n) {
  resize(n, n);
}

template <typename T, size_t N, size_t MN>
constexpr typename StreamIdentity<T, N, MN>::Traits::Elem
StreamIdentity<T, N, MN>::operator()(size_t i, size_t j) const {
  LIN_ASSERT(0 <= i && i <= rows() /* Invalid argument passed to StreamIdentity<...>::operator() */);
  LIN_ASSERT(0 <= j && j <= cols() /* Invalid argument passed to StreamIdentity<...>::operator() */);
  return (i == j ? T(1) : T(0));
}

template <typename T, size_t N, size_t MN>
constexpr typename StreamIdentity<T, N, MN>::Traits::Elem
StreamIdentity<T, N, MN>::operator()(size_t i) const {
  return (*this)(i / cols(), i % cols());
}
}  // namespace internal

template <typename T, size_t N, size_t MN>
constexpr internal::StreamIdentity<T, N, MN> identity(size_t n) {
  return internal::StreamIdentity<T, N, MN>(n);
}

/** @fn identity */
template <class C, std::enable_if_t<internal::is_square<C>::value, size_t>>
constexpr auto identity(size_t n) {
  return internal::StreamIdentity<typename C::Traits::Elem, C::Traits::Rows, C::Traits::MaxRows>(n);
}
}  // namespace lin
