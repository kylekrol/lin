/** @file lin/core/traits/inl/tensor.inl
 *  @author Kyle Krol
 *  See %lin/core/traits/tensor.hpp for more information. */

#include "../tensor.hpp"

namespace lin {
namespace internal {

template <class C, typename>
struct has_traits : std::false_type { };

template <class C>
struct has_traits<C, void_t<typename C::Traits>> : std::true_type { };

template <class C, typename>
struct has_fixed_rows : std::false_type { };

template <class C>
struct has_fixed_rows<C, std::enable_if_t<(
    (_traits<C>::Rows > 0) && (_traits<C>::Rows == _traits<C>::MaxRows)
  )>> : std::true_type { };

template <class C, typename>
struct has_fixed_cols : std::false_type { };

template <class C>
struct has_fixed_cols<C, std::enable_if_t<(
    (_traits<C>::Cols > 0) && (_traits<C>::Cols == _traits<C>::MaxCols)
  )>> : std::true_type { };

template <class C, typename>
struct has_bounded_rows : std::false_type { };

template <class C>
struct has_bounded_rows<C, std::enable_if_t<(
    has_fixed_rows<C>::value || ((_traits<C>::Rows == 0) && (_traits<C>::MaxRows > 0))
  )>> : std::true_type { };

template <class C, typename>
struct has_bounded_cols : std::false_type { };

template <class C>
struct has_bounded_cols<C, std::enable_if_t<(
    has_fixed_cols<C>::value || ((_traits<C>::Cols == 0) && (_traits<C>::MaxCols > 0))
  )>> : std::true_type { };

template <>
struct have_same_elements<> : std::true_type { };

template <class C>
struct have_same_elements<C> : std::true_type { };

template <class C, class... Cs>
struct have_same_elements<C, Cs...>
    : conjunction<std::is_same<_traits_elem_t<C>, _traits_elem_t<Cs>>...> { };

template <class C, class D, typename V = void>
struct _have_same_rows : std::false_type { };

template <class C, class D>
struct _have_same_rows<C, D, std::enable_if_t<(
    (_traits<C>::Rows == _traits<D>::Rows) && (_traits<C>::MaxRows == _traits<D>::MaxRows)
  )>> : std::true_type { };

template <>
struct have_same_rows<> : std::true_type { };

template <class C>
struct have_same_rows<C> : std::true_type { };

template <class C, class... Cs>
struct have_same_rows<C, Cs...> : conjunction<_have_same_rows<C, Cs>...> { };

template <class C, class D, typename = void>
struct _have_same_cols : std::false_type { };

template <class C, class D>
struct _have_same_cols<C, D, std::enable_if_t<(
    (_traits<C>::Cols == _traits<D>::Cols) && (_traits<C>::MaxCols == _traits<D>::MaxCols)
  )>> : std::true_type { };

template <>
struct have_same_cols<> : std::true_type { };

template <class C>
struct have_same_cols<C> : std::true_type { };

template <class C, class... Cs>
struct have_same_cols<C, Cs...> : conjunction<_have_same_cols<C, Cs>...> { };

template <>
struct have_same_dimensions<> : std::true_type { };

template <class C>
struct have_same_dimensions<C> : std::true_type { };

template <class C, class... Cs>
struct have_same_dimensions<C, Cs...>
    : conjunction<have_same_rows<Cs...>, have_same_cols<Cs...>> { };

template <>
struct have_same_traits<> : std::true_type { };

template <class C>
struct have_same_traits<C> : std::true_type { };

template <class C, class... Cs>
struct have_same_traits<C, Cs...>
    : conjunction<have_same_elements<Cs...>, have_same_dimensions<Cs...>> { };

template <class C, typename>
struct has_valid_traits : std::false_type { };

template <class C>
struct has_valid_traits<C, std::enable_if_t<(
    has_bounded_dimensions<C>::value
  )>> : std::true_type { };

template <class C, typename>
struct is_tall : std::false_type { };

template <class C>
struct is_tall<C, std::enable_if_t<(
    _traits<C>::MaxRows >= _traits<C>::MaxCols
  )>> : std::true_type { };

template <class C, typename>
struct is_short : std::false_type { };

template <class C>
struct is_short<C, std::enable_if_t<(
    _traits<C>::MaxRows <= _traits<C>::MaxCols
  )>> : std::true_type { };

}  // namespace internal
}  // namespace lin
