/** @file lin/core/traits/inl/vector.inl
 *  @author Kyle Krol
 *  See %lin/core/traits/vector.hpp for more information. */

#include "../vector.hpp"

namespace lin {
namespace internal {

template <class C, typename>
struct is_row_vector : std::false_type { };

template <class C>
struct is_row_vector<C, std::enable_if_t<(
    has_fixed_rows<C>::value && (_traits<C>::Rows == 1) && (_traits<C>::MaxCols > 1)
  )>> : std::true_type { };

template <class C, typename>
struct is_col_vector : std::false_type { };

template <class C>
struct is_col_vector<C, std::enable_if_t<(
    has_fixed_cols<C>::value && (_traits<C>::Cols == 1) && (_traits<C>::MaxRows > 1)
  )>> : std::true_type { };

template <class C>
struct _vector_traits<C, std::enable_if_t<is_row_vector<C>::value>> {
  typedef _traits_elem_t<C> Elem;
  constexpr static size_t
    Length = _traits<C>::Cols,
    MaxLength = _traits<C>::MaxCols;
};

template <class C>
struct _vector_traits<C, std::enable_if_t<is_col_vector<C>::value>> {
  typedef _traits_elem_t<C> Elem;
  constexpr static size_t
    Length = _traits<C>::Rows,
    MaxLength = _traits<C>::MaxRows;
};

template <class C, typename>
struct has_vector_traits : std::false_type { };

template <class C>
struct has_vector_traits<C, void_t<typename C::VectorTraits>>
    : std::true_type { };

template <class C, class D, typename = void>
struct _have_same_vector_dimensions_impl : std::false_type { };

template <class C, class D>
struct _have_same_vector_dimensions_impl<C, D, std::enable_if_t<(
    (_vector_traits<C>::Length == _vector_traits<D>::Length) &&
    (_vector_traits<C>::MaxLength == _vector_traits<D>::MaxLength)
  )>> : std::true_type { };

template <>
struct have_same_vector_dimensions<> : std::true_type { };

template <class C>
struct have_same_vector_dimensions<C> : is_vector<C> { };

template <class C, class... Cs>
struct have_same_vector_dimensions<C, Cs...>
    : conjunction<_have_same_vector_dimensions_impl<C, Cs>...> { };

template <>
struct have_same_vector_traits<> : std::true_type { };

template <class C>
struct have_same_vector_traits<C> : std::true_type { };

template <class C, class... Cs>
struct have_same_vector_traits<C, Cs...>
    : conjunction<have_same_elements<Cs...>, have_same_vector_dimensions<Cs...>> { };

}  // namespace internal
}  // namespace lin
