// vim: set tabstop=2:softtabstop=2:shiftwidth=2:expandtab

/** @file lin/core/operations/mapping_transpose.hpp
 *  @author Kyle Krol
 */

#ifndef LIN_CORE_OPERATIONS_MAPPING_TRANSPOSE_HPP_
#define LIN_CORE_OPERATIONS_MAPPING_TRANSPOSE_HPP_

namespace lin {
namespace internal {

/** @brief Proxy to a lazily evalutated transpose operation.
 * 
 *  @tparam Cs %Tensor type.
 * 
 *  Details to come...
 * 
 *  @ingroup COREOPERATIONS
 */
template <class C>
class MappingTranspose : public Mapping<MappingTranspose<C>> {
 private:
  /** @brief Mapping reference.
   */
  Mapping<C> &c;

 public:
  /** @brief Traits information for this type.
   * 
   *  @sa internal::traits
   */
  typedef traits<MappingTranspose<C>> Traits;

 protected:
  using Mapping<MappingTranspose<C>>::derived;

 public:
  using Mapping<MappingTranspose<C>>::size;
  using Mapping<MappingTranspose<C>>::eval;
  using Mapping<MappingTranspose<C>>::operator();
  using Mapping<MappingTranspose<C>>::operator=;

  constexpr MappingTranspose() = delete;
  constexpr MappingTranspose(MappingTranspose<C> const &) = default;
  constexpr MappingTranspose(MappingTranspose<C> &&) = default;
  constexpr MappingTranspose<C> &operator=(MappingTranspose<C> const &) = default;
  constexpr MappingTranspose<C> &operator=(MappingTranspose<C> &&) = default;

  /** @brief Constructs a proxy to a tensor transpose operation.
   * 
   *  @param c %Tensor mapping.
   */
  constexpr MappingTranspose(Mapping<C> &c)
  : c(c) { }

  /** @return Number of rows in the tensor.
   */
  constexpr size_t rows() const {
    return c.cols();
  }

  /** @return Number of columns in the tensor.
   */
  constexpr size_t cols() const {
    return c.rows();
  }

  /** @brief Read write access to the requested tensor element.
   * 
   *  @param i Row index.
   *  @param j Column index.
   * 
   *  @return Reference to the tensor element.
   */
  constexpr typename Traits::elem_t &operator()(size_t i, size_t j) {
    return c(j, i);
  }

  /** @brief Read write access to the requested tensor element.
   * 
   *  @param i Index.
   * 
   *  @return Reference to the tensor element.
   * 
   *  Element access proceeds as if all the elements of the tensor stream were
   *  flattened into an array in row major order.
   */
  constexpr typename Traits::elem_t &operator()(size_t i) {
    return (*this)(i / cols(), i % cols());
  }
};

template <class C>
struct _elem<MappingTranspose<C>> : _elem<C> { };

template <class C>
struct _dims<MappingTranspose<C>> {
  static constexpr size_t rows = _dims<C>::cols;
  static constexpr size_t cols = _dims<C>::rows;
  static constexpr size_t max_rows = _dims<C>::max_cols;
  static constexpr size_t max_cols = _dims<C>::max_rows;
};
}  // namespace internal
}  // namespace lin

#endif
