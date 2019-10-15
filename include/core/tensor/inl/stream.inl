// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../stream.hpp"

namespace lin
{
namespace internal
{

template <class D>
constexpr size_t Stream<D>::rows() const
{
  return derived().rows();
}

template <class D>
constexpr size_t Stream<D>::cols() const
{
  return derived().cols();
}

template <class D>
constexpr size_t Stream<D>::size() const
{
  return rows() * cols();
}

template <class D>
constexpr typename Stream<D>::Traits::elem Stream<D>::operator()(size_t i, size_t j) const
{
  return derived()(i, j);
}

template <class D>
constexpr typename Stream<D>::Traits::elem Stream<D>::operator()(size_t i) const
{
  return derived()(i);
}

template <class D>
constexpr typename Stream<D>::Traits::eval Stream<D>::evaluate() const
{
  return typename Traits::eval(*this);
}

template <class D>
constexpr D const &Stream<D>::derived() const
{
  return static_cast<D const &>(*this);
}

template <class D>
constexpr D &Stream<D>::derived()
{
  return static_cast<D &>(*this);
}

#ifdef LIN_DESKTOP
template <class _A>
inline std::ostream &operator<<(std::ostream &os, Stream<_A> const &A)
{
  for (size_t i = 0; i < A.rows() - 1; i++) {
    for (size_t j = 0; j < A.cols() - 1; j++)
      os << A(i, j) << " ";
    os << A(i, A.cols() - 1) << "\n";
  }
  for (size_t j = 0; j < A.cols() - 1; j++)
    os << A(A.rows() - 1, j) << " ";
  os << A(A.rows() - 1, A.cols() - 1) << "\n";
  return os;
}
#endif

}  // namespace internal
}  // namespace  lin
